#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

#define EXITO	0
#define ERROR	-1

/*
Pre-condiciones:
	"*lista" es diferente a NULL.
Post-condiciones:
	la función actualiza el valor de sus campos por valores válidos y nulos.
*/
void inicializar_lista(lista_t* lista){
	
	lista->nodo_inicio = NULL;
	lista->nodo_fin = NULL;
	lista->cantidad = 0;
}

/* 
Pre-condiciones:
	"*lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida o ser nulo;
		"lista->nodo_fin" debe apuntar a una posición válida o ser nulo.
	"*nodo_a_insertar" debe ser diferente de null y tener sus campos válidos:
		"nodo_a_insertar->elemento" debe no ser nulo;
		"nodo_a_insertar->siguiente" debe ser nulo.
	"**nodo_a_reemplazar" debe ser diferente de null y tener sus campos válidos:
		"nodo_a_reemplazar->elemento" debe no ser nulo;
		"nodo_a_reemplazar->siguiente" debe no ser nulo.
	"*retorno" debe ser ERROR.
Post-condiciones:
	la función actualiza el siguiente del nodo a insertar, con el nodo a
		reemplazar, luego reemplaza el nodo a reemplazar con el nodo a insertar:
		resultado: 
			primero: "*nodo_a_insertar";
			segundo: "*nodo_a_reemplazar";
	la función actualiza el valor de "*retorno".
*/
void insertar_nodo(lista_t* lista, nodo_t* nodo_a_insertar, nodo_t** nodo_a_reemplazar, 
	int* retorno){
	
	nodo_a_insertar->siguiente = *nodo_a_reemplazar;
	*nodo_a_reemplazar = nodo_a_insertar;
	*retorno = EXITO;				
}

/* 
Pre-condiciones:
	"*lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida;
		"lista->nodo_fin" debe apuntar a una posición válida;
		"lista->cantidad" debe ser mayor a 0.
	"*nodo_a_borrar" debe ser diferente de null y tener sus campos válidos:
		"nodo_a_borrar->elemento" debe no ser nulo;
	"**nodo_a_rellenar" debe ser diferente de null y tener sus campos válidos.
	"*retorno" debe ser ERROR.
Post-condiciones:
	la función actualiza el nodo a rellenar con relleno nodo, luego libera
		la memoria reservada para nodo a borrar;
	la función actualiza la cantidad de la lista;
	la función actualiza el valor de "*retorno".
*/
void static borrar_nodo(lista_t* lista, nodo_t* nodo_a_borrar, nodo_t** nodo_a_rellenar,
	nodo_t* relleno_nodo, int* retorno){
	
	*nodo_a_rellenar = relleno_nodo;
	free(nodo_a_borrar);
	lista->cantidad--;
	*retorno = EXITO;
}

/* 
Pre-condiciones:
	"*lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida;
		"lista->nodo_fin" debe apuntar a una posición válida;
		"lista->cantidad" debe ser mayor a 0.
	"*contexto" debe ser el parámetro que se va a usar en es_nodo_borrar():
		es un valor fijo que no depende del momento.
	"es_nodo_borrar()" debe ser es_nodo_borrar_normal() o es_nodo_borrar_posicion(); 	
	"borrar()" debe ser borrar_nodo_normal() o borrar_nodo_posicion().
Post-condiciones:
	la función busca en la lista un nodo que cumpla con es_nodo_borrar() y libera
		la memoria reservada para ese nodo;
	la función devuelve EXITO o ERROR.
*/
int static buscar_y_borrar(lista_t* lista, size_t tope, void* contexto,
	bool(*es_nodo_borrar)(void*, nodo_t*, size_t),
	void(*borrar)(lista_t*, nodo_t*, nodo_t*, int*)){
	
	nodo_t* nodo_actual = lista->nodo_inicio, *nodo_borrar;
	int retorno = ERROR;
	size_t i = 0;

	while((i < tope) && nodo_actual && (retorno != EXITO)){

		if(es_nodo_borrar(contexto, nodo_actual, i)){
					
			nodo_borrar = nodo_actual->siguiente;
			borrar(lista, nodo_borrar, nodo_actual, &retorno);
		}
		avanzar_nodo(&nodo_actual, &i);
	}

	return retorno;
}

//------------------------------------------------------------------------------------FUNCIONES PARA USAR CON PUNTEROS A FUNCIÓN

/* 
Pre-condiciones:
	"nodo_fin" debe estar inicializado y tener todos sus campos válidos:
		"nodo_fin->elemento" debe apuntar a una posición válida;
		"nodo_fin->siguiente" debe ser nulo.
	"nodo_actual" debe estar inicializado y tener todos sus campos válidos:
		"nodo_actual->elemento" debe apuntar a una posición válida;
		"nodo_actual->siguiente" debe ser distinto de nulo.
Post-condiciones:
	la función devuelve si "nodo_fin" y el siguiente nodo a "nodo_actual" son
		iguales.
*/
bool es_nodo_borrar_normal(void* nodo_fin, nodo_t* nodo_actual, size_t extra){

	return ((nodo_t*)nodo_fin == nodo_actual->siguiente);
}

/* 
Pre-condiciones:
	"posicion" debe ser mayor a 0.
Post-condiciones:
	la función devuelve si "posicion" - 1 e "i" son iguales.
*/
bool es_nodo_borrar_posicion(void* posicion, nodo_t* extra, size_t i){

	return ((*(size_t*)posicion - 1) == i);
}

/* 
Pre-condiciones:
	"*lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida;
		"lista->nodo_fin" debe apuntar a una posición válida;
		"lista->cantidad" debe ser mayor a 0.
	"*nodo_borrar" debe ser diferente de null y tener sus campos válidos:
		"nodo_a_borrar->elemento" debe no ser nulo;
	"nodo_actual" debe estar inicializado y tener todos sus campos válidos:
		"nodo_actual->elemento" debe apuntar a una posición válida;
		"nodo_actual->siguiente" debe ser distinto de nulo.
	"*retorno" debe ser ERROR.
Post-condiciones:
	la función actualiza "lista->nodo_fin";
	la funcion libera la memoria reservada para "nodo_borrar";
	la función actualiza la cantidad de la lista;
	la función actualiza el valor de "*retorno".
*/
void borrar_nodo_normal(lista_t* lista, nodo_t* nodo_borrar, nodo_t* nodo_actual,
	int* retorno){

	borrar_nodo(lista, nodo_borrar, &(lista->nodo_fin), nodo_actual, retorno);
}

/* 
Pre-condiciones:
	"*lista" debe estar inicializado y tener todos sus campos válidos:
		"lista->nodo_inicio" debe apuntar a una posición válida;
		"lista->nodo_fin" debe apuntar a una posición válida;
		"lista->cantidad" debe ser mayor a 0.
	"*nodo_borrar" debe ser diferente de null y tener sus campos válidos:
		"nodo_a_borrar->elemento" debe no ser nulo;
	"nodo_actual" debe estar inicializado y tener todos sus campos válidos:
		"nodo_actual->elemento" debe apuntar a una posición válida;
		"nodo_actual->siguiente" debe ser distinto de nulo.
	"*retorno" debe ser ERROR.
Post-condiciones:
	la función actualiza "nodo_actual->siguiente";
	la funcion libera la memoria reservada para "nodo_borrar";
	la función actualiza la cantidad de la lista;
	la función actualiza el valor de "*retorno".
*/
void borrar_nodo_posicion(lista_t* lista, nodo_t* nodo_borrar, nodo_t* nodo_actual,
	int* retorno){

	borrar_nodo(lista, nodo_borrar, &(nodo_actual->siguiente),
		nodo_borrar->siguiente, retorno);
}

//------------------------------------------------------------------------------------FUNCIONES DEL .H

/*** Pre y post condiciones en lista.h ***/
lista_t* lista_crear(){
	lista_t* lista = NULL;

	lista = malloc(sizeof(lista_t));
	if(lista)
		inicializar_lista(lista);

	return lista;
}

/*** Pre y post condiciones en lista.h ***/
int lista_insertar(lista_t* lista, void* elemento){
	nodo_t* nuevo_nodo;

	if(!lista)
		return ERROR;
	
	nuevo_nodo = crear_nodo(elemento, NULL);
	if(!nuevo_nodo)
		return ERROR;

	if(lista_vacia(lista))
		lista->nodo_inicio = nuevo_nodo;
	else
		(lista->nodo_fin)->siguiente = nuevo_nodo;

	lista->nodo_fin = nuevo_nodo;
	lista->cantidad++;

	return EXITO;
}

/*** Pre y post condiciones en lista.h ***/
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	nodo_t* nuevo_nodo, *nodo_actual = NULL;
	size_t i = 0;
	int retorno = ERROR;

	if(!lista)
		return ERROR;
	if(lista_vacia(lista) || (posicion > (lista_elementos(lista) - 1)))
		retorno = lista_insertar(lista, elemento);
	else{
		
		nuevo_nodo = crear_nodo(elemento, NULL);
		if(!nuevo_nodo)
			return ERROR;

		nodo_actual = lista->nodo_inicio;
		if(posicion == 0)
			insertar_nodo(lista, nuevo_nodo, &(lista->nodo_inicio), &retorno);
		else{
			
			while((i < posicion) && nodo_actual && (retorno != EXITO)){

				if((i + 1) == posicion)
					insertar_nodo(lista, nuevo_nodo, &(nodo_actual->siguiente), &retorno);
				avanzar_nodo(&nodo_actual, &i);
			}
		}
		lista->cantidad++;
	}

	return retorno;
}

/*** Pre y post condiciones en lista.h ***/
int lista_borrar(lista_t* lista){
	nodo_t* nodo_actual = NULL;
	int retorno;

	if(!lista || lista_vacia(lista))
		return ERROR;

	nodo_actual = lista->nodo_inicio;
	if(lista_elementos(lista) == 1){
		
		borrar_nodo(lista, nodo_actual, &(lista->nodo_fin), NULL, &retorno);
		lista->nodo_inicio = NULL;
	}
	else
		retorno = buscar_y_borrar(lista, lista_elementos(lista),
			(void*)lista->nodo_fin, es_nodo_borrar_normal, borrar_nodo_normal);
	
	return retorno;
}

/*** Pre y post condiciones en lista.h ***/
int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	nodo_t* nodo_actual = NULL;
	int retorno = ERROR;

	if(!lista || lista_vacia(lista))
		return ERROR;
	if((lista_elementos(lista) == 1) || (posicion >= (lista_elementos(lista) - 1)))
		retorno = lista_borrar(lista);
	else{

		nodo_actual = lista->nodo_inicio;
		if(posicion == 0)
			borrar_nodo(lista, nodo_actual, &(lista->nodo_inicio), nodo_actual->siguiente, &retorno);
		else
			retorno = buscar_y_borrar(lista, posicion, (void*)&posicion, es_nodo_borrar_posicion, borrar_nodo_posicion);
	}

	return retorno;
}

/*** Pre y post condiciones en lista.h ***/
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	nodo_t* nodo_actual;
	void* elemento = NULL;
	size_t i = 0;

	if(!lista || lista_vacia(lista) || (posicion > (lista_elementos(lista) - 1)))
		return NULL;

	nodo_actual = lista->nodo_inicio;
	while((i < lista_elementos(lista)) && nodo_actual && !elemento){

		if(i == posicion)		
			elemento = nodo_actual->elemento;
		avanzar_nodo(&nodo_actual, &i);
	}
	
	return elemento;
}

/*** Pre y post condiciones en lista.h ***/
void* lista_ultimo(lista_t* lista){

	if(!lista || lista_vacia(lista))
		return NULL;

	return (lista->nodo_fin)->elemento;
}

/*** Pre y post condiciones en lista.h ***/
bool lista_vacia(lista_t* lista){

	return (!lista || !lista_elementos(lista));
}

/*** Pre y post condiciones en lista.h ***/
size_t lista_elementos(lista_t* lista){
	size_t cantidad = 0;

	if(lista)
		cantidad = lista->cantidad;

	return cantidad; 
}

/*** Pre y post condiciones en lista.h ***/
void lista_destruir(lista_t* lista){
	int retorno = EXITO;

	if(!lista)
		return;

	while((lista_elementos(lista) != 0) && (retorno == EXITO))
		retorno = lista_borrar(lista);

	free(lista);
}

/*** Pre y post condiciones en lista.h ***/
lista_iterador_t* lista_iterador_crear(lista_t* lista){
	lista_iterador_t* iterador;

	if(!lista)
		return NULL;

	iterador = malloc(sizeof(lista_iterador_t));
	if(iterador){

		iterador->lista = lista;
		iterador->corriente = lista->nodo_inicio;
	}

	return iterador;
}

/*** Pre y post condiciones en lista.h ***/
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){

	return (iterador && iterador->corriente);
}

/*** Pre y post condiciones en lista.h ***/
bool lista_iterador_avanzar(lista_iterador_t* iterador){

	if(iterador && (iterador->corriente))
		iterador->corriente = (iterador->corriente)->siguiente; 
		
	return (iterador && (iterador->corriente));
}

/*** Pre y post condiciones en lista.h ***/
void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
	void* elemento;

	if(!iterador || !(iterador->corriente))
		return NULL;
	
	elemento = (iterador->corriente)->elemento;

	return elemento;
}

/*** Pre y post condiciones en lista.h ***/
void lista_iterador_destruir(lista_iterador_t* iterador){
	
	if(iterador)
		free(iterador);
}

/*** Pre y post condiciones en lista.h ***/
size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
	size_t i = 0;
	bool sigue_iterando = true;

	if(lista && funcion && !lista_vacia(lista)){
		
		do{	

			i++;
			sigue_iterando = funcion(lista_elemento_en_posicion(lista, i-1), contexto);
		}while((i < lista_elementos(lista)) && sigue_iterando);
	}

	return i;
}