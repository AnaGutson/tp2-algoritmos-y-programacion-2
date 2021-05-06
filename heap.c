#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

#define ERROR 	   -1
#define EXITO 		0

#define IZQUIERDO 	7
#define DERECHO 	8

#define IGUALES 		 0
#define PRIMERO_MAYOR 	 1
#define PRIMERO_MENOR 	-1


//_________________________________________________________INFORMACIÓN


/* 03 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retornar la posición del padre.
 */
size_t posicion_padre(size_t posicion){

	return ((posicion-1)/2);
}

/* 09 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retornar la posición del hijo.
 */
size_t posicion_hijo(size_t ubicacion, size_t posicion){
	size_t posicion_hijo;

	if(ubicacion == IZQUIERDO)
		posicion_hijo = posicion*2 + 1;
	else
		posicion_hijo = posicion*2 + 2;

	return posicion_hijo;
}


//_________________________________________________________FUNCIONES PRIVADAS


/* 06 */
/*
	Pre-condiciones:
		"heap" debe haber sido creado correctamente. 
	Post-condiciones:
		la función asigna valores iniciales a los campos de "heap".
 */
void inicializar_heap(heap_t* heap, heap_comparador comparador,
	heap_liberar_elemento destructor){

	heap->vector = NULL;
	heap->comparador = comparador;
	heap->destructor = destructor;
	heap->cant_elementos = 0;
}

/* 06 */
/*
	Pre-condiciones:
		"vector" está correctamente llenado. 
	Post-condiciones:
		la función actualiza "vector".
 */
void intercambio(void** vector, size_t pos_actual, size_t pos_padre){
	void* aux;

	aux = vector[pos_actual];
	vector[pos_actual] = vector[pos_padre];
	vector[pos_padre] = aux;
}

/* 12 */
/*
	Pre-condiciones:
		"heap" debe haber sido creado correctamente. 
	Post-condiciones:
		la función actualiza "heap->vector" si es necesario.
 */
void sift_up(heap_t* heap, heap_comparador comparador, size_t pos_actual){

	if(!heap || pos_actual == 0)
		return;

	size_t pos_padre = posicion_padre(pos_actual);

	if(comparador(heap->vector[pos_actual], heap->vector[pos_padre]) < 0){

		intercambio(heap->vector, pos_actual, pos_padre);
		sift_up(heap, comparador, pos_padre);
	}
}

/* 17 */
/*
	Pre-condiciones:
		"heap" debe haber sido creado correctamente. 
	Post-condiciones:
		la función actualiza "heap->vector" si es necesario.
 */
void sift_down(heap_t* heap, heap_comparador comparador, size_t pos_actual){
	size_t pos_hijo_derecho = posicion_hijo(DERECHO, pos_actual);
	size_t pos_hijo_izquierdo = posicion_hijo(IZQUIERDO, pos_actual);
	size_t pos_menor = pos_hijo_izquierdo;

	if(pos_hijo_izquierdo >= heap->cant_elementos)
		return;

	if(pos_hijo_derecho < heap->cant_elementos)
		if(comparador(heap->vector[pos_hijo_derecho], heap->vector[pos_hijo_izquierdo]) < 0)
			pos_menor = pos_hijo_derecho;
	
	if(comparador(heap->vector[pos_actual], heap->vector[pos_menor]) > 0){

		intercambio(heap->vector, pos_actual, pos_menor);
		sift_down(heap, comparador, pos_menor);
	}
}

/* 15 */
/*
Pre-condiciones:
	-
Post-condiciones:
	la función libera toda la memoria reservada por los elementos en "vector" si
		es que hay un "destructor";
	la función libera "vector".
*/
void liberar_elemento(void** vector, size_t *tope, heap_liberar_elemento destructor){
	size_t i = 0;

	if(destructor){

		while(i < *tope){

			destructor(vector[i]);			
			i++;
		}
		*tope = 0;
	}

	if(vector)
		free(vector);
}


//_________________________________________________________HEAP


/* 10 */
/*
	Pre y post condiciones en heap.h
 */
heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor){
	heap_t* heap = NULL;

	if(!comparador)
		return NULL;

	heap = malloc(sizeof(heap_t));
	if(heap)
		inicializar_heap(heap, comparador, destructor);

	return heap;
}

/* 12 */
/*
	Pre-condiciones:
		"puntero" debe tener todas sus campos válidos;
		"elemento" debe ser distinto de NULL.
	Post-condiciones:
		la función retorna EXITO si todo sale bien o ERROR si no se pudo
			reservar memoria:
				si retonar EXITO: mueve "elemento" a la ultima posicion de
					"puntero", ademas de actualizar "cantidad".
 */
int agrandar_vector(void*** puntero, void* elemento, size_t *cantidad){
	void* nuevo_puntero = NULL;

	nuevo_puntero = realloc((*puntero), sizeof(void*)*(*cantidad + 1));
	if(!nuevo_puntero)
		return ERROR;

	(*puntero) = nuevo_puntero;
	(*cantidad)++;
	(*puntero)[*cantidad-1] = elemento;

	return EXITO;
}

/* 09 */
/*
	Pre y post condiciones en heap.h
 */
int heap_insertar(heap_t* heap, void* elemento){

	if(!heap)
		return ERROR;

	agrandar_vector(&(heap->vector), elemento, &(heap->cant_elementos));
	sift_up(heap, heap->comparador, heap->cant_elementos - 1);

	return EXITO;
}

/* 17 */
/*
	Pre y post condiciones en heap.h
 */
int heap_eliminar_raiz(heap_t* heap){ //hacer_rpeubas

	if(!heap || heap->cant_elementos == 0)
		return ERROR;
	
	heap_t* elemento_eliminar = heap->vector[0];
	
	intercambio(heap->vector, 0, heap->cant_elementos-1);
	heap->cant_elementos--;

	if(heap->cant_elementos > 0)
		sift_down(heap, heap->comparador, 0);

	if(heap->destructor)
		heap->destructor(elemento_eliminar);

	return EXITO;
}

/* 06 */
/*
	Pre y post condiciones en heap.h
 */
void* heap_elemento_raiz(heap_t* heap){ //hacer_pruebas

	if(!heap || heap->cant_elementos == 0)
		return NULL;

	return heap->vector[0];
}

/* 09 */
/*
	Pre y post condiciones en heap.h
 */
void heap_destruir(heap_t* heap){

	if(!heap)
		return;

	if(heap->cant_elementos > 0)
		liberar_elemento(heap->vector, &(heap->cant_elementos), heap->destructor);
	else
		free(heap->vector);
	free(heap);
}