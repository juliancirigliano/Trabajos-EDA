#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_1_recursividad.h"
#include "funciones_propias_recursividad.h"
#include "../libs/validaciones/headers/validaciones.h"


//Aclaracion importante: 
//Para compilar correctamente el proyecto, es necesario compilar los siguientes archivos:

//- `01-trabajoPractico-Recursividad/main_recursividad.c`
//- `01-trabajoPractico-Recursividad/ejercicios_recursividad.c`
//- `libs/validaciones/implementaciones/validaciones.c`

//Y usar el directorio de headers ubicado en:

//- `libs/validaciones/headers`

//---------------------------------------------------------------------------------------------------------

// Menu realizado del trabajo de Recursividad. 

int obtenerOpcionValida();

int main() {
    int opcion;

    do {
        printf("\n----- MENU DE EJERCICIOS -----\n");
        printf("1. Ejercicio: Palindromo\n");
        printf("2. Ejercicio: Producto de enteros\n");
        printf("3. Ejercicio: Fibonacci\n");
        printf("4. Ejercicio: Cociente de restas sucesivas\n");
        printf("5. Ejercicio: Puntos separadores de miles\n");
        printf("6. Ejercicio: Generar onda digital\n");
        printf("7. Ejercicio: Mafia China\n");
        printf("8. Ejercicio: Subconjuntos que suman\n");
        printf("9. Ejercicio: Divisible por 7\n");
        printf("0. Salir del menu\n");
        printf("Seleccione una opcion (0-9): ");

        opcion = obtenerOpcionValida();

        switch (opcion) {
            case 1:
                cargarCadenaEj1();
                break;
            case 2:
                cargarNumerosPunto2();
                break;
            case 3:
                cargarTerminoEj3();
                break;
            case 4:
                pedirEntrada();
                break;
            case 5:
                Ejercicio5();
                break;
            case 6:
                Ejercicio6();
                break;
            case 7: 
                cargarNivelDeReunion();
                break;
            case 8:
                pedirEntradaConjuntos();
                break;
            case 9:
                cargarNumeroEj9();
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
        }

    } while (opcion != 0);

    return 0;
}

// Función para validar la entrada del menú (solo números del 0 al 9)
int obtenerOpcionValida() {
    char entrada[10];
    int numero;
    fflush(stdin);
    while (1) {
        fgets(entrada, sizeof(entrada), stdin);
        if (strlen(entrada) == 2 && entrada[1] == '\n' && entrada[0] >= '0' && entrada[0] <= '9') {
            numero = entrada[0] - '0';
            return numero;
        } else {
            printf("Entrada invalida. Ingrese un numero del 0 al 9: ");
        }
    }
}
