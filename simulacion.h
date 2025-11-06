// Archivo: simulacion.h
// Proposito: Funcion para simular un aumento de precio.

#include <stdio.h>

// --- CONSTANTES Y NOMBRES (Solo para este archivo) ---
#define SIM_MATERIALES 4
#define SIM_DIAS 7
const char *SIM_NOMBRES_MAT[SIM_MATERIALES] = {"PET", "Carton", "Aluminio", "Vidrio"};


// --- FUNCION 4: SIMULAR IMPACTO (Recibe kilos y precios) ---
void simularImpacto(double kg_matriz[][SIM_DIAS], double precios[]) {
    
    // --- Variables locales para la simulacion ---
    int i, j;
    int opcion_material; 
    double porcentaje_aumento; 
    
    // Arreglos y variables locales para guardar los calculos
    double totales_material[SIM_MATERIALES] = {0.0};
    double ingreso_actual = 0.0;
    double ingreso_simulado = 0.0;
    double nuevo_precio_simulado = 0.0;

    printf("\n==============================================================\n");
    printf("           OPCION 4: SIMULACION DE AUMENTO DE PRECIO \n");
    printf("==============================================================\n\n");

    // --- PASO 1: Preguntar al usuario (con validacion) ---
    do {
        printf("Que material desea simular?\n");
        printf("  [1] %s (Precio actual: $%.2f)\n", SIM_NOMBRES_MAT[0], precios[0]);
        printf("  [2] %s (Precio actual: $%.2f)\n", SIM_NOMBRES_MAT[1], precios[1]);
        printf("  [3] %s (Precio actual: $%.2f)\n", SIM_NOMBRES_MAT[2], precios[2]);
        printf("  [4] %s (Precio actual: $%.2f)\n", SIM_NOMBRES_MAT[3], precios[3]);
        printf("Ingrese una opcion (1-4): ");
        
        if (scanf("%d", &opcion_material) != 1) {
            printf("Error! Ingrese solo un numero.\n");
            while (getchar() != '\n');
            opcion_material = -1; // Valor malo para repetir
        } else if (opcion_material < 1 || opcion_material > 4) {
            printf("Error! Opcion fuera de rango (1-4).\n");
        }
    } while (opcion_material < 1 || opcion_material > 4);
    
    // Pregunta el porcentaje
    do {
        printf("\nQue porcentaje (%%) de aumento desea simular? (ej. 10): ");
        if (scanf("%lf", &porcentaje_aumento) != 1) {
            printf("Error! Ingrese solo un numero.\n");
            while (getchar() != '\n');
            porcentaje_aumento = -1.0;
        } else if (porcentaje_aumento <= 0.0) {
            printf("Error! El porcentaje debe ser mayor a cero.\n");
        }
    } while (porcentaje_aumento <= 0.0);

    // --- PASO 2: Calcular el Ingreso Actual ---
    // (Debe recalcular los totales aqui, localmente)
    ingreso_actual = 0.0;
    for (i = 0; i < SIM_MATERIALES; i++) {
        totales_material[i] = 0.0; // Importante resetear
        for (j = 0; j < SIM_DIAS; j++) {
            totales_material[i] += kg_matriz[i][j];
        }
        ingreso_actual += (totales_material[i] * precios[i]);
    }

    // --- PASO 3: Calcular el Ingreso Simulado ---
    int index_material = opcion_material - 1; // Convierte 1-4 a 0-3
    // Calcula el nuevo precio. Ej: 10 * (1.0 + (15.0 / 100.0)) = 11.5
    nuevo_precio_simulado = precios[index_material] * (1.0 + (porcentaje_aumento / 100.0));

    ingreso_simulado = 0.0; // Resetea el ingreso simulado
    for (i = 0; i < SIM_MATERIALES; i++) {
        // Si es el material que cambiamos...
        if (i == index_material) {
            // ...usa el precio NUEVO
            ingreso_simulado += (totales_material[i] * nuevo_precio_simulado);
        } else {
            // ...si no, usa el precio VIEJO
            ingreso_simulado += (totales_material[i] * precios[i]);
        }
    }
    
    // --- PASO 4: Mostrar Resultados ---
    printf("\n--- RESULTADOS DE LA SIMULACION ---\n\n");
    printf("  Material simulado:     %s\n", SIM_NOMBRES_MAT[index_material]);
    printf("  Aumento simulado:      %.1f%%\n", porcentaje_aumento);
    printf("  Precio anterior:       $%.2f\n", precios[index_material]);
    printf("  Precio nuevo simulado: $%.2f\n\n", nuevo_precio_simulado);
    
    printf("  Ingreso Total Actual:      $%.2f\n", ingreso_actual);
    printf("  Ingreso Total Simulado:    $%.2f\n", ingreso_simulado);
    printf("--------------------------------------\n");
    printf("  Diferencia (Ganancia):   $%.2f\n", ingreso_simulado - ingreso_actual);
}