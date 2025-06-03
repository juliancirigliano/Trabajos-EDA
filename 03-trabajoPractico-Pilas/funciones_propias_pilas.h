#include <stdbool.h>

#ifndef FuncionesAgregadas
#define FuncionesAgregadas

//-------------------------------------FUNCIONES EJERCICIO 2--------------------------------------------

void cargarPilaEj2();

//-------------------------------------FUNCIONES EJERCICIO 3--------------------------------------------

void mostrarResultadoEj3(Pila p1, Pila p2);
void cargaManualEj3(int n);
void cargaAleatoriaEj3(int n);
void cargarPilasEj3();

//-------------------------------------FUNCIONES EJERCICIO 4--------------------------------------------

void Ejercicio4();

//-------------------------------------FUNCIONES EJERCICIO 5--------------------------------------------

void mostrarResultadoEj5(Pila p);
void cargaManualEj5(int n);
void cargaAleatoriaEj5(int n);
void cargarPilasEj5();

//-------------------------------------FUNCIONES EJERCICIO 6--------------------------------------------

Pila p_ej6_eliminarclave_iterativo(Pila p, int clave);
void eliminar_rec(Pila original, Pila resultado, int clave);
Pila p_ej6_eliminarclave_recursivo(Pila p, int clave);
void cargarPilaEj6();

//-------------------------------------FUNCIONES EJERCICIO 7--------------------------------------------

void ejercicio7();
void ingresarDatosManuales();
void generarDatosAleatorios();
Pila genAleatorioPilas(int n);

//-------------------------------------FUNCIONES EJERCICIO 8--------------------------------------------

Pila pila_buscar_repetidos(Pila pila);
void intercambiar_pilas(Pila pila_1, Pila pila_2);
bool pila_buscar(Pila pila, TipoElemento te_buscado);
Pila pila_ordenar_asc(Pila pila);
void p_mostrar_y_valor(Pila pila);
int p_largo(Pila pila);
void Punto_8(void);

#endif