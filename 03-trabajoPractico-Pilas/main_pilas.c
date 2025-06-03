#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_pilas.h"
#include "funciones_propias_pilas.h"
#include "../libs/validaciones/headers/validaciones.h"
#include "../libs/tipoElemento/headers/tipo_elemento.h"
#include "../libs/pilas/headers/pilas.h"

//Aclaracion importante: 
//Para compilar correctamente el proyecto, es necesario compilar los siguientes archivos:

//- `03-trabajoPractico-Pilas/main_pilas.c`
//- `03-trabajoPractico-Pilas/ejercicios_pilas.c`
//- `libs/validaciones/implementaciones/validaciones.c`
//- `libs/pilas/implementaciones/pilas_arreglos.c`
//- `libs/tipoElemento/implementaciones/tipo_elemento.c`

//Y usar los directorios de headers ubicados en:

//- `libs/validaciones/headers`
//- `libs/pilas/headers`
//- `libs/tipoElemento/headers`

//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------

// Menu realizado del trabajo de Pilas. 

int obtenerOpcionValida();

int main() {
    int opcion;

    do {
        printf("\n----- MENU DE EJERCICIOS -----\n");
        printf("1. Ejercicio 2: Diversos ejercicios con pilas\n");
        printf("2. Ejercicio 3: Comprobar contenido igual\n");
        printf("3. Ejercicio 4: Decimal a base hexadecimal\n");
        printf("4. Ejercicio 5: Invertir contenido de pila\n");
        printf("5. Ejercicio 6: Eliminar ocurrencias\n");
        printf("6. Ejercicio 7: Elementos en comun\n");
        printf("7. Ejercicio 8: Valores repetidos\n");
        printf("0. Salir del menu\n");
        printf("Seleccione una opcion (0-7): ");

        opcion = obtenerOpcionValida();

        switch (opcion) {
            case 1:
                cargarPilaEj2();
                break;
            case 2:
                cargarPilasEj3();
                break;
            case 3:
                Ejercicio4();
                break;
            case 4:
                cargarPilasEj5();
                break;
            case 5:
                cargarPilaEj6();
                break;
            case 6:
                ejercicio7();
                break;
            case 7:
                Punto_8();
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
        }

    } while (opcion != 0);

    return 0;
}

// Función para validar la entrada del menú (solo números del 0 al 7)
int obtenerOpcionValida() {
    char entrada[10];
    int numero;
    fflush(stdin);
    while (1) {
        fgets(entrada, sizeof(entrada), stdin);
        if (strlen(entrada) == 2 && entrada[1] == '\n' && entrada[0] >= '0' && entrada[0] <= '7') {
            numero = entrada[0] - '0';
            return numero;
        } else {
            printf("Entrada invalida. Ingrese un numero del 0 al 7: ");
        }
    }
}
