#include "tp8aux.h"


Pila pila_buscar_repetidos(Pila pila){
	if(p_es_vacia(pila)){
		return NULL;
	}
	Pila pila_aux, pila_rep;
	pila_rep = p_crear();
	pila_aux = p_crear();
	TipoElemento te;
	bool primer_ciclo = true; 
	while(p_es_vacia(pila)!= true){
		if(primer_ciclo){
			te = p_desapilar(pila);
			p_apilar(pila_aux, te);
			p_apilar(pila_rep, te);
			primer_ciclo = false;
		}else{
			te = p_desapilar(pila);
			p_apilar(pila_aux, te);
		}
		//si no esta en la pila repetidos,
		//entonces se agrega
		//si esta en la lista, devuelve true
		if(pila_buscar(pila_rep, te) == false){
			p_apilar(pila_rep, te);
		}
	}
	//terminado el ciclo, recupero pila
	intercambiar_pilas(pila_aux, pila);
	return pila_rep;
}

void intercambiar_pilas(Pila pila_1, Pila pila_2){
	TipoElemento te;
	while(p_es_vacia(pila_1)!=true){
		te = p_desapilar(pila_1);
		p_apilar(pila_2, te);
	}
}


bool pila_buscar(Pila pila, TipoElemento te_buscado){
	if(p_es_vacia(pila)){
		return NULL;
	}
	Pila pila_aux = p_crear();
	TipoElemento te;
	bool respuesta = false;
	//Busqueda por desapilado
	while(p_es_vacia(pila) != true){
		te = p_desapilar(pila);
		p_apilar(pila_aux, te);
		//te contra te_buscado no son iguales
		//porque no apuntan a lo mismo 
		if(te->clave == te_buscado->clave){
			respuesta = true;
		}

	}
	//intercambiar_pilas
	intercambiar_pilas(pila_aux, pila);
	return respuesta;
}

Pila pila_ordenar_asc(Pila pila){   
	//TODO: comprobar si la pila solo tien un elemento
	if(p_largo(pila)== 1){
		return pila;
	}
	//Basicamente esto es una torre de hanoi
	Pila pila_cache;
	pila_cache = p_crear();
	TipoElemento te_1, te_2;
	bool esta_ordenada = false;
	int correctos = 0;
	int parada = 10;
	int largo_pila = p_largo(pila);
	//printf("largo de pila: %d\n",largo_pila);
	while(esta_ordenada == false){
		te_1 = p_desapilar(pila);
		while(p_es_vacia(pila)== false){
			te_2 = p_desapilar(pila);
			if(te_1->clave > te_2->clave){
				//guardo en cache
				p_apilar(pila_cache, te_1);
				//p_apilar(pila_cache, te_2);
				//sobreescribo te_1
				te_1 = te_2;
				correctos++;
				//siguiente ciclo
			}else{
				//produzco el intercambio
				correctos = 0;
				p_apilar(pila_cache, te_2);
			}
		}
		//fin de la corrida de while
		//apilo el que quedo descarriado
		p_apilar(pila_cache, te_1);
		//recupero la pila 
		//printf("Correctos: %d\n", correctos);
		intercambiar_pilas(pila_cache, pila);

		//esta condicion hace que haga un ciclo demas
		//sin ese ciclo demas se descontrola y da overflow
		if(correctos > largo_pila){
			esta_ordenada = true;
		}
	}

	return pila;
}

int p_largo(Pila pila){
	TipoElemento te;
	Pila pila_aux = p_crear();
	int contador = 0;
	while(p_es_vacia(pila)!=true){
		te = p_desapilar(pila);
		p_apilar(pila_aux, te);
		contador++;
	}
	intercambiar_pilas(pila_aux, pila);
	return contador;
}


void p_mostrar_y_valor(Pila pila) {
    if (p_es_vacia(pila)) {
        printf("PILA VACIA !!! \n");
        return;
    }
    Pila Paux = p_crear();
    TipoElemento X = te_crear(0);
    printf("Contenido de la pila: ");
    // Recorro la pila desapilandola y pasandola al auxiliar
    while (p_es_vacia(pila) != true) {
        X = p_desapilar(pila);
        printf("%d:%d, ", X->clave, *(int*)X->valor );
        p_apilar(Paux, X);
    }
    // Recorro la pila auxiliar para pasarla a la original
    while (p_es_vacia(Paux) != true) {
        X = p_desapilar(Paux);
        p_apilar(pila, X);
    }
    printf("\n");
}


