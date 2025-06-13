#include <stdbool.h>

#ifndef FuncionesAgregadas
#define FuncionesAgregadas

//-------------------------------------FUNCIONES EJERCICIO 2--------------------------------------------

void cargar_cola_manual(Cola c);
void cargar_cola_aleatoria(Cola c);
void ejercicio2 ();

//-------------------------------------FUNCIONES EJERCICIO 3--------------------------------------------

void carga_ej3(void);

//-------------------------------------FUNCIONES EJERCICIO 4--------------------------------------------

void limpiarPantalla();
void c_intercambiar(Cola C, Cola CAux);
int c_buscar(Cola origen, Cola destino, int n);
int ejercicio4();

//-------------------------------------FUNCIONES EJERCICIO 5--------------------------------------------

void mostrarResultadoEjercicio5(Cola c);
bool repeticionesEjercicio5(int *arr, int n, int lon);
void cargaEjercicio5();

//-------------------------------------FUNCIONES EJERCICIO 6--------------------------------------------

bool ya_esta_en_lista(Lista l, int clave);
void cargarEjercicio6();

#endif