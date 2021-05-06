#ifndef __LISTA_H__
#define __LISTA_H__

#include <stdbool.h>
#include <stddef.h>
#include "nodo.h"

typedef struct lista{
	nodo_t* nodo_inicio;
	nodo_t* nodo_fin;
	size_t cantidad;
}lista_t;

typedef struct lista_iterador{
	nodo_t* corriente;
	lista_t* lista;
}lista_iterador_t;

/*
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
/*
Pre-condiciones:
	-.
Post-condiciones:
	la función reserva, de ser posible, la cantidad de memoria necesaria para
		una lista y la inicializa, devolviendo un puntero a la lista creada o
		NULL en caso de error.
*/
lista_t* lista_crear();

/*
 * Inserta un elemento al final de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
/*
Pre-condiciones:
	"lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida o ser nulo;
		"lista->nodo_fin" debe apuntar a una posición válida o ser nulo.
   "*elemento" debe ser distinto de null, sino no se podrá diferenciar de una
   		posición vacía.
Post-condiciones:
	la función solicita memoria para un nuevo nodo, en caso de obtenerla
		inicializa sus campos de manera válida. Se coloca el nuevo nodo a lo
		último de la lista, además se actualiza la cantidad de elementos de la
		lista;
	la función devuelve ERROR si no hay lista o si no se pudo reservar memoria;
	la función devuelve EXITO si pudo cumplir con éxito su cometido.
*/
int lista_insertar(lista_t* lista, void* elemento);

/*
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
/*
Pre-condiciones:
	"lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida o ser nulo;
		"lista->nodo_fin" debe apuntar a una posición válida o ser nulo.
   "*elemento" debe ser distinto de null, sino no se podrá diferenciar de una
   		posición vacía.
Post-condiciones:
	la función solicita memoria para un nuevo nodo, en caso de obtenerla
		inicializa sus campos de manera válida. Se coloca el nuevo nodo en la
		posición "posicion", además se actualiza la cantidad de elementos de la
		lista;
	la función devuelve ERROR si no hay lista o si no se pudo reservar memoria;
	la función devuelve EXITO si pudo cumplir con éxito su cometido.
*/
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion);

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
/*
Pre-condiciones:
	"lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida;
		"lista->nodo_fin" debe apuntar a una posición válida;
		"lista->cantidad" debe ser diferente de 0.
Post-condiciones:
	la función libera memoria reservada para el último nodo de la lista;
	la función devuelve ERROR si no hay lista o si no se pudo liberar memoria;
	la función devuelve EXITO si pudo cumplir con éxito su cometido.
*/
int lista_borrar(lista_t* lista);

/*
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento.  
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.  
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
/*
Pre-condiciones:
	"lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida;
		"lista->nodo_fin" debe apuntar a una posición válida;
		"lista->cantidad" debe ser diferente de 0.
Post-condiciones:
	la función libera memoria reservada para el nodo de la lista en la posición
		indicada;
	la función devuelve ERROR si no hay lista, hay pero está vacía o si no se
		pudo liberar memoria: no porque fallara el free, sino que porque no
		se encontró al elemento o similares;
	la función devuelve EXITO si pudo cumplir con éxito su cometido.
*/
int lista_borrar_de_posicion(lista_t* lista, size_t posicion);

/*
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
/*
Pre-condiciones:
	"lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida;
		"lista->nodo_fin" debe apuntar a una posición válida;
		"lista->cantidad" debe ser diferente de 0.
	"posicion" debe ser un valor válido.
Post-condiciones:
	la función devuelve el elemento en la posicion requerida;
	la función devuelve NULL si no hay lista, hay pero está vacía, si se
		requirió un elemento en una posicion que no existe o si no se 
		encontró la posicion pedida.
*/
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion);

/* 
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
/*
Pre-condiciones:
	"lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida;
		"lista->nodo_fin" debe apuntar a una posición válida;
		"lista->cantidad" debe ser diferente de 0.
Post-condiciones:
	la función devuelve el último elemento;
	la función devuelve NULL si no hay lista o hay pero está vacía.
*/
void* lista_ultimo(lista_t* lista);

/* 
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
/*
Pre-condiciones:
	"lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida;
		"lista->nodo_fin" debe apuntar a una posición válida;
		"lista->cantidad" debe ser diferente de 0.
Post-condiciones:
	la función devuelve si la lista está vacía, una lista nula está vacía.
*/
bool lista_vacia(lista_t* lista);

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
/*
Pre-condiciones:
	"lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida;
		"lista->nodo_fin" debe apuntar a una posición válida.
Post-condiciones:
	la función devuelve la cantidad de elementos de la lista, una lista nula
		está vacía.
*/
size_t lista_elementos(lista_t* lista);

/*
 * Libera la memoria reservada por la lista.
 */
/*
Pre-condiciones:
	"lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida;
		"lista->nodo_fin" debe apuntar a una posición válida.
Post-condiciones:
	la función libera la memoria reservada para la lista, lo que involucra también
		liberar la memoria ocupada por los nodos de la lista;
	la función termina si no hay lista.
*/
void lista_destruir(lista_t* lista);

/*
 * Crea un iterador para una lista. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique la lista iterada (agregando o quitando
 * elementos de la lista). 
 *
 * Al momento de la creación, el iterador queda listo para devolver el
 * primer elemento utilizando lista_iterador_elemento_actual.
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
/*
Pre-condiciones:
	"lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida o ser nulo;
		"lista->nodo_fin" debe apuntar a una posición válida o ser nulo.
Post-condiciones:
	la función reserva, de ser posible, la cantidad de memoria necesaria para
		un iterador y lo inicializa, devolviendo un puntero al puntero creado;
	la función devuelve NULL en caso de no poder reservar memoria para el iterador
		o si no hay lista.
*/
lista_iterador_t* lista_iterador_crear(lista_t* lista);

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
/* 
Pre-condiciones:
	-.
Post-condiciones:
	la función devuelve si existe "iterador->corriente".
*/
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador);

/*
 * Avanza el iterador al siguiente elemento.
 * Devuelve true si pudo avanzar el iterador o false en caso de
 * que no queden elementos o en caso de error.
 *
 * Una vez llegado al último elemento, si se invoca a
 * lista_iterador_elemento_actual, el resultado siempre será NULL.
 */
/*
Pre-condiciones:
	"iterador" debe estar inicializado y tener todos sus campos válidos:
		"iterador->corriente" debe apuntar a una posición válida.
Post-condiciones:
	la función avanza el iterador->corriente al nodo siguiente;
	la función devuelve NULL en caso de que iterador sea nulo o
		iterador->corriente sea nulo.
*/
bool lista_iterador_avanzar(lista_iterador_t* iterador);

/*
 * Devuelve el elemento actual del iterador o NULL en caso de que no
 * exista dicho elemento o en caso de error.
 */
/*
Pre-condiciones:
	"iterador" debe estar inicializado y tener todos sus campos válidos:
		"iterador->corriente" debe apuntar a una posición válida.
Post-condiciones:
	la función devuelve el elemento actual;
	la función devuelve NULL si no hay iterador o no hay iterador->corriente.
*/
void* lista_iterador_elemento_actual(lista_iterador_t* iterador);

/*
 * Libera la memoria reservada por el iterador.
 */
/*
Pre-condiciones:
	"lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida;
		"lista->nodo_fin" debe apuntar a una posición válida.
Post-condiciones:
	la función libera la memoria reservada para el iterador si
		es que hay memoria reservada.
*/
void lista_iterador_destruir(lista_iterador_t* iterador);

/*
 * Iterador interno. Recorre la lista e invoca la funcion con cada elemento de
 * la misma. Dicha función puede devolver true si se deben seguir recorriendo
 * elementos o false si se debe dejar de iterar elementos.
 *
 * La función retorna la cantidad de elementos iterados o 0 en caso de error.
 */
/* 
Pre-condiciones:
	"*lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida;
		"lista->nodo_fin" debe apuntar a una posición válida;
		"lista->cantidad" debe ser mayor a 0.
	"*contexto" debe ser el parámetro que se va a usar en funcion().
Post-condiciones:
	la función llama a "funcion()" hasta que esta devuelva false;
	la función devuelve cuantas veces se llamó a funcion();
	la función devuelve 0 si no hay lista, hay pero está vacía o si 
		no hay función.
*/
size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto);

#endif /* __LISTA_H__ */
