#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include "tp_conjunto.h"
#include "funciones_propias_conjuntos.h"
#include "../libs/validaciones/headers/validaciones.h"
#include "../libs/tipoElemento/headers/tipo_elemento.h"
#include "../libs/listas/headers/listas.h"
#include "../libs/conjuntos/headers/conjuntos.h"

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 2------------------------------------------------
//-------------------------------------------------------------------------------------------------------

bool repeticionesEjercicio2(int *arr, int n, int lon){
    //comprueba que no se agreguen repeticiones en los valores

    for (int i=0; i<lon; i++){
        if (n == arr[i]){
            printf("Elemento repeitdo\n");
            return true;
        }
    }

    return false;
}


Conjunto cargaConjuntos2(){
    Conjunto c = cto_crear();
    char dato[100];   //buffer de entrada
    int valores[10];   //vector donde se almacenan los valores en una primera instancia
    int lon = 0;   //longitud del conjutno
    printf("Numeros enteros sin repeticiones( . para terminar la carga)\n");
    while (lon < 10){
        //limita el ingreso a 10 valores
        printf("%d: ", lon+1);
        fflush(stdin);
        //valida que no se ingresen valores repetidos 
		//y que el conjunto no tenga menos de un elemento
        while ((strcmp(fgets(dato, 100, stdin), ".\n") != 0) && (!esEntero(dato) 
                || repeticionesEjercicio2(valores, atoi(dato), lon))){
            printf("Error. Ingrese un valor valido\n");
            printf("%d: ", lon+1);
            fflush(stdin);
        }
        if (strcmp(dato, ".\n") == 0 && lon < 2){
            //valida que el conjunto no tenga menos de 1 elemento antes de salir
            printf("Error. El conjunto debe tener 1 elemento como minimo\n");
        }
        else if(strcmp(dato, ".\n") == 0){
            //utiliza "." para finalizar la carga
            break;
        }
        else {
            //agrega los valores al arreglo y aumenta la longitud del conjunto
            valores[lon] = atoi(dato);
            lon++;
        }
    }
    for (int i=0; i<lon; i++){
        //crea el conjunto con los valores introducidos en el vector
        cto_agregar(c, te_crear(valores[i]));
    }
    return c;
}

void cargaEjercicio_2(){
	Conjunto test = cto_crear();
	Conjunto test2 = cto_crear();
    printf("Ingrese los valores del primer conjunto (minimo 1 elemento, maximo 10 elementos)\n");
    Conjunto A = cargaConjuntos2();

    printf("Ingrese los valores del segundo conjunto (minimo 1 elemento, maximo 10 elementos)\n");
    Conjunto B = cargaConjuntos2();
	
	printf("Probando union...    ");
	test = c_ej2_union(A,B);
	if( cto_es_vacio(test)){
		printf("Error, ambos conjuntos estan vacios\n");
	}else{
		printf("Conjunto unificado:\n");
		cto_mostrar(test);
	}
	printf("\n");
	printf("Probando intersección...    ");
	test = c_ej2_interseccion(A,B);
	if( cto_es_vacio(test)){
		printf("No hay valores comunes\n");
	}else{
		printf("Valores Comunes:\n");
		cto_mostrar(test);
	}
	printf("\n");
	printf("Probando diferencia...\n");
	int dif = 0; 
	test = c_ej2_diferencia(A,B);
	if( cto_es_vacio(test)){
		printf("No hay valores que esten en A y no esten en B\n");
	}else{
		dif++;
		printf("Valores que estan en A pero no en B:\n");
		cto_mostrar(test);
	}
	test2 = c_ej2_diferencia(B,A);
	if( cto_es_vacio(test)){
		printf("No hay valores que esten en B y no esten en A\n");
	}else{
		dif++;
		printf("Valores que estan en B pero no en A:\n");
		cto_mostrar(test2);
	}
	if(dif == 2){
		printf("Valores en los que difieren:\n");
		cto_mostrar(c_ej2_union(test, test2));
	}
	
}



/**
2.	Desarrollar un algoritmo que dado dos conjuntos de elementos tipo numérico (clave) 
	verifique las operaciones de Unión,  Intersección,  Diferencia y Pertenencia. 
*/
Conjunto c_ej2_union(Conjunto A, Conjunto B){
	return cto_union(A,B);
}
Conjunto c_ej2_interseccion(Conjunto A, Conjunto B){
	return cto_interseccion(A,B);
}
Conjunto c_ej2_diferencia(Conjunto A, Conjunto B){
	return cto_diferencia(A,B); 
}


//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 3------------------------------------------------
//-------------------------------------------------------------------------------------------------------

// Funcion para comprobar si el numero ingresado ya esta en el arreglo
bool repeticionesEjercicio3(int *arr, int n, int lon) {
    for (int i = 0; i < lon; i++) {
        if (n == arr[i]) {
            printf("Elemento repetido\n");
            return true;
        }
    }
    return false;
}

// Carga los valores en un conjunto
Conjunto cargaConjuntos3() {
    Conjunto c = cto_crear();
    char dato[100];  // buffer de entrada
    int valores[10];  // vector donde se almacenan los valores en una primera instancia
    int lon = 0;  // longitud del conjunto

    printf("Numeros enteros sin repeticiones ('.' para terminar la carga)\n");
    while (lon < 10) {
        printf("%d: ", lon + 1);

        if (fgets(dato, sizeof(dato), stdin)) {
            dato[strcspn(dato, "\n")] = 0;  // Elimina el salto de linea

            // Verifica si es un numero entero y no repetido
            while (strcmp(dato, ".") != 0 && (!esEntero(dato) || repeticionesEjercicio3(valores, atoi(dato), lon))) {
                printf("Error. Ingrese un valor valido\n");
                printf("%d: ", lon + 1);
                fgets(dato, sizeof(dato), stdin);
                dato[strcspn(dato, "\n")] = 0;  // Eliminar el salto de línea
            }

            if (strcmp(dato, ".") == 0 && lon < 1) {
                printf("Error. El conjunto debe tener al menos 1 elemento\n");
            } else if (strcmp(dato, ".") == 0) {
                break;  // Finaliza la carga si el conjunto tiene al menos un valor
            } else {
                valores[lon] = atoi(dato);  // Agrega el valor al arreglo
                lon++;
            }
        }
    }

    for (int i = 0; i < lon; i++) {
        cto_agregar(c, te_crear(valores[i]));
    }
    return c;
}

// Carga una lista de conjuntos
Lista cargaListaConjuntos3() {
    Lista resultado = l_crear();
    TipoElemento te;
    int numConjuntos;

    // Solicitar cantidad de conjuntos a ingresar
    do {
        printf("¿Cuántos conjuntos desea ingresar? (Minimo 2 y Maximo 5): ");
        scanf("%d", &numConjuntos);
        getchar();  // Limpiar el buffer de entrada para evitar que se quede el salto de línea
        if (numConjuntos < 2 || numConjuntos > 5) {
            printf("Por favor, ingrese un número entre 2 y 5.\n");
        }
    } while (numConjuntos < 2 || numConjuntos > 5);

    // Ingreso de los conjuntos
    for (int i = 0; i < numConjuntos; i++) {
        printf("Ingrese los valores del conjunto %d\n", i + 1);
        printf("(minimo 1 elemento, maximo 10 elementos)\n");
        Conjunto *puntero = malloc(sizeof(Conjunto));
        *puntero = cargaConjuntos3();
        te = te_crear_con_valor(i, puntero);
        l_agregar(resultado, te);
    }

    return resultado;
}

// Función para cargar el ejercicio 3
void cargaEjercicio_3() {
    Lista listatest = cargaListaConjuntos3();
    Conjunto test;
    printf("Probando union...    ");
    test = c_ej3_uniones(listatest);
    if (cto_es_vacio(test)) {
        printf("Error, ambos conjuntos están vacios\n");
    } else {
        printf("Conjuntos unificados:\n");
        cto_mostrar(test);
    }

    printf("Probando interseccion.. (el elemento debe estar en todos los conjuntos)\n");
    test = c_ej3_intersecciones(listatest);
    if (cto_es_vacio(test)) {
        printf("No hay valores comunes\n");
    } else {
        printf("Valores Comunes:\n");
        cto_mostrar(test);
    }
}

// Operación de unión de conjuntos
Conjunto c_ej3_uniones(Lista l_de_conjuntos) {
    Iterador ite = iterador(l_de_conjuntos);
    Conjunto aux = cto_crear();
    TipoElemento te;
    while (hay_siguiente(ite)) {
        te = siguiente(ite);
        aux = cto_union(aux, *(Conjunto*)te->valor);
    }
    return aux;
}

// Operación de intersección de conjuntos
Conjunto c_ej3_intersecciones(Lista l_de_conjuntos) {
    if (l_es_vacia(l_de_conjuntos)) {
        printf("Lista vacia, nada que hacer\n");
        return NULL;
    }

    Iterador ite = iterador(l_de_conjuntos);
    Iterador ite2 = iterador(l_de_conjuntos);  // desfasado
    Conjunto aux = cto_crear();
    int numero = 0;
    TipoElemento te, te2;
    te2 = siguiente(ite2);  // desfasaje

    while (hay_siguiente(ite)) {
        te = siguiente(ite);
        while (hay_siguiente(ite2)) {
            te2 = siguiente(ite2);
            if (numero == 0) {
                numero = 1;
                aux = cto_interseccion(*(Conjunto*)te->valor, *(Conjunto*)te2->valor);
            } else {
                aux = cto_interseccion(aux, *(Conjunto*)te2->valor);
            }
        }
    }
    return aux;
}


//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 4------------------------------------------------
//-------------------------------------------------------------------------------------------------------

bool repeticionesEjercicio4(int *arr, int n, int lon){
    //comprueba que no se agreguen repeticiones en los valores

    for (int i=0; i<lon; i++){
        if (n == arr[i]){
            printf("Elemento repeitdo\n");
            return true;
        }
    }

    return false;
}


Conjunto cargaConjuntos4(){
    Conjunto c = cto_crear();
    char dato[100];   //buffer de entrada
    int valores[10];   //vector donde se almacenan los valores en una primera instancia
    int lon = 0;   //longitud del conjutno
    printf("Numeros enteros sin repeticiones( . para terminar la carga)\n");
    while (lon < 10){
        //limita el ingreso a 10 valores
        printf("%d: ", lon+1);
        fflush(stdin);
        //valida que no se ingresen valores repetidos 
		//y que el conjunto no tenga menos de un elemento
        while ((strcmp(fgets(dato, 100, stdin), ".\n") != 0) && (!esEntero(dato) 
                || repeticionesEjercicio4(valores, atoi(dato), lon))){
            printf("Error. Ingrese un valor valido\n");
            printf("%d: ", lon+1);
            fflush(stdin);
        }
        if (strcmp(dato, ".\n") == 0 && lon < 2){
            //valida que el conjunto no tenga menos de 1 elemento antes de salir
            printf("Error. El conjunto debe tener 1 elemento como minimo\n");
        }
        else if(strcmp(dato, ".\n") == 0){
            //utiliza "." para finalizar la carga
            break;
        }
        else {
            //agrega los valores al arreglo y aumenta la longitud del conjunto
            valores[lon] = atoi(dato);
            lon++;
        }
    }
    for (int i=0; i<lon; i++){
        //crea el conjunto con los valores introducidos en el vector
        cto_agregar(c, te_crear(valores[i]));
    }
    return c;
}

void cargaEjercicio_4(){
	Conjunto test = cto_crear();
	Conjunto test2 = cto_crear();
    printf("Ingrese los valores del primer conjunto (minimo 1 elemento, maximo 10 elementos)\n");
    Conjunto A = cargaConjuntos4();

    printf("Ingrese los valores del segundo conjunto (minimo 1 elemento, maximo 10 elementos)\n");
    Conjunto B = cargaConjuntos4();

	printf("Ingrese los valores del tercer conjunto (minimo 1 elemento, maximo 10 elementos)\n");
    Conjunto C = cargaConjuntos4();
	
	printf("Probando transitividad...   \n");
	if( c_ej4_transitividad(A,B,C)){
		printf("A es subconjunto de B\n");
		printf("B es subconjunto de C\n");
		printf("entonces A es subconjunto de C\n");
	}else{
		printf("No se cumple la transitividad:\n");
	}

	
}


bool c_ej4_transitividad(Conjunto A, Conjunto B, Conjunto C){
	bool resultado = false;
	//Valores que estan en A pero no es B tiene que dar vacio 
	Conjunto test = cto_diferencia(A,B); 
	if(cto_es_vacio(test) ){
		//Valores que estan en B pero no es C tiene que dar vacio 
		Conjunto test = cto_diferencia(B,C); 
		if(cto_es_vacio(test) ){
			resultado = true;
		}
	}
	return resultado;
}


//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 5------------------------------------------------
//-------------------------------------------------------------------------------------------------------

bool repeticionesEjercicio5(int *arr, int n, int lon){
    //comprueba que no se agreguen repeticiones en los valores

    for (int i=0; i<lon; i++){
        if (n == arr[i]){
            printf("Elemento repeitdo\n");
            return true;
        }
    }

    return false;
}


Conjunto cargaConjuntos5(){
    Conjunto c = cto_crear();
    char dato[100];   //buffer de entrada
    int valores[10];   //vector donde se almacenan los valores en una primera instancia
    int lon = 0;   //longitud del conjutno
    printf("Numeros enteros sin repeticiones( . para terminar la carga)\n");
    while (lon < 10){
        //limita el ingreso a 10 valores
        printf("%d: ", lon+1);
        fflush(stdin);
        //valida que no se ingresen valores repetidos 
		//y que el conjunto no tenga menos de un elemento
        while ((strcmp(fgets(dato, 100, stdin), ".\n") != 0) && (!esEntero(dato) 
                || repeticionesEjercicio5(valores, atoi(dato), lon))){
            printf("Error. Ingrese un valor valido\n");
            printf("%d: ", lon+1);
            fflush(stdin);
        }
        if (strcmp(dato, ".\n") == 0 && lon < 2){
            //valida que el conjunto no tenga menos de 1 elemento antes de salir
            printf("Error. El conjunto debe tener 1 elemento como minimo\n");
        }
        else if(strcmp(dato, ".\n") == 0){
            //utiliza "." para finalizar la carga
            break;
        }
        else {
            //agrega los valores al arreglo y aumenta la longitud del conjunto
            valores[lon] = atoi(dato);
            lon++;
        }
    }
    for (int i=0; i<lon; i++){
        //crea el conjunto con los valores introducidos en el vector
        cto_agregar(c, te_crear(valores[i]));
    }
    return c;
}

void cargaEjercicio_5(){
	Conjunto test = cto_crear();
	printf("Ingrese los valores del primer conjunto (minimo 1 elemento, maximo 10 elementos)\n");
    Conjunto A = cargaConjuntos5();

    printf("Ingrese los valores del segundo conjunto (minimo 1 elemento, maximo 10 elementos)\n");
    Conjunto B = cargaConjuntos5();
	
	printf("Probando diferencia simetrica...\n");
	test = c_ej5_dif_simetrica(A,B);
	if(cto_es_vacio(test)){
		printf("No hay diferencia simetrica\n");
	}else{
		printf("Elementos no comunes en ambos conjuntos:\n");
		cto_mostrar(test);
	}
	
}
Conjunto c_ej5_dif_simetrica(Conjunto A, Conjunto B){
	Conjunto test = cto_crear();
	Conjunto test2 = cto_crear();
	Conjunto cvacio = cto_crear();
	int dif = 0; 
	test = cto_diferencia(A,B);
	if( cto_es_vacio(test)){
		return cvacio;
	}else{
		dif++;
	}
	test2 = cto_diferencia(B,A);
	if( cto_es_vacio(test)){
		return cvacio;
	}else{
		dif++;
	}
	if(dif == 2){
		return cto_union(test, test2);
	}



}


//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 6------------------------------------------------
//-------------------------------------------------------------------------------------------------------

bool repeticionesEjercicio6(int *arr, int n, int lon){
    //comprueba que no se agreguen repeticiones en los valores

    for (int i=0; i<lon; i++){
        if (n == arr[i]){
            printf("Elemento repeitdo\n");
            return true;
        }
    }

    return false;
}


Conjunto cargaConjuntos6(){
    Conjunto c = cto_crear();
    char dato[100];   //buffer de entrada
    int valores[10];   //vector donde se almacenan los valores en una primera instancia
    int lon = 0;   //longitud del conjutno
    printf("Numeros enteros sin repeticiones( . para terminar la carga)\n");
    while (lon < 10){
        //limita el ingreso a 10 valores
        printf("%d: ", lon+1);
        fflush(stdin);
        //valida que no se ingresen valores repetidos 
		//y que el conjunto no tenga menos de un elemento
        while ((strcmp(fgets(dato, 100, stdin), ".\n") != 0) && (!esEntero(dato) 
                || repeticionesEjercicio6(valores, atoi(dato), lon))){
            printf("Error. Ingrese un valor valido\n");
            printf("%d: ", lon+1);
            fflush(stdin);
        }
        if (strcmp(dato, ".\n") == 0 && lon < 2){
            //valida que el conjunto no tenga menos de 1 elemento antes de salir
            printf("Error. El conjunto debe tener 1 elemento como minimo\n");
        }
        else if(strcmp(dato, ".\n") == 0){
            //utiliza "." para finalizar la carga
            break;
        }
        else {
            //agrega los valores al arreglo y aumenta la longitud del conjunto
            valores[lon] = atoi(dato);
            lon++;
        }
    }
    for (int i=0; i<lon; i++){
        //crea el conjunto con los valores introducidos en el vector
        cto_agregar(c, te_crear(valores[i]));
    }
    return c;
}

void cargaEjercicio_6(){
	Conjunto test = cto_crear();
	printf("Ingrese los valores del primer conjunto (minimo 1 elemento, maximo 10 elementos)\n");
    Conjunto A = cargaConjuntos6();

    printf("Ingrese los valores del segundo conjunto (minimo 1 elemento, maximo 10 elementos)\n");
    Conjunto B = cargaConjuntos6();
	
	printf("Probando...");
	if(c_ej6_subconjuntopropio(A, B)){
		printf("El Conjunto A es subconjunto propio de B \n");
	}else{
		printf("El Conjunto A no es subconjunto propio de B:\n");
	}
	printf("Complejidad: O(n^2)\n");
}

bool c_ej6_subconjuntopropio(Conjunto A, Conjunto B){
	Conjunto test = cto_crear();
	Conjunto test2 = cto_crear();
	int dif = 0; 
	test = cto_diferencia(A,B);
	//tiene que valer 0 
	//cto_mostrar(test);
	if( cto_es_vacio(test) == true ){
		dif++;
	}
	test2 = cto_diferencia(B,A);
	//tiene que tener elementos 
	//cto_mostrar(test2);
	if( cto_es_vacio(test2) == false ){
		dif++;
	}
	if(dif == 2){
		return true;
	}else{
		return false;
	}
}


//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 7------------------------------------------------
//-------------------------------------------------------------------------------------------------------

bool repeticionesEjercicio7(int *arr, int n, int lon){
    //comprueba que no se agreguen repeticiones en los valores

    for (int i=0; i<lon; i++){
        if (n == arr[i]){
            printf("Elemento repeitdo\n");
            return true;
        }
    }

    return false;
}

Conjunto cargaConjuntos7(){

    Conjunto c = cto_crear();
    char dato[100];   //buffer de entrada
    int valores[10];   //vector donde se almacenan los valores en una primera instancia
    int lon = 0;   //longitud del conjutno

    printf("Numeros enteros sin repeticiones( . para terminar la carga)\n");

    while (lon < 10){
        //limita el ingreso a 10 valores

        printf("%d: ", lon+1);

        fflush(stdin);
        //valida que no se ingresen valores repetidos y que el conjunto no tenga menos de un elemento
        while ((strcmp(fgets(dato, 100, stdin), ".\n") != 0) && (!esEntero(dato) 
                || repeticionesEjercicio7(valores, atoi(dato), lon))){

            printf("Error. Ingrese un valor valido\n");
            printf("%d: ", lon+1);
            fflush(stdin);
        }
        
        if (strcmp(dato, ".\n") == 0 && lon < 2){
            //valida que el conjunto no tenga menos de 1 elemento antes de salir
            printf("Error. El conjunto debe tener 1 elemento como minimo\n");
        }
        else if(strcmp(dato, ".\n") == 0){
            //utiliza "." para finalizar la carga
            break;
        }
        else {
            //agrega los valores al arreglo y aumenta la longitud del conjunto
            valores[lon] = atoi(dato);
            lon++;
        }
    }

    for (int i=0; i<lon; i++){
        //crea el conjunto con los valores introducidos en el vector
        cto_agregar(c, te_crear(valores[i]));
    }

    return c;
}

void cargaEjercicio7(){

    printf("Ingrese los valores del primer conjunto (minimo 1 elemento, maximo 10 elementos)\n");
    Conjunto A = cargaConjuntos7();

    printf("Ingrese los valores del segundo conjunto (minimo 1 elemento, maximo 10 elementos)\n");
    Conjunto B = cargaConjuntos7();

    printf("Ingrese los valores del tercer conjunto (minimo 1 elemento, maximo 10 elementos)\n");
    Conjunto C = cargaConjuntos7();

    c_ej7_subconjtotalparcial(A, B, C);
}

void c_ej7_subconjtotalparcial(Conjunto A, Conjunto B, Conjunto C){

    int inter;   //cantidad de elementos de la interseccion de dos conjuntos
    Conjunto ctos[3] = {A, B, C};   //arreglo que almacena todos los conjuntos para procesarlos por indices
    char nombreCtos[3] = {'A', 'B', 'C'};   //arreglo de char que almacena las etiquetas de los conjuntos
    int lon = sizeof(ctos) / sizeof(ctos[0]);   //cantidad de elementos de los arreglos
    int i;

    printf("\n");
    for (i=0; i<lon; i++){
        printf("Conjunto %d\n", i+1);
        cto_mostrar(ctos[i]);
        printf("\n");
    }

    //ciclo anidado que compara todos los elementos entre si
    for (i=0; i<lon-1; i++){
        for (int j=i+1; j<lon; j++){

            //guarda la cantidad de elementos de la interseccion en cada comparacion
            inter = cto_cantidad_elementos(cto_interseccion(ctos[i], ctos[j]));

            //compara la cantidad de elementos de la interseccion con la cantidad de los conjuntos procesados
            //plantea una condicion para cada posibilidad de subconjunto parcial/total entre ambos conjuntos
            if (inter == cto_cantidad_elementos(ctos[i])){
                printf("%c es subconjunto total de %c\n", nombreCtos[i], nombreCtos[j]);
            }
            else if (inter >= (float)cto_cantidad_elementos(ctos[i])/2){
                printf("%c es subconjunto parcial de %c\n", nombreCtos[i], nombreCtos[j]);
            }
            if (inter == cto_cantidad_elementos(ctos[j])){
                printf("%c es subconjunto total de %c\n", nombreCtos[j], nombreCtos[i]);
            }
            else if (inter >= (float)cto_cantidad_elementos(ctos[j])/2){
                printf("%c es subconjunto parcial de %c\n", nombreCtos[j], nombreCtos[i]);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 8------------------------------------------------
//-------------------------------------------------------------------------------------------------------

bool c_ej8_soniguales(Conjunto A, Conjunto B) {
    int cantidadA = cto_cantidad_elementos(A);
    int cantidadB = cto_cantidad_elementos(B);

    if (cantidadA != cantidadB) return false;

    for (int i = 1; i <= cantidadA; i++) {
        TipoElemento elem = cto_recuperar(A, i);
        if (!cto_pertenece(B, elem->clave)) {
            return false;
        }
    }
    return true;
}

void cargar_conjunto(Conjunto c, int cantidad, int aleatorio) {
    int clave;
    if (aleatorio == 1) {
        for (int i = 0; i < cantidad; i++) {
            clave = rand() % 100 + 1;
            cto_agregar(c, te_crear(clave));
        }
    } else {
        for (int i = 0; i < cantidad; i++) {
            printf("Ingrese clave para el elemento %d: ", i + 1);
            scanf("%d", &clave);
            cto_agregar(c, te_crear(clave));
        }
    }
}

void ejer8() {
    srand((unsigned)time(NULL));
    int cantidadA, cantidadB, modo;
    Conjunto A, B;

    do {
        printf("Cantidad de elementos para el conjunto A: ");
        scanf("%d", &cantidadA);
        printf("Cantidad de elementos para el conjunto B: ");
        scanf("%d", &cantidadB);
        if (cantidadA != cantidadB || cantidadA <= 0) {
            printf("Las cantidades deben ser iguales y mayores a 0. Intente nuevamente.\n");
        }
    } while (cantidadA != cantidadB || cantidadA <= 0);

    A = cto_crear();
    B = cto_crear();

    do {
        printf("Carga aleatoria (1) o manual (2) para A?: ");
        scanf("%d", &modo);
        if (modo != 1 && modo != 2) {
            printf("Opcion invalida. Ingrese 1 para aleatorio o 2 para manual.\n");
        }
    } while (modo != 1 && modo != 2);
    cargar_conjunto(A, cantidadA, modo);

    do {
        printf("Carga aleatoria (1) o manual (2) para B?: ");
        scanf("%d", &modo);
        if (modo != 1 && modo != 2) {
            printf("Opcion invalida. Ingrese 1 para aleatorio o 2 para manual.\n");
        }
    } while (modo != 1 && modo != 2);
    cargar_conjunto(B, cantidadB, modo);

    printf("Conjunto A: ");
    cto_mostrar(A);
    printf("Conjunto B: ");
    cto_mostrar(B);

    if (c_ej8_soniguales(A, B)) {
        printf("Los conjuntos son iguales.\n");
    } else {
        printf("Los conjuntos NO son iguales.\n");
    }
    printf("Complejidad: O(n^2)\n");
    getchar();
}