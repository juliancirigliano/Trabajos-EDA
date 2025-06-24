#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_conjunto.h"
#include "funciones_propias_conjuntos.h"
#include "../libs/validaciones/headers/validaciones.h"
#include "../libs/tipoElemento/headers/tipo_elemento.h"
#include "../libs/listas/headers/listas.h"
#include "../libs/conjuntos/headers/conjuntos.h"

//Aclaracion importante: 
//Para compilar correctamente el proyecto, es necesario compilar los siguientes archivos:

//- `05-trabajoPractico-Conjuntos/main_conjuntos.c`
//- `05-trabajoPractico-Conjuntos/ejercicios_conjuntos.c`
//- `libs/validaciones/implementaciones/validaciones.c`
//- `libs/listas/implementaciones/listas_cursores.c`
//- `libs/conjuntos/implementaciones/conjuntos_listas.c`
//- `libs/tipoElemento/implementaciones/tipo_elemento.c`

//Y usar los directorios de headers ubicados en:

//- `libs/validaciones/headers`
//- `libs/listas/headers`
//- `libs/conjuntos/headers`
//- `libs/tipoElemento/headers`

//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------

// Menu realizado del trabajo de Conjuntos. 

int obtenerOpcionValida();

int main() {
    int opcion;

    do {
        printf("\n----- MENU DE EJERCICIOS -----\n");
        printf("1. Ejercicio 2: Diversas operaciones entre dos conjuntos\n");
        printf("2. Ejercicio 3: Union e Interseccion entre multiples conjuntos\n");
        printf("3. Ejercicio 4: Propiedad de Transitividad\n");
        printf("4. Ejercicio 5: Diferencia Simetrica\n");
        printf("5. Ejercicio 6: Subconjunto propio con dos conjuntos\n");
        printf("6. Ejercicio 7: Subconjunto total o parcial con tres conjuntos\n");
        printf("7. Ejercicio 8: Dos conjuntos iguales sin importar posicion\n");
        printf("0. Salir del menu\n");
        printf("Seleccione una opcion (0-7): ");

        opcion = obtenerOpcionValida();

        switch (opcion) {
            case 1:
                cargaEjercicio_2();
                break;
            case 2:
                cargaEjercicio_3();
                break;
            case 3:
                cargaEjercicio_4();
                break;
            case 4:
                cargaEjercicio_5();
                break;
            case 5:
                cargaEjercicio_6();
                break;
            case 6:
                cargaEjercicio7();
                break;
            case 7:
                ejer8();
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
