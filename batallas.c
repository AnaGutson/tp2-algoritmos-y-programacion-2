#include <stdbool.h>
#include <stddef.h>
#include "funciones_generales.h"
#include "pokemon.h"
#include "batallas.h"


#define PUNTOS_RARO			-1
#define PUNTOS_NORMAL	 	1
#define PUNTOS_LINDO	 	5
#define PUNTOS_BRILLA		10
#define PUNTOS_EXTRA		15

#define PUNTOS_POCA_MASA	50
#define PUNTOS_MASA_NORMAL	100
#define PUNTOS_MUCHA_MASA	150

const static int PUNTOS_COLOR[] = {
	PUNTOS_NORMAL, PUNTOS_NORMAL, PUNTOS_BRILLA, PUNTOS_NORMAL, PUNTOS_RARO,
	PUNTOS_LINDO, PUNTOS_LINDO, PUNTOS_NORMAL, PUNTOS_NORMAL, PUNTOS_NORMAL,
	PUNTOS_NORMAL, PUNTOS_NORMAL, PUNTOS_NORMAL, PUNTOS_LINDO, PUNTOS_BRILLA
};

const static int PUNTOS_TIPOS_POKEMON[] = {
	PUNTOS_NORMAL, PUNTOS_RARO, PUNTOS_EXTRA, PUNTOS_NORMAL, PUNTOS_NORMAL,
	PUNTOS_NORMAL, PUNTOS_NORMAL, PUNTOS_RARO, PUNTOS_NORMAL, PUNTOS_EXTRA,
	PUNTOS_EXTRA, PUNTOS_RARO, PUNTOS_NORMAL, PUNTOS_NORMAL, PUNTOS_EXTRA,
	PUNTOS_BRILLA, PUNTOS_NORMAL, PUNTOS_RARO
};


/* 04 */
/*
	Pre-condiciones:
		"pokemon" es una variable válida, con todos sus campos válidos:
			"pokemon->color" es un valor de TEXTO_COLORES.
	Post-condiciones:
		la función devuelve los puntos del color.
 */
int puntos_por_color(pokemon_t* pokemon){
	int posicion = asumo_posicion_color(pokemon->color);

	return PUNTOS_COLOR[posicion];
}

/* 18 */
/*
	Pre y post condiciones en "batallas.h"
 */
int funcion_batalla_1(void* elemento_1, void* elemento_2){
	//pokemon_t* pokemon_1 = (pokemon_t*)elemento_1;
	//pokemon_t* pokemon_2 = (pokemon_t*)elemento_2;
	//int puntos_pokemon_1, puntos_pokemon_2, retorno;

	//if(!elemento_1 || !elemento_2)
		//return GANO_PRIMERO;

	//quien parece más acaudalado
	//puntos_pokemon_1 = cant_letras(pokemon_1->nombre) + puntos_por_color(pokemon_1);
	//puntos_pokemon_2 = cant_letras(pokemon_2->nombre) + puntos_por_color(pokemon_2);

	//if(puntos_pokemon_1 > puntos_pokemon_2)
		//retorno = GANO_PRIMERO;
	//else
		//retorno = GANO_SEGUNDO;

	//return retorno;
    return GANO_PRIMERO;
}

/* 18 */
/*
	Pre y post condiciones en "batallas.h"
 */
int funcion_batalla_2(void* elemento_1, void* elemento_2){
	pokemon_t* pokemon_1 = (pokemon_t*)elemento_1;
	pokemon_t* pokemon_2 = (pokemon_t*)elemento_2;
	int puntos_pokemon_1, puntos_pokemon_2, retorno;

	if(!elemento_1 || !elemento_2)
		return GANO_PRIMERO;

	//quien tiene caracteristicas más dificiles de pronunciar
	puntos_pokemon_1 = cant_consonantes(pokemon_1->nombre) + cant_consonantes(pokemon_1->tipo);
	puntos_pokemon_2 = cant_consonantes(pokemon_2->nombre) + cant_consonantes(pokemon_2->tipo);

	if(puntos_pokemon_1 > puntos_pokemon_2)
		retorno = GANO_PRIMERO;
	else
		retorno = GANO_SEGUNDO;

	return retorno;
}

/* 11 */
/*
	Pre-condiciones:
		"masa" es TEXTO_POCA_MASA, TEXTO_MASA_NORMAL o TEXTO_MUCHA_MASA.
	Post-condiciones:
		la función devuelve los puntos de la masa.
 */
int puntos_masa(char masa[MAX_MASA]){
	int retorno;

	if(strcmp(TEXTO_POCA_MASA, masa) == 0)
		retorno = PUNTOS_POCA_MASA;
	else if(strcmp(TEXTO_MASA_NORMAL, masa) == 0)
		retorno = PUNTOS_MASA_NORMAL;
	else
		retorno = PUNTOS_MUCHA_MASA;

	return retorno;
}

/* 18 */
/*
	Pre y post condiciones en "batallas.h"
 */
int funcion_batalla_3(void* elemento_1, void* elemento_2){
	pokemon_t* pokemon_1 = (pokemon_t*)elemento_1;
	pokemon_t* pokemon_2 = (pokemon_t*)elemento_2;
	int puntos_pokemon_1, puntos_pokemon_2, retorno;

	if(!elemento_1 || !elemento_2)
		return GANO_PRIMERO;

	//quien tiene mayor momento lineal
	puntos_pokemon_1 = puntos_masa(pokemon_1->masa)*pokemon_1->velocidad;
	puntos_pokemon_2 = puntos_masa(pokemon_2->masa)*pokemon_2->velocidad;

	if(puntos_pokemon_1 > puntos_pokemon_2)
		retorno = GANO_PRIMERO;
	else
		retorno = GANO_SEGUNDO;

	return retorno;
}

/* 18 */
/*
	Pre y post condiciones en "batallas.h"
 */
int funcion_batalla_4(void* elemento_1, void* elemento_2){
	pokemon_t* pokemon_1 = (pokemon_t*)elemento_1;
	pokemon_t* pokemon_2 = (pokemon_t*)elemento_2;
	int puntos_pokemon_1, puntos_pokemon_2, retorno;

	if(!elemento_1 || !elemento_2)
		return GANO_PRIMERO;

	//quien pelea mejor
	puntos_pokemon_1 = pokemon_1->defensa - pokemon_2->ataque;
	puntos_pokemon_2 = pokemon_2->defensa - pokemon_1->ataque;

	if(puntos_pokemon_1 > puntos_pokemon_2)
		retorno = GANO_PRIMERO;
	else
		retorno = GANO_SEGUNDO;

	return retorno;
}

/*
	Pre-condiciones: 
		"texto_original", "texto_a_comparar" tienen tamaño mayor a 0 y menor a MAX_TIPO;
		"i" es positivo;
		"encontro_tipo" es false.
	Post-condiciones: 
		la función actualiza de ser posible el valor de "encontro_tipo";
		la función siempre actualiza el valor del puntero "*i" incrementandolo en uno.
 */
void definir_tipo(char texto_original[MAX_TIPO],
	const char texto_a_comparar[MAX_TIPO], int *i, bool *encontro_tipo){

	if(strcmp(texto_original, texto_a_comparar) == 0)
		*encontro_tipo = true;
	(*i)++;
}

/*
	Pre-condiciones: 
		"texto" tiene tamaño mayor a 0 y menor a MAX_TIPO.
	Post-condiciones: 
   		la función devuelve la posicion del vector donde se encuentra el tipo.
 */
int asumo_posicion_tipo(char texto[MAX_TIPO]){
	int i = 0;
	bool encontro_tipo = false;
	
	while((i < CANT_TIPOS_POKEMONES) && (!encontro_tipo))
		definir_tipo(texto, TEXTO_TIPOS_POKEMON[i], &i, &encontro_tipo);
	
	if(!encontro_tipo)
		i = 1;

	return (i - 1);	
}

/*
	Pre-condiciones: 
		"posicion" debe ser un valor válido.
	Post-condiciones: 
		la función actualiza "cantidad" por la cantidad de pokemones contra los
			que se es supereficaz;
		la función devuelve la posicion donde comienzan los pokemones contra los
			que se es supereficaz.
 */
int buscar_primera_posicion_tipo_en_supereficacia(int posicion, int* cantidad){
	int retorno;

	switch(posicion){
		case NORMAL:
			retorno = POSICION_PRIMER_SUPEREFICACIA_NORMAL;
			*cantidad = SUPEREFICACIA_NORMAL;
			break;
		case FUEGO:
			retorno = POSICION_PRIMER_SUPEREFICACIA_FUEGO;
			*cantidad = SUPEREFICACIA_FUEGO;
			break;
		case AGUA:
			retorno = POSICION_PRIMER_SUPEREFICACIA_AGUA;
			*cantidad = SUPEREFICACIA_AGUA;
			break;
		case PLANTA:
			retorno = POSICION_PRIMER_SUPEREFICACIA_PLANTA;
			*cantidad = SUPEREFICACIA_PLANTA;
			break;
		case ELECTRICO:
			retorno = POSICION_PRIMER_SUPEREFICACIA_ELECTRICO;
			*cantidad = SUPEREFICACIA_ELECTRICO;
			break;
		case HIELO:
			retorno = POSICION_PRIMER_SUPEREFICACIA_HIELO;
			*cantidad = SUPEREFICACIA_HIELO;
			break;
		case LUCHA:
			retorno = POSICION_PRIMER_SUPEREFICACIA_LUCHA;
			*cantidad = SUPEREFICACIA_LUCHA;
			break;
		case VENENO:
			retorno = POSICION_PRIMER_SUPEREFICACIA_VENENO;
			*cantidad = SUPEREFICACIA_VENENO;
			break;
		case TIERRA:
			retorno = POSICION_PRIMER_SUPEREFICACIA_TIERRA;
			*cantidad = SUPEREFICACIA_TIERRA;
			break;
		case VOLADOR:
			retorno = POSICION_PRIMER_SUPEREFICACIA_VOLADOR;
			*cantidad = SUPEREFICACIA_VOLADOR;
			break;
		case PSIQUICO:
			retorno = POSICION_PRIMER_SUPEREFICACIA_PSIQUICO;
			*cantidad = SUPEREFICACIA_PSIQUICO;
			break;
		case BICHO:
			retorno = POSICION_PRIMER_SUPEREFICACIA_BICHO;
			*cantidad = SUPEREFICACIA_BICHO;
			break;
		case ROCA:
			retorno = POSICION_PRIMER_SUPEREFICACIA_ROCA;
			*cantidad = SUPEREFICACIA_ROCA;
			break;
		case FANTASMA:
			retorno = POSICION_PRIMER_SUPEREFICACIA_FANTASMA;
			*cantidad = SUPEREFICACIA_FANTASMA;
			break;
		case DRAGON:
			retorno = POSICION_PRIMER_SUPEREFICACIA_DRAGON;
			*cantidad = SUPEREFICACIA_DRAGON;
			break;
		case SINIESTRO:
			retorno = POSICION_PRIMER_SUPEREFICACIA_SINIESTRO;
			*cantidad = SUPEREFICACIA_SINIESTRO;
			break;
		case HADA:
			retorno = POSICION_PRIMER_SUPEREFICACIA_HADA;
			*cantidad = SUPEREFICACIA_HADA;
			break;
		case ACERO:
			retorno = POSICION_PRIMER_SUPEREFICACIA_ACERO;
			*cantidad = SUPEREFICACIA_ACERO;
			break;
	}

	return retorno;
}

/*
	Pre-condiciones: 
		"tipo_pokemon" debe ser un valor válido;
		"tipo_pokemon_oponente" debe ser un valor válido.
	Post-condiciones: 
		la función retona si el pokemon es supereficaz contra el oponente o no.
 */
bool pokemon_es_supereficaz_contra_oponente(char tipo_pokemon[MAX_TIPO],
	char tipo_pokemon_oponente[MAX_TIPO]){
	
	int cantidad_pokemones_supereficaz_segun_tipo, posicion_tipo, primera_posicion, i;
	bool esta = false;
	
	posicion_tipo = asumo_posicion_tipo(tipo_pokemon);
	primera_posicion = buscar_primera_posicion_tipo_en_supereficacia(posicion_tipo,
		&cantidad_pokemones_supereficaz_segun_tipo);
	i = primera_posicion;
	
	while((i < primera_posicion + cantidad_pokemones_supereficaz_segun_tipo) && (!esta)){

		if(strcmp(tipo_pokemon_oponente, TEXTO_SUPEREFICACIA[i]) == 0)
			esta = true;
		(i)++;
	}
	
	return esta;
}

/*
	Pre-condiciones:
		"pokemon" es una variable válida, con todos sus campos válidos:
			"pokemon->tipo" es un valor de TEXTO_TIPOS_POKEMONES.
	Post-condiciones:
		la función devuelve los puntos del tipo de pokemon.
 */
int puntos_por_tipo(char tipo_pokemon[MAX_TIPO]){
	int posicion_tipo;

	posicion_tipo = asumo_posicion_tipo(tipo_pokemon);
	
	return PUNTOS_TIPOS_POKEMON[posicion_tipo];
}

/*
	Pre y post condiciones en "batallas.h"
 */
int funcion_batalla_5(void* elemento_1, void* elemento_2){
	pokemon_t* pokemon_1 = (pokemon_t*)elemento_1;
	pokemon_t* pokemon_2 = (pokemon_t*)elemento_2;
	int retorno, puntos_pokemon_1, puntos_pokemon_2;
	bool pokemon_1_es_supereficaz , pokemon_2_es_supereficaz ;

	if(!elemento_1 || !elemento_2)
		return GANO_PRIMERO;

	pokemon_1_es_supereficaz = pokemon_es_supereficaz_contra_oponente(pokemon_1->tipo, pokemon_2->tipo);
	pokemon_2_es_supereficaz = pokemon_es_supereficaz_contra_oponente(pokemon_2->tipo, pokemon_1->tipo);

	if(pokemon_1_es_supereficaz)
		retorno = GANO_PRIMERO;
	else if(pokemon_2_es_supereficaz)
		retorno = GANO_SEGUNDO;
	else{

		puntos_pokemon_1 = puntos_por_tipo(pokemon_1->tipo);
		puntos_pokemon_2 = puntos_por_tipo(pokemon_2->tipo);
		if(puntos_pokemon_1 > puntos_pokemon_2)
			retorno = GANO_PRIMERO;
		else
			retorno = GANO_SEGUNDO;
	}

	return retorno;
}
