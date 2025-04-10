#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

//Valida que una cadena contenga unicamente caracteres numericos (incluye negativos y decimales)
bool esNumerico(char * dato);

//Valida que una cadena corresponde a un numero entero
bool esEntero(char * dato);

//valida que una cadena corresponda a un numero entero positivo
bool esEnteroPositivo(char *dato);

//valida que una cadena corresponda a un numero entero negativo
bool esEnteroNegativo(char * dato);

//valida que una cadena corresponda a un numero entero postivo o 0
bool esEnteroNoNegativo(char * dato);

//valida que una cadena corresponda a un numero real positivo
bool esRealPositivo(char * dato);

//valida que una cadena corresponda a un numero real negativo
bool esRealNegativo(char * dato);

//valida que una cadena corresponda a un numero real positivo o 0
bool esRealNoNegativo(char * dato);

//H o L
int cadenaOndaValidar(const char *cadena);

//Valida que una cadena corresponda a un numero real negativo o 0
int esNumeroValidoString(char* str);