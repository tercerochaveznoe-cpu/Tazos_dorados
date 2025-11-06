

Sistema de Registro de Reciclaje (ODS 12)

Este proyecto es una **versión robusta y final** de un sistema de registro y análisis de datos de reciclaje, desarrollado en lenguaje **C**. Su objetivo principal es ayudar a llevar un control de los kilogramos (Kg) de diferentes materiales reciclables recolectados a lo largo de una semana y simular el impacto económico de posibles cambios de precios.

El código está optimizado para la claridad, la validación de entrada (a prueba de errores comunes) y la organización modular a través de múltiples archivos de cabecera (`.h`).



 Características Principales

  * **Menú Interactivo:** Navegación simple y validada con un menú principal.
  * **Gestión de Datos:** Permite ingresar, modificar y sobrescribir los precios de materiales y los kilogramos recolectados por día.
  * **Reporte Detallado:** Genera un reporte completo con tablas, ingresos, porcentajes, detección de materiales "Top" y "Preocupantes", y un gráfico de participación simple.
  * **Simulación Económica:** Permite simular el impacto en el ingreso total al aumentar el precio de un material específico.
  * **Robustez:** Implementa **validaciones de entrada** (`scanf` protegido) y manejo de "banderas" (flags) para controlar el estado del programa.



 Estructura del Proyecto

El proyecto está organizado en un archivo principal (`main.c`) y tres librerías (`.h`) para una **separación lógica de responsabilidades** (Modularidad).

| Archivo | Rol | Descripción de Funcionalidad |
| :--- | :--- | :--- |
| `main.c` | **Orquestador** | Contiene la función `main()`, el **ciclo principal** del menú y las **variables globales** del sistema (precios, kilos, banderas). Llama a las funciones de las librerías. |
| `captura.h` | **Entrada de Datos** | Maneja la **captura y modificación** de los precios (`capturarPrecios`) y los kilogramos (`capturarKilogramos`), incluyendo la lógica de *primera vez* vs. *modificación*. |
| `reportes.h` | **Salida de Datos** | Encargada de realizar todos los **cálculos estadísticos** (totales, ingresos, porcentajes) y formatear la **salida en pantalla** (tablas, gráficos, sugerencias). |
| `simulacion.h` | **Análisis** | Implementa la función `simularImpacto`, que permite al usuario ingresar un **porcentaje de aumento** en el precio de un material y muestra la **ganancia** que se obtendría. |

-----

Estructura de Datos Centrales

El corazón del sistema de almacenamiento son tres variables globales definidas en `main.c`:

| Variable | Tipo | Dimensiones | Propósito |
| :--- | :--- | :--- | :--- |
| `precios_kg` | `double[]` | Arreglo de 4 | Almacena el precio por Kg de los 4 materiales (PET, Cartón, Aluminio, Vidrio). |
| `kg_material_dia` | `double[][]` | Matriz 4 x 7 | Almacena los Kg recolectados. **Filas = Materiales**, **Columnas = Días**. Es la matriz de **datos activos**. |
| `kg_matriz_original` | `double[][]` | Matriz 4 x 7 | Almacena una copia de los datos antes de cualquier modificación. Se usa en `reportes.h` para detectar si un valor fue modificado (indicado con un `*`). |

La Lógica de las Banderas (Flags)

| Bandera | Propósito | Explicación |
| :--- | :--- | :--- |
| `precios_ingresados` | Estado de Precios | `0` si nunca se han ingresado. `1` después de la primera entrada o modificación. |
| `kilos_ingresados` | Estado de Kilos | `0` si la matriz de Kilos está vacía. `1` una vez se han ingresado los 28 valores. |
| `kilos_modificados` | Indicador de Reporte | **Se vuelve `1` si se usa la opción "Modificar uno o varios días"**. Activa la detección y el indicador `*` en la tabla del reporte. |

-----

 Puntos Técnicos Destacados

1.  **Gestión de Estado con Punteros:** Las variables de estado (`flags`) se pasan **por referencia** (usando punteros `&`) a las funciones para que puedan ser modificadas directamente en la memoria.
2.  **Validación de Entrada Robusta:** Se implementa un mecanismo para manejar entradas no numéricas o fuera de rango. Si `scanf()` falla, un bucle limpia el *buffer* de entrada (`while (getchar() != '\n');`) para prevenir *loops* infinitos o lecturas erróneas.
3.  **Formato de Reporte Alineado:** El reporte utiliza especificaciones de formato avanzado en `printf` (`%-10s`, `%12.2f`) para asegurar que las columnas de datos y textos estén perfectamente alineadas.

-----

Tecnologías y Requisitos

  * **Lenguaje:** C Estándar (ANSI C / C99 o posterior).
  * **Compilador:** Se recomienda **GCC** (GNU Compiler Collection) o **Clang**.
  * **Librerías:** Solo se utilizan las librerías estándar de C (`stdio.h`, `stdlib.h`, `string.h`, `ctype.h`).

-----
 Compilación y Ejecución

Para compilar el proyecto en la terminal usando GCC, ejecute el siguiente comando:

```bash
gcc main.c -o reciclaje
```

Una vez compilado, puede ejecutar el programa:

| Sistema Operativo | Comando de Ejecución |
| :--- | :--- |
| **Linux/macOS** | `./reciclaje` |
| **Windows** | `.\reciclaje.exe` |

-----

 Contribuciones

Si deseas contribuir a este proyecto, por favor, sigue estos pasos:

1.  Haz un "fork" del repositorio.
2.  Crea una nueva rama para tus cambios (`git checkout -b feature/nueva-mejora`).
3.  Implementa tus cambios, manteniendo la estructura modular.
4.  Realiza un "commit" de tus cambios (`git commit -m 'feat: Añadir nueva funcionalidad X'`).
5.  Sube tu rama (`git push origin feature/nueva-mejora`).
6.  Abre un "Pull Request" (Solicitud de Extracción).

-----

## 👨‍💻 Autores

Este proyecto fue desarrollado por el equipo de **LOS TAZOS DORADOS**:

  * NOE DE JESUS TERCERO CHAVEZ
  * CRISTAN GUSTAVO CABRERA BAMA
  * DECNI AARON DE LEON MATIAS
  * JESUS ANTONIO CASTILLO CANIZALES
  * BYRON DE JESUS RODRIGUEZ VELAZQUEZ

**Materia:** PROGRAMACION ESTRUCTURADA
**Profesora:** VANESSA BENAVIDES GARCIA
**Fecha:** 07 de NOVIEMBRE de 2025

-----

