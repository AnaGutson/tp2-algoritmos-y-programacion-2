#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"
#include "funciones_generales.h"


#define POKEMON             'P'

#define MAX_DIGITOS_VELOCIDAD_POKEMON   4
#define MAX_DIGITOS_ATAQUE_POKEMON      4
#define MAX_DIGITOS_DEFENSA_POKEMON     4

#define CANT_FORMATO_POKEMON            4
#define FORMATO_POKEMON                 "%20[^;];%i;%i;%i\n"

#define MASA_DEFAULT    TEXTO_MASA_NORMAL
#define COLOR_DEFAULT   AMARILLO


//
//__________________________________________________________________VALIDACIONES
//


/* 03 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función devolverá si se leyó bien la linea.
 */
bool lee_bien_pokemon(int leidos){

	return (leidos == CANT_FORMATO_POKEMON);
}

/* 09 */
/*
	Pre-condiciones:
		"pokemon" debe ser válido y tener todos sus campos válidos.
	Post-condiciones:
		la función devolverá si los valores leidos son validos.
 */
bool valores_leidos_validos_pokemon(pokemon_t pokemon){
	bool velocidad_valida, ataque_valido, defensa_valida, nombre_valido;

	velocidad_valida = numero_valido(cant_digitos(pokemon.velocidad), 0, MAX_DIGITOS_VELOCIDAD_POKEMON);
	ataque_valido = numero_valido(cant_digitos(pokemon.ataque), 0, MAX_DIGITOS_ATAQUE_POKEMON);
	defensa_valida = numero_valido(cant_digitos(pokemon.defensa), 0, MAX_DIGITOS_DEFENSA_POKEMON);
	nombre_valido = (strlen(pokemon.nombre) < MAX_NOMBRE_POKEMON-1);

	return (velocidad_valida && ataque_valido && defensa_valida && nombre_valido);
}


//
//___________________________________________________________________DESTRUCCION
//


/* 06 */
/*
	Pre y post condiciones en pokemon.h
 */
void destruir_pokemon(pokemon_t* puntero_pokemon){

	if(!puntero_pokemon)
		return;

	free(puntero_pokemon); 
}


//
//______________________________________________________________________CREACION
//


/*13*/
/*
	Pre-condiciones:
		"valor_masa" debe ser POCA_MASA, MASA_NORMAL o MUCHA_MASA.
	Post-condiciones:
		la función actualiza el valor de "masa".
 */
void determinar_valor_masa(int valor_masa, char masa[MAX_MASA]){

	switch(valor_masa){
		case POCA_MASA:
			strcpy(masa, TEXTO_POCA_MASA);
			break;
		case MASA_NORMAL:
			strcpy(masa, TEXTO_MASA_NORMAL);
			break;
		case MUCHA_MASA:
			strcpy(masa, TEXTO_MUCHA_MASA);
			break;
	}
}


/* 08 */
/*
	Pre-condiciones:
		"pokemon_leido" debe haber sido creado correctamente. 
	Post-condiciones:
		la función asigna valores iniciales a los campos de "puntero",
			segun "pokemon_leido".
 */
void inicializar_pokemon(pokemon_t** puntero, pokemon_t pokemon_leido){
	int pos_random_color = numero_random(CANT_COLORES);
	int pos_random_tipo = numero_random(CANT_TIPOS_POKEMONES);

	(**puntero) = pokemon_leido;
	strcpy((*puntero)->tipo, TEXTO_TIPOS_POKEMON[pos_random_tipo]);
	strcpy((*puntero)->color, TEXTO_COLORES[pos_random_color]);
	determinar_valor_masa(numero_random(MAX_TIPOS_DE_MASA), (*puntero)->masa);//cambiar
}

/* 10 */
/*
	Pre-condiciones:
		- 
	Post-condiciones:
		la función devuelve una variable con sus campos inicializados
			correctamente, de ser posible.
 */
pokemon_t* crear_pokemon(pokemon_t pokemon_leido){
	pokemon_t* puntero;

	puntero = malloc(sizeof(pokemon_t));
	if(!puntero)
		return NULL;

	inicializar_pokemon(&puntero, pokemon_leido);

	return puntero;
}


//
//_________________________________________________________________ESCANEO LINEA
//


/* 09 */
/*
	Pre-condiciones:
		"archivo" debe estar abierto en modo LEER;
		"pokemon" debe ser una variable válida con sus campos válidos.
	Post-condiciones:
		la función leerá el archivo y devolverá cuánto pudo leer.
 */
int lectura_pokemon(FILE* archivo, pokemon_t* pokemon){
	int leidos;

	leidos = fscanf(archivo, FORMATO_POKEMON, pokemon->nombre, &(pokemon->velocidad), &(pokemon->ataque), &(pokemon->defensa));

	if(!valores_leidos_validos_pokemon(*pokemon))
		leidos = LECTURA_ERRONEA; 

	return leidos;
}


//
//_________________________________________________________LECTURA DE ESTRUCTURA
//


/* 07 */
/*
	Pre-condiciones:
		"pokemon" debe haber sido creado correctamente. 
	Post-condiciones:
		la función asigna valores iniciales a los campos de "pokemon".
 */
void inicializar_pokemon_stack(pokemon_t *pokemon){

	pokemon->velocidad = 0;
	pokemon->ataque = 0;
	pokemon->defensa = 0;
	strcpy(pokemon->masa, MASA_DEFAULT);
	strcpy(pokemon->color, COLOR_DEFAULT);
}

/* 20 */
/*
	Pre-condiciones:
		"archivo" debe estar abierto en modo lectura.		
	Post-condiciones:
		la función actualiza "puntero_entrenador" si es posible;
		la función actualiza el valor de "letra_leida";
		la función actualiza el valor de "leidos"; 
		la funcion devuelve si pudo leer correctamente un pokemon o no.
 */
int leer_pokemon(FILE* archivo, void* puntero_entrenador, char* letra_leida, int* leidos, int(*insertar_en_lista)(void*, pokemon_t*)){
	int retorno = EXITO;
	pokemon_t *puntero_pokemon = NULL, pokemon_leido;

	inicializar_pokemon_stack(&pokemon_leido);

	*leidos = lectura_pokemon(archivo, &pokemon_leido); 
	if(lee_bien_pokemon(*leidos)){

		puntero_pokemon = crear_pokemon(pokemon_leido);
		if(puntero_pokemon)
			insertar_en_lista(puntero_entrenador, puntero_pokemon);
		else
			retorno = ERROR;
		*leidos = lectura_letra(archivo, letra_leida);
	}
	else
		retorno = ERROR;

	return retorno;
}

/* 13 */
/*
	Pre y post condiciones en pokemon.h
 */
int leer_pokemones(FILE* archivo, void* puntero_entrenador, char* letra_leida, int* leidos, int(*insertar_en_lista)(void*, pokemon_t*), bool(*condicion_extra)(void*)){
	int retorno = EXITO;

	*leidos = lectura_letra(archivo, letra_leida);
	if(lee_bien_letra(*leidos, *letra_leida, POKEMON)){ 

		while(lee_bien_letra(*leidos, *letra_leida, POKEMON) && retorno == EXITO && (!condicion_extra || condicion_extra(puntero_entrenador)))
			retorno = leer_pokemon(archivo, puntero_entrenador, letra_leida, leidos, insertar_en_lista);
		if(retorno == EXITO && condicion_extra && !condicion_extra(puntero_entrenador))
			retorno = FIN_GIMNASIO;
	}
	else
		retorno = ERROR;

	return retorno;
}