#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "funciones_generales.h"
#include "pokemon.h"
#include "entrenador.h"
#include "gimnasio.h"
#include "personaje.h"
#include "lista.h"
#include "pila.h"
#include "ptda.h"


#define ESPACIO         " "
#define MARGEN          "					"
#define MINI_MARGEN     "			"

#define MAX_TEXTO       200

#define LETRA_CARGAR_PERSONAJE  	'E'
#define LETRA_CARGAR_GIMNASIO   	'A'
#define LETRA_COMENZAR_PARTIDA  	'I'
#define LETRA_SIMULAR_PARTIDA   	'S'

#define LETRA_MOSTRAR_PERSONAJE 	'E'
#define LETRA_MOSTRAR_GIMNASIOS 	'G'
#define LETRA_CAMBIAR_PARTY     	'C'
#define LETRA_COMENZAR_BATALLA  	'B'

#define LETRA_TOMAR_PRESTADO		'T'
#define LETRA_SIGUIENTE_GIMNASIO 	'N'

#define LETRA_REINTENTAR			'R'
#define LETRA_FINALIZAR				'F'

#define MAX_RESPUESTA           3

#define LARGO_TABLERO	80
#define LARGO_BARRA		25



//
//___________________________________________________________________IMPRESIONES
//


/* 03 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_error_archivo(){

	printf(ROJO_FUERTE"El nombre del archivo ingresado es incorrecto o no se puede acceder al mismo\n"FIN);
}

/* 06 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_texto_error_archivo(char ruta_leida[MAX_RUTA]){

	if(!archivo_existe(ruta_leida))
		mostrar_error_archivo();
	else
		printf(ROJO_FUERTE "Por favor, vuelva a intentarlo siguiendo las instrucciones \n");
}

/* 06 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_texto_error_menu_2(char letra, char comparacion_1, char comparacion_2){
	
	if(!ingreso_letra_es_correcto_2(letra, comparacion_1, comparacion_2))
		printf(ROJO_FUERTE "Ingreso incorrecto, vuelva a intentarlo siguiendo las instrucciones del cuadro\n" FIN);
	else 
		printf(ROJO_FUERTE "Ingreso incorrecto, cargue la información necesaria para jugar una partida\n" FIN);
}

/* 06 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_texto_error_menu_3(char letra, char comparacion_1, char comparacion_2, char comparacion_3){
	
	if(!ingreso_letra_es_correcto_3(letra, comparacion_1, comparacion_2, comparacion_3))
		printf(ROJO_FUERTE "Ingreso incorrecto, vuelva a intentarlo siguiendo las instrucciones del cuadro\n" FIN);
	else 
		printf(ROJO_FUERTE "Ingreso incorrecto, cargue la información necesaria para jugar una partida\n" FIN);
}

/* 06 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_texto_error_menu_4(char letra, char comparacion_1, char comparacion_2, char comparacion_3, char comparacion_4){
	
	if(!ingreso_letra_es_correcto_4(letra, comparacion_1, comparacion_2, comparacion_3, comparacion_4))
		printf(ROJO_FUERTE "Ingreso incorrecto, vuelva a intentarlo siguiendo las instrucciones del cuadro\n" FIN);
	else 
		printf(ROJO_FUERTE "Ingreso incorrecto, cargue la información necesaria para jugar una partida\n" FIN);
}

/* 14 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mensaje_segun_retorno(int retorno, void(*funcion_extra)(void*), void* extra){

	if(retorno == ERROR){

		printf(ROJO_FUERTE"No se realizó la acción, disculpe la molestia\n"FIN);
		detener_el_tiempo(TIEMPO_NORMAL);
	}
	else{

		if(funcion_extra)
			funcion_extra(extra);
		printf(VERDE_FUERTE"Carga exitosa, volviendo al menú...\n"FIN);
		detener_el_tiempo(TIEMPO_NORMAL);
	}
}

/* 03 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_error_ingreso_letra(char letra_1, char* opcion_1, char letra_2, char* opcion_2){

	printf(ROJO_FUERTE "Error, ingrese '%c' para %s, '%c' para %s. \n" FIN, letra_1, opcion_1, letra_2, opcion_2);
}

//
//__________________________________________________________________MOSTRAR MENU
//

/* 09 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_titulo_juego(){

	system("clear");
	printf(CELESTE_FONDO AMARILLO MINI_MARGEN"╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
	printf(MINI_MARGEN"║  ______       _                                  _            _          _____      _                              ║\n");
	printf(MINI_MARGEN"║ |  ____|     | |                                (_)          | |        |  __ \\    | |                             ║\n");
	printf(MINI_MARGEN"║ | |__   _ __ | |_ _ __ ___ _ __   __ _ _ __ ___  _  ___ _ __ | |_ ___   | |__) |__ | | _____ _ __ ___   ___  _ __  ║\n");
	printf(MINI_MARGEN"║ |  __| | '_ \\| __| '__/ _ \\ '_ \\ / _` | '_ ` _ \\| |/ _ \\ '_ \\| __/ _ \\  |  ___/ _ \\| |/ / _ \\ '_ ` _ \\ / _ \\| '_ \\ ║\n");
	printf(MINI_MARGEN"║ | |____| | | | |_| | |  __/ | | | (_| | | | | | | |  __/ | | | || (_) | | |  | (_) |   <  __/ | | | | | (_) | | | |║\n");
	printf(MINI_MARGEN"║ |______|_| |_|\\__|_|  \\___|_| |_|\\__,_|_| |_| |_|_|\\___|_| |_|\\__\\___/  |_|   \\___/|_|\\_\\___|_| |_| |_|\\___/|_| |_|║\n");
	printf(MINI_MARGEN"╚════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n"FIN);
	fflush(stdout);
	printf(FIN);
}

/* 06 */
/*
	Pre-condiciones: 
		"largo_total" positivo.	
	Post-condiciones:
		la función mostrará una linea.
*/
void mostrar_linea_superior_cuadro(int largo_total){
	
	printf(MARGEN CELESTE"█");
	for(int i = 0; i < largo_total; i++)
		printf("▀");
	printf("█\n" FIN);
}

/* 04 */
/*
	Pre-condiciones: 
		"cant_espacios" positivo.	
	Post-condiciones:
		la función mostrará espacios.
*/
void mostrar_espacio(int cant_espacios){
	
	for(int i = 0; i < cant_espacios; i++)
		printf(ESPACIO);
}

/* 05 */
/*
	Pre-condiciones: 
		"largo_total" positivo.	
	Post-condiciones:
		la función mostrará una linea vacía.
*/
void mostrar_linea_vacia_cuadro(int largo_total){
	
	printf(MARGEN CELESTE "█");
	mostrar_espacio(largo_total);
	printf("█\n" FIN);
}

/* 17 */
/*
	Pre-condiciones: 
		"largo_total" positivo.	
	Post-condiciones:
		la función mostrará el título.
*/
void mostrar_linea_titulo(int largo_total, char* texto, char* extra){
	int cant_espacio_sin_texto, cant_sub_grupos = 2, espacio, resto;
	char texto_titulo[MAX_TEXTO];

	if(extra)
		snprintf(texto_titulo, MAX_TEXTO, "%s '%s'", texto, extra); //cambiar constante
	else
		strcpy(texto_titulo, texto);

	cant_espacio_sin_texto = (largo_total - (int)strlen(texto_titulo));
	espacio = cant_espacio_sin_texto/cant_sub_grupos;
	resto = cant_espacio_sin_texto%cant_sub_grupos;
	
	printf(MARGEN CELESTE "█" FIN);
	mostrar_espacio(espacio);
	printf(AMARILLO "%s" FIN, texto_titulo);
	mostrar_espacio(espacio + resto);
	printf(CELESTE "█\n" FIN);
}
 
/* 09 */
/*
	Pre-condiciones: 
		"largo_total" positivo.	
	Post-condiciones:
		la función mostrará una linea.
*/
void mostrar_linea_inferior_cuadro(int largo_total){

	printf(MARGEN CELESTE "█");
	
	for(int i = 0; i < largo_total; i++)
		printf("▄");

	printf("█\n" FIN);
}

/* 11 */
/*
	Pre-condiciones: 
		"largo_total" positivo.	
	Post-condiciones:
		la función mostrará opciones.
*/
void mostrar_linea_titulo_opciones(int largo_total, char* texto){
	int primer_espacio, espacio_restante;

	primer_espacio = (int)strlen(MARGEN);
	espacio_restante = (largo_total - primer_espacio - (int)strlen(texto));
	
	printf(MARGEN CELESTE "█" FIN);
	mostrar_espacio(primer_espacio);
	printf(AMARILLO "%s" FIN, texto);
	mostrar_espacio(espacio_restante);
	printf(CELESTE "█\n" FIN);
}

/* 14 */
/*
	Pre-condiciones: 
		"largo_total" positivo.	
	Post-condiciones:
		la función mostrará una opción.
*/
void mostrar_linea_opcion(int largo_total, char opcion, char* descripcion){
	int primer_espacio, espacio_restante;
	char texto_opcion[MAX_TEXTO];

	snprintf(texto_opcion, MAX_TEXTO, "%s'%c'%s: %s", ROJO_FUERTE, opcion, BLANCO, descripcion); //cambiar constante

	primer_espacio = (int)strlen(MARGEN);
	espacio_restante = (largo_total - primer_espacio - (int)strlen(texto_opcion)) + (int)strlen(CELESTE) + (int)strlen(BLANCO);
	
	printf(MARGEN CELESTE "█" FIN);
	mostrar_espacio(primer_espacio);
	printf(BLANCO "%s" FIN, texto_opcion);
	mostrar_espacio(espacio_restante);
	printf(CELESTE "█\n" FIN);
}

/* 15 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_parte_visual_menu(char titulo_menu[MAX_TEXTO], char* extra, void(*mostrar_lineas_opciones_menu)(int)){
	int largo_total = LARGO_TABLERO;
	
	mostrar_titulo_juego();

	printf("\n");
	mostrar_linea_superior_cuadro(largo_total);
	mostrar_linea_vacia_cuadro(largo_total);
	/**/mostrar_linea_titulo(largo_total, titulo_menu, extra);
	mostrar_linea_vacia_cuadro(largo_total);
	mostrar_linea_vacia_cuadro(largo_total);
	/**/mostrar_lineas_opciones_menu(largo_total);
	mostrar_linea_vacia_cuadro(largo_total);
	mostrar_linea_inferior_cuadro(largo_total); 
	printf("\n" FIN); 
}


//
//___________________________________________________________MOSTRAR MENU INICIO
//


/* 07 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_lineas_opciones_menu_inicio(int largo_total){

	mostrar_linea_titulo_opciones(largo_total, "Segun lo que desee hacer, escriba la letra correspondiente");
	mostrar_linea_opcion(largo_total, LETRA_CARGAR_PERSONAJE, "Ingresar el archivo del entrenador principal (el jugador)"); 
	mostrar_linea_opcion(largo_total, LETRA_CARGAR_GIMNASIO, "Ingresar un archivo con gimnasios.");
	mostrar_linea_opcion(largo_total, LETRA_COMENZAR_PARTIDA, "Comenzar la partida");
	mostrar_linea_opcion(largo_total, LETRA_SIMULAR_PARTIDA, "Simular la partida"); 
}


//
//_________________________________________________________MOSTRAR MENU GIMNASIO
//


/* 07 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_lineas_opciones_menu_gimnasio(int largo_total){

	mostrar_linea_titulo_opciones(largo_total, "Segun lo que desee hacer, escriba la letra correspondiente");
	mostrar_linea_opcion(largo_total, LETRA_MOSTRAR_PERSONAJE, "Mostrar informacion del personaje."); 
	mostrar_linea_opcion(largo_total, LETRA_MOSTRAR_GIMNASIOS, "Mostrar informacion del gimnasio.");
	mostrar_linea_opcion(largo_total, LETRA_CAMBIAR_PARTY, "Cambiar party.");
	mostrar_linea_opcion(largo_total, LETRA_COMENZAR_BATALLA, "Comenzar batalla.");
}


//
//______________________________________MOSTRAR MENU VICTORIA CON TOMAR PRESTADO
//


/* 06 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_lineas_opciones_menu_victoria_con_tomar_prestado(int largo_total){

	mostrar_linea_titulo_opciones(largo_total, "Segun lo que desee hacer, escriba la letra correspondiente");
	mostrar_linea_opcion(largo_total, LETRA_TOMAR_PRESTADO, "Tomar prestado un pokemon del lider vencido"); 
	mostrar_linea_opcion(largo_total, LETRA_CAMBIAR_PARTY, "Cambiar party");
	mostrar_linea_opcion(largo_total, LETRA_SIGUIENTE_GIMNASIO, "Avanzar al siguiente gimnasio.");
}


//
//______________________________________MOSTRAR MENU VICTORIA SIN TOMAR PRESTADO
//


/* 05 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_lineas_opciones_menu_victoria_sin_tomar_prestado(int largo_total){

	mostrar_linea_titulo_opciones(largo_total, "Segun lo que desee hacer, escriba la letra correspondiente");
	mostrar_linea_opcion(largo_total, LETRA_CAMBIAR_PARTY, "Cambiar party");
	mostrar_linea_opcion(largo_total, LETRA_SIGUIENTE_GIMNASIO, "Avanzar al siguiente gimnasio.");
}

//
//__________________________________________________________MOSTRAR MENU DERROTA
//


/* 06 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_lineas_opciones_menu_derrota(int largo_total){

	mostrar_linea_titulo_opciones(largo_total, "Segun lo que desee hacer, escriba la letra correspondiente");
	mostrar_linea_opcion(largo_total, LETRA_CAMBIAR_PARTY, "Cambiar party");
	mostrar_linea_opcion(largo_total, LETRA_REINTENTAR, "Reintentar la batalla.");
	mostrar_linea_opcion(largo_total, LETRA_FINALIZAR, "Finalizar la partida.");
}


//
//_________________________________________MOSTRAR INFORMACIÓN POKEMON PERSONAJE
//


/* 08 */
/*
	Pre-condiciones: 
		"pokemon" es valido y todos sus campos también;
		"esta" es false;
		"party" está rellenado correctamente.	
	Post-condiciones:
		la función actualizará "esta" de ser posible.
*/
void buscar_pokemon(pokemon_t* pokemon, pokemon_t** party, bool *esta){
	size_t i = 0;

	while(i < MAX_CANT_POKEMONES_COMBATE && !*esta){

		*esta = (pokemon == party[i]);
		i++;
	}
}

/* 09 */
/*
	Pre-condiciones: 
		"pokemon" es valido y todos sus campos también;
		"party" está rellenado correctamente.	
	Post-condiciones:
		la función actualizará "color" y "respuesta" de ser posible.
*/
void determinar_si_pokemon_esta_en_party(pokemon_t* pokemon, pokemon_t** party,
	char color[MAX_COLOR], char respuesta[MAX_RESPUESTA]){
	bool esta = false;

	buscar_pokemon(pokemon, party, &esta);
	if(esta){
	
		strcpy(color, VERDE_FUERTE);
		strcpy(respuesta, "Si");
	}
}

/* 05 */
/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará el encabezado del cuadro de información de pokemones
			de personaje.
*/
void mostrar_encabezado_pokemon_personaje(){

	printf(BLANCO" ┌────┬──────────────────┬─────────────────────┬───────────────┬───────────────┬──────────┬──────────┬────────┬───────┐\n");
	printf(" │%4s │%18s│%21s│%15s│%15s│%10s│%10s│%8s│%7s│\n", "N°", "¿Esta en mi party?", "NOMBRE", "TIPO", "COLOR", "MASA", "VELOCIDAD", "DEFENSA", "ATAQUE");
	printf(" ├────┼──────────────────┼─────────────────────┼───────────────┼───────────────┼──────────┼──────────┼────────┼───────┤\n");
}

/* 09 */
/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará información de los pokemones del cuadro de
			información de pokemones de personaje.
*/
void mostrar_informacion_pokemon_personaje(pokemon_t* pokemon, size_t numero, pokemon_t** party){
	char color_asumido[MAX_COLOR], afirmacion[MAX_TEXTO] = "No", color_afirmacion[MAX_COLOR] = ROJO_FUERTE;

	asumo_color(pokemon->color, color_asumido);
	determinar_si_pokemon_esta_en_party(pokemon, party, color_afirmacion, afirmacion);

	printf(BLANCO" │%4i│%s%18s", (int)numero, color_afirmacion, afirmacion);
	printf(BLANCO"│%21s│%15s│%s%15s", pokemon->nombre, pokemon->tipo, color_asumido, pokemon->color);
	printf(BLANCO"│%10s│%10i│%8i│%7i│\n", pokemon->masa, pokemon->velocidad, pokemon->defensa, pokemon->ataque);
}

/* 10 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_pokemones_personaje(lista_t* caja, pokemon_t** party){

	ptda_nuevo_subgrupo("Pokemones");

	mostrar_encabezado_pokemon_personaje();

	for(size_t i = 0; i < lista_elementos(caja); i++)
		mostrar_informacion_pokemon_personaje(lista_elemento_en_posicion(caja, i), i, party);
	
	printf(" └────┴──────────────────┴─────────────────────┴───────────────┴───────────────┴──────────┴──────────┴────────┴───────┘\n"FIN);//cambiar por fors
}

/* 06 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_cambios_personaje(void* extra){
	personaje_t* personaje = (personaje_t*)extra;

	mostrar_titulo_juego();
	printf(VERDE_FUERTE "Así ha quedado su caja\n" FIN);
	mostrar_pokemones_personaje(personaje->caja, personaje->party);
	esperar_al_usuario();
}


//
//_________________________________________________MOSTRAR INFORMACIÓN PERSONAJE
//


/* 09 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_informacion_personaje(personaje_t* personaje){
	char texto_personaje[MAX_TEXTO];

	mostrar_titulo_juego();
	snprintf(texto_personaje, MAX_TEXTO, "Personaje '%s'", personaje->nombre);
	ptda_nueva_categoria(texto_personaje);  
	printf("\n");

	mostrar_pokemones_personaje(personaje->caja, personaje->party);
	esperar_al_usuario();
}


//
//________________________________________MOSTRAR INFORMACIÓN POKEMON ENTRENADOR
//


/* 05 */
/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará el encabezado del cuadro de información de pokemones
			de entrenador.
*/
void mostrar_encabezado_pokemones_entrenador(){

	printf(BLANCO" ┌────┬─────────────────────┬───────────────┬───────────────┬──────────┬──────────┬────────┬───────┐\n");
	printf(" │%4s │%21s│%15s│%15s│%10s│%10s│%8s│%7s│\n", "N°", "NOMBRE", "TIPO", "COLOR", "MASA", "VELOCIDAD", "DEFENSA", "ATAQUE");
	printf(" ├────┼─────────────────────┼───────────────┼───────────────┼──────────┼──────────┼────────┼───────┤\n");
}

/* 06 */
/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará información de los pokemones del cuadro de
			información de pokemones de entrenador.
*/
void mostrar_informacion_pokemon_entrenador(pokemon_t* pokemon, size_t numero){
	char color_asumido[MAX_COLOR];
	
	asumo_color(pokemon->color, color_asumido);
	printf(BLANCO" │%4i│%21s│%15s│%s%15s", (int)numero, pokemon->nombre, pokemon->tipo, color_asumido, pokemon->color);
	printf(BLANCO"│%10s│%10i│%8i│%7i│\n", pokemon->masa, pokemon->velocidad, pokemon->defensa, pokemon->ataque);
}

/* 09 */
/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará un cuadro de información de pokemones de entrenador.
*/
void mostrar_pokemones_entrenador(lista_t* lista){
	
	ptda_nuevo_subgrupo("Pokemones");
	mostrar_encabezado_pokemones_entrenador();

	for(size_t i = 0; i < lista_elementos(lista); i++)
		mostrar_informacion_pokemon_entrenador(lista_elemento_en_posicion(lista, i), i);

	printf(" └────┴─────────────────────┴───────────────┴───────────────┴──────────┴──────────┴────────┴───────┘\n"FIN);
}

/* 10 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_informacion_entrenador(entrenador_t* entrenador){
	char texto_entrenador[MAX_TEXTO];

	if(entrenador->es_lider)
		snprintf(texto_entrenador, MAX_TEXTO, "Lider '%s'", entrenador->nombre);
	else
		snprintf(texto_entrenador, MAX_TEXTO, "Entrenador '%s'", entrenador->nombre);
	ptda_nuevo_grupo(texto_entrenador);

	mostrar_pokemones_entrenador(entrenador->lista_pokemones);
}


//
//__________________________________________MOSTRAR INFORMACIÓN POKEMON GIMNASIO
//


/* 10 */
/*
	Pre-condiciones: 
		"pila_entrenadores" válida.
	Post-condiciones:
		la función mostrará información de todos los entrenadores de "pila_entrenadores".
*/
void recorrer_entrenadores_para_mostrar(pila_t* pila_entrenadores){

	if(!pila_entrenadores || pila_vacia(pila_entrenadores))
		return;

	entrenador_t* entrenador_actual = pila_tope(pila_entrenadores);
	pila_desapilar(pila_entrenadores);
	recorrer_entrenadores_para_mostrar(pila_entrenadores);
	mostrar_informacion_entrenador(entrenador_actual);
	pila_apilar(pila_entrenadores, entrenador_actual);
}

/* 08 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_gimnasio(gimnasio_t* gimnasio){
	char texto_gimnasio[MAX_TEXTO];

	mostrar_titulo_juego();
	
	snprintf(texto_gimnasio, MAX_TEXTO, "Gimnasio '%s': dificultad %i", gimnasio->nombre, gimnasio->dificultad);
	ptda_nueva_categoria(texto_gimnasio);
	recorrer_entrenadores_para_mostrar(gimnasio->pila_entrenadores);
}

/* 06 */
/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará el encabezado del cuadro de información de pokemon
			de batalla.
*/
void mostrar_encabezado_pokemon_batalla(){

	printf(CELESTE MINI_MARGEN"    ________________________________________________________________________________________________\n");
	printf(MINI_MARGEN"  / \\                                                                                                \\.\n");
	printf(MINI_MARGEN" |   |               "AMARILLO"NOMBRE           TIPO          COLOR      MASA    DEFENSA   VELOCIDAD    ATAQUE"CELESTE" |.\n");
	printf(MINI_MARGEN"  \\_ |                                                                                               |.\n"FIN);
}

/* 10 */
/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará información del pokemon de batalla.
*/
void mostrar_pokemon_batalla(pokemon_t* pokemon){
	char color_asumido[MAX_COLOR];

	mostrar_encabezado_pokemon_batalla();
	asumo_color(pokemon->color, color_asumido);
	printf(CELESTE MINI_MARGEN"     |"BLANCO"%21s%15s%s%15s", pokemon->nombre, pokemon->tipo, color_asumido, pokemon->color);
	printf(BLANCO"%10s%11i%12i%10i"CELESTE" |.\n", pokemon->masa, pokemon->defensa, pokemon->velocidad, pokemon->ataque);
	printf(MINI_MARGEN"     |   ____________________________________________________________________________________________|___\n");
    printf(MINI_MARGEN"     |  /                                                                                               /.\n");
    printf(MINI_MARGEN"     \\_/_______________________________________________________________________________________________/.\n\n"FIN);	
}

/* 09 */
/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará un ascii art.
*/
void mostrar_vs(){

	printf(NEGRO MARGEN"\t\t\t\t  ██    ██ ███████ \n"); 
	printf(MARGEN"\t\t\t\t  ██    ██ ██      \n");
	printf(MARGEN"\t\t\t\t  ██    ██ ███████ \n");
	printf(MARGEN"\t\t\t\t   ██  ██       ██ \n");
	printf(MARGEN"\t\t\t\t    ████   ███████ \n"FIN); 		
}

/* 20 */
/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará los datos del competidor.
*/
void mostrar_datos_pokemon_batalla(char titulo[MAX_TEXTO], char nombre_entrenador[MAX_TEXTO], pokemon_t* pokemon){
	char texto_entrenador[MAX_TEXTO] = {CARACTER_VACIO};

	mayusculizar_string(nombre_entrenador);
	snprintf(texto_entrenador, MAX_TEXTO, "%s '%s'", titulo, nombre_entrenador);
	ptda_nuevo_grupo(texto_entrenador);
	printf("\n");
	mostrar_pokemon_batalla(pokemon);
	detener_el_tiempo(TIEMPO_NORMAL);
}

/* 20 */
/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará los datos de la batalla.
*/
void mostrar_datos_batalla(char nombre_gimnasio[MAX_NOMBRE_GIMNASIO], char nombre_entrenador[MAX_NOMBRE_ENTRENADOR],
	bool es_lider,char nombre_personaje[MAX_NOMBRE_ENTRENADOR], pokemon_t* pokemon_personaje, pokemon_t* pokemon_oponente){

	char texto_gimnasio[MAX_TEXTO];
	
	mostrar_titulo_juego();

	printf(BLANCO MARGEN MINI_MARGEN"\t  +-+-+-+-+-+-+-+\n");
	printf(MARGEN MINI_MARGEN"\t  |b|a|t|a|l|l|a|\n");
	printf(MARGEN MINI_MARGEN"\t  +-+-+-+-+-+-+-+\n" FIN);

	mayusculizar_string(nombre_gimnasio);
	snprintf(texto_gimnasio, MAX_TEXTO, "GIMNASIO '%s'", nombre_gimnasio);
	ptda_nueva_categoria(texto_gimnasio);
	printf("\n");

	mostrar_datos_pokemon_batalla("PERSONAJE", nombre_personaje, pokemon_personaje);
	mostrar_vs();
	detener_el_tiempo(TIEMPO_NORMAL);
	if(es_lider)
		mostrar_datos_pokemon_batalla("LIDER", nombre_entrenador, pokemon_oponente);         		
	else
		mostrar_datos_pokemon_batalla("ENTRENADOR", nombre_entrenador, pokemon_oponente);         
}


//
//_____________________________________________________________MOSTRAR ADORNITOS
//Cabe aclarar que no representan la realidad, son puramente estéticos


/* 10 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_barra_progreso(){

	printf(MARGEN"\t\t\t");
	for (int i = 0; i < LARGO_BARRA; i++){
		
		detener_el_tiempo(TIEMPO_RAPIDO);
		fflush(stdout);
		printf("█");
	}
	printf(FIN);
}

/* 09 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_carga_nuevo_menu(){

	system("clear");
	mostrar_titulo_juego();
	detener_el_tiempo(TIEMPO_RAPIDO);
	printf(BLANCO "\n\n\n\n\n\n\n\n"MARGEN"\t\t\t\tCARGANDO...\n" VERDE_FUERTE);
	mostrar_barra_progreso();
	detener_el_tiempo(TIEMPO_RAPIDO);
	fflush(stdout);
}

/* 18 */
/*
	Pre-condiciones: 
		-	
	Post-condiciones:
		la función mostrará un ascii art.
 */
void mostrar_mensaje_juego_finalizado(){
	system("clear");
	
	mostrar_titulo_juego();
	
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf(NEGRO MARGEN MINI_MARGEN"   ▄████████  ▄█  ███▄▄▄▄   \n");     
	printf(MARGEN MINI_MARGEN"  ███    ███ ███  ███▀▀▀██▄ \n");     
	printf(MARGEN MINI_MARGEN"  ███    █▀  ███▌ ███   ███ \n");     
	printf(MARGEN MINI_MARGEN" ▄███▄▄▄     ███▌ ███   ███ \n");     
	printf(MARGEN MINI_MARGEN"▀▀███▀▀▀     ███▌ ███   ███ \n");     
	printf(MARGEN MINI_MARGEN"  ███        ███  ███   ███ \n");     
	printf(MARGEN MINI_MARGEN"  ███        ███  ███   ███ \n");     
	printf(MARGEN MINI_MARGEN"  ███        █▀    ▀█   █▀  \n"VERDE_FUERTE);     
    
    detener_el_tiempo(TIEMPO_NORMAL);
    fflush(stdout);
    system("clear");
}


/* 21 */
/*
	Pre-condiciones: 
		-	
	Post-condiciones:
		la función mostrará un ascii art.
 */
void mostrar_mensaje_felicitaciones (){
	system("clear");

	mostrar_titulo_juego();

	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    
	printf(AMARILLO"\t     ▄████████    ▄████████  ▄█        ▄█   ▄████████  ▄█      ███        ▄████████  ▄████████  ▄█   ▄██████▄  ███▄▄▄▄      ▄████████    ▄████████\n"); 
	printf("\t    ███    ███   ███    ███ ███       ███  ███    ███ ███  ▀█████████▄   ███    ███ ███    ███ ███  ███    ███ ███▀▀▀██▄   ███    ███   ███    ███\n"); 
	printf("\t    ███    █▀    ███    █▀  ███       ███▌ ███    █▀  ███▌    ▀███▀▀██   ███    ███ ███    █▀  ███▌ ███    ███ ███   ███   ███    █▀    ███    █▀ \n"); 
	printf("\t   ▄███▄▄▄      ▄███▄▄▄     ███       ███▌ ███        ███▌     ███   ▀   ███    ███ ███        ███▌ ███    ███ ███   ███  ▄███▄▄▄       ███       \n"); 
	printf("\t  ▀▀███▀▀▀     ▀▀███▀▀▀     ███       ███▌ ███        ███▌     ███     ▀███████████ ███        ███▌ ███    ███ ███   ███ ▀▀███▀▀▀     ▀███████████\n"); 
	printf("\t    ███          ███    █▄  ███       ███  ███    █▄  ███      ███       ███    ███ ███    █▄  ███  ███    ███ ███   ███   ███    █▄           ███\n"); 
	printf("\t    ███          ███    ███ ███▌    ▄ ███  ███    ███ ███      ███       ███    ███ ███    ███ ███  ███    ███ ███   ███   ███    ███    ▄█    ███\n"); 
	printf("\t    ███          ██████████ █████▄▄██ █▀   ████████▀  █▀      ▄████▀     ███    █▀  ████████▀  █▀    ▀██████▀   ▀█   █▀    ██████████  ▄████████▀ \n"); 
	printf("\t                            ▀                                                                                                                     \n"); 
    printf(FIN);

    detener_el_tiempo(TIEMPO_NORMAL);
    fflush(stdout);
    system("clear");
}

/* 20 */
/*
	Pre-condiciones: 
		-	
	Post-condiciones:
		la función mostrará un ascii art.
 */
void mostrar_mensaje_perdida(){
	system("clear");

	mostrar_titulo_juego();

	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    
	printf(ROJO_FUERTE MINI_MARGEN "\t ▄███████▄    ▄████████    ▄████████ ████████▄   ▄█     ▄████████     ███        ▄████████ \n");
	printf(MINI_MARGEN "\t  ███    ███   ███    ███   ███    ███ ███   ▀███ ███    ███    ███ ▀█████████▄   ███    ███ \n");
	printf(MINI_MARGEN "\t  ███    ███   ███    █▀    ███    ███ ███    ███ ███▌   ███    █▀     ▀███▀▀██   ███    █▀  \n");
	printf(MINI_MARGEN "\t  ███    ███  ▄███▄▄▄      ▄███▄▄▄▄██▀ ███    ███ ███▌   ███            ███   ▀  ▄███▄▄▄     \n");
	printf(MINI_MARGEN "\t▀█████████▀  ▀▀███▀▀▀     ▀▀███▀▀▀▀▀   ███    ███ ███▌ ▀███████████     ███     ▀▀███▀▀▀     \n");
	printf(MINI_MARGEN "\t  ███          ███    █▄  ▀███████████ ███    ███ ███           ███     ███       ███    █▄  \n");
	printf(MINI_MARGEN "\t  ███          ███    ███   ███    ███ ███   ▄███ ███     ▄█    ███     ███       ███    ███ \n");
	printf(MINI_MARGEN "\t ▄████▀        ██████████   ███    ███ ████████▀  █▀    ▄████████▀     ▄████▀     ██████████ \n");
	printf(MINI_MARGEN "\t                            ███    ███                                                      \n");
    printf(FIN);

    detener_el_tiempo(TIEMPO_NORMAL);
    fflush(stdout);
}

/* 43 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_mensaje_juego_ganado(){

	mostrar_mensaje_felicitaciones();
	mostrar_titulo_juego();

	printf(MINI_MARGEN AMARILLO"   ▄████████    ▄████████    ▄████████    ▄████████      ███    █▄  ███▄▄▄▄  \n");      
	printf(MINI_MARGEN"  ███    ███   ███    ███   ███    ███   ███    ███      ███    ███ ███▀▀▀██▄\n");      
	printf(MINI_MARGEN"  ███    █▀    ███    ███   ███    █▀    ███    █▀       ███    ███ ███   ███\n");      
	printf(MINI_MARGEN" ▄███▄▄▄      ▄███▄▄▄▄██▀  ▄███▄▄▄       ███             ███    ███ ███   ███\n");      
	printf(MINI_MARGEN"▀▀███▀▀▀     ▀▀███▀▀▀▀▀   ▀▀███▀▀▀     ▀███████████      ███    ███ ███   ███\n");      
	printf(MINI_MARGEN"  ███    █▄  ▀███████████   ███    █▄           ███      ███    ███ ███   ███\n");      
	printf(MINI_MARGEN"  ███    ███   ███    ███   ███    ███    ▄█    ███      ███    ███ ███   ███\n");      
	printf(MINI_MARGEN"  ██████████   ███    ███   ██████████  ▄████████▀       ████████▀   ▀█   █▀ \n");      
	printf(MINI_MARGEN"               ███    ███                                                    \n");  
	detener_el_tiempo(TIEMPO_NORMAL);
	printf("\n\n");    
	printf(ROJO_FUERTE MARGEN"		  ▄▄▄▄███▄▄▄▄      ▄████████    ▄████████    ▄████████     ███        ▄████████  ▄██████▄ \n"); 
	printf(MARGEN"		▄██▀▀▀███▀▀▀██▄   ███    ███   ███    ███   ███    ███ ▀█████████▄   ███    ███ ███    ███\n"); 
	printf(MARGEN"		███   ███   ███   ███    ███   ███    █▀    ███    █▀     ▀███▀▀██   ███    ███ ███    ███\n"); 
	printf(MARGEN"		███   ███   ███   ███    ███  ▄███▄▄▄       ███            ███   ▀  ▄███▄▄▄▄██▀ ███    ███\n"); 
	printf(MARGEN"		███   ███   ███ ▀███████████ ▀▀███▀▀▀     ▀███████████     ███     ▀▀███▀▀▀▀▀   ███    ███\n"); 
	printf(MARGEN"		███   ███   ███   ███    ███   ███    █▄           ███     ███     ▀███████████ ███    ███\n"); 
	printf(MARGEN"		███   ███   ███   ███    ███   ███    ███    ▄█    ███     ███       ███    ███ ███    ███\n"); 
	printf(MARGEN"		 ▀█   ███   █▀    ███    █▀    ██████████  ▄████████▀     ▄████▀     ███    ███  ▀██████▀ \n"); 
	printf(MARGEN"		                                                                     ███    ███           \n");
	detener_el_tiempo(TIEMPO_NORMAL);
	printf("\n\n");
	printf(MINI_MARGEN AMARILLO"   ▄███████▄  ▄██████▄     ▄█   ▄█▄    ▄████████   ▄▄▄▄███▄▄▄▄    ▄██████▄  ███▄▄▄▄  \n"); 
	printf(MINI_MARGEN"  ███    ███ ███    ███   ███ ▄███▀   ███    ███ ▄██▀▀▀███▀▀▀██▄ ███    ███ ███▀▀▀██▄\n"); 
	printf(MINI_MARGEN"  ███    ███ ███    ███   ███▐██▀     ███    █▀  ███   ███   ███ ███    ███ ███   ███\n"); 
	printf(MINI_MARGEN"  ███    ███ ███    ███  ▄█████▀     ▄███▄▄▄     ███   ███   ███ ███    ███ ███   ███\n"); 
	printf(MINI_MARGEN"▀█████████▀  ███    ███ ▀▀█████▄    ▀▀███▀▀▀     ███   ███   ███ ███    ███ ███   ███\n"); 
	printf(MINI_MARGEN"  ███        ███    ███   ███▐██▄     ███    █▄  ███   ███   ███ ███    ███ ███   ███\n"); 
	printf(MINI_MARGEN"  ███        ███    ███   ███ ▀███▄   ███    ███ ███   ███   ███ ███    ███ ███   ███\n"); 
	printf(MINI_MARGEN" ▄████▀       ▀██████▀    ███   ▀█▀   ██████████  ▀█   ███   █▀   ▀██████▀   ▀█   █▀ \n"); 
    printf(MINI_MARGEN"                          ▀                                        	\n"FIN);

	detener_el_tiempo(TIEMPO_NORMAL);
    fflush(stdout);
    system("clear");

    mostrar_mensaje_juego_finalizado();
}

/* 04 */
/* 
	Pre y post en interfaz_grafica.h
 */
void mostrar_mensaje_juego_perdido(){

	mostrar_mensaje_perdida();
	mostrar_mensaje_juego_finalizado();
}

/*Pre-condiciones: 
    -.
Post-condiciones:
    la función mostrará varios dibujos en secuencia, formando una animación.*/
void animacion(){
    
    for (int i = 0; i < 3; i++){
        
        system("clear");
        printf(CELESTE);
        printf("\n\n                                                               . .:.:.:.:. .:\\     /:. .:.:.:.:. ,                   \n");
        printf("                                                          .-._  `..:.:. . .:.:`- -':.:. . .:.:.,'  _.-.                  \n");
        printf("                                                         .:.:.`-._`-._..-''_...---..._``-.._.-'_.-'.:.:.                 \n");
        printf("                                                      .:.:. . .:_.`' _..-''._________,``-.._ `.._:. . .:.:.              \n");
        printf("                                                   .:.:. . . ,-'_.-''      ||_-(O)-_||      ``-._`-. . . .:.:.           \n");
        printf("                                                  .:. . . .,'_.'           '---------'           `._`.. . . .:.          \n");
        printf("                                                :.:. . . ,','               _________               `.`. . . .:.:        \n");
        printf("                                               `.:.:. .,','            _.-''_________``-._            `._.     _.'       \n");
        printf("                                             -._  `._./ /            ,'_.-'' ,       ``-._`.          ,' '`:..'  _.-     \n");
        printf("                                            .:.:`-.._' /           ,','                   `.`.       /'  '  \\.-':.:.    \n");
        printf("                                            :.:. . ./ /          ,','     "AMARILLO"ENTRENAMIENTO"CELESTE"     `.`.    / '  '  '\\. .:.:    \n");
        printf("                                           :.:. . ./ /          / /    ,                      \\ \\  :  '  '  ' \\. .:.:   \n");
        printf(""BLANCO"..................."FIN CELESTE"                        .:. . ./ /          / /           "AMARILLO"POKEMON"CELESTE"     ,     \\ \\ :  '  '  ' '::. .:.    "BLANCO"     .................\n");
        printf("  ................."FIN CELESTE"                        :. . .: :    o     / /                               \\ ;'  '  '  ' ':: . .:     "BLANCO"     ...............\n");
        printf("    ..............."FIN CELESTE"                        .:. . | |   /_\\   : :     ,                      ,    : '  '  '  ' ' :: .:.    "BLANCO"      ...............\n");
        printf("       ............"FIN CELESTE"                        :. . .| |  ((<))  | |,          ,       ,   "BLANCO"By"FIN CELESTE"        |\\'__',-._.' ' ||. .:      "BLANCO"      ...........\n");
        printf("         .........."FIN CELESTE"                        .:.:. | |   `-'   | |---....____             "BLANCO"Ana G."FIN CELESTE"   | ,---\\/--/  ' ||:.:.   "BLANCO"          .........\n");
        printf("           ........"FIN CELESTE"                        ------| |         : :    ,.     ```--..._   , "BLANCO"Gutson"FIN CELESTE"  |''  '  '  ' ' ||----      "BLANCO"       .........\n");
        printf("            ......."FIN CELESTE"                        _...--. |  ,       \\ \\             ,.    `-._     ,  /: '  '  '  ' ' ;;..._              "BLANCO".......\n");
        printf("             ......"FIN CELESTE"                        :.:. .| | -O-       \\ \\    ,.                `._    / /:'  '  '  ' ':: .:.:               "BLANCO"..... \n");
        printf("              ....."FIN CELESTE"                        .:. . | |_(`__       \\ \\                        `. / / :'  '  '  ' ';;. .:.               "BLANCO"..... \n");
        printf("               ...."FIN CELESTE"                        :. . .<' (_)  `>      `.`.          ,.    ,.     ,','   \\  '  '  ' ;;. . .:                "BLANCO"... \n");
        printf("                ..."FIN CELESTE"                        .:. . |):-.--'(         `.`-._  ,.           _,-','      \\ '  '  '//| . .:.                "BLANCO".. \n");
        printf("                 .."FIN CELESTE"                       :. . .;)()(__)(___________`-._`-.._______..-'_.-'___________\'  '  //_:. . .:                "BLANCO".."FIN CELESTE" \n");
        printf("                _::_                    .:.:,' \\/\\/--\\/--------------------------------------------`._',;'`. `.:.:.                  _::_\n");
        printf("               :    :                   :.,' ,' ,'  ,'  /   /   /   ,-------------------.   \\   \\   \\  `. `.`. `..:                 :    :\n");
        printf("______________:      :______________,' ,'  '   /   /   /   /   //                   \\   \\   \\   \\   \\  ` `.A.GUTSON________________:      :________________ \n");
        detener_el_tiempo(TIEMPO_RAPIDO);
        fflush(stdout);

        system("clear");
        printf("\n\n                                                               . .:.:.:.:. .:\\     /:. .:.:.:.:. ,                   \n");
        printf("                                                          .-._  `..:.:. . .:.:`- -':.:. . .:.:.,'  _.-.                  \n");
        printf("                                                         .:.:.`-._`-._..-''_...---..._``-.._.-'_.-'.:.:.                 \n");
        printf("                                                      .:.:. . .:_.`' _..-''._________,``-.._ `.._:. . .:.:.              \n");
        printf("                                                   .:.:. . . ,-'_.-''      ||_-(O)-_||      ``-._`-. . . .:.:.           \n");
        printf("                                                  .:. . . .,'_.'           '---------'           `._`.. . . .:.          \n");
        printf("                                                :.:. . . ,','               _________               `.`. . . .:.:        \n");
        printf("                                               `.:.:. .,','            _.-''_________``-._            `._.     _.'       \n");
        printf("                                             -._  `._./ /            ,'_.-'' ,       ``-._`.          ,' '`:..'  _.-     \n");
        printf("                                            .:.:`-.._' /           ,','                   `.`.       /'  '  \\.-':.:.    \n");
        printf("                                            :.:. . ./ /          ,','     "AMARILLO"ENTRENAMIENTO"CELESTE"     `.`.    / '  '  '\\. .:.:    \n");
        printf("                                           :.:. . ./ /          / /    ,                      \\ \\  :  '  '  ' \\. .:.:   \n");
        printf("          "BLANCO"................."FIN CELESTE"                .:. . ./ /          / /           "AMARILLO"POKEMON"CELESTE"     ,     \\ \\ :  '  '  ' '::. .:.               "BLANCO"...........\n");
        printf("           ..............."FIN CELESTE"                 :. . .: :    o     / /                               \\ ;'  '  '  ' ':: . .:               "BLANCO"...........\n");
        printf("           ..............."FIN CELESTE"                 .:. . | |   /_\\   : :     ,                      ,    : '  '  '  ' ' :: .:.               "BLANCO"...........\n");
        printf("             ..........."FIN CELESTE"                   :. . .| |  ((<))  | |,          ,       ,   "BLANCO"By"FIN CELESTE"        |\\'__',-._.' ' ||. .:     "BLANCO"          ...........\n");
        printf("              ........."FIN CELESTE"                    .:.:. | |   `-'   | |---....____             "BLANCO"Ana G."FIN CELESTE"   | ,---\\/--/  ' ||:.:.       "BLANCO"        ...........\n");
        printf("              ........."FIN CELESTE"                    ------| |         : :    ,.     ```--..._   , "BLANCO"Gutson"FIN CELESTE"  |''  '  '  ' ' ||----         "BLANCO"      ..........\n");
        printf("               ......."FIN CELESTE"                     _...--. |  ,       \\ \\             ,.    `-._     ,  /: '  '  '  ' ' ;;..._     "BLANCO"          .........\n");
        printf("                ....."FIN CELESTE"                      :.:. .| | -O-       \\ \\    ,.                `._    / /:'  '  '  ' ':: .:.:      "BLANCO"         ....... \n");
        printf("                ....."FIN CELESTE"                      .:. . | |_(`__       \\ \\                        `. / / :'  '  '  ' ';;. .:.       "BLANCO"         ..... \n");
        printf("                 ..."FIN CELESTE"                       :. . .<' (_)  `>      `.`.          ,.    ,.     ,','   \\  '  '  ' ;;. . .:         "BLANCO"        ... \n");
        printf("                 .."FIN CELESTE"                        .:. . |):-.--'(         `.`-._  ,.           _,-','      \\ '  '  '//| . .:.           "BLANCO"      .. \n");
        printf("                 .."FIN CELESTE"                       :. . .;)()(__)(___________`-._`-.._______..-'_.-'___________\'  '  //_:. . .:          "BLANCO"      .. "FIN CELESTE"\n");
        printf("                _::_                    .:.:,' \\/\\/--\\/--------------------------------------------`._',;'`. `.:.:.                  _::_\n");
        printf("               :    :                   :.,' ,' ,'  ,'  /   /   /   ,-------------------.   \\   \\   \\  `. `.`. `..:                 :    :\n");
        printf("______________:      :______________,' ,'  '   /   /   /   /   //                   \\   \\   \\   \\   \\  ` `.A.GUTSON________________:      :________________ \n");
        detener_el_tiempo(TIEMPO_RAPIDO);
        fflush(stdout);

        system("clear");
        printf("\n\n                                                               . .:.:.:.:. .:\\     /:. .:.:.:.:. ,                   \n");
        printf("                                                          .-._  `..:.:. . .:.:`- -':.:. . .:.:.,'  _.-.                  \n");
        printf("                                                         .:.:.`-._`-._..-''_...---..._``-.._.-'_.-'.:.:.                 \n");
        printf("                                                      .:.:. . .:_.`' _..-''._________,``-.._ `.._:. . .:.:.              \n");
        printf("                                                   .:.:. . . ,-'_.-''      ||_-(O)-_||      ``-._`-. . . .:.:.           \n");
        printf("                                                  .:. . . .,'_.'           '---------'           `._`.. . . .:.          \n");
        printf("                                                :.:. . . ,','               _________               `.`. . . .:.:        \n");
        printf("                                               `.:.:. .,','            _.-''_________``-._            `._.     _.'       \n");
        printf("                                             -._  `._./ /            ,'_.-'' ,       ``-._`.          ,' '`:..'  _.-     \n");
        printf("                                            .:.:`-.._' /           ,','                   `.`.       /'  '  \\.-':.:.    \n");
        printf("                                            :.:. . ./ /          ,','     "AMARILLO"ENTRENAMIENTO"CELESTE"     `.`.    / '  '  '\\. .:.:    \n");
        printf("                                           :.:. . ./ /          / /    ,                      \\ \\  :  '  '  ' \\. .:.:   \n");
        printf("                 "BLANCO"..................."FIN CELESTE"       .:. . ./ /          / /           "AMARILLO"POKEMON"CELESTE"     ,     \\ \\ :  '  '  ' '::. .:.     "BLANCO"              ...........\n");
        printf("                 ................."FIN CELESTE"         :. . .: :    o     / /                               \\ ;'  '  '  ' ':: . .:                "BLANCO"   ...........\n");
        printf("                 ..............."FIN CELESTE"           .:. . | |   /_\\   : :     ,                      ,    : '  '  '  ' ' :: .:.           "BLANCO"       ...........\n");
        printf("                 ............"FIN CELESTE"              :. . .| |  ((<))  | |,          ,       ,   "BLANCO"By"FIN CELESTE"        |\\'__',-._.' ' ||. .:  "BLANCO"                ...........\n");
        printf("                 .........."FIN CELESTE"                .:.:. | |   `-'   | |---....____             "BLANCO"Ana G."FIN CELESTE"   | ,---\\/--/  ' ||:.:.     "BLANCO"            ...........\n");
        printf("                 ........"FIN CELESTE"                  ------| |         : :    ,.     ```--..._   , "BLANCO"Gutson"FIN CELESTE"  |''  '  '  ' ' ||----  "BLANCO"              ..........\n");
        printf("                 ......."FIN CELESTE"                   _...--. |  ,       \\ \\             ,.    `-._     ,  /: '  '  '  ' ' ;;..._       "BLANCO"         .........\n");
        printf("                 ......"FIN CELESTE"                    :.:. .| | -O-       \\ \\    ,.                `._    / /:'  '  '  ' ':: .:.:               "BLANCO"  ....... \n");
        printf("                 ....."FIN CELESTE"                     .:. . | |_(`__       \\ \\                        `. / / :'  '  '  ' ';;. .:.           "BLANCO"       .....\n");
        printf("                 ...."FIN CELESTE"                      :. . .<' (_)  `>      `.`.          ,.    ,.     ,','   \\  '  '  ' ;;. . .:            "BLANCO"     ...\n");
        printf("                 ..."FIN CELESTE"                       .:. . |):-.--'(         `.`-._  ,.           _,-','      \\ '  '  '//| . .:.          "BLANCO"       .. \n");
        printf("                 .."FIN CELESTE"                       :. . .;)()(__)(___________`-._`-.._______..-'_.-'___________\'  '  //_:. . .:          "BLANCO"      .. "FIN CELESTE"\n");
        printf("                _::_                    .:.:,' \\/\\/--\\/--------------------------------------------`._',;'`. `.:.:.                  _::_\n");
        printf("               :    :                   :.,' ,' ,'  ,'  /   /   /   ,-------------------.   \\   \\   \\  `. `.`. `..:                 :    :\n");
        printf("______________:      :______________,' ,'  '   /   /   /   /   //                   \\   \\   \\   \\   \\  ` `.A.GUTSON________________:      :________________\n");
        detener_el_tiempo(TIEMPO_RAPIDO);
        fflush(stdout);

        system("clear");
        printf("\n\n                                                               . .:.:.:.:. .:\\     /:. .:.:.:.:. ,                   \n");
        printf("                                                          .-._  `..:.:. . .:.:`- -':.:. . .:.:.,'  _.-.                  \n");
        printf("                                                         .:.:.`-._`-._..-''_...---..._``-.._.-'_.-'.:.:.                 \n");
        printf("                                                      .:.:. . .:_.`' _..-''._________,``-.._ `.._:. . .:.:.              \n");
        printf("                                                   .:.:. . . ,-'_.-''      ||_-(O)-_||      ``-._`-. . . .:.:.           \n");
        printf("                                                  .:. . . .,'_.'           '---------'           `._`.. . . .:.          \n");
        printf("                                                :.:. . . ,','               _________               `.`. . . .:.:        \n");
        printf("                                               `.:.:. .,','            _.-''_________``-._            `._.     _.'       \n");
        printf("                                             -._  `._./ /            ,'_.-'' ,       ``-._`.          ,' '`:..'  _.-     \n");
        printf("                                            .:.:`-.._' /           ,','                   `.`.       /'  '  \\.-':.:.    \n");
        printf("                                            :.:. . ./ /          ,','     "AMARILLO"ENTRENAMIENTO"CELESTE"     `.`.    / '  '  '\\. .:.:    \n");
        printf("                                           :.:. . ./ /          / /    ,                      \\ \\  :  '  '  ' \\. .:.:   \n");
        printf("                    "BLANCO"..................."FIN CELESTE"    .:. . ./ /          / /           "AMARILLO"POKEMON"CELESTE"     ,     \\ \\ :  '  '  ' '::. .:. "BLANCO"             ...........\n");
        printf("                    ................."FIN CELESTE"      :. . .: :    o     / /                               \\ ;'  '  '  ' ':: . .:       "BLANCO"       ...........\n");
        printf("                   ..............."FIN CELESTE"         .:. . | |   /_\\   : :     ,                      ,    : '  '  '  ' ' :: .:.        "BLANCO"      ...........\n");
        printf("                   ............"FIN CELESTE"            :. . .| |  ((<))  | |,          ,       ,   "BLANCO"By"FIN CELESTE"        |\\'__',-._.' ' ||. .: "BLANCO"             ...........\n");
        printf("                   .........."FIN CELESTE"              .:.:. | |   `-'   | |---....____             "BLANCO"Ana G."FIN CELESTE"   | ,---\\/--/  ' ||:.:.  "BLANCO"            ...........\n");
        printf("                  ........"FIN CELESTE"                 ------| |         : :    ,.     ```--..._   , "BLANCO"Gutson"FIN CELESTE"  |''  '  '  ' ' ||----       "BLANCO"       ..........\n");
        printf("                  ......."FIN CELESTE"                  _...--. |  ,       \\ \\             ,.    `-._     ,  /: '  '  '  ' ' ;;..._      "BLANCO"        .........\n");
        printf("                  ......"FIN CELESTE"                   :.:. .| | -O-       \\ \\    ,.                `._    / /:'  '  '  ' ':: .:.:"BLANCO"               .......\n");
        printf("                 ....."FIN CELESTE"                     .:. . | |_(`__       \\ \\                        `. / / :'  '  '  ' ';;. .:.        "BLANCO"        .....\n");
        printf("                 ....."FIN CELESTE"                     :. . .<' (_)  `>      `.`.          ,.    ,.     ,','   \\  '  '  ' ;;. . .:                "BLANCO" ...   \n");
        printf("                 ...."FIN CELESTE"                      .:. . |):-.--'(         `.`-._  ,.           _,-','      \\ '  '  '//| . .:.           "BLANCO"      ..   \n");
        printf("                 .."FIN CELESTE"                       :. . .;)()(__)(___________`-._`-.._______..-'_.-'___________\'  '  //_:. . .:      "BLANCO"          .."FIN CELESTE"\n");
        printf("                _::_                    .:.:,' \\/\\/--\\/--------------------------------------------`._',;'`. `.:.:.                  _::_ \n");
        printf("               :    :                   :.,' ,' ,'  ,'  /   /   /   ,-------------------.   \\   \\   \\  `. `.`. `..:                 :    :\n");
        printf("______________:      :______________,' ,'  '   /   /   /   /   //                   \\   \\   \\   \\   \\  ` `.A.GUTSON________________:      :________________\n");
        detener_el_tiempo(TIEMPO_RAPIDO);
        fflush(stdout);

        system("clear");
        printf("\n\n                                                               . .:.:.:.:. .:\\     /:. .:.:.:.:. ,                   \n");
        printf("                                                          .-._  `..:.:. . .:.:`- -':.:. . .:.:.,'  _.-.                  \n");
        printf("                                                         .:.:.`-._`-._..-''_...---..._``-.._.-'_.-'.:.:.                 \n");
        printf("                                                      .:.:. . .:_.`' _..-''._________,``-.._ `.._:. . .:.:.              \n");
        printf("                                                   .:.:. . . ,-'_.-''      ||_-(O)-_||      ``-._`-. . . .:.:.           \n");
        printf("                                                  .:. . . .,'_.'           '---------'           `._`.. . . .:.          \n");
        printf("                                                :.:. . . ,','               _________               `.`. . . .:.:        \n");
        printf("                                               `.:.:. .,','            _.-''_________``-._            `._.     _.'       \n");
        printf("                                             -._  `._./ /            ,'_.-'' ,       ``-._`.          ,' '`:..'  _.-     \n");
        printf("                                            .:.:`-.._' /           ,','                   `.`.       /'  '  \\.-':.:.    \n");
        printf("                                            :.:. . ./ /          ,','     "AMARILLO"ENTRENAMIENTO"CELESTE"     `.`.    / '  '  '\\. .:.:    \n");
        printf("                                           :.:. . ./ /          / /    ,                      \\ \\  :  '  '  ' \\. .:.:   \n");
        printf("               "BLANCO"...................   "FIN CELESTE"      .:. . ./ /          / /           "AMARILLO"POKEMON"CELESTE"     ,     \\ \\ :  '  '  ' '::. .:.   "BLANCO"        .............\n");
        printf("               .................    "FIN CELESTE"       :. . .: :    o     / /                               \\ ;'  '  '  ' ':: . .:      "BLANCO"     .............\n");
        printf("               ...............     "FIN CELESTE"        .:. . | |   /_\\   : :     ,                      ,    : '  '  '  ' ' :: .:.      "BLANCO"     .............\n");
        printf("               ............   "FIN CELESTE"             :. . .| |  ((<))  | |,          ,       ,   "BLANCO"By"FIN CELESTE"        |\\'__',-._.' ' ||. .:  "BLANCO"         .............\n");
        printf("               ..........   "FIN CELESTE"               .:.:. | |   `-'   | |---....____             "BLANCO"Ana G."FIN CELESTE"   | ,---\\/--/  ' ||:.:.  "BLANCO"         .............\n");
        printf("                ........    "FIN CELESTE"               ------| |         : :    ,.     ```--..._   , "BLANCO"Gutson"FIN CELESTE"  |''  '  '  ' ' ||----   "BLANCO"         ...........\n");
        printf("                .......   "FIN CELESTE"                 _...--. |  ,       \\ \\             ,.    `-._     ,  /: '  '  '  ' ' ;;..._     "BLANCO"        .........\n");
        printf("                ......   "FIN CELESTE"                  :.:. .| | -O-       \\ \\    ,.                `._    / /:'  '  '  ' ':: .:.: "BLANCO"             .......\n");
        printf("                 .....          "FIN CELESTE"           .:. . | |_(`__       \\ \\                        `. / / :'  '  '  ' ';;. .:.    "BLANCO"           .....\n");
        printf("                 .....  "FIN CELESTE"                   :. . .<' (_)  `>      `.`.          ,.    ,.     ,','   \\  '  '  ' ;;. . .:      "BLANCO"          ...\n");
        printf("                 ...."FIN CELESTE"                      .:. . |):-.--'(         `.`-._  ,.           _,-','      \\ '  '  '//| . .:.        "BLANCO"        ..\n");
        printf("                 .."FIN CELESTE"                       :. . .;)()(__)(___________`-._`-.._______..-'_.-'___________\'  '  //_:. . .:       "BLANCO"         .."FIN CELESTE"\n");
        printf("                _::_                    .:.:,' \\/\\/--\\/--------------------------------------------`._',;'`. `.:.:.                  _::_\n");
        printf("               :    :                   :.,' ,' ,'  ,'  /   /   /   ,-------------------.   \\   \\   \\  `. `.`. `..:                 :    :\n");
        printf("______________:      :______________,' ,'  '   /   /   /   /   //                   \\   \\   \\   \\   \\  ` `.A.GUTSON________________:      :________________\n");
        detener_el_tiempo(TIEMPO_RAPIDO);
        fflush(stdout);

        system("clear");
        printf("\n\n                                                               . .:.:.:.:. .:\\     /:. .:.:.:.:. ,                   \n");
        printf("                                                          .-._  `..:.:. . .:.:`- -':.:. . .:.:.,'  _.-.                  \n");
        printf("                                                         .:.:.`-._`-._..-''_...---..._``-.._.-'_.-'.:.:.                 \n");
        printf("                                                      .:.:. . .:_.`' _..-''._________,``-.._ `.._:. . .:.:.              \n");
        printf("                                                   .:.:. . . ,-'_.-''      ||_-(O)-_||      ``-._`-. . . .:.:.           \n");
        printf("                                                  .:. . . .,'_.'           '---------'           `._`.. . . .:.          \n");
        printf("                                                :.:. . . ,','               _________               `.`. . . .:.:        \n");
        printf("                                               `.:.:. .,','            _.-''_________``-._            `._.     _.'       \n");
        printf("                                             -._  `._./ /            ,'_.-'' ,       ``-._`.          ,' '`:..'  _.-     \n");
        printf("                                            .:.:`-.._' /           ,','                   `.`.       /'  '  \\.-':.:.    \n");
        printf("                                            :.:. . ./ /          ,','     "AMARILLO"ENTRENAMIENTO"CELESTE"     `.`.    / '  '  '\\. .:.:    \n");
        printf("                                           :.:. . ./ /          / /    ,                      \\ \\  :  '  '  ' \\. .:.:   \n");
        printf("           "BLANCO"................ "FIN CELESTE"               .:. . ./ /          / /           "AMARILLO"POKEMON"CELESTE"     ,     \\ \\ :  '  '  ' '::. .: "BLANCO"..................\n");
        printf("           ..............  "FIN CELESTE"                :. . .: :    o     / /                               \\ ;'  '  '  ' ':: . .: "BLANCO".................\n");
        printf("           .............  "FIN CELESTE"                 .:. . | |   /_\\   : :     ,                      ,    : '  '  '  ' ' :: .:.   "BLANCO"...............\n");
        printf("           ............  "FIN CELESTE"                  :. . .| |  ((<))  | |,          ,       ,   "BLANCO"By"FIN CELESTE"        |\\'__',-._.' ' ||. .:  "BLANCO"    ............\n");
        printf("           ..........   "FIN CELESTE"                   .:.:. | |   `-'   | |---....____             "BLANCO"Ana G."FIN CELESTE"   | ,---\\/--/  ' ||:.:.   "BLANCO"     ..........\n");
        printf("            ........  "FIN CELESTE"                     ------| |         : :    ,.     ```--..._   , "BLANCO"Gutson"FIN CELESTE"  |''  '  '  ' ' ||----     "BLANCO"     ........\n");
        printf("             ....... "FIN CELESTE"                      _...--. |  ,       \\ \\             ,.    `-._     ,  /: '  '  '  ' ' ;;..._       "BLANCO"    .......\n");
        printf("              ......   "FIN CELESTE"                    :.:. .| | -O-       \\ \\    ,.                `._    / /:'  '  '  ' ':: .:.:      "BLANCO"      ......\n");
        printf("               .....           "FIN CELESTE"            .:. . | |_(`__       \\ \\                        `. / / :'  '  '  ' ';;. .:.        "BLANCO"     .....\n");
        printf("               .....         "FIN CELESTE"              :. . .<' (_)  `>      `.`.          ,.    ,.     ,','   \\  '  '  ' ;;. . .:     "BLANCO"         ....\n");
        printf("                 ..    "FIN CELESTE"                    .:. . |):-.--'(         `.`-._  ,.           _,-','      \\ '  '  '//| . .:.     "BLANCO"          ...\n");
        printf("                 .. "FIN CELESTE"                      :. . .;)()(__)(___________`-._`-.._______..-'_.-'___________\'  '  //_:. . .:      "BLANCO"          .."FIN CELESTE"\n");
        printf("                _::_                    .:.:,' \\/\\/--\\/--------------------------------------------`._',;'`. `.:.:.                  _::_\n");
        printf("               :    :                   :.,' ,' ,'  ,'  /   /   /   ,-------------------.   \\   \\   \\  `. `.`. `..:                 :    :\n");
        printf("______________:      :______________,' ,'  '   /   /   /   /   //                   \\   \\   \\   \\   \\  ` `.A.GUTSON________________:      :________________\n");
        detener_el_tiempo(TIEMPO_RAPIDO);
        fflush(stdout);

        system("clear");
        printf("\n\n                                                               . .:.:.:.:. .:\\     /:. .:.:.:.:. ,                   \n");
        printf("                                                          .-._  `..:.:. . .:.:`- -':.:. . .:.:.,'  _.-.                  \n");
        printf("                                                         .:.:.`-._`-._..-''_...---..._``-.._.-'_.-'.:.:.                 \n");
        printf("                                                      .:.:. . .:_.`' _..-''._________,``-.._ `.._:. . .:.:.              \n");
        printf("                                                   .:.:. . . ,-'_.-''      ||_-(O)-_||      ``-._`-. . . .:.:.           \n");
        printf("                                                  .:. . . .,'_.'           '---------'           `._`.. . . .:.          \n");
        printf("                                                :.:. . . ,','               _________               `.`. . . .:.:        \n");
        printf("                                               `.:.:. .,','            _.-''_________``-._            `._.     _.'       \n");
        printf("                                             -._  `._./ /            ,'_.-'' ,       ``-._`.          ,' '`:..'  _.-     \n");
        printf("                                            .:.:`-.._' /           ,','                   `.`.       /'  '  \\.-':.:.    \n");
        printf("                                            :.:. . ./ /          ,','     "AMARILLO"ENTRENAMIENTO"CELESTE"     `.`.    / '  '  '\\. .:.:    \n");
        printf("                                           :.:. . ./ /          / /    ,                      \\ \\  :  '  '  ' \\. .:.:   \n");
        printf("    "BLANCO".............        "FIN CELESTE"                  .:. . ./ /          / /           "AMARILLO"POKEMON"CELESTE"     ,     \\ \\ :  '  '  ' '::. .:.   "BLANCO"      .................\n");
        printf("    ............             "FIN CELESTE"              :. . .: :    o     / /                               \\ ;'  '  '  ' ':: . .:        "BLANCO"  ...............\n");
        printf("     .........          "FIN CELESTE"                   .:. . | |   /_\\   : :     ,                      ,    : '  '  '  ' ' :: .:.    "BLANCO"      ...............\n");
        printf("      .........        "FIN CELESTE"                    :. . .| |  ((<))  | |,          ,       ,   "BLANCO"By"FIN CELESTE"        |\\'__',-._.' ' ||. .: "BLANCO"           ...........\n");
        printf("       ..........    "FIN CELESTE"                      .:.:. | |   `-'   | |---....____             "BLANCO"Ana G."FIN CELESTE"   | ,---\\/--/  ' ||:.:. "BLANCO"            .........\n");
        printf("         ........      "FIN CELESTE"                    ------| |         : :    ,.     ```--..._   , "BLANCO"Gutson"FIN CELESTE"  |''  '  '  ' ' ||----   "BLANCO"          .........\n");
        printf("          .......  "FIN CELESTE"                        _...--. |  ,       \\ \\             ,.    `-._     ,  /: '  '  '  ' ' ;;..._      "BLANCO"        .......\n");
        printf("           ......       "FIN CELESTE"                   :.:. .| | -O-       \\ \\    ,.                `._    / /:'  '  '  ' ':: .:.:       "BLANCO"        .....\n");
        printf("            .....    "FIN CELESTE"                      .:. . | |_(`__       \\ \\                        `. / / :'  '  '  ' ';;. .:.        "BLANCO"       .....\n");
        printf("            .....  "FIN CELESTE"                        :. . .<' (_)  `>      `.`.          ,.    ,.     ,','   \\  '  '  ' ;;. . .:          "BLANCO"      ...\n");
        printf("                ... "FIN CELESTE"                       .:. . |):-.--'(         `.`-._  ,.           _,-','      \\ '  '  '//| . .:.           "BLANCO"     ..\n");
        printf("                 .."FIN CELESTE"                       :. . .;)()(__)(___________`-._`-.._______..-'_.-'___________\'  '  //_:. . .:            "BLANCO"    .."FIN CELESTE"\n");
        printf("                _::_                    .:.:,' \\/\\/--\\/--------------------------------------------`._',;'`. `.:.:.                  _::_\n");
        printf("               :    :                   :.,' ,' ,'  ,'  /   /   /   ,-------------------.   \\   \\   \\  `. `.`. `..:                 :    :\n");
        printf("______________:      :______________,' ,'  '   /   /   /   /   //                   \\   \\   \\   \\   \\  ` `.A.GUTSON________________:      :________________\n");
        detener_el_tiempo(TIEMPO_RAPIDO);
        fflush(stdout);

        system("clear");
        printf("\n\n                                                               . .:.:.:.:. .:\\     /:. .:.:.:.:. ,                   \n");
        printf("                                                          .-._  `..:.:. . .:.:`- -':.:. . .:.:.,'  _.-.                  \n");
        printf("                                                         .:.:.`-._`-._..-''_...---..._``-.._.-'_.-'.:.:.                 \n");
        printf("                                                      .:.:. . .:_.`' _..-''._________,``-.._ `.._:. . .:.:.              \n");
        printf("                                                   .:.:. . . ,-'_.-''      ||_-(O)-_||      ``-._`-. . . .:.:.           \n");
        printf("                                                  .:. . . .,'_.'           '---------'           `._`.. . . .:.          \n");
        printf("                                                :.:. . . ,','               _________               `.`. . . .:.:        \n");
        printf("                                               `.:.:. .,','            _.-''_________``-._            `._.     _.'       \n");
        printf("                                             -._  `._./ /            ,'_.-'' ,       ``-._`.          ,' '`:..'  _.-     \n");
        printf("                                            .:.:`-.._' /           ,','                   `.`.       /'  '  \\.-':.:.    \n");
        printf("                                            :.:. . ./ /          ,','     "AMARILLO"ENTRENAMIENTO"CELESTE"     `.`.    / '  '  '\\. .:.:    \n");
        printf("                                           :.:. . ./ /          / /    ,                      \\ \\  :  '  '  ' \\. .:.:   \n");
        printf("      "BLANCO"............."FIN CELESTE"                        .:. . ./ /          / /           "AMARILLO"POKEMON"CELESTE"     ,     \\ \\ :  '  '  ' '::. .:.       "BLANCO"         ...................\n");
        printf("      ............    "FIN CELESTE"                     :. . .: :    o     / /                               \\ ;'  '  '  ' ':: . .:    "BLANCO"            .................\n");
        printf("       .........   "FIN CELESTE"                        .:. . | |   /_\\   : :     ,                      ,    : '  '  '  ' ' :: .:.    "BLANCO"            ...............\n");
        printf("        .........  "FIN CELESTE"                        :. . .| |  ((<))  | |,          ,       ,   "BLANCO"By"FIN CELESTE"        |\\'__',-._.' ' ||. .: "BLANCO"               ............\n");
        printf("         ..........  "FIN CELESTE"                      .:.:. | |   `-'   | |---....____             "BLANCO"Ana G."FIN CELESTE"   | ,---\\/--/  ' ||:.:. "BLANCO"               ..........\n");
        printf("           ........ "FIN CELESTE"                       ------| |         : :    ,.     ```--..._   , "BLANCO"Gutson"FIN CELESTE"  |''  '  '  ' ' ||----"BLANCO"                ........\n");
        printf("            .......  "FIN CELESTE"                      _...--. |  ,       \\ \\             ,.    `-._     ,  /: '  '  '  ' ' ;;..._    "BLANCO"            .......\n");
        printf("             ...... "FIN CELESTE"                       :.:. .| | -O-       \\ \\    ,.                `._    / /:'  '  '  ' ':: .:.: "BLANCO"               ......\n");
        printf("              .....  "FIN CELESTE"                      .:. . | |_(`__       \\ \\                        `. / / :'  '  '  ' ';;. .:.        "BLANCO"        .....\n");
        printf("              .....   "FIN CELESTE"                     :. . .<' (_)  `>      `.`.          ,.    ,.     ,','   \\  '  '  ' ;;. . .:       "BLANCO"         ....\n");
        printf("                 ..    "FIN CELESTE"                    .:. . |):-.--'(         `.`-._  ,.           _,-','      \\ '  '  '//| . .:.       "BLANCO"         ...\n");
        printf("                 ..     "FIN CELESTE"                  :. . .;)()(__)(___________`-._`-.._______..-'_.-'___________\'  '  //_:. . .:      "BLANCO"          .."FIN CELESTE"\n");
        printf("                _::_                    .:.:,' \\/\\/--\\/--------------------------------------------`._',;'`. `.:.:.                  _::_ \n");
        printf("               :    :                   :.,' ,' ,'  ,'  /   /   /   ,-------------------.   \\   \\   \\  `. `.`. `..:                 :    :\n");
        printf("______________:      :______________,' ,'  '   /   /   /   /   //                   \\   \\   \\   \\   \\  ` `.A.GUTSON________________:      :________________\n");
        detener_el_tiempo(TIEMPO_RAPIDO);
        fflush(stdout);

        system("clear");
        printf("\n\n                                                               . .:.:.:.:. .:\\     /:. .:.:.:.:. ,                   \n");
        printf("                                                          .-._  `..:.:. . .:.:`- -':.:. . .:.:.,'  _.-.                  \n");
        printf("                                                         .:.:.`-._`-._..-''_...---..._``-.._.-'_.-'.:.:.                 \n");
        printf("                                                      .:.:. . .:_.`' _..-''._________,``-.._ `.._:. . .:.:.              \n");
        printf("                                                   .:.:. . . ,-'_.-''      ||_-(O)-_||      ``-._`-. . . .:.:.           \n");
        printf("                                                  .:. . . .,'_.'           '---------'           `._`.. . . .:.          \n");
        printf("                                                :.:. . . ,','               _________               `.`. . . .:.:        \n");
        printf("                                               `.:.:. .,','            _.-''_________``-._            `._.     _.'       \n");
        printf("                                             -._  `._./ /            ,'_.-'' ,       ``-._`.          ,' '`:..'  _.-     \n");
        printf("                                            .:.:`-.._' /           ,','                   `.`.       /'  '  \\.-':.:.    \n");
        printf("                                            :.:. . ./ /          ,','     "AMARILLO"ENTRENAMIENTO"CELESTE"     `.`.    / '  '  '\\. .:.:    \n");
        printf("                                           :.:. . ./ /          / /    ,                      \\ \\  :  '  '  ' \\. .:.:   \n");
        printf("        "BLANCO"............."FIN CELESTE"                      .:. . ./ /          / /           "AMARILLO"POKEMON"CELESTE"     ,     \\ \\ :  '  '  ' '::. .:.   "BLANCO"                ...................\n");
        printf("         ............"FIN CELESTE"                      :. . .: :    o     / /                               \\ ;'  '  '  ' ':: . .:         "BLANCO"          .................\n");
        printf("          ........."FIN CELESTE"                        .:. . | |   /_\\   : :     ,                      ,    : '  '  '  ' ' :: .:.                "BLANCO"  ...............\n");
        printf("           ........."FIN CELESTE"                       :. . .| |  ((<))  | |,          ,       ,   "BLANCO"By"FIN CELESTE"        |\\'__',-._.' ' ||. .:     "BLANCO"             ............\n");
        printf("            .........."FIN CELESTE"                     .:.:. | |   `-'   | |---....____             "BLANCO"Ana G."FIN CELESTE"   | ,---\\/--/  ' ||:.:.      "BLANCO"            ..........\n");
        printf("             ........"FIN CELESTE"                      ------| |         : :    ,.     ```--..._   , "BLANCO"Gutson"FIN CELESTE"  |''  '  '  ' ' ||----        "BLANCO"         ........\n");
        printf("              ......."FIN CELESTE"                      _...--. |  ,       \\ \\             ,.    `-._     ,  /: '  '  '  ' ' ;;..._           "BLANCO"      .......\n");
        printf("               ......"FIN CELESTE"                      :.:. .| | -O-       \\ \\    ,.                `._    / /:'  '  '  ' ':: .:.:      "BLANCO"           ......\n");
        printf("                ....."FIN CELESTE"                      .:. . | |_(`__       \\ \\                        `. / / :'  '  '  ' ';;. .:.       "BLANCO"         .....\n");
        printf("                ....."FIN CELESTE"                      :. . .<' (_)  `>      `.`.          ,.    ,.     ,','   \\  '  '  ' ;;. . .:        "BLANCO"        .....\n");
        printf("                 .."FIN CELESTE"                        .:. . |):-.--'(         `.`-._  ,.           _,-','      \\ '  '  '//| . .:.       "BLANCO"         ....\n");
        printf("                 .."FIN CELESTE"                       :. . .;)()(__)(___________`-._`-.._______..-'_.-'___________\'  '  //_:. . .:       "BLANCO"         .."FIN CELESTE"\n");
        printf("                _::_                    .:.:,' \\/\\/--\\/--------------------------------------------`._',;'`. `.:.:.                  _::_\n");
        printf("               :    :                   :.,' ,' ,'  ,'  /   /   /   ,-------------------.   \\   \\   \\  `. `.`. `..:                 :    :\n");
        printf("______________:      :______________,' ,'  '   /   /   /   /   //                   \\   \\   \\   \\   \\  ` `.A.GUTSON________________:      :________________\n");
        detener_el_tiempo(TIEMPO_RAPIDO);
        fflush(stdout);

        system("clear");
        printf("\n\n                                                               . .:.:.:.:. .:\\     /:. .:.:.:.:. ,                   \n");
        printf("                                                          .-._  `..:.:. . .:.:`- -':.:. . .:.:.,'  _.-.                  \n");
        printf("                                                         .:.:.`-._`-._..-''_...---..._``-.._.-'_.-'.:.:.                 \n");
        printf("                                                      .:.:. . .:_.`' _..-''._________,``-.._ `.._:. . .:.:.              \n");
        printf("                                                   .:.:. . . ,-'_.-''      ||_-(O)-_||      ``-._`-. . . .:.:.           \n");
        printf("                                                  .:. . . .,'_.'           '---------'           `._`.. . . .:.          \n");
        printf("                                                :.:. . . ,','               _________               `.`. . . .:.:        \n");
        printf("                                               `.:.:. .,','            _.-''_________``-._            `._.     _.'       \n");
        printf("                                             -._  `._./ /            ,'_.-'' ,       ``-._`.          ,' '`:..'  _.-     \n");
        printf("                                            .:.:`-.._' /           ,','                   `.`.       /'  '  \\.-':.:.    \n");
        printf("                                            :.:. . ./ /          ,','     "AMARILLO"ENTRENAMIENTO"CELESTE"     `.`.    / '  '  '\\. .:.:    \n");
        printf("                                           :.:. . ./ /          / /    ,                      \\ \\  :  '  '  ' \\. .:.:   \n");
        printf("            "BLANCO"............."FIN CELESTE"                  .:. . ./ /          / /           "AMARILLO"POKEMON"CELESTE"     ,     \\ \\ :  '  '  ' '::. .:.     "BLANCO"         ...................\n");
        printf("            ............."FIN CELESTE"                  :. . .: :    o     / /                               \\ ;'  '  '  ' ':: . .:        "BLANCO"      .................\n");
        printf("            ............."FIN CELESTE"                  .:. . | |   /_\\   : :     ,                      ,    : '  '  '  ' ' :: .:.        "BLANCO"      ...............\n");
        printf("            ............."FIN CELESTE"                  :. . .| |  ((<))  | |,          ,       ,   "BLANCO"By"FIN CELESTE"        |\\'__',-._.' ' ||. .:   "BLANCO"           ............\n");
        printf("            ............."FIN CELESTE"                  .:.:. | |   `-'   | |---....____             "BLANCO"Ana G."FIN CELESTE"   | ,---\\/--/  ' ||:.:.   "BLANCO"           ..........\n");
        printf("             ..........."FIN CELESTE"                   ------| |         : :    ,.     ```--..._   , "BLANCO"Gutson"FIN CELESTE"  |''  '  '  ' ' ||----     "BLANCO"          ........\n");
        printf("              ........."FIN CELESTE"                    _...--. |  ,       \\ \\             ,.    `-._     ,  /: '  '  '  ' ' ;;..._        "BLANCO"       .......\n");
        printf("               ......."FIN CELESTE"                     :.:. .| | -O-       \\ \\    ,.                `._    / /:'  '  '  ' ':: .:.:      "BLANCO"         ......\n");
        printf("                ....."FIN CELESTE"                      .:. . | |_(`__       \\ \\                        `. / / :'  '  '  ' ';;. .:.      "BLANCO"          .....\n");
        printf("                 ..."FIN CELESTE"                       :. . .<' (_)  `>      `.`.          ,.    ,.     ,','   \\  '  '  ' ;;. . .:       "BLANCO"         .....\n");
        printf("                 .."FIN CELESTE"                        .:. . |):-.--'(         `.`-._  ,.           _,-','      \\ '  '  '//| . .:.    "BLANCO"            ....\n");
        printf("                 .."FIN CELESTE"                       :. . .;)()(__)(___________`-._`-.._______..-'_.-'___________\'  '  //_:. . .:        "BLANCO"        .."FIN CELESTE"\n");
        printf("                _::_                    .:.:,' \\/\\/--\\/--------------------------------------------`._',;'`. `.:.:.                  _::_\n");
        printf("               :    :                   :.,' ,' ,'  ,'  /   /   /   ,-------------------.   \\   \\   \\  `. `.`. `..:                 :    :\n");
        printf("______________:      :______________,' ,'  '   /   /   /   /   //                   \\   \\   \\   \\   \\  ` `.A.GUTSON________________:      :________________\n");
        detener_el_tiempo(TIEMPO_RAPIDO);
        fflush(stdout);

        system("clear");
        printf("\n\n                                                               . .:.:.:.:. .:\\     /:. .:.:.:.:. ,                   \n");
        printf("                                                          .-._  `..:.:. . .:.:`- -':.:. . .:.:.,'  _.-.                  \n");
        printf("                                                         .:.:.`-._`-._..-''_...---..._``-.._.-'_.-'.:.:.                 \n");
        printf("                                                      .:.:. . .:_.`' _..-''._________,``-.._ `.._:. . .:.:.              \n");
        printf("                                                   .:.:. . . ,-'_.-''      ||_-(O)-_||      ``-._`-. . . .:.:.           \n");
        printf("                                                  .:. . . .,'_.'           '---------'           `._`.. . . .:.          \n");
        printf("                                                :.:. . . ,','               _________               `.`. . . .:.:        \n");
        printf("                                               `.:.:. .,','            _.-''_________``-._            `._.     _.'       \n");
        printf("                                             -._  `._./ /            ,'_.-'' ,       ``-._`.          ,' '`:..'  _.-     \n");
        printf("                                            .:.:`-.._' /           ,','                   `.`.       /'  '  \\.-':.:.    \n");
        printf("                                            :.:. . ./ /          ,','     "AMARILLO"ENTRENAMIENTO"CELESTE"     `.`.    / '  '  '\\. .:.:    \n");
        printf("                                           :.:. . ./ /          / /    ,                      \\ \\  :  '  '  ' \\. .:.:   \n");
        printf("               "BLANCO"..........."FIN CELESTE"                 .:. . ./ /          / /           "AMARILLO"POKEMON"CELESTE"     ,     \\ \\ :  '  '  ' '::. .:.      "BLANCO"    ................\n");
        printf("               ..........."FIN CELESTE"                 :. . .: :    o     / /                               \\ ;'  '  '  ' ':: . .:    "BLANCO"      ..............\n");
        printf("               ..........."FIN CELESTE"                 .:. . | |   /_\\   : :     ,                      ,    : '  '  '  ' ' :: .:.    "BLANCO"      .............\n");
        printf("               ..........."FIN CELESTE"                 :. . .| |  ((<))  | |,          ,       ,   "BLANCO"By"FIN CELESTE"        |\\'__',-._.' ' ||. .: "BLANCO"         ............\n");
        printf("               ..........."FIN CELESTE"                 .:.:. | |   `-'   | |---....____             "BLANCO"Ana G."FIN CELESTE"   | ,---\\/--/  ' ||:.:. "BLANCO"         ..........\n");
        printf("               .........."FIN CELESTE"                  ------| |         : :    ,.     ```--..._   , "BLANCO"Gutson"FIN CELESTE"  |''  '  '  ' ' ||---- "BLANCO"          ........\n");
        printf("               ........."FIN CELESTE"                   _...--. |  ,       \\ \\             ,.    `-._     ,  /: '  '  '  ' ' ;;..._       "BLANCO"     .......\n");
        printf("                ......."FIN CELESTE"                    :.:. .| | -O-       \\ \\    ,.                `._    / /:'  '  '  ' ':: .:.:    "BLANCO"         ......\n");
        printf("                 ....."FIN CELESTE"                     .:. . | |_(`__       \\ \\                        `. / / :'  '  '  ' ';;. .:.    "BLANCO"          .....\n");
        printf("                  ..."FIN CELESTE"                      :. . .<' (_)  `>      `.`.          ,.    ,.     ,','   \\  '  '  ' ;;. . .:     "BLANCO"         .....\n");
        printf("                  .."FIN CELESTE"                       .:. . |):-.--'(         `.`-._  ,.           _,-','      \\ '  '  '//| . .:.    "BLANCO"            ..\n");
        printf("                 .."FIN CELESTE"                       :. . .;)()(__)(___________`-._`-.._______..-'_.-'___________\'  '  //_:. . .:        "BLANCO"        .."FIN CELESTE"\n");
        printf("                _::_                    .:.:,' \\/\\/--\\/--------------------------------------------`._',;'`. `.:.:.                  _::_\n");
        printf("               :    :                   :.,' ,' ,'  ,'  /   /   /   ,-------------------.   \\   \\   \\  `. `.`. `..:                 :    :\n");
        printf("______________:      :______________,' ,'  '   /   /   /   /   //                   \\   \\   \\   \\   \\  ` `.A.GUTSON________________:      :________________\n");
        detener_el_tiempo(TIEMPO_RAPIDO);
        fflush(stdout);
        
        system("clear");
        printf("\n\n                                                               . .:.:.:.:. .:\\     /:. .:.:.:.:. ,                   \n");
        printf("                                                          .-._  `..:.:. . .:.:`- -':.:. . .:.:.,'  _.-.                  \n");
        printf("                                                         .:.:.`-._`-._..-''_...---..._``-.._.-'_.-'.:.:.                 \n");
        printf("                                                      .:.:. . .:_.`' _..-''._________,``-.._ `.._:. . .:.:.              \n");
        printf("                                                   .:.:. . . ,-'_.-''      ||_-(O)-_||      ``-._`-. . . .:.:.           \n");
        printf("                                                  .:. . . .,'_.'           '---------'           `._`.. . . .:.          \n");
        printf("                                                :.:. . . ,','               _________               `.`. . . .:.:        \n");
        printf("                                               `.:.:. .,','            _.-''_________``-._            `._.     _.'       \n");
        printf("                                             -._  `._./ /            ,'_.-'' ,       ``-._`.          ,' '`:..'  _.-     \n");
        printf("                                            .:.:`-.._' /           ,','                   `.`.       /'  '  \\.-':.:.    \n");
        printf("                                            :.:. . ./ /          ,','     "AMARILLO"ENTRENAMIENTO"CELESTE"     `.`.    / '  '  '\\. .:.:    \n");
        printf("                                           :.:. . ./ /          / /    ,                      \\ \\  :  '  '  ' \\. .:.:   \n");
        printf("                    "BLANCO"..........."FIN CELESTE"            .:. . ./ /          / /           "AMARILLO"POKEMON"CELESTE"     ,     \\ \\ :  '  '  ' '::. .:. "BLANCO"  .............\n");
        printf("                    ..........."FIN CELESTE"            :. . .: :    o     / /                               \\ ;'  '  '  ' ':: . .:  "BLANCO" ............\n");
        printf("                   ..........."FIN CELESTE"             .:. . | |   /_\\   : :     ,                      ,    : '  '  '  ' ' :: .:. "BLANCO"   .........\n");
        printf("                   ..........."FIN CELESTE"             :. . .| |  ((<))  | |,          ,       ,   "BLANCO"By"FIN CELESTE"        |\\'__',-._.' ' ||. .: "BLANCO"    .........\n");
        printf("                  ..........."FIN CELESTE"              .:.:. | |   `-'   | |---....____             "BLANCO"Ana G."FIN CELESTE"   | ,---\\/--/  ' ||:.:.  "BLANCO"    ..........\n");
        printf("                 .........."FIN CELESTE"                ------| |         : :    ,.     ```--..._   , "BLANCO"Gutson"FIN CELESTE"  |''  '  '  ' ' ||----  "BLANCO"      ........\n");
        printf("                 ........."FIN CELESTE"                 _...--. |  ,       \\ \\             ,.    `-._     ,  /: '  '  '  ' ' ;;..._   "BLANCO"      .......\n");
        printf("                  ......."FIN CELESTE"                  :.:. .| | -O-       \\ \\    ,.                `._    / /:'  '  '  ' ':: .:.: "BLANCO"         ......\n");
        printf("                   ....."FIN CELESTE"                   .:. . | |_(`__       \\ \\                        `. / / :'  '  '  ' ';;. .:. "BLANCO"          .....\n");
        printf("                  ..."FIN CELESTE"                      :. . .<' (_)  `>      `.`.          ,.    ,.     ,','   \\  '  '  ' ;;. . .:  "BLANCO"         .....\n");
        printf("                  .."FIN CELESTE"                       .:. . |):-.--'(         `.`-._  ,.           _,-','      \\ '  '  '//| . .:.   "BLANCO"            ...\n");
        printf("                 .."FIN CELESTE"                       :. . .;)()(__)(___________`-._`-.._______..-'_.-'___________\'  '  //_:. . .:   "BLANCO"             .."FIN CELESTE"\n");
        printf("                _::_                    .:.:,' \\/\\/--\\/--------------------------------------------`._',;'`. `.:.:.                  _::_\n");
        printf("               :    :                   :.,' ,' ,'  ,'  /   /   /   ,-------------------.   \\   \\   \\  `. `.`. `..:                 :    :\n");
        printf("______________:      :______________,' ,'  '   /   /   /   /   //                   \\   \\   \\   \\   \\  ` `.A.GUTSON________________:      :________________\n");
        detener_el_tiempo(TIEMPO_RAPIDO);
        fflush(stdout);
        
        system("clear"); 
        printf("\n\n                                                               . .:.:.:.:. .:\\     /:. .:.:.:.:. ,                   \n");
        printf("                                                          .-._  `..:.:. . .:.:`- -':.:. . .:.:.,'  _.-.                  \n");
        printf("                                                         .:.:.`-._`-._..-''_...---..._``-.._.-'_.-'.:.:.                 \n");
        printf("                                                      .:.:. . .:_.`' _..-''._________,``-.._ `.._:. . .:.:.              \n");
        printf("                                                   .:.:. . . ,-'_.-''      ||_-(O)-_||      ``-._`-. . . .:.:.           \n");
        printf("                                                  .:. . . .,'_.'           '---------'           `._`.. . . .:.          \n");
        printf("                                                :.:. . . ,','               _________               `.`. . . .:.:        \n");
        printf("                                               `.:.:. .,','            _.-''_________``-._            `._.     _.'       \n");
        printf("                                             -._  `._./ /            ,'_.-'' ,       ``-._`.          ,' '`:..'  _.-     \n");
        printf("                                            .:.:`-.._' /           ,','                   `.`.       /'  '  \\.-':.:.    \n");
        printf("                                            :.:. . ./ /          ,','     "AMARILLO"ENTRENAMIENTO"CELESTE"     `.`.    / '  '  '\\. .:.:    \n");
        printf("                                           :.:. . ./ /          / /    ,                      \\ \\  :  '  '  ' \\. .:.:   \n");
        printf("               "BLANCO"..........."FIN CELESTE"                 .:. . ./ /          / /           "AMARILLO"POKEMON"CELESTE"     ,     \\ \\ :  '  '  ' '::. .:.  "BLANCO"   .............\n");
        printf("               ..........."FIN CELESTE"                 :. . .: :    o     / /                               \\ ;'  '  '  ' ':: . .:  "BLANCO"   ............\n");
        printf("               ..........."FIN CELESTE"                 .:. . | |   /_\\   : :     ,                      ,    : '  '  '  ' ' :: .:. "BLANCO"     .........\n");
        printf("               ..........."FIN CELESTE"                 :. . .| |  ((<))  | |,          ,       ,   "BLANCO"By"FIN CELESTE"        |\\'__',-._.' ' ||. .:  "BLANCO"     .........\n");
        printf("               ..........."FIN CELESTE"                 .:.:. | |   `-'   | |---....____             "BLANCO"Ana G."FIN CELESTE"   | ,---\\/--/  ' ||:.:.   "BLANCO"     ..........\n");
        printf("               .........."FIN CELESTE"                  ------| |         : :    ,.     ```--..._   , "BLANCO"Gutson"FIN CELESTE"  |''  '  '  ' ' ||----   "BLANCO"       ........\n");
        printf("               ........."FIN CELESTE"                   _...--. |  ,       \\ \\             ,.    `-._     ,  /: '  '  '  ' ' ;;..._"BLANCO"           .......\n");
        printf("                ......."FIN CELESTE"                    :.:. .| | -O-       \\ \\    ,.                `._    / /:'  '  '  ' ':: .:.:        "BLANCO"    ......\n");
        printf("                 ....."FIN CELESTE"                     .:. . | |_(`__       \\ \\                        `. / / :'  '  '  ' ';;. .:.      "BLANCO"       .....\n");
        printf("                  ..."FIN CELESTE"                      :. . .<' (_)  `>      `.`.          ,.    ,.     ,','   \\  '  '  ' ;;. . .:     "BLANCO"        .....\n");
        printf("                  .."FIN CELESTE"                       .:. . |):-.--'(         `.`-._  ,.           _,-','      \\ '  '  '//| . .:.     "BLANCO"           ..\n");
        printf("                 .."FIN CELESTE"                       :. . .;)()(__)(___________`-._`-.._______..-'_.-'___________\'  '  //_:. . .:     "BLANCO"           .."FIN CELESTE"\n");
        printf("                _::_                    .:.:,' \\/\\/--\\/--------------------------------------------`._',;'`. `.:.:.                  _::_\n");
        printf("               :    :                   :.,' ,' ,'  ,'  /   /   /   ,-------------------.   \\   \\   \\  `. `.`. `..:                 :    :\n");
        printf("______________:      :______________,' ,'  '   /   /   /   /   //                   \\   \\   \\   \\   \\  ` `.A.GUTSON________________:      :________________\n");
        detener_el_tiempo(TIEMPO_RAPIDO);
        fflush(stdout);

        system("clear");
        printf("\n\n                                                               . .:.:.:.:. .:\\     /:. .:.:.:.:. ,                   \n");
        printf("                                                          .-._  `..:.:. . .:.:`- -':.:. . .:.:.,'  _.-.                  \n");
        printf("                                                         .:.:.`-._`-._..-''_...---..._``-.._.-'_.-'.:.:.                 \n");
        printf("                                                      .:.:. . .:_.`' _..-''._________,``-.._ `.._:. . .:.:.              \n");
        printf("                                                   .:.:. . . ,-'_.-''      ||_-(O)-_||      ``-._`-. . . .:.:.           \n");
        printf("                                                  .:. . . .,'_.'           '---------'           `._`.. . . .:.          \n");
        printf("                                                :.:. . . ,','               _________               `.`. . . .:.:        \n");
        printf("                                               `.:.:. .,','            _.-''_________``-._            `._.     _.'       \n");
        printf("                                             -._  `._./ /            ,'_.-'' ,       ``-._`.          ,' '`:..'  _.-     \n");
        printf("                                            .:.:`-.._' /           ,','                   `.`.       /'  '  \\.-':.:.    \n");
        printf("                                            :.:. . ./ /          ,','     "AMARILLO"ENTRENAMIENTO"CELESTE"     `.`.    / '  '  '\\. .:.:    \n");
        printf("                                           :.:. . ./ /          / /    ,                      \\ \\  :  '  '  ' \\. .:.:   \n");
        printf("            "BLANCO"............."FIN CELESTE"                  .:. . ./ /          / /           "AMARILLO"POKEMON"CELESTE"     ,     \\ \\ :  '  '  ' '::. .:.   "BLANCO"    .............\n");
        printf("            ............."FIN CELESTE"                  :. . .: :    o     / /                               \\ ;'  '  '  ' ':: . .:       "BLANCO" ............\n");
        printf("            ............."FIN CELESTE"                  .:. . | |   /_\\   : :     ,                      ,    : '  '  '  ' ' :: .:.    "BLANCO"     .........\n");
        printf("            ............."FIN CELESTE"                  :. . .| |  ((<))  | |,          ,       ,   "BLANCO"By"FIN CELESTE"        |\\'__',-._.' ' ||. .:"BLANCO"          .........\n");
        printf("            ............."FIN CELESTE"                  .:.:. | |   `-'   | |---....____             "BLANCO"Ana G."FIN CELESTE"   | ,---\\/--/  ' ||:.:.        "BLANCO"   ..........\n");
        printf("             ..........."FIN CELESTE"                   ------| |         : :    ,.     ```--..._   , "BLANCO"Gutson"FIN CELESTE"  |''  '  '  ' ' ||----    "BLANCO"        ........\n");
        printf("              ........."FIN CELESTE"                    _...--. |  ,       \\ \\             ,.    `-._     ,  /: '  '  '  ' ' ;;..._    "BLANCO"         .......\n");
        printf("               ......."FIN CELESTE"                     :.:. .| | -O-       \\ \\    ,.                `._    / /:'  '  '  ' ':: .:.:    "BLANCO"          ......\n");
        printf("                ....."FIN CELESTE"                      .:. . | |_(`__       \\ \\                        `. / / :'  '  '  ' ';;. .:.    "BLANCO"           .....\n");
        printf("                 ..."FIN CELESTE"                       :. . .<' (_)  `>      `.`.          ,.    ,.     ,','   \\  '  '  ' ;;. . .:     "BLANCO"          .....\n");
        printf("                 .."FIN CELESTE"                        .:. . |):-.--'(         `.`-._  ,.           _,-','      \\ '  '  '//| . .:.       "BLANCO"         ..\n");
        printf("                 .."FIN CELESTE"                       :. . .;)()(__)(___________`-._`-.._______..-'_.-'___________\'  '  //_:. . .:      "BLANCO"          .."FIN CELESTE"\n");
        printf("                _::_                    .:.:,' \\/\\/--\\/--------------------------------------------`._',;'`. `.:.:.                  _::_\n");
        printf("               :    :                   :.,' ,' ,'  ,'  /   /   /   ,-------------------.   \\   \\   \\  `. `.`. `..:                 :    :\n");
        printf("______________:      :______________,' ,'  '   /   /   /   /   //                   \\   \\   \\   \\   \\  ` `.A.GUTSON________________:      :________________\n");
        printf(FIN);
        detener_el_tiempo(TIEMPO_RAPIDO);
        fflush(stdout);
    }
}

// Pre y post en "interfaz.h"
void mostrar_carga_juego(){

    system("clear");
	detener_el_tiempo(TIEMPO_RAPIDO);
	
	animacion();
    system("clear");
	detener_el_tiempo(TIEMPO_RAPIDO);

    printf(BLANCO "Iniciando...\n" FIN);
    mostrar_carga_nuevo_menu();
    detener_el_tiempo(TIEMPO_RAPIDO);
    system("clear");
}
