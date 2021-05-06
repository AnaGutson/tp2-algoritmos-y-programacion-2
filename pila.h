#ifndef __PILA_H__
#define __PILA_H__


#include <stdbool.h>
#include <stddef.h>
#include "nodo.h"


typedef struct pila{
	nodo_t* nodo_inicio;
	nodo_t* nodo_fin;
	size_t cantidad;
}pila_t;


/*
 * Crea la pila reservando la memoria necesaria.
 * Devuelve un puntero a la pila creada o NULL en caso de error.
 */
/*
Pre-condiciones:
	-.
Post-condiciones:
	la función reserva, de ser posible, la cantidad de memoria necesaria para
		una pila y la inicializa, devolviendo un puntero a la pila creada o
		NULL en caso de error.
*/
pila_t* pila_crear();

/* 
 * Devuelve true si la pila está vacía o false en caso contrario.
 */
/*
Pre-condiciones:
	"pila" debe estar inicializado y tener todos sus campos válidos:
		"pila->nodo_inicio" debe apuntar a una posición válida;
		"pila->nodo_fin" debe apuntar a una posición válida;
		"pila->cantidad" debe ser diferente de 0.
Post-condiciones:
	la función devuelve si la pila está vacía, una pila nula está vacía.
*/
bool pila_vacia(pila_t* pila);

/*
 * Devuelve la cantidad de elementos almacenados en la pila.
 */
/*
Pre-condiciones:
	"pila" debe estar inicializado y tener todos sus campos válidos:
		"pila->nodo_inicio" debe apuntar a una posición válida;
		"pila->nodo_fin" debe apuntar a una posición válida.
Post-condiciones:
	la función devuelve la cantidad de elementos de la pila, una pila nula
		está vacía.
*/
size_t pila_elementos(pila_t* pila);

/* 
 * Apila un elemento.
 * Devuelve 0 si pudo o -1 en caso contrario.
 */
/*
Pre-condiciones:
	"pila" debe estar inicializado y tener todos sus campos válidos:
		"pila->nodo_inicio" debe apuntar a una posición válida o ser nulo;
		"pila->nodo_fin" debe apuntar a una posición válida o ser nulo.
   "*elemento" debe ser distinto de null, sino no se podrá diferenciar de una
   		posición vacía.
Post-condiciones:
	la función solicita memoria para un nuevo nodo, en caso de obtenerla
		inicializa sus campos de manera válida. Se coloca el nuevo nodo a lo
		último de la pila, además se actualiza la cantidad de elementos de la
		pila;
	la función devuelve ERROR si no hay pila o si no se pudo reservar memoria;
	la función devuelve EXITO si pudo cumplir con éxito su cometido.
*/
int pila_apilar(pila_t* pila, void* elemento);

/* 
 * Desapila un elemento.
 * Devuelve 0 si pudo desapilar o -1 si no pudo.
 */
/*
Pre-condiciones:
	"pila" debe estar inicializado y tener todos sus campos válidos:
		"pila->nodo_inicio" debe apuntar a una posición válida;
		"pila->nodo_fin" debe apuntar a una posición válida;
		"pila->cantidad" debe ser diferente de 0.
Post-condiciones:
	la función libera memoria reservada para el último nodo de la pila;
	la función devuelve ERROR si no hay pila o si no se pudo liberar memoria;
	la función devuelve EXITO si pudo cumplir con éxito su cometido.
*/
int pila_desapilar(pila_t* pila);

/*
 * Devuelve el elemento en el tope de la pila o NULL
 * en caso de estar vacía.
 */
/*
Pre-condiciones:
	"pila" debe estar inicializado y tener todos sus campos válidos:
		"pila->nodo_inicio" debe apuntar a una posición válida;
		"pila->nodo_fin" debe apuntar a una posición válida;
		"pila->cantidad" debe ser diferente de 0.
Post-condiciones:
	la función devuelve el último elemento;
	la función devuelve NULL si no hay pila o hay pero está vacía.
*/
void* pila_tope(pila_t* pila);

/*
 * Libera la memoria reservada por la pila.
 */
/*
Pre-condiciones:
	"pila" debe estar inicializado y tener todos sus campos válidos:
		"pila->nodo_inicio" debe apuntar a una posición válida;
		"pila->nodo_fin" debe apuntar a una posición válida.
Post-condiciones:
	la función libera la memoria reservada para la pila, lo que involucra también
		liberar la memoria ocupada por los nodos de la pila;
	la función termina si no hay pila.
*/
void pila_destruir(pila_t* pila);

#endif /* __PILA_H__ */
