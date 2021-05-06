#ifndef __GIMNASIO_H__
#define __GIMNASIO_H__


#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"
#include "personaje.h"
#include "entrenador.h"


#define GIMNASIO 		'G'

#define MAX_NOMBRE_GIMNASIO             	101
#define MAX_DIGITOS_DIFICULTAD_GIMNASIO 	  6
#define MIN_ID_FUNC_GIMNASIO            	  0
#define MAX_ID_FUNC_GIMNASIO            	  4
#define MAX_INSIGNIAS						 63


typedef struct gimnasio{

	char nombre[MAX_NOMBRE_GIMNASIO];
	int dificultad;
	int id_funcion;
	pila_t* pila_entrenadores;
} gimnasio_t;


/*
	Pre-condiciones:
		"puntero_entrenador" debe ser una variable válida con todos sus campos válidos.
	Post-condiciones:
		la función devuelve si los elementos de la caja son menos de MAX_CANT_POKEMONES_COMBATE.
 */
bool hay_espacio_libre_para_pokemones(void* puntero_entrenador);

/*
	Pre-condiciones:
		"archivo" debe estar abierto en modo lectura.
	Post-condiciones:
		la función actualiza "puntero_gimnasio" si es posible;
		la función actualiza el valor de "letra_leida";
		la función actualiza el valor de "leidos"; 
		la funcion devuelve si pudo leer correctamente un entrenador o no.
 */
int leer_entrenadores(FILE* archivo, gimnasio_t* puntero_gimnasio, char *letra_leida, int* leidos);

/*
	Pre-condiciones:
		"archivo" debe estar abierto en modo lectura;
		"termine_lectura" debe ser false.
	Post-condiciones:
		la funcion devuelve el gimnasio leido o NULL en caso de no
			haber podido leer bien el gimnasio.
 */
gimnasio_t* leer_gimnasio(FILE* archivo, bool* termine_lectura);

/*
	Pre-condiciones:
		"archivo" debe estar abierto en modo lectura.
	Post-condiciones:
		la funcion actualiza el archivo para leer en el siguiente gimnasio si
			es que hay gimnasio, sino en el final del archivo;
		la función actualiza "letra_leida";
		la función actualiza "leidos".
 */
void avanzar_de_gimnasio(FILE* archivo, char *letra_leida, int* leidos);

/*
Pre-condiciones:
	"puntero_gimnasio->pila_entrenadores" debe estar inicializado y tener
		todos sus campos válidos.
Post-condiciones:
	la función libera toda la memoria reservada por los entrenadores en
		"puntero_entrenador->pila_entrenadores";
	la función libera "puntero_entrenador->pila_entrenadores";
	la función libera "puntero_entrenador".
*/
void liberar_gimnasio_entero(gimnasio_t* puntero_gimnasio);


#endif /* __GIMNASIO_H__ */