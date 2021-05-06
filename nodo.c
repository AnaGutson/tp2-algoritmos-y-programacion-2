#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "nodo.h"


/* 
	Pre y post en nodo.h
 */
nodo_t* crear_nodo(void* elemento, nodo_t* nodo_siguiente){
	nodo_t* nuevo_nodo;

	nuevo_nodo = malloc(sizeof(nodo_t));
	if(!nuevo_nodo)
		return NULL;

	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = nodo_siguiente;

	return nuevo_nodo;
}

/* 
	Pre y post en nodo.h
 */
void avanzar_nodo(nodo_t** nodo_actual, size_t* i){
	
	*nodo_actual = (*nodo_actual)->siguiente;
	(*i)++;
}