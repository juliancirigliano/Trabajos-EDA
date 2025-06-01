#include "tp_pilas.h"
#include "tipo_elemento.c"
#include "pilas_arreglos.c"
#include "tp8aux.c"
#include "tpp_8.c"
#include <stdio.h>
#include <stdbool.h>

int main(void){
	Pila pila_test, pila_exit;
	pila_test = p_crear();
	int arreglo_test[] = {1,2,1,3,4,5,2,1,3,5,5};
	for(int i = 0; i < 12; i++){
		//el tamaño maximo de una lista es
		//10 elementos
		TipoElemento te = te_crear(arreglo_test[i]);
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
	return 0;
}
