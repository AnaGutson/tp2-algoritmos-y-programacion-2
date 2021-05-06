#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "heap.h"
#include "pila.h"
#include "lista.h"
#include "funciones_generales.h"
#include "batallas.h"
#include "pokemon.h"
#include "entrenador.h"
#include "gimnasio.h"
#include "personaje.h"
#include "interfaz_grafica.h"


#define LETRA_DEFAULT	'A'

#define IR_MENU_INICIO          				'a'
#define IR_MENU_GIMNASIO        				'b'
#define IR_MENU_GIMNASIO_NUEVO  				'c'
#define IR_MENU_VICTORIA_CON_TOMAR_PRESTADO		'd'
#define IR_MENU_VICTORIA_SIN_TOMAR_PRESTADO		'e'
#define IR_MENU_DERROTA							'f'
#define IR_MENU_MAESTRO_POKEMON					'g'
#define JUEGO_GANADO 							'h'
#define JUEGO_PERDIDO 							'i'

#define IGUALES         	 0
#define PRIMERO_MAYOR  	  	 1
#define PRIMERO_MENOR  		-1

#define CONTINUAR           'C'
#define DESDE_CERO          'R'
#define SI                  'S'
#define NO                  'N'

#define DERROTA 					ERROR

#define MAX_FUNCIONES_BATALLA   	5

#define PERSONAJE_GANO				GANO_PRIMERO

#define LETRA_SIGUIENTE_BATALLA		'N'

#define FUNCION_SUENA_CHETO		0
#define FUNCION_TRABALENGUAS	1
#define FUNCION_MOMENTO_LINEAL	2
#define FUNCION_EFICACIA_PELEA	3
#define FUNCION_TIPO_POKEMON	4


int (* const BATALLAS[MAX_FUNCIONES_BATALLA])(void*, void*) = {
	funcion_batalla_1, funcion_batalla_2, funcion_batalla_3,
	funcion_batalla_4, funcion_batalla_5
};


typedef int (*funcion_batalla)(void*, void*);

typedef struct juego{

	heap_t* heap;
	personaje_t* personaje;
	gimnasio_t* gimnasio_actual;
	char menu_actual;
} juego_t;


//
//___________________________________________________________________IMPRESIONES
//


/* 06 */
/*
	Pre-condiciones:
		"letra" debe ser LETRA_COMENZAR_PARTIDA o LETRA_SIMULAR_PARTIDA;
		"juego" debe tener alguno de sus campos nulos:
			"juego->heap" debe ser nulo o
			"juego->personaje" debe ser nulo.
	Post-condiciones:
		la función muestra un mensaje segun los parámetros recibidos.
 */
void mostrar_razon_accion_invalida_menu_inicio(char letra, juego_t* juego){

	if(!juego->heap)
		printf(ROJO_FUERTE "¡No cargaste los gimnasios todavía!\n" FIN);
	else
		printf(ROJO_FUERTE "¡No cargaste el personaje todavía!\n" FIN);
}


//
//______________________________________________________________________INGRESOS
//


/* 04 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función modica el valor de la posición recibida.
 */
void pedir_letra_menu_inicio(char *letra){

	printf(BLANCO "Letra: " FIN);
	scanf(" %c", letra);
}

/* 04 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función modica el valor de la posición recibida.
 */
void pedir_numero_pokemon_cambiar(int *numero_ingresado, size_t numero_de_pedido){

	printf(BLANCO "Ingreso %i, N° pokemon: " FIN, (int)numero_de_pedido);
	scanf("%i", numero_ingresado);
}

/* 04 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función modica el valor de la posición recibida.
 */
void pedir_numero_pokemon_agregar(int *numero_ingresado){

	printf(BLANCO "N° pokemon: " FIN);
	scanf("%i", numero_ingresado);
}

/* 12 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función modica el valor de la posición recibida por CONTINUAR
			o DESDE_CERO.
 */
void consultar_carga_gimnasios(char *respuesta){
	int cont = 0;
	
	do{

		if(cont > 0)
			mostrar_error_ingreso_letra(CONTINUAR, "continuar", DESDE_CERO, "reiniciar");
		printf(BLANCO"Ya tiene gimnasios cargados, tiene la posibilidad de continuar la carga o de reiniciarla. Escriba su deseo ('%c' para continuar, '%c' para reiniciar) \n" FIN, CONTINUAR, DESDE_CERO);
		scanf(" %c", respuesta);
		mayusculizar_letra(respuesta);
		cont++;
	} while(!ingreso_letra_es_correcto_2(*respuesta, CONTINUAR, DESDE_CERO));
}

/* 12 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función modica el valor de la posición recibida por SI o NO.
 */
void consultar_carga_personaje(char *respuesta){
	int cont = 0;
	
	do{

		if(cont > 0)
			mostrar_error_ingreso_letra(SI, "continuar", NO, "volver al menu");
		printf(BLANCO"Ya tiene un personaje cargado, desea continuar y borrar al personaje anterior? ('%c' para continuar, '%c' para volver al menu) \n" FIN, SI, NO);
		scanf(" %c", respuesta);
		mayusculizar_letra(respuesta);
		cont++;
	} while(!ingreso_letra_es_correcto_2(*respuesta, SI, NO));
}

/* 13 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función modica el valor de la posición recibida por SI o NO.
 */
void consultar_eleccion_comenzar_partida(char* respuesta){
	int cont = 0;
	
	mostrar_titulo_juego();
	do{

		if(cont > 0)
			mostrar_error_ingreso_letra(SI, "continuar", NO, "volver al menu");
		printf(BLANCO"Si continua, no podrá seguir cargando gimnasios ni modificar el personaje principal. Aún así, desea continuar? ('%c' para continuar, '%c' para volver al menu) \n" FIN, SI, NO);
		scanf(" %c", respuesta);
		mayusculizar_letra(respuesta);
		cont++;
	} while(!ingreso_letra_es_correcto_2(*respuesta, SI, NO));
}

/* 14 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función modica el valor de la posición recibida
			por LETRA_SIGUIENTE_BATALLA.
 */
void consultar_avance_batalla(){
	int cont = 0;
	char respuesta;
	
	do{

		if(cont > 0)
			printf(ROJO_FUERTE "Ingreso incorrecto, escriba '%c' para continuar.\n", LETRA_SIGUIENTE_BATALLA);
		printf(BLANCO"Escriba '%c' para continuar a la siguiente batalla \n" FIN, LETRA_SIGUIENTE_BATALLA);
		scanf(" %c", &respuesta);
		mayusculizar_letra(&respuesta);
		cont++;
	}
	while(!ingreso_letra_es_correcto_1(respuesta, LETRA_SIGUIENTE_BATALLA));
}


//
//__________________________________________________________________VALIDACIONES
//


/* 15 */
/*
	Pre-condiciones:
		"letra" debe ser LETRA_COMENZAR_PARTIDA, LETRA_SIMULAR_PARTIDA,
			LETRA_CARGAR_GIMNASIO o LETRA_CARGAR_PERSONAJE;
		"juego" debe estar inicializado correctamente.
	Post-condiciones:
		la función devolverá si se cumplen ciertos requisitos segun
			el valor de "letra".
 */
bool accion_valida_menu_inicio(char letra, juego_t* juego){
	bool valido = true;

	switch(letra){
		case LETRA_COMENZAR_PARTIDA:
			valido = (juego->heap && juego->personaje);
			break;
		case LETRA_SIMULAR_PARTIDA:
			valido = (juego->heap && juego->personaje);
			break;
		default:
			break;
	}

	return valido;
}


/* 13 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función devolverá si "numero_pokemon" se encuentra
			en "numeros_ingresados".
 */
bool numero_ya_ingresado(int numero_pokemon, size_t i,
	int numeros_ingresados[MAX_CANT_POKEMONES_COMBATE]){
	
	size_t contador = 0;
	bool encontrado = false;

	while((contador < i) && !encontrado){

		encontrado = (numero_pokemon == numeros_ingresados[contador]);
		contador++;
	}

	return encontrado;
}

/* 03 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función devolverá si la batalla finalizó.
 */
bool batalla_finalizada(bool personaje_vencido, bool finalizado){

	return (personaje_vencido || finalizado);
}

/* 06 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función devolverá si todavía ningun entrenador ganó.
 */
bool ningun_entrenador_gano(size_t cant_batallas_ganadas_personaje,
	size_t cant_pokemones_oponente, size_t cant_batallas_ganadas_oponente,
	size_t cant_pokemones_personaje){

	return ((cant_batallas_ganadas_personaje < cant_pokemones_oponente)
		&& (cant_batallas_ganadas_oponente < cant_pokemones_personaje));
}


//
//_________________________________________________________________DESTRUCCIONES
//


/* 09 */
/*
	Pre-condiciones:
		- 
	Post-condiciones:
		la función liberá al primer entrenador, de ser posible.
 */
void liberar_lider(gimnasio_t* gimnasio){
	entrenador_t* entrenador;

	if(!gimnasio || pila_vacia(gimnasio->pila_entrenadores))
		return;

	entrenador = (entrenador_t*)(pila_tope(gimnasio->pila_entrenadores));
	destruir_entrenador(entrenador);
	pila_desapilar(gimnasio->pila_entrenadores);
}

/* 07 */
/*
Pre-condiciones:
	"juego" debe estar inicializado y tener todos sus campos válidos.
Post-condiciones:
	la función libera toda la memoria reservada por los entrenadores en "juego->heap";
	la función libera "juego->personaje";
	la función libera "juego".
*/
void destruir_juego(juego_t* juego){

	if(juego->heap)
		heap_destruir(juego->heap);
	if(juego->personaje)
		destruir_personaje(juego->personaje);
	free(juego);
}


//
//_____________________________________________________________HERRAMIENTAS HEAP
//


/* 19 */
/*
	Pre-condiciones:
		- 
	Post-condiciones:
		la función retorna la relación entre los elementos, de ser posible.
 */
int comparador_gimnasios(void* elemento_1, void* elemento_2){
	int dificultad_gim_1, dificultad_gim_2, devolucion;
	char* nombre_gim_1, *nombre_gim_2;

	if(!elemento_1 || !elemento_2)
		return IGUALES;

	dificultad_gim_1 = (((gimnasio_t*)elemento_1)->dificultad);
	dificultad_gim_2 = (((gimnasio_t*)elemento_2)->dificultad);
	devolucion = dificultad_gim_1 - dificultad_gim_2;
	nombre_gim_1 = (((gimnasio_t*)elemento_1)->nombre);
	nombre_gim_2 = (((gimnasio_t*)elemento_2)->nombre);

	if((devolucion == 0) && (strcmp(nombre_gim_1, nombre_gim_2) > 0))
		devolucion = PRIMERO_MAYOR;
	else if(devolucion == 0)
		devolucion = PRIMERO_MENOR;

	return devolucion;
}

/* 07 */
/*
	Pre-condiciones:
		- 
	Post-condiciones:
		la función libera el gimnasio, de ser posible.
 */
void destructor_gimnasios(void* elemento){

	if(!elemento)
		return;

	gimnasio_t* puntero_gimnasio = (gimnasio_t*)elemento;
	liberar_gimnasio_entero(puntero_gimnasio);
}


//
//____________________________________________________________________CREACIONES
//


/* 05 */
/*
	Pre-condiciones:
		"juego" debe haber sido creado correctamente. 
	Post-condiciones:
		la función asigna valores iniciales a los campos de "juego".
 */
void inicializar_juego(juego_t* juego){

	juego->heap = NULL;
	juego->personaje = NULL;
	juego->gimnasio_actual = NULL;
}

/* 08 */
/*
	Pre-condiciones:
		- 
	Post-condiciones:
		la función devuelve una variable con sus campos inicializados
			correctamente, de ser posible.
 */
juego_t* nuevo_juego(){
	juego_t* juego;

	juego = malloc(sizeof(juego_t));
	if(juego)
		inicializar_juego(juego);

	return juego;
}

/* 09 */
/*
	Pre-condiciones:
		"carga" debe ser DESDE_CERO o CONTINUAR.
	Post-condiciones:
		la función devuelve una variable con sus campos inicializados
			correctamente según "carga".
 */
heap_t* crear_heap_actual(char carga, heap_t* heap_juego){
	heap_t* heap_actual = NULL;

	if(carga == DESDE_CERO)
		heap_actual = heap_crear(comparador_gimnasios, destructor_gimnasios);
	else
		heap_actual = heap_juego;

	return heap_actual;
}


//
//______________________________________________________________LECTURA ARCHIVOS
//


/* 24 */
/*
	Pre-condiciones:
		"fin" debe ser false.
	Post-condiciones:
		la función actualiza el valor de "ruta_archivo" con una ruta válida.
 */
void determinar_ruta_archivo_gimnasios(char ruta_archivo[MAX_RUTA], bool *fin, size_t *i){
	char ruta_leida[MAX_RUTA];
	size_t contador = 0;

	mostrar_titulo_juego();
	
	printf(BLANCO "Ingrese la ruta correspondiente al gimnasio que desea cargar. Si no desea cargar un gimnasio, escriba '%s'.\n" FIN, BASTA);
	do{

		if(contador > 0)
			mostrar_texto_error_archivo(ruta_leida);
		printf(BLANCO"Archivo %i: "FIN, (int)*i);
		scanf("%100s", ruta_leida);
		contador++;
	} while(!es_valor_fin(ruta_leida, BASTA)
		&& (ruta_muy_larga(ruta_leida) || !archivo_existe(ruta_leida)));

	if(es_valor_fin(ruta_leida, BASTA))
		*fin = true;
	else{
	
		strcpy(ruta_archivo, ruta_leida);
		(*i)++;
	}
}

/* 17 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función actualiza el valor de "ruta_archivo" con una ruta válida.
 */
void determinar_ruta_archivo_personaje(char ruta_archivo[MAX_RUTA]){
	char ruta_leida[MAX_RUTA];
	size_t contador = 0;

	mostrar_titulo_juego();

	printf(BLANCO"Ingrese la ruta correspondiente al personaje que desea cargar\n"FIN);
	do{

		if(contador > 0)
			mostrar_texto_error_archivo(ruta_leida);
		printf(BLANCO"Archivo: "FIN);
		scanf("%100s", ruta_leida);
		contador++;
	} while(ruta_muy_larga(ruta_leida) || !archivo_existe(ruta_leida));
	
	strcpy(ruta_archivo, ruta_leida);
}

/* 22 */
/*
	Pre-condiciones:
		"archivo_gimnasios" debe estar abierto.
	Post-condiciones:
		la funcion devuelve si pudo leer correctamente un gimnasio o no.
 */
int leer_archivo_gimnasio(FILE* archivo_gimnasios, heap_t* heap){
	int leidos, retorno = EXITO;
	char letra_leida = LETRA_DEFAULT;
	bool termine_lectura = false;
	gimnasio_t* gimnasio_leido;

	leidos = lectura_letra(archivo_gimnasios, &letra_leida);
	if(lee_bien_letra(leidos, letra_leida, GIMNASIO)){

		while(!termine_lectura && (retorno == EXITO)){

			gimnasio_leido = leer_gimnasio(archivo_gimnasios, &termine_lectura);
			if(gimnasio_leido)
				retorno = heap_insertar(heap, gimnasio_leido);
			else
				retorno = ERROR;
		}
	}
	else
		retorno = ERROR;

	return retorno;
}

/* 21 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la funcion devuelve si pudo leer correctamente los gimnasios o no;
		la funcion actualiza el valor de "leyo_algo" de ser posible.
 */
int leer_archivos_gimnasios(heap_t* heap, bool *leyo_algo){
	int retorno = EXITO;
	FILE* archivo_gimnasios;
	char ruta_actual[MAX_RUTA] = {CARACTER_VACIO};
	bool fin_ingresos = false;
	size_t i = 1;

	determinar_ruta_archivo_gimnasios(ruta_actual, &fin_ingresos, &i);
	while(!fin_ingresos && (retorno == EXITO)){
		
		archivo_gimnasios = fopen(ruta_actual, LEER);
		retorno = leer_archivo_gimnasio(archivo_gimnasios, heap);
		fclose(archivo_gimnasios);
		if(retorno == EXITO){
		
			*leyo_algo = true;
			determinar_ruta_archivo_gimnasios(ruta_actual, &fin_ingresos, &i);
		}
	}

	return retorno;
}

/* 35 */
/*
	Pre-condiciones:
		"juego" con sus campos válidos.
	Post-condiciones:
		la funcion devuelve si pudo cargar correctamente los gimnasios o no;
		la función muestra si surgió algun incoveniente durante el proceso.
 */
int cargar_gimnasios(juego_t* juego){
	int retorno = EXITO;
	heap_t* heap_actual = NULL;
	char carga = DESDE_CERO;
	bool leyo_algo = false;

	mostrar_titulo_juego();

	if(juego->heap){

		consultar_carga_gimnasios(&carga);
		if(carga == DESDE_CERO)
			heap_destruir(juego->heap);
	}

	heap_actual = crear_heap_actual(carga, juego->heap);
	if(!heap_actual)
		return ERROR;

	retorno = leer_archivos_gimnasios(heap_actual, &leyo_algo);
	if(!leyo_algo && ((retorno == ERROR) || (heap_actual->cant_elementos == 0))){

		heap_destruir(heap_actual);
		retorno = ERROR;
	}
	else
		juego->heap = heap_actual;

	if(leyo_algo && (retorno == ERROR)){

		retorno = EXITO;
		printf(ROJO_FUERTE "Error leyendo último archivo.\n"FIN);
	}

	return retorno;
}

/* 25 */
/*
	Pre-condiciones:
		"archivo" debe estar abierto.
	Post-condiciones:
		la funcion devuelve si pudo leer correctamente un personaje o no.
 */
int leer_personaje(FILE* archivo, juego_t *juego){
	int retorno = EXITO, leidos;
	personaje_t personaje_leido, *puntero_personaje = NULL;
	char letra_leida = LETRA_DEFAULT;

	personaje_leido.cant_insignias = 0;

	leidos = lectura_letra(archivo, &letra_leida);
	if(!lee_bien_letra(leidos, letra_leida, ENTRENADOR))
		return ERROR;

	leidos = lectura_personaje(archivo, &personaje_leido);
	if(!lee_bien_entrenador(leidos))
		return ERROR;

	puntero_personaje = crear_personaje(personaje_leido);
	if(!puntero_personaje)
		return ERROR;

	retorno = leer_pokemones(archivo, puntero_personaje, &letra_leida,
		&leidos, insertar_en_lista_personaje, NULL);
	if(retorno == EXITO)
		juego->personaje = puntero_personaje;
	
	return retorno;
}

/* 29 */
/*
	Pre-condiciones:
		"juego" con sus campos válidos.
	Post-condiciones:
		la funcion devuelve si pudo cargar correctamente al personaje o no;
		la función muestra si surgió algun incoveniente durante el proceso.
 */
int cargar_personaje(juego_t* juego){
	int retorno = EXITO;
	FILE* archivo;
	char ruta_actual[MAX_RUTA] = {CARACTER_VACIO}, carga = SI;

	mostrar_titulo_juego();

	if(juego->personaje){

		consultar_carga_personaje(&carga);
		if(carga == SI)
			destruir_personaje(juego->personaje);
	}

	if(carga == NO)
		return ERROR;
	
	determinar_ruta_archivo_personaje(ruta_actual);
	archivo = fopen(ruta_actual, LEER);
	retorno = leer_personaje(archivo, juego);
	fclose(archivo);

	if(retorno == ERROR || !juego->personaje || lista_vacia(juego->personaje->caja)){

		destruir_personaje(juego->personaje);
		retorno = ERROR;
	}

	return retorno;
}

//
//_________________________________________________________________CAMBIAR PARTY
//


/* 15 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la funcion actualiza "numero_pokemon" por un valor válido.
 */
void determinar_pokemon_a_cambiar(int *numero_pokemon, lista_t* caja,
	size_t numero_de_pedido, int numeros_ingresados[MAX_CANT_POKEMONES_COMBATE]){
	
	size_t cont = 0;
	
	do{

		if((cont > 0) && numero_ya_ingresado(*numero_pokemon, numero_de_pedido, numeros_ingresados))
			printf(ROJO_FUERTE "¡Numero repetido!\n" FIN);
		if(cont > 0)
			printf(ROJO_FUERTE "Ingreso incorrecto, ingrese un valor válido (entre '0' y '%i')\n" FIN, lista_elementos(caja) - 1);
		pedir_numero_pokemon_cambiar(numero_pokemon, numero_de_pedido+1);
		(cont)++;
	} while(!numero_valido(*numero_pokemon, 0, (int)lista_elementos(caja) - 1)
		|| numero_ya_ingresado(*numero_pokemon, numero_de_pedido, numeros_ingresados));
}

/* 13 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la funcion actualiza "party".
 */
void determinar_pokemones_a_cambiar(pokemon_t** party,
	lista_t* caja){
	
	int numero_pokemon;
	int numeros_ingresados[MAX_CANT_POKEMONES_COMBATE] = {0};

	printf(BLANCO"Ingrese el número de los %i pokemones que quiere guardar en su party\n"FIN, MAX_CANT_POKEMONES_COMBATE);
	for(size_t i = 0; i < MAX_CANT_POKEMONES_COMBATE; i++){
		
		determinar_pokemon_a_cambiar(&numero_pokemon, caja, i, numeros_ingresados);
		party[i] = lista_elemento_en_posicion(caja, (size_t)numero_pokemon);
		numeros_ingresados[i] = numero_pokemon;
	}
}

/* 18 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la funcion actualiza "juego->personaje->party" con
			MAX_CANT_POKEMONES_COMBATE nuevos valores,
		sino, la función muestra un mensaje.
 */
int cambiar_party(juego_t* juego){
	int retorno = EXITO;
	
	if(lista_elementos(juego->personaje->caja) <= MAX_CANT_POKEMONES_COMBATE){
		
		mostrar_titulo_juego();
		printf(ROJO_FUERTE "No tiene suficientes pokemones para modificar sus pokemones de combate\n" FIN);
		retorno = ERROR;
	}
	else{

		mostrar_titulo_juego();
		mostrar_pokemones_personaje(juego->personaje->caja, juego->personaje->party);
		determinar_pokemones_a_cambiar(juego->personaje->party, juego->personaje->caja);
		system("clear");
	}

	return retorno;
}


//
//______________________________________________________________________BATALLAR
//


/* 10 */
/*
	Pre-condiciones:
		"party" debe ser una variable válida, con todos su campos válidos;
		"caja" debe ser una variable'válida, con todos sus campos válidos.
	Post-condiciones:
		la funcion retorna la cantidad de pokemones en "party".
 */
size_t cantidad_pokemones_party(pokemon_t** party,
	lista_t* caja){
	
	size_t cantidad;
	if(lista_elementos(caja) <= MAX_CANT_POKEMONES_COMBATE)
		cantidad = lista_elementos(caja);
	else
		cantidad = MAX_CANT_POKEMONES_COMBATE;

	return cantidad;
}

/* 05 */
/*
	Pre-condiciones:
		"party" debe ser una variable válida, con todos su campos válidos;
		"posicion" debe ser menor a MAX_CANT_POKEMONES_COMBATE.
	Post-condiciones:
		la funcion actualiza los campos de "party" segun posicion.
 */
void actualizar_valores(pokemon_t** party, size_t posicion){

	(party[posicion]->velocidad)++;
	(party[posicion]->defensa)++;
	(party[posicion]->ataque)++;
}

/* 26 */
/*
	Pre-condiciones:
		"personaje" debe ser una variable válida, con sus campos válidos.
	Post-condiciones:
		la función muestra un mensaje segun "resultado_batalla";
		la función actualiza los parámetros recibidos según "resultado_batala".
 */
void interpretar_resultado_batalla_pokemon(int resultado_batalla,
	size_t *cant_batallas_ganadas_personaje, size_t* cant_batallas_ganadas_oponente,
	personaje_t* personaje, bool esta_simulando){

	printf(BLANCO"RESULTADO BATALLA: "FIN);
	fflush(stdout);
	detener_el_tiempo(TIEMPO_NORMAL);	
	if(resultado_batalla == PERSONAJE_GANO){

		printf(VERDE_FUERTE"GANADA.\n"FIN);
		(*cant_batallas_ganadas_personaje)++;
		if(personaje->cant_insignias <= MAX_INSIGNIAS)
			actualizar_valores(personaje->party, *cant_batallas_ganadas_oponente);
		(personaje->cant_insignias)++;
	}
	else{

		printf(ROJO_FUERTE"PERDIDA.\n"FIN);
		(*cant_batallas_ganadas_oponente)++;
	}
	printf(BLANCO"CONTADOR: %i - %i\n", (int)*cant_batallas_ganadas_personaje, (int)*cant_batallas_ganadas_oponente);

	if(!esta_simulando)
		consultar_avance_batalla();
	else
		detener_el_tiempo(TIEMPO_NORMAL);
}

/* 27 */
/*
	Pre-condiciones:
		"gimnasio_actual" debe ser una variable válida, con sus campos válidos;
		"entrenador_actual" debe ser una variable válida, con sus campos válidos;
		"funcion_batalla" debe ser alguna función de BATALLAS.
	Post-condiciones:
		la función devuelve un valor representando quién ganó la batalla.
 */
int batallar_contra_entrenador(gimnasio_t* gimnasio_actual, entrenador_t* entrenador_actual,
	size_t cant_pokemones_personaje, personaje_t* personaje,
	int (*funcion_batalla)(void*, void*), bool esta_simulando){
	
	size_t cant_batallas_ganadas_oponente = 0, cant_batallas_ganadas_personaje = 0;
	size_t cant_pokemones_oponente;
	pokemon_t *pokemon_actual_gimnasio = NULL, *pokemon_actual_personaje = NULL;
	int resultado_batalla;

	mostrar_titulo_juego();
	printf(AZUL"\nENTRENADOR A DERROTAR: \n"FIN);
	mostrar_informacion_entrenador(entrenador_actual);
	if(!esta_simulando)
		esperar_al_usuario();
	else
		detener_el_tiempo(TIEMPO_NORMAL);
	cant_pokemones_oponente = lista_elementos(entrenador_actual->lista_pokemones);
	while(ningun_entrenador_gano(cant_batallas_ganadas_personaje, cant_pokemones_oponente, cant_batallas_ganadas_oponente, cant_pokemones_personaje)){

		pokemon_actual_gimnasio = lista_elemento_en_posicion(entrenador_actual->lista_pokemones, cant_batallas_ganadas_personaje);
		pokemon_actual_personaje = personaje->party[cant_batallas_ganadas_oponente];
		mostrar_datos_batalla(gimnasio_actual->nombre, entrenador_actual->nombre, entrenador_actual->es_lider, personaje->nombre, pokemon_actual_personaje, pokemon_actual_gimnasio);
		resultado_batalla = funcion_batalla(pokemon_actual_personaje, pokemon_actual_gimnasio);
		interpretar_resultado_batalla_pokemon(resultado_batalla, &cant_batallas_ganadas_personaje, &cant_batallas_ganadas_oponente, personaje, esta_simulando);
	}

	return (int)(cant_batallas_ganadas_personaje - cant_pokemones_oponente);
}

/* 11 */
/*
	Pre-condiciones:
		"gimnasio" debe ser una variable válida, con sus campos válidos;
		"entrenador_actual" debe ser una variable válida, con sus campos válidos;
	Post-condiciones:
		la función determina cual fue el resultado de la batalla contra el entrenador,
			actualizando los parámetros como corresponda.
 */
void interpretar_resultado_batalla_entrenador(int resultado_batalla, gimnasio_t* gimnasio, entrenador_t* entrenador_actual, bool *personaje_vencido, bool *finalizado){

	if(resultado_batalla < 0) //si perdió contra el entrenador
		*personaje_vencido = true;
	else if(pila_elementos(gimnasio->pila_entrenadores) != 1){//gano contra uno que no es el lider

		pila_desapilar(gimnasio->pila_entrenadores);
		destruir_entrenador(entrenador_actual);
	}
	else
		*finalizado = true;
}

/* 23 */
/*
	Pre-condiciones:
		"personaje" debe ser una variable válida, con sus campos válidos;
		"gimnasio" debe ser una variable válida, con sus campos válidos;
	Post-condiciones:
		la función determina quién fue el ganador de la batalla.
 */
int batallar(personaje_t* personaje, gimnasio_t* gimnasio, bool esta_simulando){
	int (*funcion_batalla)(void*, void*) = BATALLAS[gimnasio->id_funcion];
	int retorno, resultado_batalla;
	bool personaje_vencido = false, finalizado = false;
	size_t cant_pokemones_personaje;
	entrenador_t* entrenador_actual = NULL;

	cant_pokemones_personaje = cantidad_pokemones_party(personaje->party, personaje->caja);
	while(!batalla_finalizada(personaje_vencido, finalizado)){

		entrenador_actual = pila_tope(gimnasio->pila_entrenadores);
		resultado_batalla = batallar_contra_entrenador(gimnasio, entrenador_actual,
			cant_pokemones_personaje, personaje, funcion_batalla, esta_simulando);
		interpretar_resultado_batalla_entrenador(resultado_batalla, gimnasio,
			entrenador_actual, &personaje_vencido, &finalizado);
	}

	if(personaje_vencido)
		retorno = DERROTA;
	else
		retorno = EXITO;

	return retorno;
}


//
//________________________________________________________TOMAR PRESTADO POKEMON
//


/* 10 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la funcion actualiza "numero_pokemon" por un valor válido.
 */
void determinar_pokemon_a_agregar(int *numero_pokemon, lista_t* lista){
	size_t cont = 0;
	
	do{

		if(cont > 0)
			printf(ROJO_FUERTE "Ingreso incorrecto, ingrese un valor válido (entre '0' y '%i').\n" FIN, lista_elementos(lista)-1);
		pedir_numero_pokemon_agregar(numero_pokemon);
		(cont)++;
	} while(!numero_valido(*numero_pokemon, 0, (int)lista_elementos(lista) - 1));
}

/* 17 */
/*
	Pre-condiciones:
		"juego" es una variable válida con todos sus campos válidos:
			"juego->heap" debe ser diferente de NULL;
			"juego->gimnasio_actual" debe ser diferente de NULL;
			"juego->personaje" debe ser diferente de NULL.
	Post-condiciones:
		la funcion actualiza "juego->personaje->caja";
		la función toma prestado, NO ROBADO, un pokemon del primer_entrenador de
			"juego->gimnasio_actual->pila_entrenadores".
 */
int tomar_prestado_pokemon_del_lider(juego_t* juego){
	int numero_pokemon;
	entrenador_t* entrenador = ((entrenador_t*)(pila_tope(juego->gimnasio_actual->pila_entrenadores)));
	
	mostrar_titulo_juego();
	mostrar_informacion_entrenador(entrenador);
	printf(BLANCO"Ingrese el número del pokemon que quiere guardar en su caja.\n"FIN);
	determinar_pokemon_a_agregar(&numero_pokemon, entrenador->lista_pokemones);
	
	entrenador = (entrenador_t*)(pila_tope(juego->gimnasio_actual->pila_entrenadores));

	insertar_en_lista_personaje(juego->personaje, lista_elemento_en_posicion(entrenador->lista_pokemones, (size_t)numero_pokemon));
	lista_borrar_de_posicion(entrenador->lista_pokemones, (size_t)numero_pokemon);
	
	liberar_lider(juego->gimnasio_actual);

	return EXITO;
}


//
//_______________________________________________________________SIMULAR PARTIDA
//

/* 09 */
/*
	Pre-condiciones:
		"juego" es una variable válida con todos sus campos válidos.
	Post-condiciones:
		la funcion actualiza "juego->gimnasio_actual";
		la función actualiza "juego->heap".
 */
void actualizar_juego(juego_t* juego){

	if(juego->gimnasio_actual)
		heap_eliminar_raiz(juego->heap);

	if(heap_elemento_raiz(juego->heap))
		juego->gimnasio_actual = (gimnasio_t*)heap_elemento_raiz(juego->heap);
	else
		juego->gimnasio_actual = NULL;
}

/* 17 */
/*
	Pre-condiciones:
		"juego" es una variable válida con todos sus campos válidos:
			"juego->heap" debe ser diferente de NULL;
			"juego->gimnasio_actual" debe ser diferente de NULL;
			"juego->personaje" debe ser diferente de NULL.
		"personaje_vencido" debe ser false.
	Post-condiciones:
		la función determina quién fue el ganador de la batalla.
 */
void batallar_con_simulacion(juego_t* juego, bool *personaje_vencido){
	int retorno;

	mostrar_gimnasio(juego->gimnasio_actual);
	detener_el_tiempo(TIEMPO_NORMAL);
	retorno = batallar(juego->personaje, juego->gimnasio_actual, true);
	liberar_lider(juego->gimnasio_actual);
	if(retorno == EXITO){
	
		mostrar_titulo_juego();
		printf(VERDE_FUERTE"\nGimnasio ganado, yendo al siguiente gimnasio...\n"FIN);
		detener_el_tiempo(TIEMPO_NORMAL);
		fflush(stdout);
	}
	else
		*personaje_vencido = true;
	actualizar_juego(juego);
}

/* 15 */
/*
	Pre-condiciones:
		"juego" es una variable válida con todos sus campos válidos:
			"juego->heap" debe ser diferente de NULL;
			"juego->gimnasio_actual" debe ser diferente de NULL;
			"juego->personaje" debe ser diferente de NULL.
	Post-condiciones:
		la función simula una partida sin necesidad de ingresos del usuario;
		la función devuelve si se ganó o no la partida.
 */
int simular_partida(juego_t* juego){
	int retorno;
	bool personaje_vencido = false;

	mostrar_titulo_juego();

	printf(VERDE_FUERTE "Simulando partida...\n" FIN);
	detener_el_tiempo(TIEMPO_NORMAL);
	actualizar_juego(juego);
	while(!personaje_vencido && juego->gimnasio_actual)
		batallar_con_simulacion(juego, &personaje_vencido);

	if(personaje_vencido)
		retorno = DERROTA;
	else
		retorno = EXITO;

	return retorno;
}



//
//_________________________________________________________________________MENUS
//


void ir_menu_inicio(juego_t*);
void ir_menu_gimnasio(juego_t*);
void ir_menu_victoria_con_tomar_prestado(juego_t*);
void ir_menu_victoria_sin_tomar_prestado(juego_t*);
void ir_menu_derrota(juego_t*);

/* 28 */
/*
	Pre-condiciones:
		"juego" es una variable válida con todos sus campos válidos.
		"resultado" debe ser IR_MENU_INICIO, IR_MENU_GIMNASIO, IR_MENU_GIMNASIO_NUEVO,
			IR_MENU_VICTORIA_CON_TOMAR_PRESTADO, IR_MENU_VICTORIA_SIN_TOMAR_PRESTADO, 
			IR_MENU_DERROTA, JUEGO_GANADO, JUEGO_PERDIDO.
	Post-condiciones:
		la función invoca a otra función según "resultado".
 */
void siguiente_pantalla_segun_resultado(juego_t* juego, int resultado){

	switch(resultado){
		case IR_MENU_INICIO:
			ir_menu_inicio(juego);
			break;
		case IR_MENU_GIMNASIO:
			ir_menu_gimnasio(juego);
			break;
		case IR_MENU_GIMNASIO_NUEVO:
			ir_menu_gimnasio(juego);
			break;
		case IR_MENU_VICTORIA_CON_TOMAR_PRESTADO:
			ir_menu_victoria_con_tomar_prestado(juego);
			break;
		case IR_MENU_VICTORIA_SIN_TOMAR_PRESTADO:
			ir_menu_victoria_sin_tomar_prestado(juego);
			break;
		case IR_MENU_DERROTA:
			ir_menu_derrota(juego);
			break;
		case JUEGO_GANADO:
			mostrar_mensaje_juego_ganado();
			break;
		case JUEGO_PERDIDO:
			mostrar_mensaje_juego_perdido();
			break;
	}
}

/* 06 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función actualiza el valor de "retorno" segun "gimnasio".
 */
void determinar_retorno(gimnasio_t* gimnasio, int *retorno){

	if(gimnasio)
		*retorno = IR_MENU_GIMNASIO_NUEVO;
	else
		*retorno = JUEGO_GANADO;	
}


//
//__________________________________________________________________MENU DERROTA
//

/* 06 */
/*
	Pre-condiciones:
		"retorno" debe ser EXITO o DERROTA.
	Post-condiciones:
		la función actualiza el valor de "retorno".
 */
void determinar_sig_pantalla_segun_segunda_batalla(int *retorno){

	if(*retorno == EXITO)
		*retorno = IR_MENU_VICTORIA_CON_TOMAR_PRESTADO;
	else
		*retorno = JUEGO_PERDIDO;      
}

/* 14 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retorna LETRA_CAMBIAR_PARTY, LETRA_REINTENTAR o LETRA_FINALIZAR.
 */
char accion_seleccionada_segun_menu_derrota(){
	char letra = LETRA_DEFAULT;
	int cont = 0;

	do{

		if(cont > 0)
			mostrar_texto_error_menu_3(letra, LETRA_CAMBIAR_PARTY, LETRA_REINTENTAR, LETRA_FINALIZAR);
		pedir_letra_menu_inicio(&letra);
		mayusculizar_letra(&letra);
		(cont)++;
	} while(!ingreso_letra_es_correcto_3(letra, LETRA_CAMBIAR_PARTY, LETRA_REINTENTAR, LETRA_FINALIZAR));

	return letra;
}

/* 20 */
/*
	Pre-condiciones:
		"accion" debe ser LETRA_CAMBIAR_PARTY, LETRA_REINTENTAR o LETRA_FINALIZAR.
	Post-condiciones:
		la función ejecuta la acción correspondiente;
		la función muestra un mensaje si es posible;
		la función devuelve "retorno".
 */
int realizar_accion_menu_derrota(juego_t* juego, char accion){
	int retorno = EXITO;

	system("clear");
	switch(accion){
		case LETRA_CAMBIAR_PARTY:
			retorno = cambiar_party(juego);
			mensaje_segun_retorno(retorno, mostrar_cambios_personaje, juego->personaje);
			retorno = IR_MENU_DERROTA;
			break;
		case LETRA_REINTENTAR:
			retorno = batallar(juego->personaje, juego->gimnasio_actual, false);
			determinar_sig_pantalla_segun_segunda_batalla(&retorno);
			break;
		case LETRA_FINALIZAR:
			retorno = JUEGO_PERDIDO;
			break;
	}

	return retorno;
}

/*
	Pre-condiciones: 
		"id_funcion" es un valor entre MIN_ID_FUNC_GIMNASIO y MAX_ID_FUNC_GIMNASIO.
	Post-condiciones: 
   		la función muestra un mensaje, el cual depende del parametro recibido.
 */
void mostrar_descripcion_combate(int id_funcion){

	printf(BLANCO"INFORMACIÓN DEL COMBATE:\n"FIN);
	switch(id_funcion){
		case FUNCION_SUENA_CHETO:
			printf(AMARILLO"+-+-+-+-+-+ +-+-+-+-+-+\n");
			printf("|$|U|E|N|A| |C|H|E|T|O|\n");
 			printf("+-+-+-+-+-+ +-+-+-+-+-+\n");
			printf("CRITERIOS A EVALUAR: \n\t■ Cantidad letras del nombre. \n\t■ Colores, siendo los mejores los de POKEMON.\n");
			break;
		case FUNCION_TRABALENGUAS:
			printf(VERDE_SUAVE"+-+-+-+-+-+-+-+-+-+-+-+-+ \n");
 		    printf("|T|R|A|B|A|L|E|N|G|U|A|S| \n");
			printf("+-+-+-+-+-+-+-+-+-+-+-+-+ \n");
			printf("CRITERIOS A EVALUAR: \n\t■ Cantidad de consonantes del nombre. \n\t■ Cantidad de consonantes del tipo de pokemon.\n");
			break;
		case FUNCION_MOMENTO_LINEAL:
 			printf(AZUL"+-+-+-+-+ +-+-+-+-+-+-+-+ +-+-+-+-+-+-+\n");
 			printf("|A|L|T|O| |M|O|M|E|N|T|O| |L|I|N|E|A|L|\n");
 			printf("+-+-+-+-+ +-+-+-+-+-+-+-+ +-+-+-+-+-+-+\n");
			printf("CRITERIO A EVALUAR: \n\t■ Momento Lineal.\n");
			break;
		case FUNCION_EFICACIA_PELEA:
			printf(CELESTE" +-+-+-+-+-+-+-+-+ +-+-+-+-+ \n");
			printf(" |B|O|X|E|A|D|O|R| |N|A|T|O| \n");
 			printf(" +-+-+-+-+-+-+-+-+ +-+-+-+-+	 \n");
			printf("CRITERIOS A EVALUAR: \n\t■ Defensa. \n\t■ Ataque.\n");
			break;
		case FUNCION_TIPO_POKEMON:
			printf(MAGENTA" +-+-+-+-+ +-+-+-+-+-+-+-+\n");
 			printf(" |T|I|P|O| |P|O|K|E|M|O|N|\n");
 			printf(" +-+-+-+-+ +-+-+-+-+-+-+-+	\n");
			printf(" CRITERIO A EVALUAR: \n\t■ Tipo de pokemon y eficacia frente a otro tipo de pokemon.\n");
			break;
	}
	printf("\n");
}

/* 15 */
/*
	Pre-condiciones:
		"juego" debe ser válido y tener todos sus campos válidos.
	Post-condiciones:
		la función muestra un menu de derrota, y permite ejecutar una acción a
			partir de las opciones.
 */
void ir_menu_derrota(juego_t* juego){
	char accion;
	int resultado;
	char nombre[MAX_NOMBRE_GIMNASIO];

	strcpy(nombre, juego->gimnasio_actual->nombre);
	mayusculizar_string(nombre);
	system("clear");
	mostrar_parte_visual_menu("DERROTA EN", nombre, mostrar_lineas_opciones_menu_derrota);
	mostrar_descripcion_combate(juego->gimnasio_actual->id_funcion);
	accion = accion_seleccionada_segun_menu_derrota();
	resultado = realizar_accion_menu_derrota(juego, accion);
	if((resultado != IR_MENU_DERROTA) && (resultado != JUEGO_PERDIDO) && (resultado != JUEGO_GANADO))
		mostrar_carga_nuevo_menu();
	siguiente_pantalla_segun_resultado(juego, resultado);
}


//
//______________________________________________MENU VICTORIA SIN TOMAR PRESTADO
//


/* 14 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retorna LETRA_CAMBIAR_PARTY o LETRA_SIGUIENTE_GIMNASIO.
 */
char accion_seleccionada_segun_menu_victoria_sin_tomar_prestado(){
	char letra = LETRA_DEFAULT;
	int cont = 0;

	do{

		if(cont > 0)
			mostrar_texto_error_menu_2(letra, LETRA_CAMBIAR_PARTY, LETRA_SIGUIENTE_GIMNASIO);
		pedir_letra_menu_inicio(&letra);
		mayusculizar_letra(&letra);
		(cont)++;
	} while(!ingreso_letra_es_correcto_2(letra, LETRA_CAMBIAR_PARTY, LETRA_SIGUIENTE_GIMNASIO));

	return letra;
}

/* 17 */
/*
	Pre-condiciones:
		"accion" debe ser LETRA_CAMBIAR_PARTY o LETRA_SIGUIENTE_GIMNASIO.
	Post-condiciones:
		la función ejecuta la acción correspondiente;
		la función muestra un mensaje si es posible;
		la función devuelve "retorno".
 */
int realizar_accion_menu_victoria_sin_tomar_prestado(juego_t* juego, char accion){
	int retorno = EXITO;

	system("clear");
	switch(accion){
		case LETRA_CAMBIAR_PARTY:
			retorno = cambiar_party(juego);
			mensaje_segun_retorno(retorno, mostrar_cambios_personaje, juego->personaje);
			retorno = IR_MENU_VICTORIA_SIN_TOMAR_PRESTADO;
			break;
		case LETRA_SIGUIENTE_GIMNASIO:
			actualizar_juego(juego);
			determinar_retorno(juego->gimnasio_actual, &retorno);
			break;
	}

	return retorno;
}

/* 11 */
/*
	Pre-condiciones:
		"juego" debe ser válido y tener todos sus campos válidos.
	Post-condiciones:
		la función muestra un menu de victoria, y permite ejecutar una acción a
			partir de las opciones.
 */
void ir_menu_victoria_sin_tomar_prestado(juego_t* juego){
	char accion;
	int resultado;

	system("clear");
	mostrar_parte_visual_menu("VICTORIA", NULL, mostrar_lineas_opciones_menu_victoria_sin_tomar_prestado);
	accion = accion_seleccionada_segun_menu_victoria_sin_tomar_prestado();
	resultado = realizar_accion_menu_victoria_sin_tomar_prestado(juego, accion);
	if((resultado != IR_MENU_VICTORIA_SIN_TOMAR_PRESTADO) && (resultado != JUEGO_GANADO))
		mostrar_carga_nuevo_menu();
	siguiente_pantalla_segun_resultado(juego, resultado);
}


//
//______________________________________________MENU VICTORIA CON TOMAR PRESTADO
//


/* 14 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retorna LETRA_TOMAR_PRESTADO, LETRA_CAMBIAR_PARTY o LETRA_SIGUIENTE_GIMNASIO.
 */
char accion_seleccionada_segun_menu_victoria_con_tomar_prestado(){
	char letra = LETRA_DEFAULT;
	int cont = 0;

	do{

		if(cont > 0)
			mostrar_texto_error_menu_3(letra, LETRA_TOMAR_PRESTADO, LETRA_CAMBIAR_PARTY, LETRA_SIGUIENTE_GIMNASIO);
		pedir_letra_menu_inicio(&letra);
		mayusculizar_letra(&letra);
		(cont)++;
	} while(!ingreso_letra_es_correcto_3(letra, LETRA_TOMAR_PRESTADO, LETRA_CAMBIAR_PARTY, LETRA_SIGUIENTE_GIMNASIO));

	return letra;
}

/* 23 */
/*
	Pre-condiciones:
		"accion" debe ser LETRA_TOMAR_PRESTADO, LETRA_CAMBIAR_PARTY o LETRA_SIGUIENTE_GIMNASIO.
	Post-condiciones:
		la función ejecuta la acción correspondiente;
		la función muestra un mensaje si es posible;
		la función devuelve "retorno".
 */
int realizar_accion_menu_victoria_con_tomar_prestado(juego_t* juego, char accion){
	int retorno = EXITO;

	system("clear");
	switch(accion){
		case LETRA_TOMAR_PRESTADO:
			tomar_prestado_pokemon_del_lider(juego);
			mensaje_segun_retorno(EXITO, mostrar_cambios_personaje, juego->personaje);
			retorno = IR_MENU_VICTORIA_SIN_TOMAR_PRESTADO;
			break;
		case LETRA_CAMBIAR_PARTY:
			retorno = cambiar_party(juego);
			mensaje_segun_retorno(retorno, mostrar_cambios_personaje, juego->personaje);
			retorno = IR_MENU_VICTORIA_CON_TOMAR_PRESTADO;
			break;
		case LETRA_SIGUIENTE_GIMNASIO:
			liberar_lider(juego->gimnasio_actual);
			actualizar_juego(juego);
			determinar_retorno(juego->gimnasio_actual, &retorno);
			break;
	}

	return retorno;
}

/* 14 */
/*
	Pre-condiciones:
		"juego" debe ser válido y tener todos sus campos válidos.
	Post-condiciones:
		la función muestra un menu de victoria, y permite ejecutar una acción a
			partir de las opciones.
 */
void ir_menu_victoria_con_tomar_prestado(juego_t* juego){
	char accion;
	int resultado;
	char nombre[MAX_NOMBRE_GIMNASIO];

	strcpy(nombre, juego->gimnasio_actual->nombre);
	mayusculizar_string(nombre);
	system("clear");
	mostrar_parte_visual_menu("VICTORIA EN", nombre, mostrar_lineas_opciones_menu_victoria_con_tomar_prestado);
	accion = accion_seleccionada_segun_menu_victoria_con_tomar_prestado();
	resultado = realizar_accion_menu_victoria_con_tomar_prestado(juego, accion);
	if((resultado != IR_MENU_VICTORIA_CON_TOMAR_PRESTADO) && (resultado != JUEGO_GANADO))
		mostrar_carga_nuevo_menu();
	siguiente_pantalla_segun_resultado(juego, resultado);
}


//
//_________________________________________________________________MENU GIMNASIO
//


/* 13 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retorna LETRA_MOSTRAR_PERSONAJE, LETRA_MOSTRAR_GIMNASIOS, LETRA_CAMBIAR_PARTY o LETRA_COMENZAR_BATALLA.
 */
char accion_seleccionada_segun_menu_gimnasio(){
	char letra = LETRA_DEFAULT;
	int cont = 0;

	do{
		if(cont > 0)
			mostrar_texto_error_menu_4(letra, LETRA_MOSTRAR_PERSONAJE, LETRA_MOSTRAR_GIMNASIOS, LETRA_CAMBIAR_PARTY, LETRA_COMENZAR_BATALLA);
		pedir_letra_menu_inicio(&letra);
		mayusculizar_letra(&letra);
		(cont)++;
	} while(!ingreso_letra_es_correcto_4(letra, LETRA_MOSTRAR_PERSONAJE, LETRA_MOSTRAR_GIMNASIOS, LETRA_CAMBIAR_PARTY, LETRA_COMENZAR_BATALLA));

	return letra;
}

/* 06 */
/*
	Pre-condiciones:
		"retorno" debe ser EXITO o DERROTA.
	Post-condiciones:
		la función actualiza el valor de "retorno".
 */
void determinar_sig_pantalla_segun_batalla(int *retorno){

	if(*retorno == EXITO)
		*retorno = IR_MENU_VICTORIA_CON_TOMAR_PRESTADO;
	else
		*retorno = IR_MENU_DERROTA;      
}

/* 26 */
/*
	Pre-condiciones:
		"accion" debe ser LETRA_MOSTRAR_PERSONAJE, LETRA_MOSTRAR_GIMNASIOS, LETRA_CAMBIAR_PARTY o LETRA_COMENZAR_BATALLA.
	Post-condiciones:
		la función ejecuta la acción correspondiente;
		la función muestra un mensaje si es posible;
		la función devuelve "retorno".
 */
int realizar_accion_menu_gimnasio(juego_t* juego, char accion){
	int retorno = EXITO;

	system("clear");
	switch(accion){
		case LETRA_MOSTRAR_PERSONAJE:
			mostrar_informacion_personaje(juego->personaje);
			retorno = IR_MENU_GIMNASIO;
			break;
		case LETRA_MOSTRAR_GIMNASIOS:
			mostrar_gimnasio(juego->gimnasio_actual);
			esperar_al_usuario();
			retorno = IR_MENU_GIMNASIO;
			break;
		case LETRA_CAMBIAR_PARTY:
			retorno = cambiar_party(juego);
			mensaje_segun_retorno(retorno, mostrar_cambios_personaje, juego->personaje);
			retorno = IR_MENU_GIMNASIO;
			break;
		default:
			retorno = batallar(juego->personaje, juego->gimnasio_actual, false);
			determinar_sig_pantalla_segun_batalla(&retorno);
			break;
	}

	return retorno;
}

/* 11 */
/*
	Pre-condiciones:
		"juego" debe ser válido y tener todos sus campos válidos.
	Post-condiciones:
		la función muestra un menu de gimnasio, y permite ejecutar una acción a
			partir de las opciones.
 */
void ir_menu_gimnasio(juego_t* juego){
	char accion;
	int resultado;
	char nombre[MAX_NOMBRE_GIMNASIO];

	strcpy(nombre, juego->gimnasio_actual->nombre);
	mayusculizar_string(nombre);

	system("clear");
	mostrar_parte_visual_menu("GIMNASIO", nombre, mostrar_lineas_opciones_menu_gimnasio);
	accion = accion_seleccionada_segun_menu_gimnasio();
	resultado = realizar_accion_menu_gimnasio(juego, accion);
	if(resultado != IR_MENU_GIMNASIO)
		mostrar_carga_nuevo_menu();
	siguiente_pantalla_segun_resultado(juego, resultado);
}

//
//___________________________________________________________________MENU INICIO
//


/* 18 */
/*
	Pre-condiciones:
		-
	Post-condiciones:
		la función retorna LETRA_CARGAR_PERSONAJE, LETRA_CARGAR_GIMNASIO, LETRA_COMENZAR_PARTIDA o LETRA_SIMULAR_PARTIDA.
 */
char accion_seleccionada_segun_menu_inicio(juego_t* juego){
	char letra = LETRA_DEFAULT;
	int cont = 0;

	do{

		if((cont > 0) && !accion_valida_menu_inicio(letra, juego))
			mostrar_razon_accion_invalida_menu_inicio(letra, juego);
		if(cont > 0)
			mostrar_texto_error_menu_4(letra, LETRA_CARGAR_PERSONAJE, LETRA_CARGAR_GIMNASIO, LETRA_COMENZAR_PARTIDA, LETRA_SIMULAR_PARTIDA);
		pedir_letra_menu_inicio(&letra);
		mayusculizar_letra(&letra);
		(cont)++;
	} while(!ingreso_letra_es_correcto_4(letra, LETRA_CARGAR_PERSONAJE, LETRA_CARGAR_GIMNASIO, LETRA_COMENZAR_PARTIDA, LETRA_SIMULAR_PARTIDA)
		|| !accion_valida_menu_inicio(letra, juego));

	return letra;
}

/* 06 */
/*
	Pre-condiciones:
		"retorno" debe ser SI o NO.
	Post-condiciones:
		la función actualiza el valor de "retorno".
 */
void determinar_sig_pantalla_segun_respuesta_menu_inicio(char respuesta, int *retorno){

	if(respuesta == SI)
		*retorno = IR_MENU_GIMNASIO_NUEVO;
	else
		*retorno = IR_MENU_INICIO;      
}

/* 06 */
/*
	Pre-condiciones:
		"retorno" debe ser EXITO o DERROTA.
	Post-condiciones:
		la función actualiza el valor de "retorno".
 */
void determinar_sig_pantalla_segun_simulacion(int *retorno){

	if(*retorno == EXITO)
		*retorno = JUEGO_GANADO;
	else
		*retorno = JUEGO_PERDIDO;
}

/* 28 */
/*
	Pre-condiciones:
		"accion" debe ser LETRA_CARGAR_PERSONAJE, LETRA_CARGAR_GIMNASIO, LETRA_COMENZAR_PARTIDA o LETRA_SIMULAR_PARTIDA.
	Post-condiciones:
		la función ejecuta la acción correspondiente;
		la función muestra un mensaje si es posible;
		la función devuelve "retorno".
 */
int realizar_accion_menu_inicio(juego_t* juego, char accion){
	int retorno = EXITO;
	char respuesta;

	system("clear");
	switch(accion){
		case LETRA_CARGAR_GIMNASIO:
			retorno = cargar_gimnasios(juego);
			mensaje_segun_retorno(retorno, NULL, NULL);
			retorno = IR_MENU_INICIO;
			break;
		case LETRA_CARGAR_PERSONAJE:
			retorno = cargar_personaje(juego);
			mensaje_segun_retorno(retorno, NULL, NULL);
			retorno = IR_MENU_INICIO;
			break;
		case LETRA_COMENZAR_PARTIDA:
			consultar_eleccion_comenzar_partida(&respuesta);
			determinar_sig_pantalla_segun_respuesta_menu_inicio(respuesta, &retorno);
			if(retorno == IR_MENU_GIMNASIO_NUEVO)
				actualizar_juego(juego);
			break;
		default:
			retorno = simular_partida(juego);
			determinar_sig_pantalla_segun_simulacion(&retorno);
			break;
	}

	return retorno;
}

/* 11 */
/*
	Pre-condiciones:
		"juego" debe ser válido y tener todos sus campos válidos.
	Post-condiciones:
		la función muestra un menu de inicio, y permite ejecutar una acción a
			partir de las opciones.
 */
void ir_menu_inicio(juego_t* juego){
	char accion;
	int resultado;

	system("clear");
	mostrar_parte_visual_menu("MENU INICIO", NULL, mostrar_lineas_opciones_menu_inicio);
	accion = accion_seleccionada_segun_menu_inicio(juego);
	resultado = realizar_accion_menu_inicio(juego, accion);
	if((resultado != IR_MENU_INICIO) && (resultado != JUEGO_GANADO) && (resultado != JUEGO_PERDIDO))
		mostrar_carga_nuevo_menu();
	siguiente_pantalla_segun_resultado(juego, resultado);
}


//
//
//
//


/*12*/
int main(int cantidad_argumentos, char* argumentos[]){
	srand ((unsigned)time(NULL));
	juego_t* juego;

	mostrar_carga_juego();
	juego = nuevo_juego();
	if(!juego)
		return 0;
	ir_menu_inicio(juego);
	destruir_juego(juego);

	return 0;
}