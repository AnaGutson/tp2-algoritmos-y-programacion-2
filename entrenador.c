#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "entrenador.h"


#define FORMATO_ENTRENADOR              "%100[^\n]\n"
#define CANT_FORMATO_ENTRENADOR         1


//
//__________________________________________________________ENVIAR POR PARÁMETRO
//


/* 03 */
/* 
	Pre y post condiciones en entrenador.h
 */
int insertar_en_lista_entrenador(void* puntero_entrenador, pokemon_t* puntero_pokemon){

	return lista_insertar(((entrenador_t*)puntero_entrenador)->lista_pokemones, puntero_pokemon);
}

/* 03 */
/* 
	Pre y post condiciones en personaje.h
 */
bool hay_espacio_libre_para_pokemones(void* puntero_entrenador){

	return lista_elementos(((entrenador_t*)puntero_entrenador)->lista_pokemones) < MAX_CANT_POKEMONES_COMBATE;
}


//
//__________________________________________________________________VALIDACIONES
//


/* 03 */
/* 
	Pre y post condiciones en entrenador.h
 */
bool lee_bien_entrenador(int leidos){

	return (leidos == CANT_FORMATO_ENTRENADOR);
}


//
//______________________________________________________________________CREACION
//


/* 16 */
/* 
	Pre y post condiciones en entrenador.h
 */
entrenador_t* crear_entrenador(entrenador_t entrenador_leido, bool es_lider){
	entrenador_t* puntero;

	puntero = malloc(sizeof(entrenador_t));
	if(!puntero)
		return NULL;

	(*puntero) = entrenador_leido;
	puntero->lista_pokemones = lista_crear();
	if(!(puntero->lista_pokemones)){

		free(puntero);
		return NULL;
	}
	puntero->es_lider = es_lider;

	return puntero;
}


//
//___________________________________________________________________DESTRUCCION
//


/* 14 */
/* 
	Pre y post condiciones en entrenador.h
 */
void destruir_entrenador(entrenador_t* puntero_entrenador){
	pokemon_t *puntero_pokemon = NULL;

	if(!puntero_entrenador)
		return;

	while(lista_elementos(puntero_entrenador->lista_pokemones) > 0){

		puntero_pokemon = lista_elemento_en_posicion(puntero_entrenador->lista_pokemones, 0);
		destruir_pokemon(puntero_pokemon);
		lista_borrar_de_posicion(puntero_entrenador->lista_pokemones, 0);
	}
	lista_destruir(puntero_entrenador->lista_pokemones);
	free(puntero_entrenador);
}


//
//_________________________________________________________________ESCANEO LINEA
//


/* 09 */
/* 
	Pre y post condiciones en entrenador.h
 */
int lectura_entrenador(FILE* archivo, entrenador_t* entrenador){
	int leidos;
	
	leidos = fscanf(archivo, FORMATO_ENTRENADOR, entrenador->nombre);

	if(strlen(entrenador->nombre) == MAX_NOMBRE_ENTRENADOR-1)
		leidos = LECTURA_ERRONEA; 

	return leidos;
}

