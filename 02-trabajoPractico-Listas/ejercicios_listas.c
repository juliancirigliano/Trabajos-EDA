#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include "tp_2_listas.h"
#include "funciones_propias_listas.h"
#include "../libs/validaciones/headers/validaciones.h"
#include "../libs/tipoElemento/headers/tipo_elemento.h"
#include "../libs/listas/headers/listas.h"

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 2------------------------------------------------
//-------------------------------------------------------------------------------------------------------

// Función que devuelve los elementos de L1 que no están en L2 (punto a y b)
Lista verElementosQueNoSeRepiten(Lista l1, Lista l2) {
    Lista resultado = l_crear();   // Crea una nueva lista para almacenar el resultado
    Iterador it = iterador(l1);    // Crea un iterador sobre L1
    while (hay_siguiente(it)) { 
        TipoElemento elem = siguiente(it);  // Recorre la lista obteniendo los elementos mientras existan
        if (!l_buscar(l2, elem->clave)) {   
            l_agregar(resultado, te_crear(elem->clave));  // Si el elemento no está en L2 lo agrega
        }
    }
    return resultado;
}

// Función que devuelve los elementos comunes entre L1 y L2 (punto c)
Lista verElementosRepetidos(Lista l1, Lista l2) {
    Lista resultado = l_crear();  
    Iterador it = iterador(l1);
    while (hay_siguiente(it)) {
        TipoElemento elem = siguiente(it);
        if (l_buscar(l2, elem->clave) && !l_buscar(resultado, elem->clave)) {
            l_agregar(resultado, te_crear(elem->clave)); // Si el elemento coincide lo agrega
        }
    }
    return resultado;
}

// Función para calcular el promedio de los valores en una lista (punto d)
float promedio(Lista l) {
    Iterador it = iterador(l); 
    int suma = 0, cantidad = 0;   // Variables para la suma y la cantidad de elementos
    while (hay_siguiente(it)) {
        TipoElemento elem = siguiente(it);
        suma += elem->clave;     // Suma el valor del elemento
        cantidad++;              // Aumenta el contador de elementos
    }
    if (cantidad == 0) return 0;
    return (float)suma / cantidad;   // Calcula y retorna el promedio
}

// Función para obtener los valores mínimos y sus posiciones en L1 y L2 (punto e)
ResultadoValorMinimo valorMinimo(Lista l1, Lista l2) {
    ResultadoValorMinimo res;     // Almacena el resultado
    res.valor = INT_MAX;
    res.pos = -1;
    res.valor_2 = INT_MAX;
    res.pos_2 = -1;               // Inicializacion de valores y posiciones

    Iterador it = iterador(l1);   // Crea un iterador sobre L1
    int i = 1;                    // Inicializa el contador de posiciones para L1
    while (hay_siguiente(it)) {
        TipoElemento elem = siguiente(it);
        if (elem->clave < res.valor) {
            res.valor = elem->clave;
            res.pos = i;          // Actualiza el valor y las posiciones
        }
        i++;
    }

    it = iterador(l2);
    i = 1;
    while (hay_siguiente(it)) {
        TipoElemento elem = siguiente(it);
        if (elem->clave < res.valor_2) {
            res.valor_2 = elem->clave;
            res.pos_2 = i;
        }
        i++;
    }

    return res;                // Retorna el resultado obtenido de ambas listas
}

// Función para ingresar un número entero con validación
int ingresarEnteroValidado(const char* mensaje) {
    char entrada[100];     // Almacena la entrada del usuario
    int valor;             // Almacena el valor convertido

    while (1) {           // Bucle que se repite hasta que el usuario ingrese un valor valido
        printf("%s", mensaje);
        fgets(entrada, sizeof(entrada), stdin);
        if (esEntero(entrada)) {
            valor = atoi(entrada);
            return valor;
        } else {
            printf("Entrada inválida. Ingrese un número entero válido.\n");
        }
    }
}

// Función para cargar las listas y resolver el ejercicio
void cargarListasYResolverPunto2() {
    Lista l1 = l_crear();
    Lista l2 = l_crear();
    int cantidad, valor; // Variables para almacenar la cantidad de elementos y los valores a ingresar

    printf("\nCarga de Lista L1\n");
    cantidad = ingresarEnteroValidado("Ingrese la cantidad de elementos para L1 (máximo 100): ");
    for (int i = 0; i < cantidad; i++) {  // Bucle para cargar los elementos en L1
        char msg[50];
        sprintf(msg, "Ingrese el elemento %d para L1: ", i + 1);
        valor = ingresarEnteroValidado(msg);
        l_agregar(l1, te_crear(valor));
    }

    printf("\nCarga de Lista L2\n");
    cantidad = ingresarEnteroValidado("Ingrese la cantidad de elementos para L2 (máximo 100): ");
    for (int i = 0; i < cantidad; i++) {  // Bucle para cargar los elementos en L2
        char msg[50];
        sprintf(msg, "Ingrese el elemento %d para L2: ", i + 1);
        valor = ingresarEnteroValidado(msg);
        l_agregar(l2, te_crear(valor));
    }

    // Mostrar listas cargadas
    printf("\n--- Listas cargadas ---\n");
    printf("L1 → ");
    l_mostrar(l1);
    printf("L2 → ");
    l_mostrar(l2);

    // Punto a
    printf("\nL1 (elementos que no estan en L2) → ");
    l_mostrar(verElementosQueNoSeRepiten(l1, l2));

    // Punto b
    printf("L2 (elementos que no estan en L1) → ");
    l_mostrar(verElementosQueNoSeRepiten(l2, l1));

    // Punto c
    printf("Elementos comunes entre L1 y L2 → ");
    l_mostrar(verElementosRepetidos(l1, l2));

    // Punto d
    printf("\nPromedio de L1: %.2f\n", promedio(l1));
    printf("Promedio de L2: %.2f\n", promedio(l2));

    // Punto e
    ResultadoValorMinimo min = valorMinimo(l1, l2);
    printf("\nValor minimo en L1: %d (posicion %d)\n", min.valor, min.pos);
    printf("Valor minimo en L2: %d (posicion %d)\n", min.valor_2, min.pos_2);
}


//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 3------------------------------------------------
//-------------------------------------------------------------------------------------------------------

// Función que determina si L2 es múltiplo de L1 y, si es así, calcula el escalar
ResultadosMul multiplo(Lista l1, Lista l2) {
    ResultadosMul res;       // Estructura para almacenar los resultados
    res.esMultiplo = true;   // Asumimos inicialmente que L2 es múltiplo de L1
    res.escalar = true;      // Asumimos inicialmente que L2 tiene un escalar
    res.numEscalar = 0;      // Inicializamos el valor del escalar a 0

    Iterador it1 = iterador(l1);  // Iterador para L1
    Iterador it2 = iterador(l2);  // Iterador para L2
    int i = 1;                    // Contador para las posiciones

    while (hay_siguiente(it1) && hay_siguiente(it2)) {  // Mientras haya elementos en ambas listas
        TipoElemento elem1 = siguiente(it1);  // Obtiene el siguiente elemento de L1
        TipoElemento elem2 = siguiente(it2);  // Obtiene el siguiente elemento de L2

        if (elem1->clave == 0 || elem2->clave % elem1->clave != 0) {  // Si L1 tiene un valor 0 o L2 no es múltiplo exacto de L1
            res.esMultiplo = false;  // Marca que no es multiplo
            break;  // Salimos del bucle ya que no es multiplo
        }

        // Si es múltiplo, verificamos el escalar
        if (res.escalar) {
            int escalar = elem2->clave / elem1->clave;  // Calcula el escalar
            if (res.numEscalar == 0) {  // Si no hemos encontrado un escalar aun, lo guardamos
                res.numEscalar = escalar;
            } else if (res.numEscalar != escalar) {  
                res.escalar = false;  // Si cambia en alguna pos, no es escalar, salimos del bucle
                break;  
            }
        }
        i++;  // Aumenta la posición
    }

    return res;  // Retorna los resultados
}

// Función para mostrar los resultados
void mostrarResultadoMultiplo(ResultadosMul res) {
    if (res.esMultiplo) {
        printf("L2 es multiplo de L1\n");
        if (res.escalar) {
            printf("L2 es multiplo de L1 por un escalar: %d\n", res.numEscalar);
        } else {
            printf("L2 es multiplo de L1 pero no tiene un escalar constante.\n");
        }
    } else {
        printf("L2 no es multiplo de L1.\n");
    }
}

// Función para ingresar un entero validado
int ingresarEnteroVal(const char* mensaje) {
    char entrada[100];
    int valor;

    while (1) {
        printf("%s", mensaje);
        fgets(entrada, sizeof(entrada), stdin);  // Leemos la entrada del usuario
        if (esEntero(entrada)) {  // Encargado de la validacion
            valor = atoi(entrada);  
            return valor;
        } else {
            printf("Entrada inválida. Ingrese un número entero válido.\n");  
        }
    }
}

// Función principal del ejercicio
void cargarListasYResolverMultiplo() {
    Lista l1 = l_crear();  
    Lista l2 = l_crear();  
    int cantidad, valor;   // Variables para almacenar la cantidad de elementos y los valores a ingresar

    // Pedimos una única vez la cantidad de elementos para ambas listas
    printf("\nCarga de Listas\n");
    cantidad = ingresarEnteroVal("Ingrese la cantidad de elementos para ambas listas (máximo 100): ");

    // Carga de la lista L1
    printf("\nCarga de Lista L1\n");
    for (int i = 0; i < cantidad; i++) {  // Bucle para cargar los elementos en L1
        char mensaje[50];
        do {
            sprintf(mensaje, "Ingrese el elemento %d para L1 (no puede ser 0): ", i + 1);  // Mensaje personalizado
            valor = ingresarEnteroVal(mensaje);  // Pide al usuario el valor
            if (valor == 0) {
                printf("El número 0 no está permitido. Intente nuevamente.\n");  // Validación de cero
            }
        } while (valor == 0);  // Repite mientras el valor sea inválido
        l_agregar(l1, te_crear(valor));  // Agrega el valor a la lista L1
    }

    // Carga de la lista L2
    printf("\nCarga de Lista L2\n");
    for (int i = 0; i < cantidad; i++) {  // Bucle para cargar los elementos en L2
        char mensaje2[50];
        do {
            sprintf(mensaje2, "Ingrese el elemento %d para L2 (no puede ser 0): ", i + 1);  // Mensaje personalizado
            valor = ingresarEnteroVal(mensaje2);  
            if (valor == 0) {
                printf("El número 0 no está permitido. Intente nuevamente.\n");  // Validación de cero
            }
        } while (valor == 0);  // Repite mientras el valor sea inválido
        l_agregar(l2, te_crear(valor));  // Agrega el valor a la lista L2
    }

    // Mostrar las listas cargadas
    printf("\n- Listas cargadas -\n");
    printf("L1 → ");
    l_mostrar(l1);  // Muestra la lista L1
    printf("L2 → ");
    l_mostrar(l2);  // Muestra la lista L2

    // Verifica si L2 es múltiplo de L1
    ResultadosMul resultado = multiplo(l1, l2);

    // Mostrar el resultado
    mostrarResultadoMultiplo(resultado);
}


//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 4------------------------------------------------
//-------------------------------------------------------------------------------------------------------

void resultadoListasMayorMenor(Lista l1, Lista l2){
    //llama a la comparacion y muestra el resultado

    system("cls");

    printf("LISTAS:\n");
    l_mostrar(l1);
    l_mostrar(l2);

    int resu = CompararListas(l1, l2);

    printf("\n");
    if (resu == 1){
        printf("L1 > L2");
    }
    else if (resu == 2){
        printf("L2 > L1");
    }
    else {
        printf("L1 = L2");
    }
    printf("\nComplejidad algoritmica lineal O(n), donde n es el tamanio de las listas");

}

void cargaMayorMenorManual(int lon){
    //carga manualmente las listas y llama a la funcion resultado

    Lista l1 = l_crear();
    Lista l2 = l_crear();

    int i;

    char dato[100];   //buffer de entrada

    printf("\nIngrese los valores de la primera lista (numeros enteros)\n");

    for (i=0; i<lon; i++){

        printf("%d: ", i+1);

        fflush(stdin);
        while(!esEntero(fgets(dato, 100, stdin))){
            printf("Error. Ingrese un valor valido (numero entero)");
            printf("\n%d: ", i+1);
            fflush(stdin);
        }

        l_agregar(l1, te_crear(atoi(dato)));

    }

    printf("\nIngrese los valores de la segunda lista (numeros enteros)\n");

    for (i=0; i<lon; i++){

        printf("%d: ", i+1);

        fflush(stdin);
        while(!esEntero(fgets(dato, 100, stdin))){
            printf("Error. Ingrese un valor valido (numero entero)");
            printf("\n%d: ", i+1);
            fflush(stdin);
        }

        l_agregar(l2, te_crear(atoi(dato)));

    }

    resultadoListasMayorMenor(l1, l2);
}

void cargaMayorMenorAleatoria(int lon){
    //carga aleatoriamente las listas y llama a la funcion resultado

    Lista l1 = l_crear();
    Lista l2 = l_crear();

    srand(time(NULL));

    for (int i=0; i<lon; i++){

        l_agregar(l1, te_crear((rand() % 21) -10));
        l_agregar(l2, te_crear((rand() % 21) -10));

    }

    resultadoListasMayorMenor(l1,l2);
}

void cargarListasMayorMenor(){

    char dato[100];   //buffer de entrada

    printf("Ingrese el tamanio de las listas (numero entero entre 1 y 10): ");

    fflush(stdin);
    while(!esEnteroPositivo(fgets(dato, 100, stdin)) || atoi(dato) > 10){
        printf("Error. Ingrese un numero valido (entero entre 1 y 10): ");
        fflush(stdin);
    }

    int longListas = atoi(dato);   //define el tamanio de las listas

    printf("\n1. Carga manual\n2. Carga aleatoria\nOpcion: ");
    
    fflush(stdin);
    while(!esEntero(fgets(dato, 100, stdin))  || (atoi(dato) != 1 && atoi(dato) != 2)){
        printf("Error. Ingrese una opcion valida: ");
        fflush(stdin);
    }

    int opcion = atoi(dato);

    switch(opcion){
        case 1: cargaMayorMenorManual(longListas);
            break;
        case 2: cargaMayorMenorAleatoria(longListas);
            break;
    }
}

int CompararListas(Lista l1, Lista l2){

    Iterador iter1 = iterador(l1);
    Iterador iter2 = iterador(l2);

    //elementos a comparar claves
    TipoElemento elem1;
    TipoElemento elem2;

    int resuComp = 0;   //resultado de las comparaciones

    while (hay_siguiente(iter1)){

        elem1 = siguiente(iter1);
        elem2 = siguiente(iter2);

        //si elem1 es mayor aumenta en 1 el resultado
        if (elem1->clave > elem2->clave){
            resuComp++;
        }

        //si elem2 es mayor decrementa en 1 el resultado
        else if (elem1->clave < elem2->clave){
            resuComp--;
        }

    }

    //si el resutltado es positivo lo cambia a 1
    if (resuComp > 0){
        resuComp = 1;
    }
    //si el resultado es negativo lo cambia a 2
    else if (resuComp < 0){
        resuComp = 2;
    }

    return resuComp;

}

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 5------------------------------------------------
//-------------------------------------------------------------------------------------------------------

void hacerPolinomio(Lista list) {
    int exponente;
    float* coef;
    char continuar;
    char dato[100];

    do {
        coef = malloc(sizeof(float));
        if (coef == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria.\n");
            exit(EXIT_FAILURE);
        }

        printf("Ingrese el exponente (entero mayor o igual a 0): ");

        fflush(stdin);
        while(!esEnteroNoNegativo(fgets(dato, 100, stdin))){
            printf("Error. exponente invalido\n");
             printf("Ingrese el exponente (entero mayor o igual a 0): ");
            fflush(stdin);
        }

        exponente = atoi(dato);

        printf("Ingrese el coeficiente: ");

        fflush(stdin);
        while(!esNumerico(fgets(dato, 100, stdin))){
            printf("Error. Coeficiente invalido\n");
            printf("Ingrese el coeficiente: ");
            fflush(stdin);
        }

        *coef = atof(dato);

        TipoElemento te = te_crear_con_valor(exponente, coef);
        l_agregar(list, te);

        do {
            printf("¿Desea agregar otro término? (s/n): ");
            scanf(" %c", &continuar);
            while (getchar() != '\n'); 
            if (continuar != 's' && continuar != 'S' && continuar != 'n' && continuar != 'N') {
                printf("Error: Respuesta inválida. Por favor, ingrese 's' para sí o 'n' para no.\n");
            }
        } while (continuar != 's' && continuar != 'S' && continuar != 'n' && continuar != 'N');

    } while (continuar == 's' || continuar == 'S');
}


float evaluarPolinomio(Lista list, float x) {
    float resultado = 0.0;
    Iterador it = iterador(list);

    while (hay_siguiente(it)) {
        TipoElemento te = siguiente(it);
        int exponente = te->clave;
        float coeficiente = *((float*)te->valor);
        resultado += coeficiente * powf(x, exponente);
    }

    return resultado;
}


Lista calcularRango(Lista list, double x_min, double x_max, double incremento) {
    if (incremento <= 0.0) {
        fprintf(stderr, "Error: el incremento debe ser mayor que 0.\n");
        return NULL;
    }

    if (x_max < x_min) {
        fprintf(stderr, "Error: x_max debe ser mayor o igual a x_min.\n");
        return NULL;
    }

    Lista resultados = l_crear();
    int idx = 0;

    int steps = (int)((x_max - x_min) / incremento) + 1;
    for (int i = 0; i < steps; i++) {
        double x = x_min + i * incremento;
        float* fx = malloc(sizeof(float));
        if (fx == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria.\n");
            exit(EXIT_FAILURE);
        }
        *fx = evaluarPolinomio(list, (float)x);

        TipoElemento te = te_crear_con_valor(idx++, fx);
        l_agregar(resultados, te);
    }

    return resultados;
}



void mostrarResultados(Lista resultados, double x_min, double incremento) {
    if (resultados == NULL) {
        fprintf(stderr, "Error: la lista de resultados es NULL.\n");
        return;
    }

    Iterador it = iterador(resultados);
    if (it == NULL) {
        fprintf(stderr, "Error: no se pudo crear el iterador.\n");
        return;
    }

    int i = 0;
    while (hay_siguiente(it)) {
        TipoElemento te = siguiente(it);
        if (te->valor == NULL) {
            fprintf(stderr, "Advertencia: valor nulo encontrado.\n");
            continue;
        }

        float fx = *((float*)te->valor);
        double x = x_min + i * incremento;
        printf("F(%.2f) = %.2f\n", x, fx);

        i++;
    }
}

void ejercicio5() {
    Lista polinomio = l_crear();
    

    printf("=== Crear Polinomio ===\n");
    hacerPolinomio(polinomio);

    char dato[100];
    float x;
    printf("\nIngrese un valor de x para evaluar el polinomio: ");
    fflush(stdin);
    while(!esNumerico(fgets(dato, 100, stdin))){
        printf("Valor invalido\nIngrese un valor de x para evaluar el polinomio: ");
        fflush(stdin);
    }
    x = atof(dato);

    printf("F(%.2f) = %.2f\n", x, evaluarPolinomio(polinomio, x));

    double xmin, xmax, paso;
    printf("\nIngrese el valor minimo de x: ");
    fflush(stdin);
    while(!esNumerico(fgets(dato, 100, stdin))){
        printf("Valor invalido\nIngrese el valor minimo de x: ");
        fflush(stdin);
    }
    xmin = atof(dato);


    printf("Ingrese el valor maximo de x: ");
    fflush(stdin);
    while(!esNumerico(fgets(dato, 100, stdin))){
        printf("Valor invalido\nIngrese el valor maximo de x: ");
        fflush(stdin);
    }
    xmax = atof(dato);    


    do {
        printf("Ingrese el incremento (mayor a 0): ");
        
        while(!esRealNoNegativo(fgets(dato, 100, stdin))){
            printf("Error. Valor invalido. Ingrese el incremento (mayor a 0): ");
            fflush(stdin);
        }
        paso = atof(dato);

    } while (paso <= 0);


    Lista resultados = calcularRango(polinomio, xmin, xmax, paso);
    printf("\n=== Valores de F(x) en el rango ===\n");
    mostrarResultados(resultados, xmin, paso);

    printf("\nPresione ENTER para salir...");
    getchar();

}

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 6------------------------------------------------
//-------------------------------------------------------------------------------------------------------

bool esSublista(Lista l1, Lista l2) {
    Iterador it2 = iterador(l2);             //Se crea un iterador que recorre la lista 2
    while (hay_siguiente(it2)) {
        TipoElemento elem = siguiente(it2);  //Si hay elementos en la lista 2, se obtiene el siguiente 
        TipoElemento encontrado = l_buscar(l1, elem->clave); //Se busca el elemento de la lista 1 por su clave
        if (encontrado == NULL) {            
            return false;                //Si no se encuentra, no es sublista
        }
    }
    return true;                         //Si se encontraron todos los elementos de la lista 2, es sublista
}

int leerEntero(const char* mensaje, int min, int max) {   //Funcion que lee los enteros y los valida
    char ingreso[100];      //Variable que almacena la entrada como cadena
    int num;                //Variable que almacena el numero ya convertido
    while (1) {
        printf("%s", mensaje);
        fgets(ingreso, sizeof(ingreso), stdin);   //Bucle que pide y lee la entrada al usuario

        ingreso[strcspn(ingreso, "\n")] = 0;      //Elimina saltos de linea

        if (esEntero(ingreso)) {
            num = atoi(ingreso);
            if (num >= min && num <= max) {
                return num;
            }                                     //Valida que el numero sea entero (positivo o negativo)
        }

        printf("Entrada inválida. Ingrese un número entre %d y %d.\n", min, max);
    }
}

void cargarLista(Lista lista, int cantidad) { // Función que carga una lista con una cantidad específica de elementos
    for (int i = 0; i < cantidad; i++) {
        int valor = leerEntero("Ingrese un número entero (positivo o negativo): ", -1000000, 1000000);
        TipoElemento elem = te_crear(valor); // Crea un nuevo elemento con el valor obtenido
        l_agregar(lista, elem);              // Agrega el nuevo elemento a la lista
    }
}

void cargarYProcesarSublista() {     //Funcion final que carga datos, valida y verifica si es sublista

    printf("CARGA DE LISTA 1\n"); //Solicita al usuario la cantidad de elementos para la lista 1
    int cant1 = leerEntero("Ingrese cantidad de elementos de L1 (entre 1 y 100): ", 1, 100);

    Lista l1 = l_crear();      //Crea una lista vacía para L1
    cargarLista(l1, cant1);    //Llama a cargarLista para agregar los elementos a L1

    printf("\nCARGA DE LISTA 2\n");
    int cant2 = leerEntero("Ingrese cantidad de elementos de L2 (entre 1 y 100): ", 1, 100);

    Lista l2 = l_crear();
    cargarLista(l2, cant2);

    printf("\nLista 1: ");    //Muestra el contenido de ambas listas
    l_mostrar(l1);
    printf("Lista 2: ");
    l_mostrar(l2);

    if (esSublista(l1, l2)) {   //Verifica si L2 es sublista de L1 y muestra el resultado
        printf("\n L2 es sublista de L1.\n");
    } else {
        printf("\n L2 NO es sublista de L1.\n");
    }
}
