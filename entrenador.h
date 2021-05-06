#ifndef __ENTRENADOR_H__
#define __ENTRENADOR_H__


#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "pokemon.h"


#define LIDER               'L'
#define ENTRENADOR          'E'

#define MAX_NOMBRE_ENTRENADOR           101


typedef struct entrenador{

	char nombre[MAX_NOMBRE_ENTRENADOR];
	bool es_lider;
	lista_t* lista_pokemones;
} entrenador_t;


/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función devolverá si se leyó bien la linea.
 */
bool lee_bien_entrenador(int leidos);

/*
	Pre-condiciones:
		- 
	Post-condiciones:
		la función devuelve una variable con sus campos inicializados
			correctamente, de ser posible.
 */
entrenador_t* crear_entrenador(entrenador_t entrenador_leido, bool es_lider);

/*
	Pre-condiciones:
		"archivo" debe estar abierto en modo LEER;
		"entrenador" debe ser una variable válida con sus campos válidos.
	Post-condiciones:
		la función leerá el archivo y devolverá cuánto pudo leer.
 */
int lectura_entrenador(FILE* archivo, entrenador_t* entrenador);

/*
Pre-condiciones:
	"puntero_entrenador->lista_pokemones" debe estar inicializado y tener todos
		sus campos válidos.
	"puntero_pokemon" debe ser distinto de null, sino no se podrá diferenciar
		de una posición vacía.
Post-condiciones:
	la función devuelve ERROR si no hay lista o si no se pudo reservar memoria;
	la función devuelve EXITO si pudo cumplir con éxito su cometido.
*/
int insertar_en_lista_entrenador(void* puntero_entrenador, pokemon_t* puntero_pokemon);

/*
Pre-condiciones:
	"puntero_entrenador->lista_pokemones" debe estar inicializado y tener todos
		sus campos válidos.
Post-condiciones:
	la función libera toda la memoria reservada por los pokemones en
		"puntero_entrenador->lista_pokemones";
	la función libera "puntero_entrenador->lista_pokemones";
	la función libera "puntero_entrenador".
*/
void destruir_entrenador(entrenador_t* puntero_entrenador);


#endif /* __ENTRENADOR_H__ */