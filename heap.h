#ifndef __HEAP_H__
#define __HEAP_H__


#include <stdbool.h>
#include <stdlib.h>


/*
 * Comparador de elementos. Recibe dos elementos del arbol y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
typedef int (*heap_comparador)(void*, void*);

/*
 * Destructor de elementos. Cada vez que un elemento deja el arbol
 * (arbol_borrar o arbol_destruir) se invoca al destructor pasandole
 * el elemento.
 */
typedef void (*heap_liberar_elemento)(void*);


typedef struct heap{
  void** vector;
  heap_comparador comparador;
  heap_liberar_elemento destructor;
  size_t cant_elementos;
} heap_t;

/*
	Pre-condiciones:
		"heap->comparador" debe ser diferente de NULL. 
	Post-condiciones:
		la función devuelve una variable con sus campos inicializados
			correctamente, de ser posible.
 */
heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor);

/*
Pre-condiciones:
	"heap" debe estar inicializado y tener todos sus campos válidos;
   "*elemento" debe ser distinto de null, sino no se podrá diferenciar de una
   		posición vacía.
Post-condiciones:
	la función solicita memoria para agrandar el vector, en caso de obtenerla
		inicializa sus campos de manera válida. Se coloca el elemento en donde
		corresponda, además se actualiza la cantidad de elementos de la
		lista;
	la función devuelve ERROR si no hay "heap", "vector" o si no se pudo reservar memoria;
	la función devuelve EXITO si pudo cumplir con éxito su cometido.
*/
int heap_insertar(heap_t* heap, void* elemento);

/*
Pre-condiciones:
	"heap" debe estar inicializado y tener todos sus campos válidos.
Post-condiciones:
	la función actualiza el vector;
	la función devuelve ERROR si no hay heap o si no hay elementos;
	la función devuelve EXITO si pudo cumplir con éxito su cometido.
*/
int heap_eliminar_raiz(heap_t* heap);

/*
Pre-condiciones:
	"heap" debe estar inicializado y tener todos sus campos válidos.
Post-condiciones:
	la función devuelve el elemento de la raiz;
	la función devuelve NULL si no hay "heap" o hay pero está vacío.
*/
void* heap_elemento_raiz(heap_t* heap);

/*
Pre-condiciones:
	"heap" debe estar inicializado y tener todos sus campos válidos.
Post-condiciones:
	la función libera la memoria reservada para "heap", lo que involucra también
		liberar la memoria ocupada por los elementos del vector;
	la función libera el vector;
	la función termina si no hay "heap".
*/
void heap_destruir(heap_t* heap);


#endif /* __HEAP_H__ */