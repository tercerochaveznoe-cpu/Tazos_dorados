// Archivo: reportes.h
// Proposito: Funcion para calcular y mostrar el reporte completo.

#include <stdio.h>

// --- CONSTANTES Y NOMBRES (Solo para este archivo) ---
#define REP_MATERIALES 4
#define REP_DIAS 7
const char *REP_NOMBRES_MAT[REP_MATERIALES] = {"PET", "Carton", "Aluminio", "Vidrio"};
const char *REP_NOMBRES_D[REP_DIAS] = {"Lun", "Mar", "Mie", "Jue", "Vie", "Sab", "Dom"};

// --- FUNCION 3: GENERAR REPORTES ---
// Recibe todos los datos y banderas desde 'main.c'
void generarReportes(double kg_matriz[][REP_DIAS], double kg_matriz_original[][REP_DIAS], double precios[], int precios_ingresados, int kilos_ingresados, int kilos_modificados) {
    
    // --- Variables locales para los calculos ---
    double totales_material[REP_MATERIALES] = {0.0};
    double ingreso_material[REP_MATERIALES] = {0.0};
    double porcentaje_material[REP_MATERIALES] = {0.0};
    double total_general_kg = 0.0;
    double total_general_ingreso = 0.0;
    
    // Arreglo para guardar los totales por dia (columnas)
    double totales_dia[REP_DIAS] = {0.0}; 
    
    // Variables para encontrar el material Maximo y Minimo
    double max_kg = -1.0; 
    double min_kg = 9999999.0; // Se inicia con un numero muy alto
    int top_material_indice = 0; 
    int low_material_indice = 0; 
    
    int i, j; // Contadores

    printf("\n==============================================================\n");
    printf("           OPCION 3: REPORTE DETALLADO \n");
    
    // --- MENSAJES DE ESTADO (MEJORADOS) ---
    // Muestra mensajes especificos basados en las banderas
    if (precios_ingresados == 1) {
        printf("           (Precios Cargados/Modificados)\n");
    }
    // Muestra un mensaje especifico si se modifico
    if (kilos_modificados == 1) {
        printf("           (Kilos Modificados - * indica cambio)\n");
    } else if (kilos_ingresados == 1) {
        printf("           (Kilos Cargados)\n");
    }
    
    printf("==============================================================\n\n");

    // --- PASO 1: Calcular Totales (Filas y Columnas) ---
    for (i = 0; i < REP_MATERIALES; i++) {
        for (j = 0; j < REP_DIAS; j++) {
            // Suma el total de la fila (material)
            totales_material[i] += kg_matriz[i][j]; 
            // Suma el total de la columna (dia)
            totales_dia[j] += kg_matriz[i][j]; 
            // Suma el gran total
            total_general_kg += kg_matriz[i][j];
        }
    }
    
    // --- PASO 2: Calcular Ingresos, Porcentajes y Min/Max ---
    for (i = 0; i < REP_MATERIALES; i++) {
        ingreso_material[i] = totales_material[i] * precios[i];
        total_general_ingreso += ingreso_material[i];
        
        // Logica para encontrar el MAXIMO
        if (totales_material[i] > max_kg) {
            max_kg = totales_material[i]; 
            top_material_indice = i;      
        }
        
        // Logica para encontrar el MINIMO (que no sea cero)
        if (totales_material[i] > 0 && totales_material[i] < min_kg) {
            min_kg = totales_material[i];
            low_material_indice = i;
        }
    }
    
    // --- PASO 3: Mostrar la Tabla de Kilos (CON FORMATO ALINEADO) ---
    printf("--- 1. Tabla de Kilos (Material x Dia) ---\n\n");
    
    // Imprime la cabecera con formato de ancho fijo
    // "%-10s" = Texto de 10 espacios, alineado a la izquierda (-)
    // "%8s" = Texto de 8 espacios, alineado a la derecha (default)
    printf("%-10s |%8s |%8s |%8s |%8s |%8s |%8s |%8s |\n", 
           "Material", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab", "Dom");
    printf("----------------------------------------------------------------------------------\n");
    
    // Bucle para imprimir los datos
    for (i = 0; i < REP_MATERIALES; i++) {
        printf("%-10s |", REP_NOMBRES_MAT[i]); // Columna de material
        for (j = 0; j < REP_DIAS; j++) {
            
            // --- LOGICA DEL ASTERISCO (*) ---
            // Si la bandera de modificado esta activa Y
            // el valor actual es DIFERENTE del valor original...
            if (kilos_modificados == 1 && kg_matriz[i][j] != kg_matriz_original[i][j]) {
                // Imprime el numero con un asterisco
                // "%7.1f*" = 7 espacios para el numero + 1 para el '*' = 8 total
                printf(" %7.1f*|", kg_matriz[i][j]);
            } else {
                // Imprime normal
                // "%8.1f" = 8 espacios para el numero
                printf(" %8.1f |", kg_matriz[i][j]); 
            }
        }
        printf("\n"); // Nueva linea al final de la fila
    }
    printf("----------------------------------------------------------------------------------\n");
    
    // --- NUEVA FILA DE TOTALES POR DIA ---
    printf("%-10s |", "TOTAL DIA");
    for (j = 0; j < REP_DIAS; j++) {
        printf(" %8.1f |", totales_dia[j]);
    }
    printf("\n----------------------------------------------------------------------------------\n");


    // --- PASO 4: Mostrar Resumen por Material (CON FORMATO ALINEADO) ---
    printf("\n--- 2. Resumen por Material ---\n\n");
    // Cabecera de la segunda tabla
    printf("%-10s | %12s | %12s | %14s\n", "Material", "Total (Kg)", "Ingreso ($)", "Porcentaje (%)");
    printf("-------------------------------------------------------------------\n");
    
    for (i = 0; i < REP_MATERIALES; i++) {
        // Validacion de division por cero
        if (total_general_kg > 0) {
            porcentaje_material[i] = (totales_material[i] / total_general_kg) * 100.0;
        } else {
            porcentaje_material[i] = 0.0;
        }
        
        // Imprime la fila de datos alineada
        // "%-10s" (texto izq), "%12.2f" (numero der), "%%" (imprime un '%')
        printf("%-10s | %12.2f | %12.2f | %13.1f%%\n", 
            REP_NOMBRES_MAT[i], 
            totales_material[i], 
            ingreso_material[i], 
            porcentaje_material[i]);
    }
    
    // --- PASO 5: Mostrar Totales Generales (SIN META) ---
    printf("-------------------------------------------------------------------\n");
    // Imprime la fila de totales
    printf("%-10s | %12.2f | %12.2f | %13.1f%%\n", 
        "TOTAL", 
        total_general_kg, 
        total_general_ingreso, 
        100.0);
    
    // --- PASO 6: Mostrar Sugerencias (CON MIN/MAX) ---
    printf("\n--- 3. Analisis y Sugerencias ---\n\n");
    
    // Solo muestra sugerencias si hay kilos ingresados
    if (total_general_kg > 0) {
        // Muestra el material 'Top'
        printf("  Material 'Top': %s (con %.2f Kg recolectados)\n", 
            REP_NOMBRES_MAT[top_material_indice], 
            max_kg);
        
        // Muestra el material 'Preocupante' (si es diferente del 'Top')
        if (top_material_indice != low_material_indice) {
             printf("  Material 'Preocupante': %s (con %.2f Kg recolectados)\n\n", 
                REP_NOMBRES_MAT[low_material_indice], 
                min_kg);
        } else {
            printf("\n"); // Solo un espacio
        }

    } else {
        printf("  Aun no se han ingresado kilos.\n\n");
    }
    
    // Sugerencia fija del PET (Indice 0)
    if (porcentaje_material[0] > 25.0) { 
        printf("  Sugerencia Fija: El PET supera el 25%% del total. Buen trabajo!\n");
    } else {
        printf("  Sugerencia Fija: El PET esta bajo. Considerar campana para recoleccion de PET.\n");
    }
    
    // --- PASO 7: GRAFICO SIMPLE (CON FORMATO ALINEADO) ---
    printf("\n--- 4. Grafico de Participacion por Material ---\n\n");
    
    for (i = 0; i < REP_MATERIALES; i++) {
        // "%-10s" alinea los nombres para que las barras empiecen en el mismo lugar
        printf("  %-10s |", REP_NOMBRES_MAT[i]);
        
        // Calcula 1 asterisco por cada 5%
        int asteriscos = (int)(porcentaje_material[i] / 5.0);
        
        // Bucle para imprimir los asteriscos
        for (j = 0; j < asteriscos; j++) {
            printf("*");
        }
        
        // Imprime el porcentaje al final
        printf(" (%.1f%%)\n", porcentaje_material[i]);
    }
}