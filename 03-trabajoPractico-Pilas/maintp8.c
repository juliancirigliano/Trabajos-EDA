#include "tp_pilas.h"
#include "tipo_elemento.c"
#include "pilas_arreglos.c"
#include "tp8aux.c"
#include "tpp_8.c"
#include "validaciones.c"
#include <stdio.h>
#include <stdbool.h>

void Punto_8(void){
	Pila pila_test, pila_exit;
	pila_test = p_crear();
	TipoElemento te;
	int resultado;
	printf("Ejercicio 8\n");
	printf("\n");
	int eleccion;
	printf("Tipo de ingreso: (1) Manual, (2) Predefinido\n");
	scanf("%d", &eleccion);
	switch(eleccion){
		case 1:
			int arreglo[10];
			for (int i = 0; i < 10; i++) {
				printf("Elemento %d: ", i + 1);
				resultado = scanf("%d", &arreglo[i]);
				arreglo[i] = (int)arreglo[i];
				while(resultado != 1|| arreglo[i] <= 0 ){
					printf("Entrada inválida. Debe ser un número entero mayor que 0.\n");
					printf("Intente nuevamente\n");
					printf("Elemento %d: ", i + 1);
					resultado = scanf("%d", &arreglo[i]);
				}
			}
			for(int i = 0; i < 10; i++){
				te = te_crear(arreglo[i]);
				p_apilar(pila_test, te);	
			}
			printf("Pila inicial: \n");
			p_mostrar(pila_test);
			pila_exit = p_ej8_sacarrepetidos(pila_test);
			printf("Pila inicial (para verificar que no tubo cambios) \n:");
			p_mostrar(pila_test);
			printf("Pila salida \n:");
			p_mostrar(pila_exit);
			printf("Pila salida + valores \n:");
			p_mostrar_y_valor(pila_exit);
			break;
		case 2:
			int arreglo_test[] = {1,2,1,3,4,5,2,1,3,5,5};
			for(int i = 0; i < 12; i++){
				te = te_crear(arreglo_test[i]);
				p_apilar(pila_test, te);	
			}
			printf("Pila inicial: \n");
			p_mostrar(pila_test);
			pila_exit = p_ej8_sacarrepetidos(pila_test);
			printf("Pila inicial (para verificar que no tubo cambios) \n:");
			p_mostrar(pila_test);
			printf("Pila salida \n:");
			p_mostrar(pila_exit);
			printf("Pila salida + valores \n:");
			p_mostrar_y_valor(pila_exit);
			break;
		default:
			printf("Error, intente nuevamente:\n");
			printf("Tipo de ingreso: (1) Manual, (2) Predefinido\n");
			break;
	}
}

int main(void){
	Punto_8();
	return 0;
}




