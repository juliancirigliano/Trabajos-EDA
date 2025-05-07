#include <stdbool.h>

#ifndef FuncionesAgregadas
#define FuncionesAgregadas

//-------------------------------------FUNCIONES EJERCICIO 2--------------------------------------------

int ingresarEnteroValidado(const char* mensaje);
void cargarListasYResolverPunto2();

//-------------------------------------FUNCIONES EJERCICIO 3--------------------------------------------

void mostrarResultadoMultiplo(ResultadosMul res);
int ingresarEnteroVal(const char* mensaje);
void cargarListasYResolverMultiplo();

//-------------------------------------FUNCIONES EJERCICIO 4--------------------------------------------

void resultadoListasMayorMenor(Lista l1, Lista l2);
void cargaMayorMenorManual(int lon);
void cargaMayorMenorAleatoria(int lon);
void cargarListasMayorMenor();

//-------------------------------------FUNCIONES EJERCICIO 5--------------------------------------------

void mostrarResultados(Lista resultados, double x_min, double incremento);
void ejercicio5(void);

//-------------------------------------FUNCIONES EJERCICIO 6--------------------------------------------

int leerEntero(const char* mensaje, int min, int max);
void cargarLista(Lista lista, int cantidad);
void cargarYProcesarSublista();

#endif