#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

#define EXITO	0
#define ERROR	-1

/*
Pre-condiciones:
	"*pila" es diferente a NULL.
Post-condiciones:
	la función actualiza el valor de sus campos por valores válidos y nulos.
*/
void inicializar_pila(pila_t* pila){
	
	pila->nodo_inicio = NULL;
	pila->nodo_fin = NULL;
	pila->cantidad = 0;
}

/* 
Pre-condiciones:
	"*pila" debe estar inicializado y tener todos sus campos válidos:
		"pila->nodo_inicio" debe apuntar a una posición válida;
		"pila->nodo_fin" debe apuntar a una posición válida;
		"pila->cantidad" debe ser mayor a 0.
	"*nodo_a_borrar" debe ser diferente de null y tener sus campos válidos:
		"nodo_a_borrar->elemento" debe no ser nulo;
	"**nodo_a_rellenar" debe ser diferente de null y tener sus campos válidos.
	"*retorno" debe ser ERROR.
Post-condiciones:
	la función actualiza el nodo a rellenar con relleno nodo, luego libera
		la memoria reservada para nodo a borrar;
	la función actualiza la cantidad de la pila;
	la función actualiza el valor de "*retorno".
*/
void static borrar_nodo(pila_t* pila, nodo_t* nodo_a_borrar, nodo_t** nodo_a_rellenar,
	nodo_t* relleno_nodo, int* retorno){
	
	*nodo_a_rellenar = relleno_nodo;
	free(nodo_a_borrar);
	pila->cantidad--;
	*retorno = EXITO;
}

/* 
Pre-condiciones:
	"*pila" debe estar inicializado y tener todos sus campos válidos:
		"pila->nodo_inicio" debe apuntar a una posición válida;
		"pila->nodo_fin" debe apuntar a una posición válida;
		"pila->cantidad" debe ser mayor a 0.
Post-condiciones:
	la función busca en la pila un nodo que cumpla con es_nodo_borrar() y libera
		la memoria reservada para ese nodo;
	la función devuelve EXITO o ERROR.
*/
int static buscar_y_borrar(pila_t* pila, size_t tope, nodo_t* nodo_fin){
	nodo_t* nodo_actual = pila->nodo_inicio, *nodo_borrar;
	int retorno = ERROR;
	size_t i = 0;

	while((i < tope) && nodo_actual && (retorno != EXITO)){

		if(nodo_fin == nodo_actual->siguiente){
					
			nodo_borrar = nodo_actual->siguiente;
			borrar_nodo(pila, nodo_borrar, &(pila->nodo_fin), nodo_actual, &retorno);
		}
		avanzar_nodo(&nodo_actual, &i);
	}

	return retorno;
}

//------------------------------------------------------------------------------------FUNCIONES DEL .H

/*** Pre y post condiciones en pila.h ***/
pila_t* pila_crear(){
	pila_t* pila = NULL;

	pila = malloc(sizeof(pila_t));
	if(pila)
		inicializar_pila(pila);

	return pila;
}

/*** Pre y post condiciones en pila.h ***/
bool pila_vacia(pila_t* pila){

	return (!pila || !pila_elementos(pila));
}

/*** Pre y post condiciones en pila.h ***/
size_t pila_elementos(pila_t* pila){
	size_t cantidad = 0;

	if(pila)
		cantidad = pila->cantidad;

	return cantidad; 
}

/*** Pre y post condiciones en pila.h ***/
int pila_apilar(pila_t* pila, void* elemento){

	nodo_t* nuevo_nodo;

	if(!pila)
		return ERROR;
	
	nuevo_nodo = crear_nodo(elemento, NULL);
	if(!nuevo_nodo)
		return ERROR;

	if(pila_vacia(pila))
		pila->nodo_inicio = nuevo_nodo;
	else
		(pila->nodo_fin)->siguiente = nuevo_nodo;

	pila->nodo_fin = nuevo_nodo;
	pila->cantidad++;

	return EXITO;
}

/*** Pre y post condiciones en pila.h ***/
int pila_desapilar(pila_t* pila){

	nodo_t* nodo_actual = NULL;
	int retorno;

	if(!pila || pila_vacia(pila))
		return ERROR;

	nodo_actual = pila->nodo_inicio;
	if(pila_elementos(pila) == 1){
		
		borrar_nodo(pila, nodo_actual, &(pila->nodo_fin), NULL, &retorno);
		pila->nodo_inicio = NULL;
	}
	else
		retorno = buscar_y_borrar(pila, pila_elementos(pila), pila->nodo_fin);
	
	return retorno;
}

/*** Pre y post condiciones en pila.h ***/
void* pila_tope(pila_t* pila){

	if(!pila || pila_vacia(pila))
		return NULL;

	return (pila->nodo_fin)->elemento;
}

/*** Pre y post condiciones en pila.h ***/
void pila_destruir(pila_t* pila){
	int retorno = EXITO;

	if(!pila)
		return;

	while((pila_elementos(pila) != 0) && (retorno == EXITO))
		retorno = pila_desapilar(pila);

	free(pila);
}

void* pila_elemento_en_posicion(pila_t* pila, size_t posicion){
	nodo_t* nodo_actual;
	void* elemento = NULL;
	size_t i = 0;

	if(!pila || pila_vacia(pila) || (posicion > (pila_elementos(pila) - 1)))
		return NULL;

	nodo_actual = pila->nodo_inicio;
	while((i < pila_elementos(pila)) && nodo_actual && !elemento){

		if(i == posicion)		
			elemento = nodo_actual->elemento;
		avanzar_nodo(&nodo_actual, &i);
	}
	
	return elemento;
}

