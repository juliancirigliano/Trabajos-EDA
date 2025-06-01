Pila p_ej8_sacarrepetidos(Pila p){
	if(p_es_vacia(p)){
		return NULL;
	}
	Pila pila_repetidos, pila_aux, pila_ordenada;
	pila_repetidos = p_crear();
	pila_ordenada = p_crear();
	pila_aux = p_crear();
	TipoElemento te_o, te_p;
	pila_repetidos = pila_buscar_repetidos(p);
	pila_repetidos = pila_ordenar_asc(pila_repetidos);
	//ahora tengo que hacer el recuento
	int contador = 0;
	while(p_es_vacia(pila_repetidos) == false){
		//desapilo un elemento de los repetidos
		te_o = p_desapilar(pila_repetidos);

		while(p_es_vacia(p)== false){
			te_p = p_desapilar(p);
			p_apilar(pila_aux, te_p);
			//claves iguales
			if(te_o->clave == te_p->clave){
				contador++;
			}
		}
		//printf("contador: %d\n", contador);
		intercambiar_pilas(pila_aux, p);
		//aplicar el contador al valor de la clave:
		int * puntero = malloc(sizeof(int));
		* puntero = contador; 
		te_o->valor = puntero;
		//apilar
		p_apilar(pila_ordenada, te_o);
		//reiniciar el contador: 
		contador = 0;
	}
	//invertir la pila ordenada
	return pila_ordenada;
}
