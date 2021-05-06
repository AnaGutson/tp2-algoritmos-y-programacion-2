#ifndef __INTERFAZ_GRAFICA_H__
#define __INTERFAZ_GRAFICA_H__


#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


#define ESPACIO         " "
#define MARGEN          "					"
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

#define MAX_TEXTO       200


/*
	Pre-condiciones:
		"-
	Post-condiciones:
		la función muestra un mensaje de error.
 */
void mostrar_error_archivo();

/*
	Pre-condiciones:
		"-
	Post-condiciones:
		la función muestra un mensaje de error.
 */
void mostrar_texto_error_archivo(char ruta_leida[MAX_RUTA]);

/*
	Pre-condiciones:
		"-
	Post-condiciones:
		la función muestra un mensaje de error.
 */
void mostrar_texto_error_menu_2(char letra, char comparacion_1, char comparacion_2);

/*
	Pre-condiciones:
		"-
	Post-condiciones:
		la función muestra un mensaje de error.
 */
void mostrar_texto_error_menu_3(char letra, char comparacion_1, char comparacion_2, char comparacion_3);

/*
	Pre-condiciones:
		"-
	Post-condiciones:
		la función muestra un mensaje de error.
 */
void mostrar_texto_error_menu_4(char letra, char comparacion_1, char comparacion_2, char comparacion_3, char comparacion_4);

/*
	Pre-condiciones:
		"-
	Post-condiciones:
		la función muestra un mensaje de error.
 */
void mostrar_error_ingreso_letra(char letra_1, char* opcion_1, char letra_2, char* opcion_2);

/*
	Pre-condiciones:
		"retorno" debe ser ERROR o EXITO.
	Post-condiciones:
		la función muestra un mensaje segun "retorno.
 */
void mensaje_segun_retorno(int retorno, void(*funcion_extra)(void*), void* extra);

/*
	Pre-condiciones: 
		-	
	Post-condiciones:
		la función mostrará un menú seǵún los parámetros recibidos.
*/
void mostrar_parte_visual_menu(char titulo_menu[MAX_TEXTO], char* extra, void(*mostrar_lineas_opciones_menu)(int));

/*
	Pre-condiciones: 
		"largo_total" positivo.	
	Post-condiciones:
		la función mostrará las lineas de opciones del menu.
*/
void mostrar_lineas_opciones_menu_inicio(int largo_total);

/*
	Pre-condiciones: 
		"largo_total" positivo.	
	Post-condiciones:
		la función mostrará las lineas de opciones del menu.
*/
void mostrar_lineas_opciones_menu_gimnasio(int largo_total);

/*
	Pre-condiciones: 
		"largo_total" positivo.	
	Post-condiciones:
		la función mostrará las lineas de opciones del menu.
*/
void mostrar_lineas_opciones_menu_victoria_con_tomar_prestado(int largo_total);

/*
	Pre-condiciones: 
		"largo_total" positivo.	
	Post-condiciones:
		la función mostrará las lineas de opciones del menu.
*/
void mostrar_lineas_opciones_menu_victoria_sin_tomar_prestado(int largo_total);

/*
	Pre-condiciones: 
		"largo_total" positivo.	
	Post-condiciones:
		la función mostrará las lineas de opciones del menu.
*/
void mostrar_lineas_opciones_menu_derrota(int largo_total);

/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará un cuadro de información de pokemones de personaje.
*/
void mostrar_pokemones_personaje(lista_t* caja, pokemon_t** party);

/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará información de personaje.
*/
void mostrar_cambios_personaje(void* extra);

/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará información de personaje.
*/
void mostrar_informacion_personaje(personaje_t* personaje);

/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará información de entrenador.
*/
void mostrar_informacion_entrenador(entrenador_t* entrenador);

/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará los datos de la batalla.
*/
void mostrar_datos_batalla(char nombre_gimnasio[MAX_TEXTO], char nombre_entrenador[MAX_TEXTO],
	bool es_lider,char nombre_personaje[MAX_TEXTO], pokemon_t* pokemon_personaje, pokemon_t* pokemon_oponente);

/*
	Pre-condiciones: 
		-
	Post-condiciones:
		la función mostrará información del gimnasio.
*/
void mostrar_gimnasio(gimnasio_t* gimnasio);

/*
	Pre-condiciones: 
    	-
	Post-condiciones:
    	la función mostrará un punto tras otro, formando una barra de progreso.
 */
void mostrar_barra_progreso();

/*
	Pre-condiciones: 
    	-
	Post-condiciones:
    	la función mostrará un punto tras otro, formando una barra de progreso.
 */
void mostrar_carga_nuevo_menu();

/*
	Pre-condiciones: 
		-	
	Post-condiciones:
		la función mostrará un ascii art.
 */
void mostrar_mensaje_felicitaciones();

/*
	Pre-condiciones: 
		-	
	Post-condiciones:
		la función mostrará un ascii art.
 */
void mostrar_mensaje_juego_ganado();

/*
	Pre-condiciones: 
		-	
	Post-condiciones:
		la función mostrará un ascii art.
 */
void mostrar_mensaje_juego_perdido();

/*
	Pre-condiciones: 
		-	
	Post-condiciones:
		la función mostrará un ascii art.
 */
void mostrar_titulo_juego();

/*
	Pre-condiciones: 
		-	
	Post-condiciones:
		la función mostrará un ascii art.
 */
void mostrar_carga_juego();

#endif /* __INTERFAZ_GRAFICA_H__ */