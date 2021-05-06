#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__


#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "pokemon.h"


#define MAX_NOMBRE_PERSONAJE            101


typedef struct personaje{

	char nombre[MAX_NOMBRE_PERSONAJE];
	lista_t* caja;
	pokemon_t** party;
	int cant_insignias;
} personaje_t;


/*
Pre-condiciones:
	"puntero_entrenador->caja" debe estar inicializado y tener todos sus campos válidos.
	"puntero_pokemon" debe ser distinto de null, sino no se podrá diferenciar de una
   		posición vacía.
Post-condiciones:
	la función actualiza "puntero_entrenador->party" si es posible;
	la función actualiza "puntero_entrenador->caja", siempre que se pueda;
	la función devuelve ERROR si no hay "puntero_entrenador->caja" o si no se pudo reservar memoria;
	la función devuelve EXITO si pudo cumplir con éxito su cometido.
*/
int insertar_en_lista_personaje(void* puntero_entrenador, pokemon_t* puntero_pokemon);

/*
	Pre-condiciones:
		"archivo" debe estar abierto en modo LEER;
		"personaje" debe ser una variable válida con sus campos válidos.
	Post-condiciones:
		la función leerá el archivo y devolverá cuánto pudo leer.
 */
int lectura_personaje(FILE* archivo, personaje_t* personaje);

/*
	Pre-condiciones:
		- 
	Post-condiciones:
		la función devuelve una variable con sus campos inicializados
			correctamente, de ser posible.
 */
personaje_t* crear_personaje(personaje_t personaje_leido);

/*
Pre-condiciones:
	"puntero_personaje->caja" debe estar inicializado y tener todos sus campos válidos.
Post-condiciones:
	la función libera toda la memoria reservada por los entrenadores en "puntero_personaje->caja";
	la función libera "puntero_personaje->caja";
	la función libera "puntero_personaje".
*/
void destruir_personaje(personaje_t* puntero_personaje);


#endif /* __PERSONAJE_H__ */