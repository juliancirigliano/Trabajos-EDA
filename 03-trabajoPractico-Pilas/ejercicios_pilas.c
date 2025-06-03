#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include "tp_pilas.h"
#include "funciones_propias_pilas.h"
#include "../libs/validaciones/headers/validaciones.h"
#include "../libs/tipoElemento/headers/tipo_elemento.h"
#include "../libs/pilas/headers/pilas.h"

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 2------------------------------------------------
//-------------------------------------------------------------------------------------------------------

#define MAX_VALOR 100
#define MAX_TAM_PILA 10

// Verifica si existe un elemento con una clave específica en la pila
bool p_ej2_existeclave(Pila p, int clave) {
    bool existe = false;
    Pila aux = p_crear();       // Se crea pila auxiliar para conservar los elementos
    TipoElemento te;

    while (!p_es_vacia(p)) {
        te = p_desapilar(p);    // Se desapila el elemento
        if (te->clave == clave) {
            existe = true;      // Si la clave coincide, se marca como encontrada
        }
        p_apilar(aux, te);      // Se guarda el elemento en la pila auxiliar
    }

    while (!p_es_vacia(aux)) {
        p_apilar(p, p_desapilar(aux));  // Se restauran los elementos a la pila original
    }
    return existe;
}

// Inserta un nuevo elemento en una posicion ordinal dada dentro de la pila
Pila p_ej2_colocarelemento(Pila p, int posicionordinal, TipoElemento x) {
    if (posicionordinal < 1 || posicionordinal > MAX_TAM_PILA + 1) return p; // Verifica si la posicion es válida

    Pila aux = p_crear();
    int contador = 1;
    TipoElemento te;

    while (!p_es_vacia(p)) {
        if (contador == posicionordinal) {
            p_apilar(aux, x);       // Inserta el nuevo elemento en la posicion indicada
        }
        p_apilar(aux, p_desapilar(p));   // Sigue apilando los demás elementos
        contador++;
    }
    if (contador <= posicionordinal) p_apilar(aux, x); // Si aun no se alcanzo la posicion, se inserta al final

    while (!p_es_vacia(aux)) {
        p_apilar(p, p_desapilar(aux)); // Se restaura la pila original
    }
    return p;
}

// Elimina la primera ocurrencia de una clave en la pila
Pila p_ej2_eliminarclave(Pila p, int clave) {
    Pila aux = p_crear();
    bool eliminado = false;
    TipoElemento te;

    while (!p_es_vacia(p)) {
        te = p_desapilar(p);
        if (te->clave == clave && !eliminado) {
            eliminado = true;       // Se marca como eliminado y se omite apilarlo
            continue;
        }
        p_apilar(aux, te);          // Se guarda el resto de elementos
    }

    while (!p_es_vacia(aux)) {
        p_apilar(p, p_desapilar(aux));  // Se restaura la pila sin el elemento eliminado
    }
    return p;
}

// Intercambia dos elementos de la pila según sus posiciones ordinales
Pila p_ej2_intercambiarposiciones(Pila p, int pos1, int pos2) {
    if (pos1 < 1 || pos2 < 1 || pos1 == pos2) return p;     // Verificacion de posiciones válidas

    Pila aux = p_crear();
    TipoElemento elementos[MAX_TAM_PILA + 1];
    int total = 0;

    while (!p_es_vacia(p)) {         // Se pasa el contenido de la pila a un arreglo
        elementos[total++] = p_desapilar(p);
    }

    if (pos1 > total || pos2 > total) {
        for (int i = total - 1; i >= 0; i--) p_apilar(p, elementos[i]); // Restaura pila si las posiciones no son validas
        return p;
    }

    TipoElemento temp = elementos[pos1 - 1];    // Intercambio de posiciones
    elementos[pos1 - 1] = elementos[pos2 - 1];
    elementos[pos2 - 1] = temp;

    for (int i = total - 1; i >= 0; i--) p_apilar(p, elementos[i]); // Se reconstruye la pila con los elementos intercambiados
    return p;
}

// Duplica cada elemento de la pila original
Pila p_ej2_duplicar(Pila p) {
    Pila aux = p_crear();
    TipoElemento elementos[MAX_TAM_PILA + 1];
    int total = 0;

    while (!p_es_vacia(p)) { // Se copia la pila en un arreglo para duplicar
        elementos[total++] = p_desapilar(p);
    }

    for (int i = total - 1; i >= 0; i--) { // Se apila cada elemento dos veces
        p_apilar(aux, elementos[i]);
        p_apilar(aux, elementos[i]);
    }
    return aux;
}

// Cuenta la cantidad de elementos en la pila
int p_ej2_cantidadelementos(Pila p) {
    Pila aux = p_crear();
    int cantidad = 0;
    TipoElemento te;

    while (!p_es_vacia(p)) {
        te = p_desapilar(p);
        cantidad++; // Incrementa contador por cada elemento
        p_apilar(aux, te); // Guarda el elemento en auxiliar
    }

    while (!p_es_vacia(aux)) {
        p_apilar(p, p_desapilar(aux)); // Restaura la pila original
    }
    return cantidad;
}

// Funcion principal para cargar y manipular una pila segun el usuario
void cargarPilaEj2() {
    Pila p = p_crear();
    char opcion[10];

    // Se solicita al usuario el tipo de carga: manual o aleatoria
    while (1) {
        printf("Seleccione tipo de carga (1=manual, 2=aleatoria): ");
        fgets(opcion, sizeof(opcion), stdin);
        if ((strlen(opcion) == 2 && (opcion[0] == '1' || opcion[0] == '2')) ||
            (strlen(opcion) == 1 && (opcion[0] == '1' || opcion[0] == '2'))) {
            break;
        } else {
            printf("Entrada invalida. Por favor ingrese 1 o 2.\n");
        }
    }

    char ingreso[100];
    int clave, pos;

    // Caso 2: carga aleatoria
    if (opcion[0] == '2') {
        srand(time(NULL));
        int cantidad = (rand() % MAX_TAM_PILA) + 1;
        printf("\nCantidad aleatoria de elementos: %d\n", cantidad);
        for (int i = 0; i < cantidad; i++) {
            int aleatorio = rand() % MAX_VALOR;
            p_apilar(p, te_crear(aleatorio)); // Se genera un elemento aleatorio
        }

        printf("\nPila generada aleatoriamente:\n");
        p_mostrar(p);

        // Buscar clave aleatoria
        int claveBusqueda = rand() % MAX_VALOR;
        bool existe = p_ej2_existeclave(p, claveBusqueda);
        printf("\n¿Existe la clave %d en la pila? %s\n", claveBusqueda, existe ? "Sí" : "No");

         // Insertar nuevo elemento en posicion aleatoria
        int totalAntes = p_ej2_cantidadelementos(p);
        int nuevaClave = rand() % MAX_VALOR;
        int posInsercion = (rand() % (totalAntes + 1)) + 1;
        if (posInsercion > totalAntes + 1) posInsercion = totalAntes + 1;
        p = p_ej2_colocarelemento(p, posInsercion, te_crear(nuevaClave));
        printf("\nPila tras insertar %d en posicion %d:\n", nuevaClave, posInsercion);
        p_mostrar(p);

        // Eliminar clave aleatoria
        int claveEliminar = rand() % MAX_VALOR;
        p = p_ej2_eliminarclave(p, claveEliminar);
        printf("\nPila tras eliminar clave %d:\n", claveEliminar);
        p_mostrar(p);

        // Intercambio de dos posiciones
        int totalActual = p_ej2_cantidadelementos(p);
        if (totalActual >= 2) {
            int pos1 = (rand() % totalActual) + 1;
            int pos2 = (rand() % totalActual) + 1;
            while (pos2 == pos1) pos2 = (rand() % totalActual) + 1;

            p = p_ej2_intercambiarposiciones(p, pos1, pos2);
            printf("\nPila tras intercambiar las posiciones %d y %d:\n", pos1, pos2);
            p_mostrar(p);
        } else {
            printf("\nNo se puede realizar intercambio: pila con menos de dos elementos.\n");
        }

        // Duplicación de pila
        printf("\nPila duplicada:\n");
        Pila duplicada = p_ej2_duplicar(p);
        p_mostrar(duplicada);

        int totalFinal = p_ej2_cantidadelementos(duplicada);
        printf("\nCantidad de elementos en la pila duplicada: %d\n", totalFinal);

        // Carga manual de elementos
    } else {
        printf("Ingrese cantidad de elementos: ");
        int cantidad;
        while (1) {
            fgets(ingreso, sizeof(ingreso), stdin);
            if (esEnteroPositivo(ingreso)) {
                cantidad = atoi(ingreso);
                if (cantidad <= MAX_TAM_PILA) break;
            }
            printf("Cantidad invalida. Ingrese un entero positivo (maximo %d): ", MAX_TAM_PILA);
        }

        for (int i = 0; i < cantidad; i++) {
            while (1) {
                printf("Elemento %d: ", i + 1);
                fgets(ingreso, sizeof(ingreso), stdin);
                if (esEntero(ingreso)) {
                    clave = atoi(ingreso);
                    p_apilar(p, te_crear(clave));
                    break;
                } else {
                    printf("Entrada invalida. Debe ingresar un numero entero.\n");
                }
            }
        }

        p_mostrar(p);

        while (1) {
            printf("\nIngrese clave a buscar: ");
            fgets(ingreso, sizeof(ingreso), stdin);
            if (esEntero(ingreso)) {
                clave = atoi(ingreso);
                printf("¿Existe? %s\n", p_ej2_existeclave(p, clave) ? "Sí" : "No");
                break;
            } else {
                printf("Entrada invalida. Debe ingresar un numero entero.\n");
            }
        }

        int longitud = p_ej2_cantidadelementos(p);
        while (1) {
            printf("\nIngrese posicion ordinal donde insertar nuevo elemento (1 a %d): ", longitud + 1);
            fgets(ingreso, sizeof(ingreso), stdin);
            if (esEnteroPositivo(ingreso)) {
                pos = atoi(ingreso);
                if (pos >= 1 && pos <= longitud + 1) break;
            }
            printf("Entrada invalida. Debe ingresar un numero entero positivo dentro del rango valido.\n");
        }

        while (1) {
            printf("Ingrese clave del nuevo elemento: ");
            fgets(ingreso, sizeof(ingreso), stdin);
            if (esEntero(ingreso)) {
                clave = atoi(ingreso);
                p = p_ej2_colocarelemento(p, pos, te_crear(clave));
                printf("\nPila tras insercion:\n");
                p_mostrar(p);
                break;
            } else {
                printf("Entrada invalida. Debe ingresar un numero entero.\n");
            }
        }

        while (1) {
            printf("\nIngrese clave a eliminar: ");
            fgets(ingreso, sizeof(ingreso), stdin);
            if (esEntero(ingreso)) {
                clave = atoi(ingreso);
                p = p_ej2_eliminarclave(p, clave);
                printf("\nPila tras eliminacion:\n");
                p_mostrar(p);
                break;
            } else {
                printf("Entrada invalida. Debe ingresar un numero entero.\n");
            }
        }

        int pos1 = -1, pos2 = -1;
        printf("\nIngrese dos posiciones a intercambiar (por ejemplo: 1 y 3):\n");
        while (1) {
            printf("Posición 1: ");
            fgets(ingreso, sizeof(ingreso), stdin);
            if (esEnteroPositivo(ingreso)) {
                pos1 = atoi(ingreso);
                break;
            } else {
                printf("Entrada invalida. Debe ingresar un numero entero positivo.\n");
            }
        }
        while (1) {
            printf("Posición 2: ");
            fgets(ingreso, sizeof(ingreso), stdin);
            if (esEnteroPositivo(ingreso)) {
                pos2 = atoi(ingreso);
                break;
            } else {
                printf("Entrada invalida. Debe ingresar un numero entero positivo.\n");
            }
        }
        p = p_ej2_intercambiarposiciones(p, pos1, pos2);
        printf("\nPila tras intercambio:\n");
        p_mostrar(p);

        printf("\nPila duplicada:\n");
        Pila duplicada = p_ej2_duplicar(p);
        p_mostrar(duplicada);

        printf("\nCantidad de elementos: %d\n", p_ej2_cantidadelementos(duplicada));
    }
}


//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 3------------------------------------------------
//-------------------------------------------------------------------------------------------------------

void mostrarResultadoEj3(Pila p1, Pila p2){
    //llama a la funcion principal y muestra el resultado

    //muestra el contenido de ambas pilas
    printf("\nPila 1: ");
    p_mostrar(p1);
    printf("Pila 2: ");
    p_mostrar(p2);
    
    //evalua con la funcion principal e imprime el resultado
    if (p_ej3_iguales(p1, p2)){
        printf("Las pilas son iguales\n");
    }
    else{
        printf("Las pilas son distintas\n");
    }

    printf("\nComplejidad algoritmica lineal (ciclos simples para cada pila que solo dependen de la cantidad de elementos)");
}

void cargaManualEj3(int n){

    Pila p1 = p_crear();
    Pila p2 = p_crear();
    char dato[100];   //buffer de entrada
    int i;

    printf("\nIngrese los valores de la primera pila (numeros enteros)\n");

    for(i=0; i<n; i++){

        printf("%d: ", i+1);
        //validacion de valores ingresados
        fflush(stdin);
        while(!esEntero(fgets(dato, 100, stdin))){
            printf("Error. Ingrese un valor valido (numero entero)");
            printf("\n%d: ", i+1);
            fflush(stdin);
        }

        //castea el buffer y guarda el dato en la pila
        p_apilar(p1, te_crear(atoi(dato)));
    }

    printf("Ingrese los valores de la segunda pila (numeros enteros)\n");

    for(i=0; i<n; i++){

        printf("%d: ", i+1);
        //validacion de valores ingresados
        fflush(stdin);
        while(!esEntero(fgets(dato, 100, stdin))){
            printf("Error. Ingrese un valor valido (numero entero)");
            printf("\n%d: ", i+1);
            fflush(stdin);
        }

        p_apilar(p2, te_crear(atoi(dato)));
    }

    mostrarResultadoEj3(p1, p2);
}

void cargaAleatoriaEj3(int n){

    Pila p1 = p_crear();
    Pila p2 = p_crear();
    srand(time(NULL));   //funcion aleatoria

    for (int i=0; i<n; i++){

        //genera un numero aleatorio entre -5 y 5 para cada valor de las pilas
        p_apilar(p1, te_crear((rand() % 11) - 5));
        p_apilar(p2, te_crear((rand() % 11) - 5));
    }

    mostrarResultadoEj3(p1, p2);
}

void cargarPilasEj3(){

    char dato[100];   //buffer de entrada

    printf("Ingrese el tamanio de las pilas (numero entero entre 1 y 5): ");

    //validacion de datos ingresados
    fflush(stdin);
    while(!esEnteroPositivo(fgets(dato, 100, stdin)) || atoi(dato) > 5){
        printf("Error. Ingrese un numero valido (entero entre 1 y 5): ");
        fflush(stdin);
    }

    int longPilas = atoi(dato);   //define el tamanio de las pilas

    printf("\n1. Carga manual\n2. Carga aleatoria\nOpcion: ");
    
    //validacion de datos ingresados
    fflush(stdin);
    while(!esEntero(fgets(dato, 100, stdin))  || (atoi(dato) != 1 && atoi(dato) != 2)){
        //mientras el valor no sea entero o sea distinto de 1 y 2
        printf("Error. Ingrese una opcion valida: ");
        fflush(stdin);
    }

    int opcion = atoi(dato);   //castea el valor del buffer

    switch(opcion){
        case 1: cargaManualEj3(longPilas);
            break;
        case 2: cargaAleatoriaEj3(longPilas);
            break;
    }
}

bool p_ej3_iguales(Pila p1, Pila p2){

    Pila pilaAux = p_crear();   //pila que guarda los valores de las pilas originales
    bool resu = true;   //variable retornada como resultado

    while(!p_es_vacia(p1)){

        //compara los valores de los elementos en cada tope
        if (p_tope(p1)->clave != p_tope(p2)->clave){
            resu = false;
        }

        //apila los topes de las pilas originales en la pila auxiliar
        p_apilar(pilaAux, p_desapilar(p1));
        p_apilar(pilaAux, p_desapilar(p2));
    }

    while(!p_es_vacia(pilaAux)){

        //desapila los valores de la pila auxiliar en orden y los devuelve a las pilas originales para no perderlas
        p_apilar(p2, p_desapilar(pilaAux));
        p_apilar(p1, p_desapilar(pilaAux));
    }

    return resu;
}

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 4------------------------------------------------
//-------------------------------------------------------------------------------------------------------

char* p_ej4_cambiarbase(int nrobasedecimal, int nrootrabase) {
    char digitos[] = "0123456789ABCDEF";
    Pila pila = p_crear();

    if (nrobasedecimal == 0) {
        char* resultado = malloc(2);
        strcpy(resultado, "0");
        return resultado;
    }

    int n = nrobasedecimal;
    int longitud = 0;

    while (n > 0) {
        int resto = n % nrootrabase;
        p_apilar(pila, te_crear(resto));
        n = n / nrootrabase;
        longitud++;
    }

    char* resultado = malloc(longitud + 1);
    int i = 0;
    while (!p_es_vacia(pila)) {
        TipoElemento te = p_desapilar(pila);
        resultado[i++] = digitos[te->clave];
    }
    resultado[i] = '\0';

    return resultado;
}

void Ejercicio4() {
    char entrada_numero[100], entrada_base[100], opcion[10];
    int numero, base;

    do {
        printf("Carga manual (1) - Carga aleatoria (2): ");
        fgets(opcion, sizeof(opcion), stdin);
        opcion[strcspn(opcion, "\n")] = 0;
        if (strcmp(opcion, "1") != 0 && strcmp(opcion, "2") != 0) {
            printf("Opcion invalida. Ingrese 1 o 2.\n");
        }
    } while (strcmp(opcion, "1") != 0 && strcmp(opcion, "2") != 0);

    if (strcmp(opcion, "2") == 0) {
        srand((unsigned int)time(NULL));
        numero = rand() % 1000;
        base = (rand() % 15) + 2;
        printf("Numero aleatorio generado: %d\n", numero);
        printf("Base aleatoria generada: %d\n", base);
    } else {
        printf("Ingrese un numero entero no negativo (maximo 1000): ");
        fgets(entrada_numero, sizeof(entrada_numero), stdin);
        entrada_numero[strcspn(entrada_numero, "\n")] = 0;

        while (!esEnteroNoNegativo(entrada_numero) || atoi(entrada_numero)>1000) {
            printf("Entrada invalida. Ingrese un numero entero no negativo: ");
            fgets(entrada_numero, sizeof(entrada_numero), stdin);
            entrada_numero[strcspn(entrada_numero, "\n")] = 0;
        }
        numero = atoi(entrada_numero);

        printf("Ingrese la base (2-16): ");
        fgets(entrada_base, sizeof(entrada_base), stdin);
        entrada_base[strcspn(entrada_base, "\n")] = 0;

        while (!esEntero(entrada_base) || (base = atoi(entrada_base)) < 2 || base > 16) {
            printf("Base no valida. Ingrese una base entre 2 y 16: ");
            fgets(entrada_base, sizeof(entrada_base), stdin);
            entrada_base[strcspn(entrada_base, "\n")] = 0;
        }
        base = atoi(entrada_base);
    }

    char* resultado = p_ej4_cambiarbase(numero, base);
    printf("El numero %d en base %d es: %s\n", numero, base, resultado);
    free(resultado);

    getchar();
}


//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 5------------------------------------------------
//-------------------------------------------------------------------------------------------------------

void mostrarResultadoEj5(Pila p){
    //llama a la funcion principal y muestra el resultado

    //muestra el contenido de la pila original
    printf("\nPila original: ");
    p_mostrar(p);
    
    //llama a la funcion principal y muestra el contenido de la pila resultado
    printf("Pila invertida: ");
    p_mostrar(p_ej5_invertir(p));

    printf("\nComplejidad algoritmica lineal (ciclos simples que solo dependen de la cantidad de elementos de la pila)");
}

void cargaManualEj5(int n){

    Pila p = p_crear();
    char dato[100];   //buffer de entrada

    printf("\nIngrese los valores de la pila (numeros enteros)\n");

    for(int i=0; i<n; i++){

        printf("%d: ", i+1);
        //validacion de valores ingresados
        fflush(stdin);
        while(!esEntero(fgets(dato, 100, stdin))){
            printf("Error. Ingrese un valor valido (numero entero)");
            printf("\n%d: ", i+1);
            fflush(stdin);
        }

        //castea el buffer y guarda el dato en la pila
        p_apilar(p, te_crear(atoi(dato)));
    }

    mostrarResultadoEj5(p);
}

void cargaAleatoriaEj5(int n){

    Pila p = p_crear();
    srand(time(NULL));   //funcion aleatoria

    for (int i=0; i<n; i++){

        //genera un numero aleatorio entre -5 y 5 para cada valor de la pila
        p_apilar(p, te_crear((rand() % 11) - 5));
    }

    mostrarResultadoEj5(p);
}

void cargarPilasEj5(){

    char dato[100];   //buffer de entrada

    printf("Ingrese el tamanio de la pila (numero entero entre 1 y 10): ");

    //validacion de datos ingresados
    fflush(stdin);
    while(!esEnteroPositivo(fgets(dato, 100, stdin)) || atoi(dato) > 10){
        printf("Error. Ingrese un numero valido (entero entre 1 y 10): ");
        fflush(stdin);
    }

    int longPilas = atoi(dato);   //define el tamanio de la pila

    printf("\n1. Carga manual\n2. Carga aleatoria\nOpcion: ");
    
    //validacion de datos ingresados
    fflush(stdin);
    while(!esEntero(fgets(dato, 100, stdin))  || (atoi(dato) != 1 && atoi(dato) != 2)){
        //mientras el valor no sea entero o sea distinto de 1 y 2
        printf("Error. Ingrese una opcion valida: ");
        fflush(stdin);
    }

    int opcion = atoi(dato);   //castea el valor del buffer

    switch(opcion){
        case 1: cargaManualEj5(longPilas);
            break;
        case 2: cargaAleatoriaEj5(longPilas);
            break;
    }
}

Pila  p_ej5_invertir(Pila p){

    Pila pAux = p_crear();   //pila que almacena temporalmente los valores de la original
    Pila resu = p_crear();   //pila que almacena los valores invertidos de la original y se retorna como resultado
    TipoElemento tAux;   //variable que guarda los valores del tope de la pila original

    while(!p_es_vacia(p)){

        //mientras la pila original no este vacia la desapila y guarda su tope en dos pilas iguales
        tAux = p_desapilar(p);
        p_apilar(resu, tAux);
        p_apilar(pAux, tAux);
    }

    while(!p_es_vacia(pAux)){

        //mientras la pila auxiliar no este vacia se desapila y apila sobre la pila original para no perderla
        p_apilar(p, p_desapilar(pAux));
    }

    return resu;
}

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 6------------------------------------------------
//-------------------------------------------------------------------------------------------------------

// Iterativa: elimina todas las ocurrencias de una clave sin perder la pila original
Pila p_ej6_eliminarclave_iterativo(Pila p, int clave) {
    Pila aux = p_crear();  // Pila auxiliar para invertir y luego restaurar
    Pila resultado = p_crear(); // Pila donde se guardan los elementos sin la clave
    TipoElemento te;

    // Se transfiere el contenido de la pila original a la auxiliar (se invierte el orden)
    while (!p_es_vacia(p)) {
        te = p_desapilar(p);
        p_apilar(aux, te);  // Guarda temporalmente los elementos para no perderlos
    }

    // Se recorre la auxiliar para construir y restaurar
    while (!p_es_vacia(aux)) {
        te = p_desapilar(aux);
        if (te->clave != clave) {
            p_apilar(resultado, te); // Solo se guarda en resultado si no coincide con la clave
        }
        p_apilar(p, te); // Siempre se restaura en la pila original
    }

    return resultado;
}

// Función auxiliar recursiva para eliminar claves
void eliminar_rec(Pila original, Pila resultado, int clave) {
    if (p_es_vacia(original)) return; // Caso base: pila vacia

    TipoElemento te = p_desapilar(original);    // Desapila un elemento
    eliminar_rec(original, resultado, clave);   // Llamada recursiva antes de procesar el elemento

    if (te->clave != clave) {                   // Si no coincide, se guarda
        p_apilar(resultado, te);
    }
    p_apilar(original, te);                     // Siempre se restaura la pila original
}

// Recursiva: elimina ocurrencias sin perder la pila original
Pila p_ej6_eliminarclave_recursivo(Pila p, int clave) {
    Pila resultado = p_crear();
    eliminar_rec(p, resultado, clave);  // Llama a la funcion recursiva
    return resultado;
}

// Funcion principal para eliminar clave (usando la version iterativa)
Pila p_ej6_eliminarclave(Pila p, int clave) {
    return p_ej6_eliminarclave_iterativo(p, clave);     
}

// Funcion de carga y ejecucion del ejercicio
void cargarPilaEj6() {
    Pila p = p_crear();       // Crea pila vacia
    char ingreso[100];
    char opcion[10];
    int clave;

    // Solicita tipo de carga
    while (1) {
        printf("Seleccione tipo de carga (1=manual, 2=aleatoria): ");
        fgets(opcion, sizeof(opcion), stdin);
        if ((strlen(opcion) == 2 && (opcion[0] == '1' || opcion[0] == '2')) ||
            (strlen(opcion) == 1 && (opcion[0] == '1' || opcion[0] == '2'))) {
            break;
        }
        printf("Entrada invalida. Por favor ingrese 1 o 2.\n");
    }

    if (opcion[0] == '2') {
        // Carga aleatoria
        srand(time(NULL));
        int cantidad = (rand() % MAX_TAM_PILA) + 1;
        printf("\nCantidad aleatoria de elementos: %d\n", cantidad);
        for (int i = 0; i < cantidad; i++) {
            int valor = rand() % MAX_VALOR;
            p_apilar(p, te_crear(valor));
        }

        printf("\nPila generada:\n");
        p_mostrar(p);

        clave = rand() % MAX_VALOR;
        printf("\nClave aleatoria a eliminar: %d\n", clave);

    } else {
        // Carga manual
        int cantidad;
        printf("Ingrese cantidad de elementos para la pila: ");
        while (1) {
            fgets(ingreso, sizeof(ingreso), stdin);
            if (esEnteroPositivo(ingreso)) {
                cantidad = atoi(ingreso);
                if (cantidad <= MAX_TAM_PILA) break;
            }
            printf("Cantidad invalida. Ingrese un entero positivo (maximo %d): ", MAX_TAM_PILA);
        }

        for (int i = 0; i < cantidad; i++) {
            while (1) {
                printf("Elemento %d: ", i + 1);
                fgets(ingreso, sizeof(ingreso), stdin);
                if (esEntero(ingreso)) {
                    int valor = atoi(ingreso);
                    p_apilar(p, te_crear(valor));
                    break;
                } else {
                    printf("Entrada invalida. Debe ingresar un numero entero.\n");
                }
            }
        }

        printf("\nPila generada:\n");
        p_mostrar(p);

        // Solicita la clave a eliminar
        while (1) {
            printf("\nIngrese la clave a eliminar: ");
            fgets(ingreso, sizeof(ingreso), stdin);
            if (esEntero(ingreso)) {
                clave = atoi(ingreso);
                break;
            } else {
                printf("Entrada invalida. Debe ingresar un numero entero.\n");
            }
        }
    }

    // Ejecuta funcion de eliminacion
    Pila nueva = p_ej6_eliminarclave(p, clave);

    printf("\nPila sin la clave %d:\n", clave);
    p_mostrar(nueva);

    printf("\nPila original restaurada:\n");
    p_mostrar(p);
}


//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 7------------------------------------------------
//-------------------------------------------------------------------------------------------------------

void ejercicio7(){
    char opcion; // Variable para almacenar la opción del usuario

    do { // Bucle para seguir mostrando el menú hasta que se presione 'q'
        system("@cls||clear"); // Limpia la pantalla de la consola
        printf("==== Ejercicio 7: Valores comunes entre dos pilas ====\n");
        printf("¿Como desea ingresar los datos?\n");
        printf("Manual (M)\n");
        printf("Aleatorio (A)\n");
        printf("Salir (Q)\n");
        printf("Ingrese su opcion: ");
        scanf(" %c", &opcion); // Lee la entrada de un carácter del usuario
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Consume los caracteres en el buffer
        opcion = tolower(opcion);

        switch (opcion) {
            case 'm':
                printf("\nHas elegido la opcion Manual.\n");
                ingresarDatosManuales();
                break;
            case 'a':
                printf("\nHas elegido la opcion Aleatorio.\n");
                generarDatosAleatorios();
                break;
            case 'q':
                printf("\nSaliendo del Ejercicio 7. ¡Hasta luego!\n");
                break;
            default:
                printf("\nOpcion no valida. Por favor, intente de nuevo.\n");
                break;
        }
        
        if (opcion != 'q') {
            printf("\nPresione Enter para continuar...\n");
            // Consume cualquier carácter de nueva línea restante del buffer de entrada
            while (getchar() != '\n'); 
            getchar(); 
        }

    } while (opcion != 'q');
}


void ingresarDatosManuales() {
    printf("\n--- Ingreso Manual de Datos ---\n");

    Pila P1 = p_crear();
    Pila P2 = p_crear();
    char input[100]; // Buffer para leer la entrada del usuario
    int valor;

    printf("Ingrese elementos para Pila 1 (ingrese 'fin' para terminar):\n");
    while (1) {
        printf("Elemento P1 (entero): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "fin") == 0 || strcmp(input, "FIN") == 0) {
            break; // Salir del bucle si el usuario ingresa 'fin'
        }

        if (esEntero(input)) { 
            valor = atoi(input);
            p_apilar(P1, te_crear(valor));
            printf("Elemento %d agregado a P1.\n", valor);
        } else {
            printf("Entrada no valida. Por favor, ingrese un numero entero o 'fin'.\n");
        }
    }

    printf("\nIngrese elementos para Pila 2 (ingrese 'fin' para terminar):\n");
    while (1) {
        printf("Elemento P2 (entero): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "fin") == 0 || strcmp(input, "FIN") == 0) {
            break;
        }

        if (esEntero(input)) {
            valor = atoi(input);
            p_apilar(P2, te_crear(valor));
            printf("Elemento %d agregado a P2.\n", valor);
        } else {
            printf("Entrada no valida. Por favor, ingrese un numero entero o 'fin'.\n");
        }
    }

    printf("\nLas pilas ingresadas son:\n");
    printf("Pila P1: ");
    p_mostrar(P1);
    printf("Pila P2: ");
    p_mostrar(P2);

    printf("\nLos elementos en comun son los siguientes:\n");
    Pila PR = p_ej7_elementoscomunes(P1, P2);
    p_mostrar(PR);
    printf("\nLa complejidad algoritmica es 0(N^2) porque hay anidado dos bucles que recorren cada uno los N elementos de la cola.\n");
}


void generarDatosAleatorios() {

    Pila P1 = p_crear();
    Pila P2 = p_crear();

    srand(time(NULL));
    for (int i=0; i<10; i++){
        p_apilar(P1, te_crear((rand() % (10 - 1 + 1)) + 1));
    }
    for (int i=0; i<10; i++){
        p_apilar(P2, te_crear((rand() % (10 - 1 + 1)) + 1));
    }

    p_mostrar(P1);
    p_mostrar(P2);

	printf("\nLos elementos en comun son los siguientes:\n");
	Pila PR = p_ej7_elementoscomunes(P1, P2);
	p_mostrar(PR);
	printf("\nLa complejidad algoritmica es 0(N^2) porque hay anidado dos bucles que recorren cada uno los N elementos de la cola.\n");
}
	
	
Pila p_ej7_elementoscomunes(Pila P1, Pila P2){
	Pila PR = p_crear();
	Pila P1_BUFF = p_crear();
	Pila P2_BUFF = p_crear();
	Pila PR_BUFF = p_crear();
	TipoElemento x;
	TipoElemento y;
	int cl;
	int parar; //bandera para detener la busqueda 
	int enPR = 1;  //bandera de seguimiento de PR (1 = estan en PR, 0 = estan en PR_BUFF)
	
	while(!p_es_vacia(P1)){
		x = p_desapilar(P1); 	//toma un elemento de la pila
		cl = x->clave; 			//copia su clave para usarla de criterio de busqueda
		p_apilar(P1_BUFF, x); 	//apila en P1_BUFF el elemento
		parar = 0;
		
		//Verifica que el elemento x no se haya apilado ya en PR
		//Para hacerlo mueve los elementos a PR_BUFF
		//Para evitar tener que volver a moverlos a PR, los deja ahí y 
		//luego se cambia la bandera enPR para que el siguiente bucle sepa donde almacenar
		//la proxima coincidencia
		if (enPR){
			while(!p_es_vacia(PR)){
				x = p_desapilar(PR);
				p_apilar(PR_BUFF, x);	//lo guarda en el buffer correspondiente
				if (cl == x->clave){
					parar = 1; //evita que entre al bucle siguiente ya que el elemento fue agregado previamente a PR
				}
			}
		}
		
		if (!enPR){
			while(!p_es_vacia(PR_BUFF)){
				x = p_desapilar(PR_BUFF);
				p_apilar(PR, x);
				if (cl == x->clave){
					parar = 1;
				}
			}
		}
		enPR = !enPR;
		
		
		while(!p_es_vacia(P2) && parar == 0){
			x = p_desapilar(P2);
			p_apilar(P2_BUFF, x);	//lo guarda en el buffer correspondiente
			if (cl == x->clave){
				y = te_crear(cl);
				if (enPR){
					p_apilar(PR, y); //agrega el elemento encontrado a la pila PR
				}else{
					p_apilar(PR_BUFF, y);}
				parar = 1;	//detiene la busqueda saliendo del bucle
			}
		}
		
		//devuelve todos los elementos del buffer a P2
		while(!p_es_vacia(P2_BUFF)){
			x = p_desapilar(P2_BUFF);
			p_apilar(P2, x);
			}
		}
	
	//devuelve todos los elementos del buffer a P1
	while(!p_es_vacia(P1_BUFF)){
		x = p_desapilar(P1_BUFF);
		p_apilar(P1, x);
	}
	if (enPR) {return PR;} else {return PR_BUFF;}
	
	}

 
Pila genAleatorioPilas(int n){
	srand(time(NULL));
	int min = 1;
    int max = 10;
    int r;
    Pila pila = p_crear();
    
    for (int i = 0; i < n; i++){
		r = (rand() % (max - min + 1)) + min; //valor aleatorio entre 1 y 10
		p_apilar(pila, te_crear(r));
	}
	
	return pila;
} 

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 8------------------------------------------------
//-------------------------------------------------------------------------------------------------------

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

void Punto_8(void){

    char dato[100];

	Pila pila_test, pila_exit;
	pila_test = p_crear();
	TipoElemento te;
	int resultado;
	printf("Ejercicio 8\n");
	printf("\n");
	int eleccion;
    int arreglo[10];
    int arreglo_test[] = {1,2,1,3,4,5,2,1,3,5,5};

	printf("Tipo de ingreso: (1) Manual, (2) Predefinido: ");

    fflush(stdin);
    while (!esEnteroNoNegativo(fgets(dato, 100, stdin)) || (atoi(dato) != 1 && atoi(dato) != 2)){
        printf("Error, ingrese valor valido\n");
        printf("Tipo de ingreso: (1) Manual, (2) Predefinido: ");
        fflush(stdin);
    }

    eleccion = atoi(dato);


	switch(eleccion){
		case 1:
			//int arreglo[10];
			for (int i = 0; i < 10; i++) {

				printf("Elemento %d: ", i + 1);
                fflush(stdin);
                while (!esEnteroNoNegativo(fgets(dato, 100, stdin))){
                    printf("Error. Ingrese dato valido (numero entero positivo)\n");
                    printf("Elemento %d: ", i + 1);
                    fflush(stdin);
                }

                p_apilar(pila_test, te_crear(atoi(dato)));

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
			for(int i = 0; i < 12; i++){
				te = te_crear(arreglo_test[i]);
				p_apilar(pila_test, te);	
			}
			printf("Pila inicial: \n");
			p_mostrar(pila_test);
			pila_exit = p_ej8_sacarrepetidos(pila_test);
			printf("Pila inicial (para verificar que no tuvo cambios) \n:");
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
