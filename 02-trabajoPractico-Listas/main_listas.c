#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_2_listas.h"
#include "funciones_propias_listas.h"
#include "../libs/validaciones/headers/validaciones.h"
#include "../libs/tipoElemento/headers/tipo_elemento.h"
#include "../libs/listas/headers/listas.h"

//Aclaracion importante: 
//Para compilar correctamente el proyecto, es necesario compilar los siguientes archivos:

//- `02-trabajoPractico-Listas/main_listas.c`
//- `02-trabajoPractico-Listas/ejercicios_listas.c`
//- `libs/validaciones/implementaciones/validaciones.c`
//- `libs/listas/implementaciones/listas_arreglos.c`
//- `libs/tipoElemento/implementaciones/tipo_elemento.c`

//Y usar los directorios de headers ubicados en:

//- `libs/validaciones/headers`
//- `libs/listas/headers`
//- `libs/tipoElemento/headers`

//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------

// Menu realizado del trabajo de Listas. 

int obtenerOpcionValida();

int main() {
    int opcion;

    do {
        printf("\n----- MENU DE EJERCICIOS -----\n");
        printf("1. Ejercicio 2: Diversos analisis entre listas\n");
        printf("2. Ejercicio 3: Multiplos entre listas\n");
        printf("3. Ejercicio 4: Comparacion entre listas\n");
        printf("4. Ejercicio 5: Coeficientes de un polinomio\n");
        printf("5. Ejercicio 6: Verificacion de sublista\n");
        printf("0. Salir del menu\n");
        printf("Seleccione una opcion (0-5): ");

        opcion = obtenerOpcionValida();

        switch (opcion) {
            case 1:
                cargarListasYResolverPunto2();
                break;
            case 2:
                cargarListasYResolverMultiplo();
                break;
            case 3:
                cargarListasMayorMenor();
                break;
            case 4:
                ejercicio5();
                break;
            case 5:
                cargarYProcesarSublista();
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
