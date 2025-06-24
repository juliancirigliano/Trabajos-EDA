#ifndef TP_CONJUNTOS_H
#define TP_CONJUNTOS_H

#include <stdbool.h>
#include "../libs/conjuntos/headers/conjuntos.h"
#include "../libs/listas/headers/listas.h"

/**
2.	Desarrollar un algoritmo que dado dos conjuntos de elementos tipo numérico (clave) 
	verifique las operaciones de Unión,  Intersección,  Diferencia y Pertenencia. 
*/
Conjunto c_ej2_union(Conjunto A, Conjunto B);
Conjunto c_ej2_interseccion(Conjunto A, Conjunto B);
Conjunto c_ej2_diferencia(Conjunto A, Conjunto B);


/**
3.	Desarrollar un algoritmo que dada una colección de conjuntos de elementos tipo numérico (clave) 
	realice las operaciones de Unión e Intersección.
	La lista contendra la coleccion de conjuntos.  Cada campo void apunta a un conjunto.
*/
Conjunto c_ej3_uniones(Lista l_de_conjuntos);
Conjunto c_ej3_intersecciones(Lista l_de_conjuntos);


/**
4.	Desarrollar un algoritmo que dado tres conjuntos puedan demostrar la propiedad de la transitividad:  
	“si A es subconjunto de B y B a su vez es subconjunto de C, entonces A es subconjunto de C”.
*/
bool c_ej4_transitividad(Conjunto A, Conjunto B, Conjunto C);

/**
5.	Desarrollar un algoritmo capaz de resolver la diferencia simétrica (por la clave) entre dos conjuntos. 
	La diferencia simétrica es una operación entre dos conjuntos donde el conjunto resultante está conformado 
	por los elementos no comunes a los dos conjuntos.
*/
Conjunto c_ej5_dif_simetrica(Conjunto A, Conjunto B);

/**
6.	Dados dos conjuntos de números naturales se pide determinar si uno es subconjunto propio del otro.  
	Determinar la complejidad algorítmica
*/
bool c_ej6_subconjuntopropio(Conjunto A, Conjunto B);

/**
7.	Dados 3 conjuntos determinar si alguno es un subconjunto parcial o total del otro.  
	Se considera un subconjunto parcial cuando al menos la mitad de los elementos de uno están en el otro.  
	Determinar la complejidad algorítmica.
	Imprimir el resultado en la función.
*/
void c_ej7_subconjtotalparcial(Conjunto A, Conjunto B, Conjunto C);

/**
8.	Dados dos conjuntos de números naturales se pide determinar si son iguales sin importar la posición 
	de sus elementos.  
	Determinar la complejidad algorítmica.
*/
bool c_ej8_soniguales(Conjunto A, Conjunto B);

#endif // TP_CONJUNTOS_H
