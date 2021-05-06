#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "personaje.h"


#define FORMATO_PERSONAJE               "%100[^\n]\n"


//
//__________________________________________________________ENVIAR POR PARÁMETRO
//

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
int agrandar_party(pokemon_t*** puntero, pokemon_t* elemento, size_t cantidad){
	void* nuevo_puntero = NULL;

	nuevo_puntero = realloc((*puntero), sizeof(void*)*(cantidad + 1));
	if(!nuevo_puntero)
		return ERROR;

	(*puntero) = nuevo_puntero;
	(*puntero)[cantidad-1] = elemento;

	return EXITO;
}


/* 10 */
/* 
	Pre y post condiciones en personaje.h
 */
int insertar_en_lista_personaje(void* puntero_entrenador, pokemon_t* puntero_pokemon){
	int retorno;
	size_t cant_pokemones;

	retorno = lista_insertar(((personaje_t*)puntero_entrenador)->caja, puntero_pokemon);
	cant_pokemones = lista_elementos(((personaje_t*)puntero_entrenador)->caja);
	if(retorno == EXITO && cant_pokemones <= MAX_CANT_POKEMONES_COMBATE)
		agrandar_party(&(((personaje_t*)puntero_entrenador)->party), (pokemon_t*)lista_elemento_en_posicion(((personaje_t*)puntero_entrenador)->caja, cant_pokemones-1), cant_pokemones);

	return retorno;
}


//
//______________________________________________________________________CREACIÓN
//


/* 17 */
/* 
	Pre y post condiciones en personaje.h
 */
personaje_t* crear_personaje(personaje_t personaje_leido){
	personaje_t* puntero;

	puntero = malloc(sizeof(personaje_t));
	if(!puntero)
		return NULL;

	(*puntero) = personaje_leido;
	puntero->caja = lista_crear();
	if(!(puntero->caja)){

		free(puntero);
		return NULL;
	}
	puntero->party = NULL;
	puntero->cant_insignias = 0;

	return puntero;
}


//
//___________________________________________________________________DESTRUCCION
//


/* 14 */
/* 
	Pre y post condiciones en personaje.h
 */
void destruir_personaje(personaje_t* puntero_personaje){
	pokemon_t *puntero_pokemon = NULL;

	if(!puntero_personaje)
		return;

	while(lista_elementos(puntero_personaje->caja) > 0){

		puntero_pokemon = lista_elemento_en_posicion(puntero_personaje->caja, 0);
		destruir_pokemon(puntero_pokemon);
		lista_borrar_de_posicion(puntero_personaje->caja, 0);
	}
	lista_destruir(puntero_personaje->caja);
	free(puntero_personaje->party);
	free(puntero_personaje);
}


//
//_________________________________________________________________ESCANEO LINEA
//


/* 09 */
/* 
	Pre y post condiciones en personaje.h
 */
int lectura_personaje(FILE* archivo, personaje_t* personaje){
	int leidos;
	
	leidos = fscanf(archivo, FORMATO_PERSONAJE, personaje->nombre);

	if(strlen(personaje->nombre) == MAX_NOMBRE_PERSONAJE - 1)
		leidos = LECTURA_ERRONEA; 

	return leidos;
}
