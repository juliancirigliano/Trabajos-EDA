#include <stdbool.h>

#ifndef FuncionesAgregadas
#define FuncionesAgregadas

//-------------------------------------FUNCIONES EJERCICIO 1--------------------------------------------

char reemplazarTilde(unsigned char cadena);
void limpiarCadena(char *cadenarecibida, char *cadenafinal);
void cargarCadenaEj1(); 

//-------------------------------------FUNCIONES EJERCICIO 2--------------------------------------------

int cargarNumerosPunto2();

//-------------------------------------FUNCIONES EJERCICIO 3--------------------------------------------

bool esNumeroValidoEj3(const char *ingreso);
void cargarTerminoEj3();

//-------------------------------------FUNCIONES EJERCICIO 4--------------------------------------------

int divEntera(int m,int n);
float divDecimal(int residuo, int n, int profundi);
void pedirEntrada();

//-------------------------------------FUNCIONES EJERCICIO 5--------------------------------------------

void Ejercicio5();

//-------------------------------------FUNCIONES EJERCICIO 6--------------------------------------------

void generarOnda(const char *seniales, char *resultado, int index, int posRes, char estadoAnterior);
void Ejercicio6();

//-------------------------------------FUNCIONES EJERCICIO 7--------------------------------------------

char * cargarNivelDeReunion();

//-------------------------------------FUNCIONES EJERCICIO 8--------------------------------------------

void EnconSubCon(int conj[], int n, int index, int subset[], int subsetSize, int sumanow, int objetivo, char *output);
void pedirEntradaConjuntos();

//-------------------------------------FUNCIONES EJERCICIO 9--------------------------------------------

bool esNumeroValidoEj9(const char *ingreso);
void cargarNumeroEj9();


#endif
