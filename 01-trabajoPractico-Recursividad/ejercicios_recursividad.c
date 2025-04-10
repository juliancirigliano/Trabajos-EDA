#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "tp_1_recursividad.h"
#include "funciones_propias_recursividad.h"
#include "../libs/validaciones/headers/validaciones.h"

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 1------------------------------------------------
//-------------------------------------------------------------------------------------------------------

bool palindromo (char * cadena) {               // Función recursiva para verificar si es palíndromo
    int longitud = strlen(cadena);              // Obtencion de la longitud de la cadena
    if (longitud <= 1) 
        return true;                            //Verifica que es palindromo en un caso base de que sea 1
    if (cadena[0] != cadena[longitud - 1]) 
        return false;                           //Si es distinta al principio y al final, no es palindromo
    cadena[longitud - 1] = '\0';                // Eliminamos el último carácter para continuar con la recursividad
    return palindromo(cadena + 1);              // Llamamos recursivamente desde el segundo carácter
}

char reemplazarTilde(unsigned char cadena) {    //Funcion que remplaza letras con tildes y ñ
    //Cadena de caracteres ASCII
    unsigned char acentuadas[] = {160, 193, 225, 130, 201, 233, 161, 205, 237, 162, 211, 243, 163, 218, 250, 164, 209, 241};
    //Remplazo de los caracteres ASCII
    char reemplazos[]  = {'a',  'a',  'a',  'e',  'e',  'e',  'i',  'i',  'i',  'o',  'o',  'o',  'u',  'u',  'u',  'n',  'n',  'n'};

    for (int i = 0; i < sizeof(acentuadas); i++) { //Recorre la cadena de caracteres
        if (cadena == acentuadas[i])
            return reemplazos[i];
    }

    return tolower(cadena); // Si no tiene tilde, pasarlo a minúscula
}

void limpiarCadena(char *cadenarecibida, char *cadenafinal) {  //Función para limpiar y validar la entrada
    int posfinal = 0;
    for (int i = 0; cadenarecibida[i] != '\0'; i++) {          //Recorre todos los caracteres
        unsigned char caracter = cadenarecibida[i];            //Captura el caracter actual
        if (!isspace(caracter)) {                              //Ignora los espacios
            cadenafinal[posfinal++] = reemplazarTilde(caracter); //Valida formato y tildes
        }
    }
    cadenafinal[posfinal] = '\0';
}


void cargarCadenaEj1() {    // Función que carga la cadena, valida y llama a la funcion palindromo
    char entrada[100];   // Guarda el ingreso
    char final[100];     // Guarda la cadena ya procesada

    while (1) {                       // Bucle infinito hasta que la entrada sea válida
        printf("Ingrese un palindromo: ");
        fgets(entrada, sizeof(entrada), stdin);
        size_t len = strlen(entrada); // Elimina el salto de línea
        if (len > 0 && entrada[len - 1] == '\n') {
            entrada[len - 1] = '\0';
        }

        int contieneCaracter = 0;    // Valida que la entrada no esté vacía o contenga solo espacios
        for (int i = 0; entrada[i] != '\0'; i++) {
            if (!isspace(entrada[i])) {
                contieneCaracter = 1;
                break;
            }
        }

        if (!contieneCaracter) {
            printf("Entrada no valida. No puede estar vacia o contener solo espacios.\n\n");
        } else {
            break;                  // Salimos del while si la entrada es válida
        }
    }

    limpiarCadena(entrada, final);  // Procesa la cadena con la función anteriormente creada

    
    if (palindromo(final)) {        // Teniendo ya la entrada procesada, se declara si es palíndromo o no
        printf("Es un palindromo.\n");
    } else {
        printf("No es un palindromo.\n");
    }
}

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 2------------------------------------------------
//-------------------------------------------------------------------------------------------------------

static int MAX_AUX=100;


int producto(int m, int n){

    int resultado=0; //variable retornada como el resultado de la multiplicacion

    if (n > 0){
        resultado = m+(producto(m, n-1));
        //suma al factor m la cantidad de veces que n se decremente hasta 1
    }
    else if (n < 0){
        //si el factor n es negativo, invierte el signo de ambos factores 
        //para que n sea positivo y pueda decrementarse
        resultado = (producto(m*(-1), n*(-1)));
    }

    return resultado;

}

int cargarNumerosPunto2(){

    char ingresoNum[MAX_AUX]; //cadena de ingreso
    int m; //factor de multiplicacion
    int n; //factor de multiplicacion
    int val=0; //flag de validacion

    printf("Ingrese el primer factor (entero entre -40000 y 40000): ");

    while (val == 0){

        val=1;

        //carga de datos como string
        fflush(stdin);
        fgets(ingresoNum, sizeof(ingresoNum), stdin);
        fflush(stdin);

        //valida si la entrada es un numero entero, en caso negativo, el flag de valdiacion vuelve a 0
        if(!esEntero(ingresoNum)){
            printf("ERROR. Ingrese un numero valido (entero entre -40000 y 40000): ");
            val=0;
        }
        else {
            //castea el string de ingreso a int
            m=atoi(ingresoNum);
            if (m<-40000 || m>40000){
                printf("ERROR. Ingrese un numero valido (entero entre -40000 y 40000): ");
                val=0;
            }
        }
    }

    val=0;

    printf("\nIngrese el segundo factor (entero entre -40000 y 40000): ");

    while (val == 0){

        val=1;

        //ingreso de datos como string
        fflush(stdin);
        fgets(ingresoNum, sizeof(ingresoNum), stdin);
        fflush(stdin);

        //valida si la entrada es un numero entero, en caso negativo, el flag de valdiacion vuelve a 0
        if (!esEntero(ingresoNum)){
            printf("ERROR. Ingrese un numero valido (entero entre -40000 y 40000): ");
            val=0;
        }
        else {
            //castea el string de ingreso a int
            n=atoi(ingresoNum);
            if (n<-40000 || n>40000){
                printf("ERROR. Ingrese un numero valido (entero entre -40000 y 40000): ");
                val=0;
            }
        }
    }

    int resultado = producto(m, n);
    printf("\nResultado del producto: %d\n", resultado);
    return resultado;     //llamado a la funcion recursiva

}

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 3------------------------------------------------
//-------------------------------------------------------------------------------------------------------

int terminoSeridFibonacci(int k) {   // Función recursiva para calcular el k-ésimo término de Fibonacci
    int resultado;     // Guarda el numero obtenido
    if (k <= 2) {
        resultado = k; // Casos base, devuelve k directamente
    }
    else { 
        resultado = terminoSeridFibonacci(k - 1) + terminoSeridFibonacci(k - 2); 
        // Cálculo recursivo para obtener el k-ésimo término
    }
return resultado;
}


bool esNumeroValidoEj3(const char *ingreso) {  // Función para validar que la entrada sea numerica
    for (int i = 0; ingreso[i] != '\0'; i++) {
        if (ingreso[i] < '0' || ingreso[i] > '9') {
            return false;
        }
    }
    return true;
}

void cargarTerminoEj3() { //Funcion para pedir el ingreso, validar y llamar a la funcion terminoSeridFibonacci
    char entrada[100]; //Guarda el ingreso
    int numero;        //Guarda el ingreso validado

    while (1) {        //Bucle infinito hasta que la entrada sea valida
        printf("Ingrese un numero entre 0 y 44 para obtener su termino de Fibonacci: ");
        fgets(entrada, sizeof(entrada), stdin);

        size_t longitud = strlen(entrada);  //Elimina salto de linea
        if (longitud > 0 && entrada[longitud - 1] == '\n') {
            entrada[longitud - 1] = '\0';
        }

        if (!esNumeroValidoEj3(entrada)) {    //Validacion de que la entrada sea numerica
            printf("Entrada no valida. Ingrese solo numeros enteros positivos.\n\n");
            continue;
        }

        numero = atoi(entrada);            //Convertimos la entrada a entero

        if (numero < 0 || numero > 44) {   //Validacion del rango establecido
            printf("El numero debe estar entre 0 y 44.\n\n");
        } else {
            break;
        }
    }

    int resultado = terminoSeridFibonacci(numero);   
    //Teniendo ya el numero, se declara a que numero pertenece dentro de la serie Fibonacci
    printf("El %d-esimo termino de la serie de Fibonacci es: %d\n", numero, resultado);

}

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 4------------------------------------------------
//-------------------------------------------------------------------------------------------------------

int divEntera(int m,int n){ // funcion que calcula parte entera
    if(m < n){
        return 0;
    } else{
        return 1 + divEntera(m - n, n);
    }  
}
float divDecimal(int residuo, int n, int profundi){ // funcion que calcula la parte decimal
    if(profundi == 5 || residuo == 0){
        return 0;
    } else{
        residuo*= 10;
        return (residuo / n)*0.1 + divDecimal(residuo%n,n,profundi+1)*0.1;
    }
}
float division(int m, int n) {  // Esta es la función principal que devuelve el cociente como float
    int parteEntera = divEntera(m, n);
    float parteDecimal = divDecimal(m % n, n, 0);
    return parteEntera + parteDecimal;
}
void pedirEntrada() { // funcion que solicita al usuario y valida la entrada
    int m, n;

    printf("Ingrese el dividendo m: ");

    char ingreso[100];

    fflush(stdin);
    while (!esEnteroNoNegativo(fgets(ingreso, 100, stdin))){
        printf("Error: Ingrese un numero entero: ");
        fflush(stdin);
    }

    m = atoi(ingreso);

    printf("Ingrese el divisor n: ");

    fflush(stdin);
    while (!esEnteroPositivo(fgets(ingreso, 100, stdin))){
        printf("Error: Ingrese un numero entero positivo: ");
        fflush(stdin);
    }

    n = atoi(ingreso);

    // Llamamos a la función después de validar la entrada
    float valor = division(m, n);
    printf("%.5f\n",valor);
}

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 5------------------------------------------------
//-------------------------------------------------------------------------------------------------------

char * agregarSeparadorMiles(char numero[]) {
    // Manejamos si es negativo
    int negativo = 0;
    if (numero[0] == '-') {
        negativo = 1;
        numero++; // Saltamos el signo
    }

    // Saltar ceros a la izquierda
    while (*numero == '0' && *(numero + 1) != '\0') {
        numero++;
    }

    int len = strlen(numero);

    // Caso base: vacío o "0"
    if (len == 0) {
        char* res = malloc(negativo ? 3 : 2); // "-0" o "0"
        strcpy(res, negativo ? "-0" : "0");
        return res;
    }

    // Caso base: 3 o menos dígitos
    if (len <= 3) {
        char* res = malloc(len + 1 + negativo);
        if (negativo) {
            sprintf(res, "-%s", numero);
        } else {
            strcpy(res, numero);
        }
        return res;
    }

    // Dividir en izquierda y derecha
    int ultimosDigitos = len - 3;
    char izquierda[ultimosDigitos + 1];
    strncpy(izquierda, numero, ultimosDigitos);
    izquierda[ultimosDigitos] = '\0';

    const char* derecha = &numero[ultimosDigitos];

    // Llamada recursiva sobre la izquierda
    char* izquierdaSeparada = agregarSeparadorMiles(izquierda);

    // Calcular tamaño total
    char* resultado = malloc(strlen(izquierdaSeparada) + 1 + strlen(derecha) + 2); // '.' + '\0'

    sprintf(resultado, "%s.%s", izquierdaSeparada, derecha);

    // Agregar el signo negativo si hacía falta
    if (negativo) {
        char* conSigno = malloc(strlen(resultado) + 2); // '-' + '\0'
        sprintf(conSigno, "-%s", resultado);
        free(resultado);
        free(izquierdaSeparada);
        return conSigno;
    }

    free(izquierdaSeparada);
    return resultado;
}

void Ejercicio5() {
    char numero[100];
    char numeroLimpio[100];

    printf("Ingrese un numero entero (los espacios seran ignorados): ");
    fgets(numero, sizeof(numero), stdin);

    // Limpiar la cadena para eliminar espacios
    limpiarCadena(numero, numeroLimpio);

    while (!esNumeroValidoString(numeroLimpio)) {
        printf("Error: solo se permiten numeros enteros positivos. Intente de nuevo: ");
        fgets(numero, sizeof(numero), stdin);
        limpiarCadena(numero, numeroLimpio);
    }

    char* resultado = agregarSeparadorMiles(numeroLimpio);
    printf("Numero con separadores de miles: %s\n", resultado);

    free(resultado);
}

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 6------------------------------------------------
//-------------------------------------------------------------------------------------------------------

void generarOnda(const char *seniales, char *resultado, int index, int posRes, char estadoAnterior) {

    // posRes es la posición actual en el resultado
    // index es la posición actual en la cadena de seniales
    // estadoAnterior es el estado anterior (L o H) para determinar si se necesita un separador
    // Caso base: si hemos llegado al final de la cadena de seniales
    // y el resultado está vacio, no hacemos nada

    if (strlen(resultado) == 0 && seniales[index] == '\0') {
        return;
    }


    if (seniales[index] == '\0') {  // Caso base: fin de la cadena
        resultado[posRes] = '\0';
        return;
    }

    char actual = toupper(seniales[index]);
    char anterior = toupper(estadoAnterior);

    // Agregar un separador si hay un cambio de estado
    if (index > 0 && actual != anterior) {
        resultado[posRes++] = '|';
    }


    // Determinar la representacion del caracter actual
    if (actual == 'L') {
        resultado[posRes++] = '_';
    } else if (actual == 'H') {
        resultado[posRes++] = '-';
    }

    // Llamada recursiva al siguiente carácter
    generarOnda(seniales, resultado, index + 1, posRes, actual);
}


char *ondaDigital(char seniales[]) {
    static char resultado[200];
    resultado[0] = '\0';

    generarOnda(seniales, resultado, 0, 0, seniales[0]);

    return resultado;
}

void Ejercicio6() {
    char seniales[100];
    char senialesLimpias[100];

    printf("Ingrese la cadena de seniales (solo H y L): ");
    fgets(seniales, sizeof(seniales), stdin);

    // Limpiar la cadena para eliminar espacios
    limpiarCadena(seniales, senialesLimpias);

    while (!cadenaOndaValidar(senialesLimpias)) {
        printf("Error: solo se permiten las letras H y L. Intente de nuevo: ");
        fgets(seniales, sizeof(seniales), stdin);
        limpiarCadena(seniales, senialesLimpias);
    }

    char *onda = ondaDigital(senialesLimpias);
    printf("Onda digital:\n%s\n", onda);
}

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 7------------------------------------------------
//-------------------------------------------------------------------------------------------------------

#define MAX 100

char * reunionMafia(int nivel){
    
    //caso base
    if (nivel == 1){

        char * base=malloc(6);
        strcpy(base, "(-.-)"); //retorna el chino del medio

        return base;
    }
    else {

        char * medio=reunionMafia(nivel-1); //llamada recursiva

        char * reunion=malloc(strlen(medio)+7);
        strcpy(reunion, "(-."); //almacena el resultado

        //concatena los string devueltos
        strcat(reunion, medio); 
        strcat(reunion, ".-)");

        return reunion;
    }

}

//ingreso del nivel
char * cargarNivelDeReunion(){

    printf("Introduzca el nivel de la reunion (debe ser un numero entero entre 1 y 20): ");

    char ingresoNivel[MAX]; //cadena de entrada
    int nivel; //nivel de la reunion
    int val=0; //flag de validacion de entrada de nivel

    //validacion de ingreso de datos
    while (val == 0){

        val=1;

        //ingreso de la cadena
        fflush(stdin);
        fgets(ingresoNivel, sizeof(ingresoNivel), stdin);
        fflush(stdin);

        //valida que la cadena no sea un numero negativo
        if (esEnteroNoNegativo(ingresoNivel)){

            nivel=atoi(ingresoNivel); //guarda el ingreso como entero (int)

            //valida que el nivel este entre 1 y 20
            if (nivel<1 || nivel>20){
                printf("ERROR. Introduza un valor valido (entero de 1 a 20): ");
                val=0;
            }

        }
        else{
            printf("ERROR. Introduza un valor valido (entero de 1 a 20): ");
            val=0;
        }
    }

    char* resultado = reunionMafia(nivel);
    printf("\nReunión generada: %s\n", resultado);
    return resultado;     //llama a la funcion recursiva
}


//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 8------------------------------------------------
//-------------------------------------------------------------------------------------------------------

#define MAX_AUXILIAR 20
#define MAX_SALIDA 1000  // Tamaño para la cadena de salida

// Función recursiva que construye subconjuntos y guarda en una cadena
void EnconSubCon(int conj[], int n, int index, int subset[], int subsetSize, int sumanow, int objetivo, char *output) {
    if (sumanow == objetivo) {
        strcat(output, "{");
        for (int i = 0; i < subsetSize; i++) {
            char num[10];
            sprintf(num, "%d", subset[i]);
            strcat(output, num);
            if (i < subsetSize - 1) strcat(output, ", ");
        }
        strcat(output, "}\n");
        return;
    }

     if (index == n) return; 

    // Incluir el elemento actual
    subset[subsetSize] = conj[index];
    EnconSubCon(conj, n, index + 1, subset, subsetSize + 1, sumanow + conj[index], objetivo, output);

    // Excluir el elemento actual
    EnconSubCon(conj, n, index + 1, subset, subsetSize, sumanow, objetivo, output);
}
// FUNCION con el prototipo pedido
void subconjuntosQueSumanN(int conjunto[], int tamano, int objetivo, char **output) {
    static char salida[MAX_SALIDA]; // Buffer para la salida
    salida[0] = '\0'; // Inicializamos cadena vacía

    int subset[MAX_AUXILIAR];
    EnconSubCon(conjunto, tamano, 0, subset, 0, 0, objetivo, salida);

    *output = salida; // Apuntamos el parámetro de salida al buffer
}
// FUNCIÓN auxiliar para pedir datos al usuario
void pedirEntradaConjuntos() {
    int n, objetivo;

    char carga[100];

    // Solicitar tamaño del conjunto
    printf("Ingrese el tamanio del conjunto: ");

    fflush(stdin);
    while (!esEnteroPositivo(fgets(carga, 100, stdin)) || atoi(carga) > MAX_AUXILIAR){
        printf("Error: Ingrese un numero entero positivo menor o igual a %d: ", MAX_AUXILIAR);
        fflush(stdin);
    }

    n = atoi(carga);

    // Declarar el conjunto
    int conj[MAX_AUXILIAR];

    // Cargar uno por uno los elementos del conjunto con validación individual
    printf("Ingrese los %d elementos del conjunto:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Elemento %d: ", i + 1);

        fflush(stdin);
        while (!esEntero(fgets(carga, 100, stdin))){
            printf("Error: Ingrese un numero entero valido.\n");
            fflush(stdin);
            printf("Elemento %d: ", i + 1);
        }

        conj[i] = atoi(carga);
    }

    // Solicitar objetivo de suma
    printf("Ingrese el objetivo de suma: ");

    fflush(stdin);
    while (!esEntero(fgets(carga, 100, stdin))){
        printf("Error: Ingrese un numero entero valido.\n");
        fflush(stdin);
        printf("Ingrese el objetivo de la suma: ");
    }

    objetivo = atoi(carga);

    // Llamar a la función que resuelve el problema
    char *output;
    subconjuntosQueSumanN(conj, n, objetivo, &output);

    printf("Subconjuntos que suman %d:\n%s", objetivo, output);
}

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 9------------------------------------------------
//-------------------------------------------------------------------------------------------------------

bool divisiblePor7(int n) {             //Función recursiva para verificar si un numero es divisible por 7
    if (n < 0) return false;            //Si es negativo, no se considera
    if (n < 70) return (n % 7 == 0);    //Si es menor a 70 se aplica una formula base

    int ultimacifra = n % 10;               //Obtenemos la última cifra del número
    int resto = n / 10;                     //Eliminamos esa cifra, quedándonos con el resto

    int numnuevo = resto - 2 * ultimacifra; //Se resta el doble de la ultima cifra

    return divisiblePor7(numnuevo);         //LLamada recursiva con el nuevo numero
}

bool esNumeroValidoEj9(const char *ingreso) {      // Función para validar que la entrada sea numerica
    for (int i = 0; ingreso[i] != '\0'; i++) {
        if (ingreso[i] < '0' || ingreso[i] > '9') return false;
    }
    return true;
}

void cargarNumeroEj9() {   //Funcion que pide el ingreso, valida y llama a la funcion divisiblePor7
    char entrada[100];  //Guarda el ingreso
    int numero;         //Guarda el ingreso validado

    while (1) {                          //Bucle infinito hasta que la entrada sea valida
        printf("Ingrese un numero divisible por 7 entre 0 y 1000000: ");
        fgets(entrada, sizeof(entrada), stdin);

        size_t longitud = strlen(entrada);    //Elimina salto de linea
        if (longitud > 0 && entrada[longitud - 1] == '\n') {
            entrada[longitud - 1] = '\0';
        }

        if (!esNumeroValidoEj9(entrada)) {   //Validacion de que la entrada sea numerica
            printf("Entrada no valida. Solo se permiten numeros enteros positivos.\n\n");
            continue;
        }

        numero = atoi(entrada);                    // Convertimos la entrada a entero

        if (numero < 0 || numero > 1000000) {      // Validacion del rango declarado
            printf("El numero debe estar entre 0 y 1000000.\n\n");
        } else {
            break;
        }
    }

    if (divisiblePor7(numero)) {  //Teniendo ya el numero procesado, se declara si es divisible por 7 o no
        printf("El numero %d es divisible por 7.\n", numero);
    } else {
        printf("El numero %d no es divisible por 7.\n", numero);
    }
}
