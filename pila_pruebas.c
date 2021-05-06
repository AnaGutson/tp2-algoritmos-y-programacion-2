#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"
#include "ptda.h"

#define EXITO	0
#define ERROR	-1

#define STRING_CANT_INSERCION  			"50"
#define CANT_INSERCION  				50
#define STRING_CANT_INSERCION_MENOS_1  	"49"

#define STRING_CANT_BORRAR	  	"30"
#define CANT_BORRAR 	 		30

#define STRING_CANT_BUSCAR  	"50"
#define CANT_BUSCAR  			50

int* crear_valores_insertar(){
	int *vector = NULL;

	vector = malloc(sizeof(int)*CANT_INSERCION);
	if(!vector)
		return NULL;

	for(int i = 0; i < CANT_INSERCION; i++)
		vector[i] = i;

	return vector;
}

int borrar_muchos(pila_t* pila, int(*eliminar)(pila_t*)){
	int retorno = EXITO, i = 0;

	while(i < CANT_BORRAR && retorno == EXITO){
		
		retorno = eliminar(pila);
		i++;
	}

	return retorno;
}

int insertar_elementos_pila(int* valor, pila_t* pila, int cant_elementos,
	int(*funcion_insertar)(pila_t*, void*)){
	int retorno = EXITO, i = 0;

	while((i < cant_elementos) && (retorno == EXITO)){
		
		retorno = funcion_insertar(pila, &(valor[i]));
		i++;
	}

	return retorno;
}

void reiniciar_pila(pila_t* pila, int(*eliminar)(pila_t*)){

	while(pila_elementos(pila) != 0)
		eliminar(pila);
}

//-------------------------------------------------------------------------PILA

void probar_crear_pila(){
	pila_t* pila;

	pila = pila_crear();

	ptda_nuevo_subgrupo("Creación pila");
	
	ptda_afirmar(pila, "Se puede crear una pila");
	ptda_subafirmar_fin(pila && pila_vacia(pila), "La pila tiene sus campos inicializados correctamente");

	pila_destruir(pila);
}

void probar_apilar_pila(int* valor){
	int retorno;
	pila_t* pila;

	pila = pila_crear();
	
	ptda_nuevo_subgrupo("Apilar - pila");
	
	ptda_afirmar(pila_apilar(NULL, &(valor[0])) == ERROR, "No se puede apilar en una pila no creada");
	
	retorno = insertar_elementos_pila(valor, pila, 1, pila_apilar);
	ptda_afirmar(retorno == EXITO, "Se puede apilar en una pila vacía");
	ptda_subafirmar((retorno == EXITO) && (1 == pila_elementos(pila)), "La cantidad de elementos de la pila es correcta");
	ptda_subafirmar_fin((retorno == EXITO) && ((pila->nodo_inicio) == (pila->nodo_fin)) && (pila->nodo_inicio), "El inicio y fin de la pila son correctos");

	pila_destruir(pila);
}

void probar_desapilar_pila(int* valor){
	int retorno;
	nodo_t *nodo_inicio_inicial;
	pila_t* pila;

	pila = pila_crear();
	
	ptda_nuevo_subgrupo("Desapilar - pila");

	ptda_afirmar(pila_desapilar(NULL) == ERROR, "No se puede desapilar una pila no creada");

	ptda_afirmar(pila_desapilar(pila) == ERROR, "No se puede desapilar en una pila vacía");
	
	insertar_elementos_pila(valor, pila, 1, pila_apilar);
	retorno = pila_desapilar(pila);
	ptda_afirmar(retorno == EXITO, "Se puede desapilar el unico elemento en una pila");
	ptda_subafirmar((retorno == EXITO) && (0 == pila_elementos(pila)), "La cantidad de elementos de la pila es correcta");
	ptda_subafirmar_fin((retorno == EXITO) && (pila->nodo_fin == NULL) && (pila->nodo_inicio == pila->nodo_fin), "El inicio y fin de la pila son correctos");

	insertar_elementos_pila(valor, pila, CANT_INSERCION, pila_apilar);
	nodo_inicio_inicial = pila->nodo_inicio;
	retorno = borrar_muchos(pila, pila_desapilar);
	ptda_afirmar(retorno == EXITO, "Se puede desapilar "STRING_CANT_BORRAR" elementos de la pila");
	ptda_subafirmar(retorno == EXITO && (CANT_INSERCION - CANT_BORRAR) == pila_elementos(pila), "La cantidad de elementos de la pila es correcta");
	ptda_subafirmar_fin(retorno == EXITO && nodo_inicio_inicial == pila->nodo_inicio, "Los elementos de la pila están correctamente ordenados");

	while(pila_elementos(pila) != 0 && retorno == EXITO)
		retorno = pila_desapilar(pila);
	ptda_afirmar(retorno == EXITO, "Se puede desapilar todos los elementos de la pila");
	ptda_subafirmar_fin(retorno == EXITO && pila_vacia(pila), "La pila quedó vacía correctamente");

	pila_destruir(pila);
}

void probar_obtener_tope_pila(int* valor){
	void* elemento;
	pila_t* pila;

	pila = pila_crear();

	ptda_nuevo_subgrupo("Obtener elemento en el tope - pila");

	ptda_afirmar(!pila_tope(NULL), "No se puede obtener el tope de una pila no creada");

	ptda_afirmar(!pila_tope(pila), "No se puede obtener el tope de una pila vacía");

	insertar_elementos_pila(valor, pila, 1, pila_apilar);
	elemento = pila_tope(pila);
	ptda_afirmar(elemento, "Se puede obtener el tope de una pila con un elemento");
	ptda_subafirmar_fin(elemento == &(valor[0]), "El valor del elemento buscado en la pila es correcto");

	reiniciar_pila(pila, pila_desapilar);
	insertar_elementos_pila(valor, pila, CANT_INSERCION, pila_apilar);
	elemento = pila_tope(pila);
	ptda_afirmar(elemento, "Se puede obtener el tope de una pila con muchos elementos");
	ptda_subafirmar_fin(elemento == &(valor[CANT_INSERCION-1]), "El valor del elemento buscado en la pila es correcto");

	pila_destruir(pila);
}

void probar_esta_vacia_pila(int* valor){
	pila_t* pila;

	pila = pila_crear();

	ptda_nuevo_subgrupo("Esta vacía - pila");
	
	ptda_afirmar(pila_vacia(NULL), "Se puede detectar que una pila nula está vacía")

	ptda_afirmar(pila_vacia(pila), "Se puede detectar que una pila sin elementos está vacía")
	
	insertar_elementos_pila(valor, pila, 1, pila_apilar);
	ptda_afirmar(!pila_vacia(pila), "Se puede detectar que una pila con un elemento no está vacía")

	reiniciar_pila(pila, pila_desapilar);
	insertar_elementos_pila(valor, pila, CANT_INSERCION, pila_apilar);
	ptda_afirmar(!pila_vacia(pila), "Se puede detectar que una pila con varios elementos no está vacía");

	pila_destruir(pila);
}

void probar_cantidad_elementos_pila(int* valor){
	pila_t* pila;

	pila = pila_crear();

	ptda_nuevo_subgrupo("Obtener cantidad elementos - pila");

	ptda_afirmar(pila_elementos(NULL) == 0, "Se puede detectar la cantidad de elementos en una pila nula");

	ptda_afirmar(pila_elementos(pila) == 0, "Se puede detectar la cantidad de elementos en una pila con 0 elementos");
	
	insertar_elementos_pila(valor, pila, 1, pila_apilar);
	ptda_afirmar(pila_elementos(pila) == 1, "Se puede detectar la cantidad de elementos en una pila con 1 elemento");
	
	reiniciar_pila(pila, pila_desapilar);
	insertar_elementos_pila(valor, pila, CANT_INSERCION, pila_apilar);
	ptda_afirmar(pila_elementos(pila) == CANT_INSERCION, "Se puede detectar la cantidad de elementos en una pila con muchos elementos");

	pila_destruir(pila);
}

void probar_pila(){
	int *valor;

	valor = crear_valores_insertar();
	if(!valor)
		return;
	
	ptda_nuevo_grupo("Pruebas: operaciones");
	probar_crear_pila();
	probar_apilar_pila(valor);
	probar_desapilar_pila(valor);
	probar_obtener_tope_pila(valor);

	ptda_nuevo_grupo("Pruebas: información");
	probar_esta_vacia_pila(valor);
	probar_cantidad_elementos_pila(valor);
	
	free(valor);
}

//-------------------------------------------------------------------

int main(){
	
	ptda_nueva_categoria("Pruebas pila");
	probar_pila();

	ptda_mostrar_reporte();
}