#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#include <ctype.h>
#include "validaciones.h"

/*
---ESPECIFICACIONES GENERALES---
-se considera como indicador decimal el punto ".", no la coma ","
-las cadenas que contengan unicamente "-", "+" o "." (decimal) seran interpretadas como 0 sin signo
-se interpreta que una cadena numerica comenzada en "." (decimal) corresponde a un numero que comienza por 0
EJ: .45 es interpretada como 0.45
-se interpreta que una cadena numerica finalizada en "." (decimal) corresponde a un numero terminado en .0
EJ: 12. es interpretado como 12.0 (o solo 12 en su defecto)
*/


int posDecimal=0;
int flagDecimal=0;

//Valida que una cadena contenga unicamente caracteres numericos (incluye negativos y decimales)
bool esNumerico(char * dato){

    if (dato[0] == '\n' || dato [0] == '\0'){
        return false;   //retorna falso si la cadena esta vacia
    }
    else if (dato[strlen(dato)-1] == '\n'){
        dato[strlen(dato)-1] = '\0';   //si hay un ENTER (\n) lo elimina y termina la cadena en \0
    }

    int i=0;
    int contadorDecimal=0;
    int lon = strlen(dato);

    //si el primer caracter es "-", "+", o un "." decimal, lo salta para mantener el signo o decimal
    if (dato[0] == 43 || dato[0] == 45){
        i++;  
    }
    else if (dato[i] == 46){
        posDecimal=i;
        flagDecimal=1;
        i++;
        contadorDecimal++;
    }

    for (; i<lon; i++){

        if ((dato[i] < 48 || dato[i] > 57) && dato[i] != 46){
            return false;   //hay un caracter no numerico
        }
        else if (dato[i] == 46){
            contadorDecimal++;
            posDecimal=i;
            flagDecimal=1;
            if (contadorDecimal > 1){
                return false;   //retorna false si hay mas de un ". decimal"
            }
        }
    }
    
    return true;

}


//Valida que una cadena corresponde a un numero entero
bool esEntero(char * dato){

    flagDecimal=0; //0 si no hay "." decimales, 1 si los hay
    
    if(esNumerico(dato)){

        if (flagDecimal==1){

            int lon=strlen(dato);
            posDecimal++;

            //En caso de haber un "." decimal, valida que solo hayan 0's luego del "."
            for (; posDecimal<lon; posDecimal++){
                if (dato[posDecimal]!=48){
                    return false;
                }
            }

            return true;
        }

        return true;
    }

    return false;
}

//valida que una cadena corresponda a un numero entero positivo
bool esEnteroPositivo(char * dato){

    if (esEntero(dato)){

        int num=atoi(dato);
        
        if (num>0){
            return true;
        }

        return false;
    }

    return false;
}

//valida que una cadena corresponda a un numero entero negativo
bool esEnteroNegativo(char * dato){

    if (esEntero(dato)){

        int num=atoi(dato);

        if (num<0){
            return true;
        }

        return false;
    }

    return false;
}

//valida que una cadena corresponda a un numero entero postivo o 0
bool esEnteroNoNegativo(char * dato){

    if (esEntero(dato)){

        if (dato[0] == 43 && dato[1] == 0){
            return true;   //si la cadena solo tiene "+" lo considera como 0 
        }

        else {

            int num=atoi(dato);
        
            if (num>=0){
                return true;
            }
    
            return false;    
        }

    }

    return false;
}

//valida que una cadena corresponda a un numero real positivo
bool esRealPositivo(char * dato){

    if (esNumerico(dato)){

        float num=atof(dato);
        
        if (num>0){
            return true;
        }

        return false;
    }

    return false;
}

//valida que una cadena corresponda a un numero real negativo
bool esRealNegativo(char * dato){

    if (esNumerico(dato)){

        float num=atof(dato);
        
        if (num<0){
            return true;
        }

        return false;
    }

    return false;
}

//valida que una cadena corresponda a un numero real positivo o 0
bool esRealNoNegativo(char * dato){

    if (esNumerico(dato)){

        if (dato[0] == 43 && dato[1] == 0){
            return true;   //si la cadena solo tiene "+" lo considera como 0 
        }

        else {

            float num=atof(dato);
        
            if (num>=0){
                return true;
            }
    
            return false;    
        }

    }

    return false;
}

int esNumeroValidoString(char* str) {
    if (str[0] == '\0') return 0;

    int i = 0;

    if (str[0] == '-') {
        i = 1;
        if (str[1] == '\0') return 0;
    }

    for (; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }

    return 1;
}

int cadenaOndaValidar(const char *cadena) {
    if (cadena[0] == '\0') return 0;

    for (int i = 0; cadena[i] != '\0'; i++) {
        char c = toupper(cadena[i]);
        if (c != 'H' && c != 'L') {
            return 0;
        }
    }
    return 1;
}