#ifndef __NODO_H__
#define __NODO_H__


#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


typedef struct nodo{
	void* elemento;
	struct nodo* siguiente;
}nodo_t;


/*Pre-condiciones:
	-.
Post-condiciones:
	la función reserva, de ser posible, la cantidad de memoria necesaria para
		un nodo y lo inicializa, devolviendo un puntero al puntero creado o
		NULL en caso de error.
*/
nodo_t* crear_nodo(void* elemento, nodo_t* nodo_siguiente);

/* 
Pre-condiciones:
	"**nodo_actual" debe estar inicializado y tener todos sus campos válidos:
		"nodo_actual->siguiente" debe apuntar a una posición válida o ser nulo;
		"nodo_actual->elemento" debe apuntar a una posición válida.
Post-condiciones:
	la función modifica el valor del nodo actual, reemplazándolo por su siguiente;
	la función actualiza el valor de "i" incrementádolo en 1.
*/
void avanzar_nodo(nodo_t** nodo_actual, size_t* i);

#endif /* __NODO_H__ */
