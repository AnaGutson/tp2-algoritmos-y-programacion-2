#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "gimnasio.h"


#define FORMATO_GIMNASIO					"%100[^;];%5i;%5i\n"
#define CANT_FORMATO_GIMNASIO				3
#define MAX_NOMBRE_GIMNASIO					101
#define MAX_DIGITOS_DIFICULTAD_GIMNASIO		6

#define FORMATO_AVANZAR_GIMNASIO 			"%[^\n]\n%c;"

#define MAX_TEXTO		200

#define LETRA_DEFAULT   'A'


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
bool lee_bien_gimnasio(int leidos){

	return (leidos == CANT_FORMATO_GIMNASIO);
}

/* 12 */
/*
	Pre-condiciones:
		"gimnasio" debe ser válido y tener todos sus campos válidos.
	Post-condiciones:
		la función devolverá si los valores leidos son validos.
 */
bool valores_leidos_validos_gimnasio(gimnasio_t gimnasio){
	bool dificultad_valida, id_valido, nombre_valido;

	dificultad_valida = numero_valido(cant_digitos(gimnasio.dificultad), 0, MAX_DIGITOS_DIFICULTAD_GIMNASIO);
	id_valido = numero_valido(gimnasio.id_funcion, MIN_ID_FUNC_GIMNASIO, MAX_ID_FUNC_GIMNASIO);
	nombre_valido = (strlen(gimnasio.nombre) < MAX_NOMBRE_GIMNASIO - 1);

	return (dificultad_valida && id_valido && nombre_valido);
}


//
//_________________________________________________________________DESTRUCCIONES
//


/* 04 */
/*
Pre-condiciones:
	-
Post-condiciones:
	la función libera "gimnasio" si hay memoria reservada.
*/
void destruir_gimnasio(gimnasio_t* gimnasio){

	if(gimnasio)
		free(gimnasio);
}

/* 14 */
/* 
	Pre y post condiciones en gimnasio.h
 */
void liberar_gimnasio_entero(gimnasio_t* puntero_gimnasio){
	entrenador_t *puntero_entrenador = NULL;

	if(!puntero_gimnasio)
		return;

	while(pila_elementos(puntero_gimnasio->pila_entrenadores) > 0){

		puntero_entrenador = pila_tope(puntero_gimnasio->pila_entrenadores);
		destruir_entrenador(puntero_entrenador);
		pila_desapilar(puntero_gimnasio->pila_entrenadores);
	}
	pila_destruir(puntero_gimnasio->pila_entrenadores); 
	destruir_gimnasio(puntero_gimnasio);
}


//
//______________________________________________________________________CREACION
//


/* 16 */
/*
	Pre-condiciones:
		- 
	Post-condiciones:
		la función devuelve una variable con sus campos inicializados
			correctamente, de ser posible.
 */
gimnasio_t* crear_gimnasio(gimnasio_t gimnasio_leido){
	gimnasio_t* puntero;

	puntero = malloc(sizeof(gimnasio_t));
	if(!puntero)
		return NULL;

	(*puntero) = gimnasio_leido;
	puntero->pila_entrenadores = pila_crear();
	if(!(puntero->pila_entrenadores)){

		free(puntero);
		return NULL;
	}
	
	return puntero;
}


//
//_________________________________________________________________ESCANEO LINEA
//


/* 06 */
/* 
	Pre y post condiciones en gimnasio.h
 */
void avanzar_de_gimnasio(FILE* archivo, char *letra_leida, int* leidos){
	char basura[MAX_TEXTO];

	do
		*leidos = fscanf(archivo, FORMATO_AVANZAR_GIMNASIO, basura, letra_leida);
	while(!lee_bien_letra(*leidos, *letra_leida, GIMNASIO) && *leidos != EOF);
}

/* 09 */
/*
	Pre-condiciones:
		"archivo" debe estar abierto en modo LEER;
		"gimnasio" debe ser una variable válida con sus campos válidos.
	Post-condiciones:
		la función leerá el archivo y devolverá cuánto pudo leer.
 */
int lectura_gimnasio(FILE* archivo, gimnasio_t* gimnasio){
	int leidos;

	leidos = fscanf(archivo, FORMATO_GIMNASIO, gimnasio->nombre, &(gimnasio->dificultad), &(gimnasio->id_funcion));

	if(!valores_leidos_validos_gimnasio(*gimnasio))
		leidos = LECTURA_ERRONEA; 

	return leidos;
}


//
//_________________________________________________________LECTURA DE ESTRUCTURA
//

/* 24 */
/* 
	Pre y post condiciones en gimnasio.h
 */
int leer_entrenador(FILE* archivo, gimnasio_t* puntero_gimnasio, char* letra_leida, int* leidos, bool es_lider){
	int retorno = EXITO;
	entrenador_t *puntero_entrenador = NULL, entrenador_leido;

	*leidos = lectura_entrenador(archivo, &entrenador_leido);
	if(lee_bien_entrenador(*leidos)){

		puntero_entrenador = crear_entrenador(entrenador_leido, es_lider);
		if(puntero_entrenador){

			retorno = leer_pokemones(archivo, puntero_entrenador, letra_leida, leidos, insertar_en_lista_entrenador, hay_espacio_libre_para_pokemones);
			if(retorno == ERROR)
				destruir_entrenador(puntero_entrenador);
		}
		else
			retorno = ERROR;
	}
	else
		retorno = ERROR;

	if(retorno == EXITO || retorno == FIN_GIMNASIO)
		pila_apilar(puntero_gimnasio->pila_entrenadores, puntero_entrenador);

	return retorno;
}

/* 20 */
/*
	Pre-condiciones:
		"archivo" debe estar abierto en modo lectura.
	Post-condiciones:
		la función actualiza "puntero_gimnasio" si es posible;
		la función actualiza el valor de "letra_leida";
		la función actualiza el valor de "leidos"; 
		la funcion devuelve si pudo leer correctamente un entrenador o no.
 */
int leer_entrenadores(FILE* archivo, gimnasio_t* puntero_gimnasio, char *letra_leida, int* leidos){
	int retorno = EXITO;

	*leidos = lectura_letra(archivo, letra_leida);

	if(lee_bien_letra(*leidos, *letra_leida, LIDER)){ //si no tiene lider, no guarda el gimnasio

		retorno = leer_entrenador(archivo, puntero_gimnasio, letra_leida, leidos, true);
		while((retorno == EXITO) && lee_bien_letra(*leidos, *letra_leida, ENTRENADOR))
			retorno = leer_entrenador(archivo, puntero_gimnasio, letra_leida, leidos, false);
		if((retorno == EXITO) && (*leidos != EOF) && lee_bien_letra(*leidos, *letra_leida, LIDER))//lee un lider en el medio
			retorno = ERROR;
		else if(retorno == FIN_GIMNASIO)
			avanzar_de_gimnasio(archivo, letra_leida, leidos);
	}
	else{
		
		avanzar_de_gimnasio(archivo, letra_leida, leidos);
		retorno = ERROR;
	}
	
	return retorno;
}

/* 04 */
/*
	Pre-condiciones:
		"gimnasio" debe haber sido creado correctamente. 
	Post-condiciones:
		la función asigna valores iniciales a los campos de "gimnasio".
 */
void inicializar_gimnasio_stack(gimnasio_t* gimnasio){

	gimnasio->dificultad = 0;
	gimnasio->id_funcion = 0;
}

/* 25 */
/* 
	Pre y post condiciones en gimnasio.h
 */
gimnasio_t* leer_gimnasio(FILE* archivo, bool* termine_lectura){
	gimnasio_t* puntero_gimnasio = NULL, gimnasio_leido;
	char letra_leida = LETRA_DEFAULT;
	int leidos, retorno = EXITO;

	inicializar_gimnasio_stack(&gimnasio_leido);

	leidos = lectura_gimnasio(archivo, &gimnasio_leido);
	if(!lee_bien_gimnasio(leidos))
		return NULL;

	puntero_gimnasio = crear_gimnasio(gimnasio_leido);
	if(!puntero_gimnasio)
		return NULL;

	retorno = leer_entrenadores(archivo, puntero_gimnasio, &letra_leida, &leidos);
	if(retorno == ERROR){

		liberar_gimnasio_entero(puntero_gimnasio);
		return NULL;
	}
	
	*termine_lectura = lectura_archivo_finalizada(leidos);

	return puntero_gimnasio;
}


