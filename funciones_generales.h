#ifndef _FUNCIONES_GENERALES_H_
#define _FUNCIONES_GENERALES_H_


#include <stdio.h>
#include <stdbool.h>


#define MAX_ESPECIE		100
#define MAX_COLOR 		50
#define MAX_PALABRA 	100

#define VOCAL_1		'A'
#define VOCAL_2		'E'
#define VOCAL_3		'I'
#define VOCAL_4		'O'
#define VOCAL_5		'U'

#define DECENA 						10
#define VALOR_NULO					0

#define LEER 						"r"
#define ESCRIBIR 					"w"
#define EXTENSION_ARCHIVO_TEXTO		".txt"
#define PUNTO 						'.'
#define MAX_NOMBRE_ARCHIVO 			100
#define MAX_EXTENSION_ARCHIVO 		  4
#define CARACTER_VACIO				'\0'
#define LECTURA_ERRONEA				  0
#define BASTA						"B"
#define MAX_RUTA					101

#define TIEMPO_NORMAL	2
#define TIEMPO_RAPIDO	0.125

#define FIN  			"\033[0m"
#define NEGRO	 		"\033[0m\033[30m"
#define GRIS	 		"\033[1m\033[30m"
#define ROJO_SUAVE 		"\033[0m\033[31m"
#define ROJO_FUERTE 	"\033[1m\033[31m"
#define VERDE_SUAVE 	"\033[0m\033[32m"
#define VERDE_FUERTE 	"\033[1m\033[32m"
#define AMARILLO 		"\033[1m\033[33m"
#define MARRON	 		"\033[0m\033[33m"
#define AZUL_SUAVE 		"\033[0m\033[34m"
#define AZUL 			"\033[1m\033[34m"
#define MAGENTA_SUAVE	"\033[0m\033[35m"
#define MAGENTA 		"\033[1m\033[35m"
#define CELESTE_SUAVE	"\033[0m\033[36m"
#define CELESTE			"\033[1m\033[36m"
#define SILVER 			"\033[0m\033[37m"
#define BLANCO 			"\033[1m\033[37m"
#define CELESTE_FONDO 	"\033[0m\033[46m"

#define CANT_COLORES	15

const static char TEXTO_COLORES[][MAX_COLOR] = {
	"negro", "azul", "amarillo", "blanco", "blanquirrojo",
	"rosa", "bermellon", "gris", "naranja", "marron",  "morado",
	"violeta", "rojo", "verde", "celeste"
};

const static char CODIGO_COLORES[][MAX_COLOR] = {
	NEGRO, AZUL, AMARILLO, BLANCO, ROJO_SUAVE, ROJO_FUERTE, ROJO_FUERTE, GRIS,
	MARRON, MARRON, MAGENTA, MAGENTA, ROJO_SUAVE, VERDE_FUERTE, CELESTE
};


/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función convierte en mayúscula "letra" si el mismo no lo estaba;
			si "letra" ya estaba en mayúscula, no se actualizará el valor.
 */
void mayusculizar_letra(char *letra);

/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función convierte en mayúscula "frase" si el mismo no lo estaba;
			si "frase" ya estaba en mayúscula, no se actualizará el valor.
 */
void mayusculizar_string(char frase[]);


/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función espera que el usuario presione "enter".
 */
void esperar_al_usuario();


/*
	Pre-condiciones: 
		"texto" y "color" tienen tamaño mayor a 0 y menor a MAX_COLOR.
	Post-condiciones: 
   		la función actualiza "color" de ser posible, con alguna posición
   			de "CODIGO_COLORES".
 */
void asumo_color(char texto[MAX_COLOR], char color[MAX_COLOR]);


/*
	Pre-condiciones: 
		"texto" tiene tamaño mayor a 0 y menor a MAX_COLOR.
	Post-condiciones: 
   		la función devuelve la posicion del vector donde se encuentra el color.
 */
int asumo_posicion_color(char texto[MAX_COLOR]);

/*
	Pre-condiciones: 
	    "palabra" es diferente a "".
	Post-condiciones: 
	    la función actualiza el valor de nueva_palabra.
 */
void palabra_invertida(char palabra[MAX_PALABRA], char nueva_palabra[MAX_PALABRA]);

/*
 * Detendrá el tiempo los segundos indicados como parámetro.
 * Ejemplos: 
 * - Para detener medio segundo se deberá llamar detener_el_tiempo(0.5)
 * - Para detener dos segundos se deberá llamar detener_el_tiempo(2)  
 */
/*
	Pre-condiciones: 
    	-
	Post-condiciones: 
    	la función detiene el tiempo según el valor recibido por parámetro.
 */
void detener_el_tiempo(float segundos);

/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retorna si la letra es diferente a todas las vocales.
 */
bool es_consonante(char letra);

/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retornará si el archivo se pudo abrir para leer.
 */
bool archivo_existe(const char archivo[MAX_NOMBRE_ARCHIVO]);

/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retornará si el archivo terino de leerse.
 */
bool lectura_archivo_finalizada(int leidos);

/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retornará si se pudo leer bien la letra.
 */
bool lee_bien_letra(int leidos, char letra_leida, char letra_valida);

/*
	Pre-condiciones: 
		"comparacion_1" debe ser menor a "comparacion_2".
	Post-condiciones:
		la función retorna true si el primer parámetro ("letra") es
			igual al valor a comparar.
 */
bool ingreso_letra_es_correcto_1(char letra, char comparacion);

/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retorna true si el primer parámetro ("letra") es igual
			a ninguno de los dos valores a comparar.
 */
bool ingreso_letra_es_correcto_2(char letra, char comparacion_1,  char comparacion_2);

/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retorna true si el primer parámetro ("letra") es igual
			a ninguno de los tres valores a comparar.
 */
bool ingreso_letra_es_correcto_3(char letra, char comparacion_1,
	char comparacion_2, char comparacion_3);

/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retorna true si el primer parámetro ("letra") es igual
			a ninguno de los cuatro valores a comparar.
 */
bool ingreso_letra_es_correcto_4(char letra, char comparacion_1,
	char comparacion_2, char comparacion_3, char comparacion_4);

/*
	Pre-condiciones:
		-
	Post-condiciones:
	 la función retorna true si la ruta es muy larga.
 */
bool ruta_muy_larga(char ruta_archivo[]);

/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retorna true si es el valor de fin.
 */
bool es_valor_fin(char ruta_archivo[MAX_RUTA], char palabra_fin[]);

/*
	Pre-condiciones:
		"comparacion_1" menor a "comparacion_2".
	Post-condiciones:
		la función retorna true si el número es válido.
 */
bool numero_valido(int valor, int comparacion_1, int comparacion_2);

/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retorna cuántas posiciones de "nombre" son diferentes
			a todas las vocales.
 */
int cant_consonantes(char nombre[MAX_ESPECIE]);

/*
	Pre-condiciones: 
	    "valor" positivo.
	Post-condiciones: 
	    la función devolverá la cantidad de digitos de "valor".
 */
int cant_digitos(int valor);

/*
	Pre-condiciones:
		"palabra" es diferente a "".
	Post-condiciones:
		la función retorna cuántas posiciones tiene palabra antes del primer
			CARACTER_NULO.
 */
int cant_letras(char palabra[MAX_PALABRA]);

/*
	Pre-condiciones: 
	    "tope" debe ser mayor a 0;
	Post-condiciones: 
	    la función retornará un valor entre 1 y "tope".
 */
int numero_random(int tope);

/*
	Pre-condiciones:
		"archivo" debe estar abierto en modo LEER.
	Post-condiciones:
		la función leerá el archivo y devolverá cuánto pudo leer;
		la función actualizará *letra_leida.
 */
int lectura_letra(FILE* archivo, char *letra_leida);


#endif /* _FUNCIONES_GENERALES_H_ */
