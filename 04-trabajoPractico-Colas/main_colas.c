#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_colas_3.h"
#include "funciones_propias_colas.h"
#include "../libs/validaciones/headers/validaciones.h"
#include "../libs/tipoElemento/headers/tipo_elemento.h"
#include "../libs/listas/headers/listas.h"
#include "../libs/pilas/headers/pilas.h"
#include "../libs/colas/headers/colas.h"

//Aclaracion importante: 
//Para compilar correctamente el proyecto, es necesario compilar los siguientes archivos:

//- `04-trabajoPractico-Colas/main_colas.c`
//- `04-trabajoPractico-Colas/ejercicios_colas.c`
//- `libs/validaciones/implementaciones/validaciones.c`
//- `libs/listas/implementaciones/listas_arreglos.c`
//- `libs/pilas/implementaciones/pilas_arreglos.c`
//- `libs/colas/implementaciones/colas_arreglos.c`
//- `libs/tipoElemento/implementaciones/tipo_elemento.c`

//Y usar los directorios de headers ubicados en:

//- `libs/validaciones/headers`
//- `libs/listas/headers`
//- `libs/pilas/headers`
//- `libs/colas/headers`
//- `libs/tipoElemento/headers`

//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------

// Menu realizado del trabajo de Colas. 

int obtenerOpcionValida();

int main() {
    int opcion;

    do {
        printf("\n----- MENU DE EJERCICIOS -----\n");
        printf("1. Ejercicio 2: Diversos ejercicios con colas\n");
        printf("2. Ejercicio 3: Comprobar contenido igual\n");
        printf("3. Ejercicio 4: Elementos no repetidos de la cola\n");
        printf("4. Ejercicio 5: Divisores totales o parciales\n");
        printf("5. Ejercicio 6: Valores comunes entre pila y cola\n");
        printf("0. Salir del menu\n");
        printf("Seleccione una opcion (0-5): ");

        opcion = obtenerOpcionValida();

        switch (opcion) {
            case 1:
                ejercicio2 ();
                break;
            case 2:
                carga_ej3();
                break;
            case 3:
                ejercicio4();
                break;
            case 4:
                cargaEjercicio5();
                break;
            case 5:
                cargarEjercicio6();
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
        }

    } while (opcion != 0);

    return 0;
}

// Función para validar la entrada del menú (solo números del 0 al 5)
int obtenerOpcionValida() {
    char entrada[10];
    int numero;
    fflush(stdin);
    while (1) {
        fgets(entrada, sizeof(entrada), stdin);
        if (strlen(entrada) == 2 && entrada[1] == '\n' && entrada[0] >= '0' && entrada[0] <= '5') {
            numero = entrada[0] - '0';
            return numero;
        } else {
            printf("Entrada invalida. Ingrese un numero del 0 al 5: ");
        }
    }
}
