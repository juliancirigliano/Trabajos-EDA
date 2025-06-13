#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include "tp_colas_3.h"
#include "funciones_propias_colas.h"
#include "../libs/validaciones/headers/validaciones.h"
#include "../libs/tipoElemento/headers/tipo_elemento.h"
#include "../libs/listas/headers/listas.h"
#include "../libs/pilas/headers/pilas.h"
#include "../libs/colas/headers/colas.h"

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 2------------------------------------------------
//-------------------------------------------------------------------------------------------------------

//  a. Informar si un elemento dado se encuentra en la cola.
bool c_ej2_existeclave(Cola c, int clave) {
    bool existe = false;
    Cola aux = c_crear();
    TipoElemento te;

    while (!c_es_vacia(c)) {
        te = c_desencolar(c);
        if (te->clave == clave) {
            existe = true;
        }
        c_encolar(aux, te);
    }
    // Restaurar la cola original
    while (!c_es_vacia(aux)) {
        c_encolar(c, c_desencolar(aux));
    }
    return existe;
}

//  b. Agregar un nuevo elemento en una posición dada (colarse).
Cola c_ej2_colarelemento(Cola c, int posicionordinal, TipoElemento X) {
    if (posicionordinal < 1) return c; // posición inválida

    Cola nueva = c_crear();
    Cola aux = c_crear();
    int pos = 1;
    TipoElemento te;
    bool insertado = false;

    while (!c_es_vacia(c)) {
        te = c_desencolar(c);
        if (pos == posicionordinal) {
            c_encolar(nueva, X);
            insertado = true;
        }
        c_encolar(nueva, te);
        c_encolar(aux, te);
        pos++;
    }
    // Si la posición es justo después del último elemento
    if (pos == posicionordinal) {
        c_encolar(nueva, X);
        insertado = true;
    }

    while (!c_es_vacia(aux)) {
        c_encolar(c, c_desencolar(aux));
    }
    if (!insertado) {
        while (!c_es_vacia(nueva)) c_desencolar(nueva);
        return c;
    }
    return nueva;
}

//  c. Dado un elemento sacarlo de la cola todas las veces que aparezca.
Cola c_ej2_sacarelemento(Cola c, int clave) {
    Cola nueva = c_crear();
    Cola aux = c_crear();
    TipoElemento te;
    bool encontrado = false;

    while (!c_es_vacia(c)) {
        te = c_desencolar(c);
        if (te->clave != clave) {
            c_encolar(nueva, te);
        } else {
            encontrado = true;
        }
        c_encolar(aux, te);
    }
    while (!c_es_vacia(aux)) {
        c_encolar(c, c_desencolar(aux));
    }
    if (!encontrado) {
        while (!c_es_vacia(nueva)) c_desencolar(nueva);
        return c;
    }
    return nueva;
}

//  d. Contar los elementos de la cola.
int c_ej2_contarelementos(Cola c) {
    int count = 0;
    Cola aux = c_crear();
    TipoElemento te;

    while (!c_es_vacia(c)) {
        te = c_desencolar(c);
        count++;
        c_encolar(aux, te);
    }
    while (!c_es_vacia(aux)) {
        c_encolar(c, c_desencolar(aux));
    }
    return count;
}

//  e. Realizar una función que realice una copia de una cola.
Cola c_ej2_copiar(Cola c) {
    Cola copia = c_crear();
    Cola aux = c_crear();
    TipoElemento te;

    while (!c_es_vacia(c)) {
        te = c_desencolar(c);
        TipoElemento te_copia = te_crear(te->clave);
        c_encolar(copia, te_copia);
        c_encolar(aux, te);
    }
    while (!c_es_vacia(aux)) {
        c_encolar(c, c_desencolar(aux));
    }
    return copia;
}

//  f. Invertir el contenido de una cola sin destruir la cola original.
Cola c_ej2_invertir(Cola c) {
    Cola aux = c_crear();
    Cola invertida = c_crear();
    TipoElemento te;
    int n = c_ej2_contarelementos(c);
    TipoElemento* temp = (TipoElemento*)malloc(n * sizeof(TipoElemento));
    int i = 0;

    while (!c_es_vacia(c)) {
        te = c_desencolar(c);
        temp[i++] = te;
        c_encolar(aux, te);
    }

    while (!c_es_vacia(aux)) {
        c_encolar(c, c_desencolar(aux));
    }

    for (int j = n - 1; j >= 0; j--) {
        TipoElemento te_copia = te_crear(temp[j]->clave);
        c_encolar(invertida, te_copia);
    }
    free(temp);
    return invertida;
}

void cargar_cola_manual(Cola c) {
    int n, clave;
    printf("Ingrese la cantidad de elementos a cargar: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Clave del elemento %d: ", i + 1);
        scanf("%d", &clave);
        c_encolar(c, te_crear(clave));
    }
}

void cargar_cola_aleatoria(Cola c) {
    int n, clave;
    printf("Ingrese la cantidad de elementos aleatorios: ");
    scanf("%d", &n);
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        clave = rand() % 100;
        printf("Clave generada: %d\n", clave);
        c_encolar(c, te_crear(clave));
    }
}

void ejercicio2 () {
    Cola c = c_crear();
    int opcion, clave, pos;
    TipoElemento te;
    bool existe;
    Cola resultado;
    int cantidad;

    printf("=== Ejercicio 2: Operaciones con Colas ===\n");
    printf("1. Cargar cola manualmente\n");
    printf("2. Cargar cola aleatoriamente\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        cargar_cola_manual(c);
    } else {
        cargar_cola_aleatoria(c);
    }

    do {
        printf("\n--- Menu de Operaciones ---\n");
        printf("1. Mostrar cola\n");
        printf("2. Buscar clave\n");
        printf("3. Colarse en posicion\n");
        printf("4. Sacar elemento por clave\n");
        printf("5. Contar elementos\n");
        printf("6. Copiar cola\n");
        printf("7. Invertir cola\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                c_mostrar(c);
                break;
            case 2:
                printf("Ingrese clave a buscar: ");
                scanf("%d", &clave);
                existe = c_ej2_existeclave(c, clave);
                if (existe) printf("La clave %d existe en la cola.\n", clave);
                else printf("La clave %d NO existe en la cola.\n", clave);
                break;
            case 3:
                printf("Ingrese posicion ordinal para colarse: ");
                scanf("%d", &pos);
                printf("Ingrese clave del nuevo elemento: ");
                scanf("%d", &clave);
                te = te_crear(clave);
                resultado = c_ej2_colarelemento(c, pos, te);
                if (resultado != c) {
                    c = resultado;
                    printf("Elemento insertado correctamente.\n");
                } else {
                    printf("No se pudo insertar (posicion invalida).\n");
                }
                break;
            case 4:
                printf("Ingrese clave a eliminar: ");
                scanf("%d", &clave);
                resultado = c_ej2_sacarelemento(c, clave);
                if (resultado != c) {
                    c = resultado;
                    printf("Elemento(s) eliminado(s).\n");
                } else {
                    printf("No se encontro la clave en la cola.\n");
                }
                break;
            case 5:
                cantidad = c_ej2_contarelementos(c);
                printf("Cantidad de elementos en la cola: %d\n", cantidad);
                break;
            case 6:
                resultado = c_ej2_copiar(c);
                printf("Cola copiada:\n");
                c_mostrar(resultado);
                break;
            case 7:
                resultado = c_ej2_invertir(c);
                printf("Cola invertida:\n");
                c_mostrar(resultado);
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 0);
}

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 3------------------------------------------------
//-------------------------------------------------------------------------------------------------------

bool c_ej3_iguales(Cola c1, Cola c2){
	//ambas colas son vacias, por ende son iguales
	if(c_es_vacia(c1)){
		if(c_es_vacia(c2)){
			return true;
		}
	}
	//si difieren en largo, son distintas
	int largo_1, largo_2;
	largo_1 = c_ej2_contarelementos(c1);
	largo_2 = c_ej2_contarelementos(c2);
	if(largo_1 != largo_2){
		return false;
	}

	Cola aux = c_crear();
	TipoElemento tec1, tec2;
	bool check_igual = true;
	int contador = 0;
	//como ya tengo el largo uso un for
	//recorro ambas colas de principio a fin
	for(int i = 0; i < largo_1; i++){
		tec1 = c_desencolar(c1);
		tec2 = c_desencolar(c2);
		if(check_igual){
			if(tec1->clave == tec2->clave){
				check_igual = true;
			}else{
				//conque haya uno distinto elimina la comparacion
				check_igual = false;
			}
		}
		//encolo denuevo
		c_encolar(c1, tec1);
		c_encolar(c2, tec2);
	}
	return check_igual;

}

void carga_ej3(void){
	Cola cola_test, cola_test2;
	cola_test = c_crear();
	cola_test2 = c_crear();
	TipoElemento te;

	printf("Ejercicio 4\n");
	printf("Determinar si 2 colas son iguales\n");
	printf("\n");
	int eleccion;
	printf("Tipo de ingreso: (1) Manual, (2) Predefinido\n");

	char dato[100];
	fflush(stdin);
	while(!esEnteroNoNegativo(fgets(dato, 100, stdin)) || (atoi(dato) != 1 && atoi(dato) !=2)){
		printf("Error, Ingrese denuevo, una eleccion valida\n");
		printf("Tipo de ingreso: (1) Manual, (2) Predefinido\n");
		fflush(stdin);
	}
	eleccion = atoi(dato);
	switch(eleccion){
		case 1:
			int largo_cola_1, largo_cola_2;
			//largo de la cola 1 
			printf("Ingrese el largo de la cola 1\n");
			fflush(stdin);
			while(!esEnteroNoNegativo(fgets(dato, 100, stdin)) || (atoi(dato) <= 0 && atoi(dato) >10)){
				printf("Entrada inválida. Debe ser un número entero mayor que 0.\n");
				printf("Intente nuevamente\n");
				fflush(stdin);
			}
			largo_cola_1 = atoi(dato);

			for (int i = 0; i < largo_cola_1; i++) {
				printf("Elemento Cola 1 %d: ", i + 1);
				fflush(stdin);
				while(!esEnteroNoNegativo(fgets(dato, 100, stdin))){
					printf("Entrada inválida. Debe ser un número entero mayor que 0.\n");
					printf("Intente nuevamente\n");
					printf("Elemento %d: ", i + 1);
					fflush(stdin);
				}
				c_encolar(cola_test, te_crear(atoi(dato)));
			}
			//largo de la cola 2 
			printf("Ingrese el largo de la cola 2\n");
			fflush(stdin);
			while(!esEnteroNoNegativo(fgets(dato, 100, stdin)) || (atoi(dato) <= 0 && atoi(dato) >10)){
				printf("Entrada inválida. Debe ser un número entero mayor que 0.\n");
				printf("Intente nuevamente\n");
				fflush(stdin);
			}
			largo_cola_2 = atoi(dato);


			for (int i = 0; i < largo_cola_2; i++) {
				printf("Elemento Cola 1 %d: ", i + 1);
				fflush(stdin);
				while(!esEnteroNoNegativo(fgets(dato, 100, stdin))){
					printf("Entrada inválida. Debe ser un número entero mayor que 0.\n");
					printf("Intente nuevamente\n");
					printf("Elemento %d: ", i + 1);
					fflush(stdin);
				}
				c_encolar(cola_test2, te_crear(atoi(dato)));
			}



			printf("Cola 1 inicial: \n");
			c_mostrar(cola_test);
			printf("Cola 2 inicial: \n");
			c_mostrar(cola_test2);
			if(c_ej3_iguales(cola_test, cola_test2)){
				printf("Ambas colas son iguales \n:");
			}else{
				printf("Las colas no son iguales \n:");
			}
			printf("Cola inicial 1: \n");
			c_mostrar(cola_test);
			printf("Cola inicial 2: \n");
			c_mostrar(cola_test2);
			break;
		case 2:
			int arreglo_test[] = {1,2,3,4,5,6,7,8,9};
			//int arreglo_test2[] = {1,2,3,4,5,6,7,8,9};
			int arreglo_test2[] = {1,2,4,3,5,6,7,8,9};
			for(int i = 0; i < 5; i++){
				te = te_crear(arreglo_test[i]);
				c_encolar(cola_test, te);	
			}
			for(int i = 0; i < 5; i++){
				te = te_crear(arreglo_test2[i]);
				c_encolar(cola_test2, te);	
			}
			printf("Cola inicial 1: \n");
			c_mostrar(cola_test);
			printf("Cola inicial 2: \n");
			c_mostrar(cola_test2);
			if(c_ej3_iguales(cola_test, cola_test2)){
				printf("Ambas colas son iguales \n:");
			}else{
				printf("Las colas no son iguales \n:");
			}
			printf("Cola inicial 1, para comprobar que no hubo cambios: \n");
			c_mostrar(cola_test);
			printf("Cola inicial 2, para comprobar que no hubo cambios: \n");
			c_mostrar(cola_test2);
			break;
		default:
			printf("Error, intente nuevamente:\n");
			printf("Tipo de ingreso: (1) Manual, (2) Predefinido\n");
			break;

	}
}

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 4------------------------------------------------
//-------------------------------------------------------------------------------------------------------

// Función para limpiar la pantalla 
void limpiarPantalla() {
#ifdef _WIN32
    system("cls"); // Para Windows
#else
    system("clear"); // Para Linux
#endif
}


void c_intercambiar(Cola C, Cola CAux) {
    // Pasa los elementos de CAux a C
    TipoElemento x;
    while (!c_es_vacia(CAux)) {
        x = c_desencolar(CAux);
        c_encolar(C, x);
    }
}

int c_buscar(Cola origen, Cola destino, int n) {
    // Toma los elementos de origen y aquellos cuya clave sea distinta de n,
    // los guarda en el destino.
    // Si encuentra al menos uno que tiene como clave n, retorna 1, sino 0.
    int repetido = 0;
    TipoElemento x;

    while (!c_es_vacia(origen)) {
        x = c_desencolar(origen);
        if (n != x->clave) {
            c_encolar(destino, x);
        } else {
            repetido = 1;
        }
    }
    return repetido;
}


Cola c_ej4_colanorepetidos(Cola original) {
	// Retorna la cola con las claves que no tienen repeticiones, caso contrario si todas se repiten retorna cola vacia.
    Cola A = c_crear();
    Cola B = c_crear();
    Cola R = c_crear();
    TipoElemento x;

    // Copiamos los elementos originales a la cola A
    // Para no alterar la original
    while (!c_es_vacia(original)) {
        x = c_desencolar(original);
        c_encolar(A, te_crear(x->clave));
        c_encolar(B, x);
    }

    c_intercambiar(original, B);
    int repetido = 0;
    int n;

    while (!c_es_vacia(A) || !c_es_vacia(B)) {
        if (!c_es_vacia(A)) {
            x = c_desencolar(A);
            n = x->clave;
            repetido = c_buscar(A, B, n);
        } else {
            x = c_desencolar(B);
            n = x->clave;
            repetido = c_buscar(B, A, n);
        }
        if (!repetido) {
            c_encolar(R, x);
        }
    }
    
    return R;
}

int ejercicio4() {
    char continue_choice[10];

    do {
        limpiarPantalla();

        Cola c = c_crear();
        Cola res;
        char opcion[10];
        char entrada[50];
        int numero;

        printf("Seleccione una opcion para llenar la cola inicial:\n");
        printf("1. Llenado aleatorio (10 elementos)\n");
        printf("2. Llenado manual (ingrese '.' para finalizar)\n");
        printf("Opcion: ");

        fgets(opcion, sizeof(opcion), stdin);
        opcion[strcspn(opcion, "\n")] = 0;

        if (strcmp(opcion, "1") == 0) {
            srand(time(NULL));
            int rd;
            printf("\nLlenando la cola con 10 numeros aleatorios...\n");
            for (int i = 0; i < 10; i++) {
                rd = (rand() % 10) + 1;
                c_encolar(c, te_crear(rd));
            }
        } else if (strcmp(opcion, "2") == 0) {
            printf("\nIngrese numeros enteros para encolar. Escriba '.' y presione Enter para finalizar.\n");
            while (1) {
                printf("> ");
                fgets(entrada, sizeof(entrada), stdin);
                entrada[strcspn(entrada, "\n")] = 0;

                if (strcmp(entrada, ".") == 0) {
                    break;
                }

                if (esEntero(entrada)) {
                    numero = atoi(entrada);
                    c_encolar(c, te_crear(numero));
                } else {
                    printf("Error: '%s' no es un numero entero valido. Intente de nuevo.\n", entrada);
                }
            }
        } else {
            printf("Opcion no valida. Volviendo al menu principal.\n");
            printf("\nPresione Enter para repetir, o 'q' para salir al menu principal: ");
            fgets(continue_choice, sizeof(continue_choice), stdin);
            continue_choice[strcspn(continue_choice, "\n")] = 0;
            if (strcmp(continue_choice, "q") == 0 || strcmp(continue_choice, "Q") == 0) {
                break;
            }
            continue;
        }

        if (c_es_vacia(c)) {
            printf("\nLa cola esta vacia. No hay nada que procesar.\n");
        } else {
            printf("\nCola Original:\n");
            c_mostrar(c);

            res = c_ej4_colanorepetidos(c);

            printf("\nCola con elementos no repetidos:\n");
            c_mostrar(res);
        }

        printf("\n-------------------------------------------------\n");
        printf("Analisis de Complejidad Algoritmica:\n");
        printf("La funcion principal c_ej4_colanorepetidos tiene una complejidad de O(N^2).\n");
        printf("Esto se debe a que por cada elemento de la cola, recorre el resto de los elementos para buscar duplicados.\n");
        printf("Esta complejidad asume que las operaciones basicas de la cola (encolar, desencolar) son O(1), como en implementaciones con punteros o arreglos circulares.\n");
        printf("Si la implementacion usara arreglos con desplazamiento, donde desencolar es O(N), la complejidad total podria ascender a O(N^3).\n");

        printf("\nPresione Enter para repetir, o 'q' para salir al menu principal: ");
        fgets(continue_choice, sizeof(continue_choice), stdin);
        continue_choice[strcspn(continue_choice, "\n")] = 0;

    } while (strcmp(continue_choice, "q") != 0 && strcmp(continue_choice, "Q") != 0);

    return 0;
}


//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 5------------------------------------------------
//-------------------------------------------------------------------------------------------------------

void mostrarResultadoEjercicio5(Cola c){
    //llama a la funcion principal y muestra el resultado

    Cola cAux = c_crear();   //cola auxiliar para no perder la lista resultado
    Cola resu = c_crear();   //cola resultado
    TipoElemento tAux;   //variable tipo elemento auxiliar

    c_mostrar(c);   //cola original

    resu = c_ej5_divisortotal(c); 

    while (!c_es_vacia(resu)){
        //imprime el resultado de la cola

        tAux = c_desencolar(resu);

        printf("%d - ", tAux->clave);
        
        if ((*(bool*)tAux->valor) == true){
            printf("divisor total\n");
        }
        else {
            printf("divisor parcial\n");
        }
    }

    while (!c_es_vacia(cAux)){
        //vuelve a armar la lista resultado
        c_encolar(resu, c_desencolar(cAux));
    }

}

bool repeticionesEjercicio5(int *arr, int n, int lon){
    //comprueba que no se agreguen repeticiones en los valores

    for (int i=0; i<lon; i++){
        if (n == arr[i]){
            return true;
        }
    }

    return false;
}

void cargaEjercicio5(){

    Cola c = c_crear();
    char dato[100];   //buffer de entrada
    int valores[10];   //vector donde se almacenan los valores en una primera instancia
    int lon = 0;   //longitud de la cola

    printf("Ingrese los valores de la cola (minimo 2 elementos, maximo 10 elementos)\n");
    printf("Numeros enteros mayores a 1 sin repeticiones( . para terminar la carga)\n");

    while (lon < 10){
        //limita el ingreso a 10 valores

        printf("%d: ", lon+1);

        fflush(stdin);
        //valida que no se ingresen valores menores a 2, que no sean repetidos
        //y que la cola no tenga menos de dos elementos
        while ((strcmp(fgets(dato, 100, stdin), ".\n") != 0) && (!esEnteroNoNegativo(dato) 
                || atoi(dato)<2 || repeticionesEjercicio5(valores, atoi(dato), lon))){

            printf("Error. Ingrese un valor valido\n");
            printf("%d: ", lon+1);
            fflush(stdin);
        }
        
        if (strcmp(dato, ".\n") == 0 && lon < 2){
            //valida que la cola no tenga menos de 2 elementos antes de salir
            printf("Error. La lista debe tener 2 elementos como minimo\n");
        }
        else if(strcmp(dato, ".\n") == 0){
            //utiliza "." para finalizar la carga
            printf("Saliendo\n");
            break;
        }
        else {
            //agrega los valores al arreglo y aumenta la longitud de la cola
            valores[lon] = atoi(dato);
            lon++;
        }
    }

    for (int i=0; i<lon; i++){
        //crea la cola con los valores introducidos en el vector
        c_encolar(c, te_crear(valores[i]));
    }

    mostrarResultadoEjercicio5(c);
}

Cola c_ej5_divisortotal(Cola c){

    int lon = 0;   //almacena la longitud de la cola

    TipoElemento tAux1;   
    TipoElemento tAux2;   //variables tipo elemento auxiliares para manipular valores

    Cola cAux1 = c_crear();
    Cola cAux2 = c_crear();   //colas que procesan los datos para no afectar los elementos de la cola original

    Cola resu = c_crear();   //cola que almacena el resultado

    static bool total = true;
    static bool parcial = false;   //variables que se usaran para almacenar el resultado del divisor en el campo de valor

    while (!c_es_vacia(c)){
        //vacia la lista original para contar sus elementos y crear las auxiliares

        tAux1 = c_desencolar(c);

        int *val = malloc(sizeof(int));   //variable que almacena en "valor" la cantidad de multiplos de la clave en la cola
        *val = 1;                         //comienza en 1 ya que el elemento siempre es divisor de si mismo

        c_encolar(cAux1, te_crear_con_valor(tAux1->clave, val));   //crea una lista auxiliar con los valores inicializados en 1
        c_encolar(cAux2, tAux1);   //almacena los elementos de la cola origianl sin manipular claves ni valores

        lon++;   //aumenta en 1 la lonigutd de la cola
    }

    while (!c_es_vacia(cAux2)){
        //devuelve los elementos a la cola original para no perderla
        c_encolar(c, c_desencolar(cAux2));
    }
    
    while (!c_es_vacia(cAux1)){
        //saca el primer elemento de la cola auxiliar
        tAux1 = c_desencolar(cAux1);

        while (!c_es_vacia(cAux1)){
            //saca el segundo elemento de la cola auxiliar
            tAux2 = c_desencolar(cAux1);

            //pregunta si alguno de los dos elementos a evaluar es divisor del otro
            //si alguno es divisor aumenta el valor en una unidad
            if (tAux2->clave % tAux1->clave == 0){
                (*(int*)tAux1->valor)++;   
            }          
            if (tAux1->clave % tAux2->clave == 0){
                (*(int*)tAux2->valor)++;
            }

            c_encolar(cAux2, tAux2);   //guarda en una cola auxiliar solo el segundo elemento evaluado
        }

        while (!c_es_vacia(cAux2)){
            //vuelve a llenar la primera cola auxiliar eliminando el primer elemento usado
            //ya que fue comparado contra el resto de los elementos
            c_encolar(cAux1, c_desencolar(cAux2));
        }

        //si el "valor" del elemento es igual a la longitud es divisor total
        if ((*(int*)tAux1->valor == lon)){
            //free(tAux1->valor);   //libera el puntero a entero usado como contador en "valor"
            tAux1->valor = &total;   //asigna a "valor" el booleano correspondiente al divisor total
            c_encolar(resu, tAux1);
        }
        //si el valor del elemento esta entre la longitud y la mitad de la longitud es divisor parcial
        else if ((*(int*)tAux1->valor) >= (float)lon/2){
            //free(tAux1->valor);   //libera el puntero a entero usado como contador en "valor"
            tAux1->valor = &parcial;   //asigna a "valor" el booleano correspondiente al divisor parcial
            c_encolar(resu, tAux1);
        }
    }

    return resu;
}

//-------------------------------------------------------------------------------------------------------
//--------------------------------------------EJERCICIO 6------------------------------------------------
//-------------------------------------------------------------------------------------------------------

#define MAX_TAM 10
#define MAX_VALOR 100

//Funcion auxiliar que recorre una lista y verifica si una clave ya existe
bool ya_esta_en_lista(Lista l, int clave) {
    Iterador it = iterador(l);
    while (hay_siguiente(it)) {
        TipoElemento te = siguiente(it);
        if (te->clave == clave) return true;
    }
    return false;
}

//Funcion principal del ejercicio:
Lista c_ej6_comunesapilaycola(Pila p, Cola c) {
    Lista resultado = l_crear();    //Lista donde se guardan los valores comunes
    Pila aux_pila = p_crear();      //Pila auxiliar para no perder la original
    Cola aux_cola = c_crear();      //Cola auxiliar para no perder la original
    TipoElemento te_p, te_c;
    int posiciones_pila[MAX_VALOR] = {0};
    int posiciones_cola[MAX_VALOR] = {0};
    int pila_elementos[MAX_TAM];
    int pos = 0;

    while (!p_es_vacia(p)) {   //Recorre la pila, se guarda cada clave y se apila en una auxiliar
        te_p = p_desapilar(p);
        pila_elementos[pos++] = te_p->clave;
        p_apilar(aux_pila, te_p);
    }
    for (int i = pos - 1, ord = 1; i >= 0; i--, ord++) {   //Recorre los elementos guardados en orden inverso
        if (posiciones_pila[pila_elementos[i]] == 0)
            posiciones_pila[pila_elementos[i]] = ord;
    }
    while (!p_es_vacia(aux_pila)) {  //Restaura la pila original volviendo a desapilar desde la auxiliar
        p_apilar(p, p_desapilar(aux_pila));
    }

    pos = 1;
    while (!c_es_vacia(c)) {    //Recorre la cola normalmente y registra la posicion ordinal de cada clave
        te_c = c_desencolar(c);
        if (posiciones_cola[te_c->clave] == 0)
            posiciones_cola[te_c->clave] = pos;
        c_encolar(aux_cola, te_c);
        pos++;
    }
    while (!c_es_vacia(aux_cola)) {   //Restaura la cola original desde la auxiliar
        c_encolar(c, c_desencolar(aux_cola));
    }

    for (int i = 0; i < MAX_VALOR; i++) { //Se recorren las claves y se verifica las claves comunes
        if (posiciones_pila[i] > 0 && posiciones_cola[i] > 0) {
            char *cadena = malloc(30);
            sprintf(cadena, "%d:%d:%d", i, posiciones_pila[i], posiciones_cola[i]);
            TipoElemento te = te_crear_con_valor(i, cadena);
            l_agregar(resultado, te);
        }
    }

    return resultado; //Devuelve la lista con los resultados encontrados de la pila y la cola
}

//Funcion de carga del ejercicio junto al uso de la funcion principal
void cargarEjercicio6() {
    Pila p = p_crear();
    Cola c = c_crear();
    char opcion[10];

    //Menu que presenta carga manual o aleatoria, junto a su validacion
    while (1) {
        printf("Seleccione tipo de carga (1=manual, 2=aleatoria): ");
        fgets(opcion, sizeof(opcion), stdin);
        if ((strlen(opcion) == 2 && (opcion[0] == '1' || opcion[0] == '2')) ||
            (strlen(opcion) == 1 && (opcion[0] == '1' || opcion[0] == '2'))) {
            break;
        }
        printf("Entrada invalida. Ingrese 1 o 2.\n");
    }

    char buffer[100];
    int cantidad;

    if (opcion[0] == '2') { //Carga aleatoria
        srand(time(NULL));
        int cantidad_p = rand() % MAX_TAM + 1;
        int cantidad_c = rand() % MAX_TAM + 1;
        for (int i = 0; i < cantidad_p; i++) {  //Se generan valores aleatorios para la pila
            p_apilar(p, te_crear(rand() % MAX_VALOR));
        }
        for (int i = 0; i < cantidad_c; i++) {  //Se generan valores aleatorios para la cola
            c_encolar(c, te_crear(rand() % MAX_VALOR));
        }
        printf("\nPila generada:\n");
        p_mostrar(p);

        printf("\nCola generada:\nContenido de la cola: ");
        Cola aux = c_crear();
        while (!c_es_vacia(c)) {
            TipoElemento x = c_desencolar(c);
            printf("%d ", x->clave);
            c_encolar(aux, x);
        }
        printf("\n");
        while (!c_es_vacia(aux)) {
            c_encolar(c, c_desencolar(aux));
        }
    } else { //Carga manual
        printf("\nIngrese cantidad de elementos para la pila: ");
        while (1) {
            fgets(buffer, sizeof(buffer), stdin);
            if (esEnteroPositivo(buffer)) {
                cantidad = atoi(buffer);
                if (cantidad <= MAX_TAM) break;
            }
            printf("Cantidad invalida. Maximo permitido: %d\n", MAX_TAM);
        }
        for (int i = 0; i < cantidad; i++) {  //Solicita valores uno por uno con validacion de enteros
            printf("Elemento pila [%d]: ", i + 1);
            fgets(buffer, sizeof(buffer), stdin);
            while (!esEntero(buffer)) {
                printf("Entrada invalida. Ingrese un entero: ");
                fgets(buffer, sizeof(buffer), stdin);
            }
            p_apilar(p, te_crear(atoi(buffer)));
        }

        printf("\nIngrese cantidad de elementos para la cola: ");  //Misma logica que lo anterior para la cola
        while (1) {
            fgets(buffer, sizeof(buffer), stdin);
            if (esEnteroPositivo(buffer)) {
                cantidad = atoi(buffer);
                if (cantidad <= MAX_TAM) break;
            }
            printf("Cantidad invalida. Maximo permitido: %d\n", MAX_TAM);
        }
        for (int i = 0; i < cantidad; i++) {
            printf("Elemento cola [%d]: ", i + 1);
            fgets(buffer, sizeof(buffer), stdin);
            while (!esEntero(buffer)) {
                printf("Entrada invalida. Ingrese un entero: ");
                fgets(buffer, sizeof(buffer), stdin);
            }
            c_encolar(c, te_crear(atoi(buffer)));
        }

        printf("\nPila ingresada:\n");
        p_mostrar(p);

        printf("\nCola ingresada:\nContenido de la cola: ");
        Cola aux = c_crear();
        while (!c_es_vacia(c)) {
            TipoElemento x = c_desencolar(c);
            printf("%d ", x->clave);
            c_encolar(aux, x);
        }
        printf("\n");
        while (!c_es_vacia(aux)) {
            c_encolar(c, c_desencolar(aux));
        }
    }

    Lista comunes = c_ej6_comunesapilaycola(p, c);  //Se obtiene la lista de valores comunes y se muestra al usuario
    printf("\nValores comunes y sus posiciones:\n");
    Iterador it = iterador(comunes);
    bool hay_resultados = false;
    while (hay_siguiente(it)) {
        TipoElemento te = siguiente(it);
        printf("%s\n", (char *) te->valor);
        hay_resultados = true;
    }
    if (!hay_resultados) {
        printf("No se encontraron elementos en comun entre la pila y la cola.\n");
    }
}
