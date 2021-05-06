#ifndef __BATALLAS_H__
#define __BATALLAS_H__


#include <stdbool.h>
#include <stddef.h>


#define GANO_PRIMERO	 1
#define GANO_SEGUNDO	-1


/*
	Pre-condiciones:
		(pokemon_t*)"elemento_1" es una variable válida, con todos sus campos
			válidos:
				(pokemon_t*)"elemento_1->color" es un valor de TEXTO_COLORES.
				(pokemon_t*)"elemento_1->nombre" es un valor válido.
	Pre-condiciones:
		(pokemon_t*)"elemento_2" es una variable válida, con todos sus campos
			válidos:
				(pokemon_t*)"elemento_2->color" es un valor de TEXTO_COLORES.
				(pokemon_t*)"elemento_2->nombre" es un valor válido.
	Post-condiciones:
		la función devuelve GANO_PRIMERO o GANO_SEGUNDO.
 */
int funcion_batalla_1(void* pokemon_1, void* pokemon_2);

/*
	Pre-condiciones:
		(pokemon_t*)"elemento_1" es una variable válida, con todos sus campos
			válidos:
				(pokemon_t*)"elemento_1->tipo" es un valor de TEXTO_TIPOS_POKEMON.
				(pokemon_t*)"elemento_1->nombre" es un valor válido.
		(pokemon_t*)"elemento_2" es una variable válida, con todos sus campos
			válidos:
				(pokemon_t*)"elemento_2->tipo" es un valor de TEXTO_TIPOS_POKEMON.
				(pokemon_t*)"elemento_2->nombre" es un valor válido.
	Post-condiciones:
		la función devuelve GANO_PRIMERO o GANO_SEGUNDO.
 */
int funcion_batalla_2(void* pokemon_1, void* pokemon_2);

/*
	Pre-condiciones:
		(pokemon_t*)"elemento_1" es una variable válida, con todos sus campos
			válidos:
				(pokemon_t*)"elemento_1->velocidad" es un valor válido.
				(pokemon_t*)"elemento_1->masa" es POCA_MASA, MASA NORMAL
					o MUCHA_MASA.
		(pokemon_t*)"elemento_2" es una variable válida, con todos sus campos
			válidos:
				(pokemon_t*)"elemento_2->velocidad" es un valor válido.
				(pokemon_t*)"elemento_2->masa" es POCA_MASA, MASA NORMAL
					o MUCHA_MASA.
	Post-condiciones:
		la función devuelve GANO_PRIMERO o GANO_SEGUNDO.
 */
int funcion_batalla_3(void* pokemon_1, void* pokemon_2);

/*
	Pre-condiciones:
		(pokemon_t*)"elemento_1" es una variable válida, con todos sus campos
			válidos:
				(pokemon_t*)"elemento_1->ataque" es un valor válido.
				(pokemon_t*)"elemento_1->defensa" es un valor válido.
		(pokemon_t*)"elemento_2" es una variable válida, con todos sus campos
			válidos:
				(pokemon_t*)"elemento_2->ataque" es un valor válido.
				(pokemon_t*)"elemento_2->defensa" es un valor válido.
	Post-condiciones:
		la función devuelve GANO_PRIMERO o GANO_SEGUNDO.
 */
int funcion_batalla_4(void* pokemon_1, void* pokemon_2);

/*
	Pre-condiciones:
		(pokemon_t*)"elemento_1" es una variable válida, con todos sus campos
			válidos:
				(pokemon_t*)"elemento_1->tipo" es un valor de TEXTO_TIPOS_POKEMONES.
		(pokemon_t*)"elemento_2" es una variable válida, con todos sus campos
			válidos:
				(pokemon_t*)"elemento_2->tipo" es un valor de TEXTO_TIPOS_POKEMONES.
	Post-condiciones:
		la función devuelve GANO_PRIMERO o GANO_SEGUNDO.
 */
int funcion_batalla_5(void* pokemon_1, void* pokemon_2);


#endif /* __BATALLAS_H__ */
