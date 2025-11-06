/*EQUIPO : LOZ TAZOS DORADOS
 * AUTORES: 
 * NOE DE JESUS TERCERO CHAVEZ
 * CRISTAN GUSTAVO CABRERA BAMA
 * DECNI AARON DE LEON MATIAS
 * JESUS ANTONIO CASTILLO CANIZALES
 * BYRON DE JESUS RODRIGUEZ VELAZQUEZ
 *
 * Materia: PROGRAMACION ESTRUCTURADA
 * Profesor: VANESSA BENAVIDES GARCIA
 * Fecha: 07 de NOVIEMBRE de 2025
 *
 * Proposito: Menu principal del programa de reciclaje .
 * .
 */

// --- LIBRERIAS NECESARIAS ---

// Libreria Estandar de Entrada/Salida (Standard Input/Output)
// Nos permite usar funciones como printf() (imprimir) y scanf() (leer)
#include <stdio.h>      

// Libreria Estandar (Standard Library)
// Necesaria para system() (ej. "cls" o "clear") y exit()
#include <stdlib.h>     

// Libreria de Tipos de Caracteres (Character Type)
// (No se usa en este archivo, pero si en captura.h para tolower())
#include <ctype.h>      

// Libreria de Cadenas (String)
// Necesaria para usar strlen(), que usamos para validar la entrada del menu
#include <string.h>     

// --- NUESTRAS PROPIAS LIBRERIAS ---
// Usamos comillas "" para incluir archivos locales (de nuestra carpeta)

// Incluye las funciones para capturar datos
#include "captura.h"    
// Incluye las funciones para generar reportes
#include "reportes.h"   
// Incluye las funciones para la simulacion
#include "simulacion.h" 

// --- CONSTANTES ---
// #define crea una constante global. Es una buena practica
// usar nombres en mayusculas para evitar "numeros magicos" en el codigo.
#define NUM_MATERIALES 4
#define NUM_DIAS 7

// --- VARIABLES PRINCIPALES (Globales a este archivo) ---
// Estas variables almacenaran todos los datos del programa
// mientras este se este ejecutando.

// Arreglo para guardar los 4 precios. Se inicializa en 0.0
double precios_kg[NUM_MATERIALES] = {0.0};
// Matriz (arreglo de arreglos) para guardar los kilos (4 filas x 7 columnas)
double kg_material_dia[NUM_MATERIALES][NUM_DIAS] = {{0.0}};

// Matriz de "respaldo" para guardar los valores originales
// antes de que el usuario los modifique. Se usa en el reporte.
double kg_matriz_original[NUM_MATERIALES][NUM_DIAS] = {{0.0}};

// --- Banderas (Flags) ---
// Variables que actuan como interruptores (0 = Falso, 1 = Verdadero)

// Se vuelve 1 cuando el usuario ingresa precios por primera vez
int precios_ingresados = 0; 
// Se vuelve 1 cuando el usuario ingresa kilos por primera vez
int kilos_ingresados = 0;   
// Se vuelve 1 si el usuario usa la opcion de "modificar" kilos
int kilos_modificados = 0;  

// --- FUNCION PRINCIPAL ---
// 'int main()' es el punto de entrada de todo programa en C.
int main() {
    
    // --- Variables Locales de main() ---
    
    // Arreglo de char (string) para leer la entrada del menu.
    // Se usa un arreglo de 10 para validar la entrada (solucion al error "67")
    char opcion_texto[10];
    
    // Variable para guardar el caracter valido de la opcion (ej. '1', '2'...)
    char opcion_final; 

    // --- CICLO PRINCIPAL DEL MENU ---
    // 'do-while' se ejecuta al menos una vez, y se repite
    // mientras la condicion en 'while()' sea verdadera.
    do {
        
        // Limpia la pantalla de la consola para mostrar el menu limpio
        #ifdef _WIN32
            // Si el sistema es Windows, ejecuta "cls"
            system("cls");
        #else
            // Para cualquier otro sistema (Mac, Linux), ejecuta "clear"
            system("clear");
        #endif

        // --- MUESTRA EL MENU (5 OPCIONES) ---
        printf("**************************************************************\n");
        printf("* SISTEMA DE REGISTRO DE RECICLAJE (ODS 12)          *\n");
        printf("**************************************************************\n\n");
        printf("  MENU PRINCIPAL\n");
        printf("--------------------------------------------------------------\n");
        printf("  [1] Ingresar/Modificar Precios de Materiales\n");
        printf("  [2] Ingresar/Modificar Kilos Recolectados\n");
        printf("  [3] Ver Reporte Completo\n");
        printf("  [4] Simular Aumento de Precio\n");
        printf("  [5] Salir\n"); // Salir es la 5
        printf("--------------------------------------------------------------\n");
        printf("\n  Seleccione una opcion: ");

        // --- VALIDACION DE ENTRADA DEL MENU ---
        
        // Lee la entrada del usuario como un TEXTO (string, "%s")
        scanf(" %s", opcion_texto);

        // 'strlen()' (de string.h) cuenta cuantos caracteres tiene el texto
        if (strlen(opcion_texto) > 1) {
            // Si el usuario escribio mas de 1 caracter (ej. "67" o "abc")
            // se le asigna 'x' para forzar el error 'default'
            opcion_final = 'x'; 
        } else {
            // Si solo escribio 1 caracter, se guarda en 'opcion_final'
            opcion_final = opcion_texto[0];
        }

        // --- SELECTOR DE OPCIONES ---
        // 'switch' compara la variable 'opcion_final' con los 'case'
        switch (opcion_final) {
            
            case '1':
                // Llama a la funcion de 'captura.h'
                // Le pasa el arreglo 'precios_kg' para que lo llene
                // Le pasa la direccion (&) de 'precios_ingresados' para que la modifique
                capturarPrecios(precios_kg, &precios_ingresados); 
                break; // 'break' sale del switch

            case '2':
                // Llama a la funcion de 'captura.h'
                // Pasa ambas matrices y ambas banderas de kilos
                capturarKilogramos(kg_material_dia, kg_matriz_original, &kilos_ingresados, &kilos_modificados); 
                break;

            case '3':
                // Llama a la funcion de 'reportes.h'
                // Pasa todos los datos necesarios para que el reporte los lea
                generarReportes(kg_material_dia, kg_matriz_original, precios_kg, precios_ingresados, kilos_ingresados, kilos_modificados);
                break;

            case '4':
                // Llama a la funcion de 'simulacion.h'
                simularImpacto(kg_material_dia, precios_kg);
                break;
            
            case '5':
                // Opcion 5 ahora es Salir
                printf("\nGracias por usar el programa. Adios!\n");
                break;

            // 'default' se ejecuta si 'opcion_final' no coincide con ningun 'case'
            default:
                printf("\nOpcion no valida. Ingrese solo UN numero del 1 al 5.\n");
                break;
        }

       // --- PAUSA ANTES DE VOLVER AL MENU ---
        if (opcion_final != '5') { // Salir es la 5
            printf("\nPresione ENTER para continuar...");
            while (getchar() != '\n'); // 1. Limpia el buffer de la funcion
            while (getchar() != '\n'); // 2. La pausa (AHORA ES UN BUCLE)
        }
    } while (opcion_final != '5'); // Repite el bucle mientras la opcion NO sea '5'

    return 0; // Termina el programa exitosamente
}