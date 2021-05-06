#ifndef __POKEMON_H__
#define __POKEMON_H__


#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "funciones_generales.h"


#define MAX_CANT_POKEMONES_COMBATE       6
#define MAX_NOMBRE_POKEMON              21
#define CANT_TIPOS_POKEMONES            18
#define MAX_TIPO 			 	        50
#define MAX_MASA        				50

#define ERROR 					-1
#define EXITO 					 0
#define FIN_GIMNASIO 			 2


#define POCA_MASA           0
#define TEXTO_POCA_MASA     "Poca"
#define MASA_NORMAL         1
#define TEXTO_MASA_NORMAL   "Normal"
#define MUCHA_MASA          2
#define TEXTO_MUCHA_MASA    "Mucha"
#define MAX_TIPOS_DE_MASA	3

#define	NORMAL		 0
#define	FUEGO		 1
#define	AGUA 		 2
#define	PLANTA		 3
#define	ELECTRICO	 4
#define	HIELO		 5
#define	LUCHA		 6
#define	VENENO		 7
#define	TIERRA		 8
#define	VOLADOR		 9
#define	PSIQUICO	10
#define	BICHO		11
#define	ROCA		12
#define	FANTASMA	13
#define	DRAGON		14
#define	SINIESTRO	15
#define	HADA		16
#define	ACERO		17

#define POSICION_PRIMER_SUPEREFICACIA_NORMAL 		0
#define SUPEREFICACIA_NORMAL 						1
#define POSICION_PRIMER_SUPEREFICACIA_FUEGO 		1
#define SUPEREFICACIA_FUEGO 						4
#define POSICION_PRIMER_SUPEREFICACIA_AGUA 			5
#define SUPEREFICACIA_AGUA 							3
#define POSICION_PRIMER_SUPEREFICACIA_PLANTA 		8
#define SUPEREFICACIA_PLANTA 						3
#define POSICION_PRIMER_SUPEREFICACIA_ELECTRICO    11
#define SUPEREFICACIA_ELECTRICO 					2
#define POSICION_PRIMER_SUPEREFICACIA_HIELO 	   13
#define SUPEREFICACIA_HIELO	 						4
#define POSICION_PRIMER_SUPEREFICACIA_LUCHA 	   17
#define SUPEREFICACIA_LUCHA	 						5
#define POSICION_PRIMER_SUPEREFICACIA_VENENO 	   22
#define SUPEREFICACIA_VENENO	 					2
#define POSICION_PRIMER_SUPEREFICACIA_TIERRA 	   24
#define SUPEREFICACIA_TIERRA	 					5
#define POSICION_PRIMER_SUPEREFICACIA_VOLADOR	   29
#define SUPEREFICACIA_VOLADOR 						3
#define POSICION_PRIMER_SUPEREFICACIA_PSIQUICO     32
#define SUPEREFICACIA_PSIQUICO 						2
#define POSICION_PRIMER_SUPEREFICACIA_BICHO        34
#define SUPEREFICACIA_BICHO    						3
#define POSICION_PRIMER_SUPEREFICACIA_ROCA         37
#define SUPEREFICACIA_ROCA     						4
#define POSICION_PRIMER_SUPEREFICACIA_FANTASMA     41
#define SUPEREFICACIA_FANTASMA 						2
#define POSICION_PRIMER_SUPEREFICACIA_DRAGON       43
#define SUPEREFICACIA_DRAGON   						1
#define POSICION_PRIMER_SUPEREFICACIA_SINIESTRO    44
#define SUPEREFICACIA_SINIESTRO						2
#define POSICION_PRIMER_SUPEREFICACIA_HADA         46
#define SUPEREFICACIA_HADA     						3
#define POSICION_PRIMER_SUPEREFICACIA_ACERO        49
#define SUPEREFICACIA_ACERO    						3

const static char TEXTO_TIPOS_POKEMON[][MAX_TIPO] = {
	"normal",
	"fuego",
	"agua",
	"planta",
	"electrico",
	"hielo",
	"lucha",
	"veneno",
	"tierra", 
	"volador", 
	"psiquico",
	"bicho",
	"roca",
	"fantasma",
	"dragon",
	"siniestro",
	"hada", 
	"acero"
};

const static char TEXTO_SUPEREFICACIA[][MAX_TIPO] = {
	"nada",
	"planta", "hielo", "bicho", "acero",
	"fuego", "tierra", "roca",
	"agua", "tierra", "roca",
	"agua", "volador",
	"planta", "tierra", "volador", "dragon",
	"normal", "hielo", "roca", "siniestro", "acero",
	"planta", "hada",
	"fuego", "electrico", "veneno", "roca", "acero", 
	"planta", "lucha", "bicho",
	"lucha", "veneno",
	"planta", "psiquico", "siniestro",
	"fuego", "hielo", "volador", "bicho",
	"psiquico", "fantasma",
	"dragon",
	"psiquico", "fantasma",
	"hada", "hielo", "roca",
	"lucha", "dragon", "siniestro" 
};

typedef struct pokemon{

	char nombre[MAX_NOMBRE_POKEMON];
	int velocidad;
	int defensa;
	int ataque;
	char tipo[MAX_TIPO];
	char color[MAX_COLOR];
	char masa[MAX_MASA];
} pokemon_t;


/*
	Pre-condiciones:
		"archivo" debe estar abierto en modo lectura.		
	Post-condiciones:
		la función actualiza "puntero_entrenador" si es posible;
		la función actualiza el valor de "letra_leida";
		la función actualiza el valor de "leidos"; 
		la funcion devuelve si pudo leer correctamente un pokemon o no.
 */
int leer_pokemones(FILE* archivo, void* puntero_entrenador, char* letra_leida, int* leidos,
	int(*insertar_en_lista)(void*, pokemon_t*),
	bool(*condicion_extra)(void*));

/*
Pre-condiciones:
	-
Post-condiciones:
	la función libera "puntero_pokemon" si hay memoria reservada.
*/
void destruir_pokemon(pokemon_t* puntero_pokemon);


#endif /* __POKEMON_H__ */