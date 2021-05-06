#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "funciones_generales.h"

#define DEFAULT 		3

/* 12 */
/*
	Pre y post condiciones en funciones_generales.h
 */
bool archivo_existe(const char archivo[MAX_NOMBRE_ARCHIVO]){
	FILE* archivo_nuevo;
	bool existe = true;

	archivo_nuevo = fopen(archivo, LEER);

	if(!archivo_nuevo)
		existe = false;
	else
		fclose(archivo_nuevo);
	
	return existe;
}

/* 03 */
/*
	Pre y post condiciones en funciones_generales.h
 */
bool lectura_archivo_finalizada(int leidos){

	return leidos == EOF;
}

/* 03 */
/*
	Pre y post condiciones en funciones_generales.h
 */
bool lee_bien_letra(int leidos, char letra_leida, char letra_valida){

	return ((leidos != EOF) && (letra_leida == letra_valida)); 
}

/* 03 */
/*
	Pre y post condiciones en funciones_generales.h
 */
bool ingreso_letra_es_correcto_1(char letra, char comparacion){

    return (letra == comparacion);
}

/* 03 */
/*
	Pre y post condiciones en funciones_generales.h
 */
bool ingreso_letra_es_correcto_2(char letra, char comparacion_1,  char comparacion_2){

    return ((letra == comparacion_1) || (letra == comparacion_2));
}

/* 03 */
/*
	Pre y post condiciones en funciones_generales.h
 */
bool ingreso_letra_es_correcto_3(char letra, char comparacion_1,
	char comparacion_2, char comparacion_3){

    return ( (letra == comparacion_1) || (letra == comparacion_2) || (letra == comparacion_3));
}

/* 03 */
/*
	Pre y post condiciones en funciones_generales.h
 */
bool ingreso_letra_es_correcto_4(char letra, char comparacion_1, char comparacion_2,
	char comparacion_3, char comparacion_4){

    return ( (letra == comparacion_1) || (letra == comparacion_2) || (letra == comparacion_3) || (letra == comparacion_4));
}

/* 03 */
/*
	Pre y post condiciones en funciones_generales.h
 */
bool ruta_muy_larga(char ruta_archivo[]){

	return (strlen(ruta_archivo) > MAX_RUTA);
}

/*07*/
/*
	Pre y post condiciones en funciones_generales.h
 */
bool es_valor_fin(char ruta_archivo[MAX_RUTA], char palabra_fin[]){
	char ruta_comparar[MAX_RUTA];
	strcpy(ruta_comparar, ruta_archivo);

	mayusculizar_letra(ruta_comparar);

	return (strcmp(ruta_comparar, palabra_fin) == 0);
}

/*
	Pre y post condiciones en funciones_generales.h
 */
bool numero_valido(int valor, int comparacion_1, int comparacion_2){

    return ((valor >= comparacion_1) && (valor <= comparacion_2));
}

/*
	Pre y post condiciones en funciones_generales.h
 */
void mayusculizar_letra(char *letra){

    *letra = (char)toupper(*letra);
}

/*
	Pre y post condiciones en funciones_generales.h
 */
void mayusculizar_string(char frase[]){
	size_t largo = strlen(frase);

	for(size_t i = 0; i < largo; i++)
    	frase[i] = (char)toupper(frase[i]);
}

/*
	Pre y post condiciones en funciones_generales.h
 */
bool es_consonante(char letra){

	mayusculizar_letra(&letra);

	return ( (letra != VOCAL_1) && (letra != VOCAL_2) && (letra != VOCAL_3)
		&& (letra != VOCAL_4) && (letra != VOCAL_5) );
}

/*
	Pre y post condiciones en funciones_generales.h
 */
int cant_consonantes(char nombre[MAX_ESPECIE]){
	int largo, consonantes = 0;

	largo = (int)strlen(nombre);
	for(int i = 0; i < largo; i++){

		if(es_consonante(nombre[i]))
			consonantes++;
	}

	return consonantes;
}

/*
	Pre y post condiciones en funciones_generales.h
 */
int cant_digitos(int valor){
	int digitos = 0;
	
	do{
		
		digitos++;
		valor/=DECENA;
	}while(valor != VALOR_NULO);
	
	return digitos;
}

/*
	Pre y post condiciones en funciones_generales.h
 */
int cant_letras(char palabra[MAX_PALABRA]){

	return (int)strlen(palabra);
}

/*
	Pre y post condiciones en funciones_generales.h
 */
int numero_random(int tope){
	
	return (rand()%tope);
}

/*
	Pre y post condiciones en funciones_generales.h
 */
int lectura_letra(FILE* archivo, char *letra_leida){

	return fscanf(archivo, "%c;", letra_leida);
}

/*
	Pre-condiciones: 
		"texto_original", "texto_a_comparar", "donde_guardar" y "color"
			tienen tamaño mayor a 0 y menor a MAX_COLOR;
		"color" es un codigo para mostrar el color;
		"*i" es positivo;
		"*encontro_color" es false.
	Post-condiciones: 
	    la función actualiza "donde_guardar" de ser posible, con "color",
	    	además de actualizar el valor del puntero "*encontro_color";
	    no solo eso, sino que la función siempre actualiza el valor del
	    	puntero "*i" incrementandolo en uno.
 */
void definir_color(char texto_original[MAX_COLOR], const char texto_a_comparar[MAX_COLOR],
	char donde_guardar[MAX_COLOR], const char color[MAX_COLOR], int *i, bool *encontro_color){

	if(strcmp(texto_original, texto_a_comparar) == 0){

		strcpy(donde_guardar, color);
		*encontro_color = true;
	}
	(*i)++;
}

/*
	Pre y post condiciones en funciones_generales.h
 */
void asumo_color(char texto[MAX_COLOR], char color[MAX_COLOR]){
	int i = 0;
	bool encontro_color = false;
	
	while((i < CANT_COLORES) && (!encontro_color))
		definir_color(texto, TEXTO_COLORES[i], color, CODIGO_COLORES[i], &i, &encontro_color);
	
	if(!encontro_color)
		strcpy(color, CODIGO_COLORES[DEFAULT]);
}

/*
	Pre y post condiciones en funciones_generales.h
 */
int asumo_posicion_color(char texto[MAX_COLOR]){
	int i = 0;
	bool encontro_color = false;
	char basura[MAX_COLOR];

	while((i < CANT_COLORES) && (!encontro_color))
		definir_color(texto, TEXTO_COLORES[i], basura, CODIGO_COLORES[i], &i, &encontro_color);
	
	if(!encontro_color)
		i = 0;

	return i;	
}


/*Pre-condiciones: 
    "pos" positivo - o cero - y menor a "cant_letras(palabra)".
Post-condiciones: 
    la función recursiva actualiza nueva_palabra a partir de palabra y vuelve a invocarse a si misma siempre y cuando "pos" sea mayor o igual a 0.*/
void palabra_invertida_aux(char palabra[MAX_PALABRA], int pos, char nueva_palabra[MAX_PALABRA]){
	int largo_original = cant_letras(palabra) - 1;

	if(pos >= 0){
		
		nueva_palabra[largo_original - pos] = palabra[pos];
		palabra_invertida_aux(palabra, (pos - 1), nueva_palabra);
	}
}

/*
	Pre y post condiciones en funciones_generales.h
 */
void palabra_invertida(char palabra[MAX_PALABRA], char nueva_palabra[MAX_PALABRA]){
	int largo = cant_letras(palabra);
	
	palabra_invertida_aux(palabra, largo-1, nueva_palabra);
}

/*
	Pre y post condiciones en funciones_generales.h
 */
void esperar_al_usuario(){

    printf(BLANCO"\n\nPresione enter para continuar\n");
    while(getchar()!='\n');
    while(getchar()!='\n');
}

/*
	Pre y post condiciones en funciones_generales.h
 */
void detener_el_tiempo(float segundos){
	char comando[MAX_PALABRA];

	snprintf(comando, MAX_PALABRA, "sleep %0.1f", segundos);
	system(comando);
}

