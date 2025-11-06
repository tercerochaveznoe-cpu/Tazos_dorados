// Archivo: captura.h
// Proposito: Contiene todas las funciones para INGRESAR o MODIFICAR datos.

// Librerias que estas funciones necesitan
#include <stdio.h> // Para printf y scanf
#include <ctype.h> // Para tolower() (convertir a minuscula)

// --- CONSTANTES Y NOMBRES (Solo para este archivo) ---
#define CAP_MATERIALES 4
#define CAP_DIAS 7

// Arreglos de texto (const char*) para los menus.
const char *NOMBRES_MAT[CAP_MATERIALES] = {"PET", "Carton", "Aluminio", "Vidrio"};
const char *NOMBRES_D[CAP_DIAS] = {"Lun", "Mar", "Mie", "Jue", "Vie", "Sab", "Dom"};


// --- FUNCION 1: CAPTURAR PRECIOS ---
// Recibe el arreglo de precios y un puntero (*) a la bandera de 'ingresados'
// Un puntero es una variable que guarda la direccion de memoria de otra variable.
void capturarPrecios(double precios[], int *flag_precios_ingresados) {
    
    // Variables locales (solo existen en esta funcion)
    int i; 
    int opcion_cambio; 
    int indice_cambio; 

    // Revisa el valor de la bandera.
    // *flag_precios_ingresados significa "ver el valor en la direccion guardada"
    if (*flag_precios_ingresados == 0) {
        
        // --- INGRESO POR PRIMERA VEZ ---
        printf("\n--- Opcion 1: Ingresar Precios (Primera Vez) ---\n");
        // Bucle 'for' que se repite 4 veces (i=0, 1, 2, 3)
        for (i = 0; i < CAP_MATERIALES; i++) {
            // Bucle 'do-while' para validar la entrada (a prueba de tontos)
            do {
                printf("Precio por Kg de %s: $", NOMBRES_MAT[i]);
                
                // VALIDACION: scanf() devuelve 1 si leyo 1 numero.
                if (scanf("%lf", &precios[i]) != 1) {
                    printf("Error! Debe ingresar un numero.\n");
                    while (getchar() != '\n'); // Limpia la entrada erronea
                    precios[i] = -1.0; // Pone -1 para forzar que el bucle repita
                } else if (precios[i] < 0.0) {
                    printf("Error! El precio no puede ser negativo.\n");
                }
            } while (precios[i] < 0.0); // Repite si el precio es negativo
        }
        
        // *** IMPORTANTE: Cambia el valor de la bandera en main.c ***
        *flag_precios_ingresados = 1; // Pone un '1' en la direccion de memoria
        printf("\nPrecios guardados!\n");

    } else {
        
        // --- MODIFICAR PRECIOS (Si ya existen) ---
        printf("\n--- Opcion 1: Modificar Precios ---\n");
        printf("Los precios actuales son:\n");

        // Bucle 'for' para MOSTRAR los precios actuales
        for (i = 0; i < CAP_MATERIALES; i++) {
            printf("  [%d] %s: $%.2f\n", i + 1, NOMBRES_MAT[i], precios[i]);
        }
        printf("  [0] Volver al menu\n");
        printf("\nQue precio desea cambiar? (1-4, 0 para salir): ");
        
        // Lee la opcion
        if (scanf("%d", &opcion_cambio) != 1) {
             printf("Error! Debe ingresar un numero.\n");
             while (getchar() != '\n'); 
        } else if (opcion_cambio == 0) {
            return; // 'return' sale de la funcion
        } else if (opcion_cambio >= 1 && opcion_cambio <= 4) {
            
            // Convierte la opcion (1-4) al indice del arreglo (0-3)
            indice_cambio = opcion_cambio - 1; 
            
            // Repite la validacion, solo para el precio elegido
            do {
                printf("Nuevo precio para %s: $", NOMBRES_MAT[indice_cambio]);
                if (scanf("%lf", &precios[indice_cambio]) != 1) {
                    printf("Error! Debe ingresar un numero.\n");
                    while (getchar() != '\n');
                    precios[indice_cambio] = -1.0; 
                } else if (precios[indice_cambio] < 0.0) {
                    printf("Error! El precio no puede ser negativo.\n");
                }
            } while (precios[indice_cambio] < 0.0);
            
            printf("\nPrecio de %s actualizado!\n", NOMBRES_MAT[indice_cambio]);
            // No es necesario cambiar la bandera, ya era '1'
        } else {
            printf("\nOpcion no valida.\n");
        }
    }
}

// --- FUNCION "AYUDANTE" 1: SOBREESCRIBIR ---
// Esta funcion es 'static', significa que SOLO puede ser llamada
// por otras funciones dentro de ESTE archivo (captura.h).
static void sobreescribirTodos(double kg_matriz[][CAP_DIAS], double kg_matriz_original[][CAP_DIAS], int *flag_kilos_ingresados, int *flag_kilos_modificados) {
    int i, j;
    printf("\n--- Ingresando los 28 registros ---\n");
    for (i = 0; i < CAP_MATERIALES; i++) {
        printf("\nMaterial: %s\n", NOMBRES_MAT[i]);
        for (j = 0; j < CAP_DIAS; j++) {
            do {
                printf("  Kilos del dia %s: ", NOMBRES_D[j]);
                if (scanf("%lf", &kg_matriz[i][j]) != 1) {
                    printf("Error! Debe ingresar un numero.\n");
                    while (getchar() != '\n'); 
                    kg_matriz[i][j] = -1.0; 
                } else if (kg_matriz[i][j] < 0.0) {
                    printf("Error! Los kilos no pueden ser negativos.\n");
                } else if (kg_matriz[i][j] > 1000.0) {
                    printf("Advertencia! Maximo 1000 Kg.\n");
                }
            } while (kg_matriz[i][j] < 0.0 || kg_matriz[i][j] > 1000.0);
            
            // Copia el valor nuevo a la matriz "original"
            // Esto es para que el reporte sepa que este es el nuevo valor base.
            kg_matriz_original[i][j] = kg_matriz[i][j];
        }
    }
    *flag_kilos_ingresados = 1; // Pone la bandera de 'ingresados' en 1
    *flag_kilos_modificados = 0; // Resetea la bandera de 'modificados'
    printf("\nKilos guardados!\n");
}

// --- FUNCION "AYUDANTE" 2: MODIFICAR VARIOS ---
// Esta funcion tambien es 'static'.
static void modificarVarios(double kg_matriz[][CAP_DIAS], int *flag_kilos_modificados) {
    int i_material, i_dia;
    int opcion_mat, opcion_dia;
    
    // Inicia un bucle 'do-while' para permitir multiples modificaciones
    do {
        printf("\n--- Modificar un dia (ingrese 0 para terminar) ---\n");
        
        // 1. Preguntar por el Material
        printf("Que material desea editar?\n");
        for(i_material = 0; i_material < CAP_MATERIALES; i_material++) {
            printf("  [%d] %s\n", i_material + 1, NOMBRES_MAT[i_material]);
        }
        printf("  [0] Terminar Modificaciones y Volver\n");
        printf("Ingrese opcion (1-4, 0 para salir): ");
        
        if (scanf("%d", &opcion_mat) != 1) {
             printf("Error! Ingrese un numero.\n");
             while (getchar() != '\n');
             opcion_mat = -1; // Pone -1 para forzar repeticion
             continue; // 'continue' salta al inicio del bucle 'do-while'
        }
        
        // Si el usuario presiona 0, sale del bucle
        if (opcion_mat == 0) {
            break; // 'break' rompe el bucle 'do-while'
        }

        // Valida el rango
        if (opcion_mat < 1 || opcion_mat > CAP_MATERIALES) {
            printf("Error! Opcion fuera de rango.\n");
            continue; // Salta al inicio del bucle
        }

        // 2. Preguntar por el Dia
        do {
            printf("\nQue dia desea editar para %s?\n", NOMBRES_MAT[opcion_mat - 1]);
            for(i_dia = 0; i_dia < CAP_DIAS; i_dia++) {
                printf("  [%d] %s\n", i_dia + 1, NOMBRES_D[i_dia]);
            }
            printf("Ingrese opcion (1-7): ");

            if (scanf("%d", &opcion_dia) != 1) {
                 printf("Error! Ingrese un numero.\n");
                 while (getchar() != '\n');
                 opcion_dia = -1;
            } else if (opcion_dia < 1 || opcion_dia > CAP_DIAS) {
                printf("Error! Opcion fuera de rango.\n");
            }
        } while (opcion_dia < 1 || opcion_dia > CAP_DIAS); // Repite si la opcion de dia es mala

        // 3. Convertir opciones a indices (ej. Opcion 1 -> Indice 0)
        i_material = opcion_mat - 1;
        i_dia = opcion_dia - 1;

        // 4. Mostrar valor actual y pedir el nuevo
        printf("\nEl valor actual para %s el dia %s es: %.2f Kg\n", 
            NOMBRES_MAT[i_material], NOMBRES_D[i_dia], kg_matriz[i_material][i_dia]);
        
        // Bucle de validacion para el nuevo valor
        do {
            printf("Ingrese el nuevo valor de Kilos: ");
            // Lee en la celda correcta de la matriz
            if (scanf("%lf", &kg_matriz[i_material][i_dia]) != 1) {
                printf("Error! Debe ingresar un numero.\n");
                while (getchar() != '\n'); 
            } else if (kg_matriz[i_material][i_dia] < 0.0) {
                printf("Error! Los kilos no pueden ser negativos.\n");
            } else {
                break; // Sale del bucle si el numero es valido
            }
        } while (1); // Bucle infinito hasta que se rompa con 'break'
        
        // *** IMPORTANTE: Activa la bandera de modificacion ***
        *flag_kilos_modificados = 1;
        printf("\nValor actualizado exitosamente!\n");
    
    } while (1); // Bucle infinito (se rompe con 'break' cuando opcion_mat es 0)
    
    printf("Terminando modificaciones...\n");
}


// --- FUNCION 2: CAPTURAR KILOGRAMOS (Logica principal) ---
// Esta es la funcion que 'main.c' llama
void capturarKilogramos(double kg_matriz[][CAP_DIAS], double kg_matriz_original[][CAP_DIAS], int *flag_kilos_ingresados, int *flag_kilos_modificados) {
    
    int sub_opcion; // Variable para el sub-menu

    // Si la bandera es 0 (Primera vez)
    if (*flag_kilos_ingresados == 0) {
        printf("\n--- Opcion 2: Ingresar Kilos (Primera Vez) ---\n");
        // Llama a la funcion ayudante 'sobreescribirTodos'
        sobreescribirTodos(kg_matriz, kg_matriz_original, flag_kilos_ingresados, flag_kilos_modificados);
    } else {
        // Si la bandera es 1 (Ya hay datos), muestra el sub-menu
        printf("\n--- Opcion 2: Ingresar/Modificar Kilos ---\n");
        printf("Ya existen kilos registrados.\n");
        printf("  [1] Sobreescribir TODOS los 28 registros\n");
        printf("  [2] Modificar uno o varios dias\n");
        printf("  [0] Volver al menu\n");
        printf("\nSeleccione una opcion: ");

        if (scanf("%d", &sub_opcion) != 1) {
            printf("Entrada no valida.\n");
            while (getchar() != '\n');
            return;
        }

        switch(sub_opcion) {
            case 1:
                // Llama a la funcion ayudante 'sobreescribirTodos'
                sobreescribirTodos(kg_matriz, kg_matriz_original, flag_kilos_ingresados, flag_kilos_modificados);
                break;
            case 2:
                // Llama a la funcion ayudante 'modificarVarios'
                modificarVarios(kg_matriz, flag_kilos_modificados); 
                break;
            case 0:
                printf("Operacion cancelada. Volviendo al menu...\n");
                return;
            default:
                printf("Opcion no valida.\n");
                break;
        }
    }
}