#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include "heap.h"
#include "ptda.h"

#define IGUALES 		 0
#define PRIMERO_MAYOR 	 1
#define PRIMERO_MENOR 	-1

#define COLOR_PAJARO_MACHO  			"Negro"
#define COLOR_PAJARO_HEMBRA  			"Gris"

#define VERDE_CLARO			"\033[0m\033[32m"
#define VERDE_OSCURO		"\033[1m\033[32m"

#define MAX_TEXTO				200

#define ERROR 	   -1
#define EXITO 		0

typedef struct pajaro{

    int id;
    char color[15];
}pajaro_t;

//____________________________________________________________FUNCIONES DEL HEAP

/*16*/
int comparador_elementos(void* elemento_1, void* elemento_2){

	if(!elemento_1 || !elemento_2)
		return IGUALES;

	int id_elemento_1 = (((pajaro_t*)elemento_1)->id);
	int id_elemento_2 = (((pajaro_t*)elemento_2)->id);
	int devolucion = id_elemento_1 - id_elemento_2;

	char* color_elemento_1 = (((pajaro_t*)elemento_1)->color);
	char* color_elemento_2 = (((pajaro_t*)elemento_2)->color);

	if((devolucion == 0) && (strcmp(color_elemento_1, color_elemento_2) != 0))
		devolucion = PRIMERO_MENOR;

	return devolucion;
}

/*06*/
void destructor_elementos(void* elemento){

	if(!elemento)
        return;

	free(elemento);
}

//____________________________________________________________IMPRESIONES

void mostrar_error_malloc(){

	printf(ROJO_CLARO "No sabemos qué ocurrió, disculpe las molestias. \n" FIN);
}

void mostrar_accion(char* frase, void** vector, int (*id_mostrar)(void*), size_t tope){
	int id;

	printf(MAGENTA "\n");
	if(tope > 0){

		printf("%s\n", frase);
		for(int i = 0; i < tope; i++){

			id = id_mostrar(vector[i]);
			if(id < 0)
				printf("ID: no tiene");
			else
				printf("ID: %i", id);
			if(i < (tope - 1))
				printf(" - ");
			else
				printf(".\n");
		}
	}
	printf("Cantidad: %i.\n", (int)tope);
}

//____________________________________________________________VALIDACIONES


bool campos_validos(heap_t* heap, void** vector, size_t cantidad, heap_comparador comparador, heap_liberar_elemento destructor){

	return (((heap->vector) == vector)
		&& ((heap->cant_elementos) == cantidad)
		&& ((heap->comparador) == comparador)
		&& ((heap->destructor) == destructor));
}

bool elemento_en_el_heap(heap_t* heap, pajaro_t* pajaro, size_t pos_valida){

	if(heap->cant_elementos <= pos_valida)
		return false;

	if(heap && ((pajaro_t*)heap->vector[pos_valida] != pajaro))
		if(heap->destructor)
			heap->destructor(pajaro);

	return (heap && ((pajaro_t*)heap->vector[pos_valida] == pajaro));
}

//____________________________________________________________CREACIONES

heap_t* crear_un_heap(heap_comparador comparador, heap_liberar_elemento destructor, pajaro_t** pajaros){
	heap_t* heap;

	heap = heap_crear(comparador, destructor);
	if(!heap){
		
		mostrar_error_malloc();
		if(pajaros)
			free(pajaros);	
		return NULL;
	}

	return heap;
}

int crear_pajaro(pajaro_t** conjunto_de_pajaros, size_t pos, int id){
	pajaro_t* pajaro;

	pajaro = malloc(sizeof(pajaro_t));
	if(!pajaro)
		return ERROR;

	pajaro->id = id;
	if((pos % 2) == 0)
		strcpy(pajaro->color, COLOR_PAJARO_MACHO);
	else
		strcpy(pajaro->color, COLOR_PAJARO_HEMBRA);

	conjunto_de_pajaros[pos] = pajaro;

    return EXITO;
}

pajaro_t** crear_valores_insertar(size_t cantidad_total, size_t cantidad_rellenar){
	pajaro_t** conjunto_de_pajaros = NULL;
	size_t i = 0;
	int devolucion = EXITO;

	conjunto_de_pajaros = malloc(sizeof(pajaro_t*)*cantidad_total);
	if(!conjunto_de_pajaros){

		mostrar_error_malloc();
		return NULL;
	}
   
	while((i < cantidad_rellenar) && (devolucion == EXITO)){

		devolucion = crear_pajaro(conjunto_de_pajaros, i, (int)i);
		i++;
	}

	return conjunto_de_pajaros;
}

//____________________________________________________________ENVIAR POR PARÁMETRO

int id_posiciones(void* posicion){

	return (int)(posicion);
}

//____________________________________________________________PRUEBAS GENERALIZADAS

void probar_crear_heap_valido(heap_comparador comparador, heap_liberar_elemento destructor, char* frase){
	heap_t* heap;
	char texto[MAX_TEXTO];

	snprintf(texto, MAX_TEXTO, "%s: Se puede crear un heap.", frase);

	heap = heap_crear(comparador, destructor);
	ptda_afirmar(heap, texto);
	ptda_subafirmar_fin((heap && campos_validos(heap, NULL, 0, comparador, destructor)), "El heap tiene una estructura válida.");
	heap_destruir(heap);
}

//____________________________________________________________PRUEBAS POR FUNCIÓN

/*09*/
void probar_crear_heap(){

	ptda_nuevo_subgrupo("Creación - Heap");
	
	ptda_afirmar(!heap_crear(NULL, destructor_elementos), "No hay criterio para comparar elementos: No se puede crear el heap.");
	
	probar_crear_heap_valido(comparador_elementos, NULL, "No hay un destructor de elementos");

	probar_crear_heap_valido(comparador_elementos, destructor_elementos, "Hay un comparador y destructor de elementos");
}

/*81*/
void probar_insertar_heap(){
	heap_t* heap;
	int retorno;
	size_t i = 0;
	bool todo_ok = true;
	pajaro_t** pajaros = crear_valores_insertar(15, 15);
	if(!pajaros)
		return;
	
	heap = crear_un_heap(comparador_elementos, destructor_elementos, pajaros);
	if(!heap)
		return;

	ptda_nuevo_subgrupo("Inserción - Heap");

	ptda_afirmar(heap_insertar(NULL, pajaros[0]) == ERROR, "Heap sin crear: No se puede colocar un pájaro.");
	
	retorno = heap_insertar(heap, pajaros[8]);
	ptda_afirmar(retorno == EXITO, "Heap válido y vacío: Se puede colocar un pájaro (ID 8).");
	ptda_subafirmar(retorno == EXITO && heap->cant_elementos == 1, "La cantidad de elementos del heap es correcta.");
	ptda_subafirmar_fin(retorno == EXITO && elemento_en_el_heap(heap, pajaros[8], 0), "El elemento insertado está en donde corresponde.");

 	retorno = heap_insertar(heap, pajaros[3]);
	ptda_afirmar(retorno == EXITO, "Heap válido y con un pájaro: Se puede colocar un pájaro (ID 3).");
	ptda_subafirmar(retorno == EXITO && heap->cant_elementos == 2, "La cantidad de elementos del heap es correcta.");
	ptda_subafirmar_fin(retorno == EXITO && elemento_en_el_heap(heap, pajaros[3], 0), "El elemento insertado está en donde corresponde.");

 	retorno = heap_insertar(heap, pajaros[10]);
	ptda_afirmar(retorno == EXITO, "Heap válido y con dos pájaros: Se puede colocar un pájaro (ID 10).");
	ptda_subafirmar(retorno == EXITO && heap->cant_elementos == 3, "La cantidad de elementos del heap es correcta.");
	ptda_subafirmar_fin(retorno == EXITO && elemento_en_el_heap(heap, pajaros[10], 2), "El elemento insertado está en donde corresponde.");

	size_t posiciones[] = {1, 6, 9, 14, 0, 2, 4, 7, 13, 5, 11, 12};
	
	mostrar_accion("Se intentan colocar, en este orden, los pajaros cuyo ID es:", (void**)posiciones, id_posiciones, 12);
	while(i < 12 && retorno == EXITO){

		retorno = heap_insertar(heap, pajaros[posiciones[i]]);
		i++;
	}
	ptda_afirmar(retorno == EXITO, "Heap válido y varios pájaros: Se pueden colocar 12 pájaros.");
	ptda_subafirmar(retorno == EXITO && heap->cant_elementos == 15, "La cantidad de elementos del heap es correcta.");
	/* Mi vector debería ser
	(8)
	(8, 3) -> (3, 8)
	(3, 8, 10)
	(3, 8, 10, 1) -> (3, 1, 10, 8) -> (1, 3, 10, 8)
	(1, 3, 10, 8, 6)
	(1, 3, 10, 8, 6, 9) -> (1, 3, 9, 8, 6, 10) 
	(1, 3, 9, 8, 6, 10, 14)
	(1, 3, 9, 8, 6, 10, 14, 0) -> (1, 3, 9, 0, 6, 10, 14, 8) -> (1, 0, 9, 3, 6, 10, 14, 8) -> (0, 1, 9, 3, 6, 10, 14, 8)
	(0, 1, 9, 3, 6, 10, 14, 8, 2) -> (0, 1, 9, 2, 6, 10, 14, 8, 3)
	(0, 1, 9, 2, 6, 10, 14, 8, 3, 4) -> (0, 1, 9, 2, 4, 10, 14, 8, 3, 6)
	(0, 1, 9, 2, 4, 10, 14, 8, 3, 6, 7)
	(0, 1, 9, 2, 4, 10, 14, 8, 3, 6, 7, 13)
	(0, 1, 9, 2, 4, 10, 14, 8, 3, 6, 7, 13, 5) -> (0, 1, 9, 2, 4, 5, 14, 8, 3, 6, 7, 13, 10) -> (0, 1, 5, 2, 4, 9, 14, 8, 3, 6, 7, 13, 10)
	(0, 1, 5, 2, 4, 9, 14, 8, 3, 6, 7, 13, 10, 11) -> (0, 1, 5, 2, 4, 9, 11, 8, 3, 6, 7, 13, 10, 14)
	(0, 1, 5, 2, 4, 9, 11, 8, 3, 6, 7, 13, 10, 14, 12) 
	=> FIN */
	size_t ordenado[] = {0, 1, 5, 2, 4, 9, 11, 8, 3, 6, 7, 13, 10, 14, 12};
	i = 0;
	while(i < 12 && todo_ok){

		todo_ok = elemento_en_el_heap(heap, pajaros[ordenado[i]], i);
		i++;
	}
	ptda_subafirmar_fin(todo_ok, "Los elementos insertados están en donde corresponde.");
	heap_destruir(heap);

	heap  = crear_un_heap(comparador_elementos, destructor_elementos, pajaros);
	if(!heap)
		return;

 	retorno = heap_insertar(heap, NULL);
	ptda_afirmar(retorno == EXITO, "Heap válido y vacío: Se puede colocar un pájaro recién nacido (sin información).");
	ptda_subafirmar(retorno == EXITO && heap->cant_elementos == 1, "La cantidad de elementos del heap es correcta.");
	ptda_subafirmar_fin(retorno == EXITO && heap->vector[0] == NULL, "El elemento insertado está en donde corresponde.");
	
	heap_destruir(heap);

	free(pajaros);
}

void probar_elemento_raiz_heap(){
	void* elemento;
	size_t i = 0;
	heap_t* heap;
	pajaro_t** pajaros;

	ptda_nuevo_subgrupo("Elemento Raíz - Heap");
	
	pajaros = crear_valores_insertar(15, 15);
	if(!pajaros)
		return;
	heap = crear_un_heap(comparador_elementos, destructor_elementos, pajaros);
	if(!heap)
		return;

	ptda_afirmar(heap_elemento_raiz(NULL) == NULL, "Heap sin crear: No se puede visualizar la raíz.");

	ptda_afirmar(heap_elemento_raiz(heap) == NULL, "Heap válido y vacío: No se puede visualizar la raíz.");

	heap_insertar(heap, NULL);
	ptda_afirmar(heap_elemento_raiz(heap) == NULL, "Heap válido y con un pájaro recién nacido (sin información): Se puede visualizar la raiz.");
	heap_eliminar_raiz(heap);

	size_t posiciones[] = {8, 3, 10, 1, 6, 9, 14, 0, 2, 4, 7, 13, 5, 11, 12};	
	mostrar_accion("Se colocan, en este orden, los pajaros cuyo ID es:", (void**)posiciones, id_posiciones, 15);
	while(i < 15){

		heap_insertar(heap, pajaros[posiciones[i]]);
		i++;
	}
	printf("\nMi vector debe ser (0, 1, 5, 2, 4, 9, 11, 8, 3, 6, 7, 13, 10, 14, 12).\n");
		
	elemento = heap_elemento_raiz(heap);
	ptda_afirmar(elemento, "Heap válido y con muchos pájaros: Se puede visualizar la raiz.");
	ptda_subafirmar_fin((pajaro_t*)elemento == pajaros[0], "El elemento visualizado es el esperado");
	heap_eliminar_raiz(heap);

	heap_destruir(heap);
	free(pajaros);
}

void probar_eliminar_raiz_heap(){
	size_t i = 0;
	int retorno = EXITO;
	heap_t* heap;
	pajaro_t** pajaros;

	ptda_nuevo_subgrupo("Eliminar Raíz - Heap");
	
	pajaros = crear_valores_insertar(15, 15);
	if(!pajaros)
		return;
	heap = crear_un_heap(comparador_elementos, destructor_elementos, pajaros);
	if(!heap)
		return;

	ptda_afirmar(heap_eliminar_raiz(NULL) == ERROR, "Heap sin crear: No se puede eliminar la raíz.");

	ptda_afirmar(heap_eliminar_raiz(heap) == ERROR, "Heap válido y vacío: No se puede eliminar la raíz.");

	heap_insertar(heap, NULL);
	ptda_afirmar(heap_eliminar_raiz(heap) == EXITO, "Heap válido y con un pájaro recién nacido (sin información): Se puede eliminar la raiz.");
	ptda_subafirmar_fin(heap->cant_elementos == 0, "El heap quedó vacío.");

	size_t posiciones[] = {8, 3, 10, 1, 6, 9, 14, 0, 2, 4, 7, 13, 5, 11, 12};	
	mostrar_accion("Se colocan, en este orden, los pajaros cuyo ID es:", (void**)posiciones, id_posiciones, 15);
	while(i < 15){

		heap_insertar(heap, pajaros[posiciones[i]]);
		i++;
	}
	printf("\nMi vector debe ser (0, 1, 5, 2, 4, 9, 11, 8, 3, 6, 7, 13, 10, 14, 12).\n");
		
	ptda_afirmar(heap_eliminar_raiz(heap) == EXITO, "Heap válido y con muchos pájaros: Se puede eliminar la raiz.");
	ptda_subafirmar_fin(heap->cant_elementos == 14, "El heap quedó con la cantidad correcta de elementos.");
	
	printf(MAGENTA "Mi vector quedó como (");
	for(int j = 0; j < 14; j++){
		printf("%i", ((pajaro_t*)(heap->vector[j]))->id);
		if(j < 13)
			printf(", ");
	}
	printf(").\n Y debía quedar como (1, 2, 5, 3, 4, 9, 11, 8, 12, 6, 7, 13, 10, 14).\n\n");
	
	printf(BLANCO "Intento extraer hasta que quede un elemento, mi vector queda de la siguiente manera: \n");
	i = 0;
	while(i < 13 && retorno == EXITO){

		retorno = heap_eliminar_raiz(heap);
		printf("(");
		for(int j = 0; j < 13-i; j++){

			printf("%i", ((pajaro_t*)(heap->vector[j]))->id);
			if(j < 12-i)
				printf(", ");
		}
		printf(")\n");
		i++;
	}

	printf(MAGENTA "\nLa extracción debería ser así: \n(2, 3, 5, 8, 4, 9, 11, 14, 12, 6, 7, 13, 10)\n");
	printf("(3, 4, 5, 8, 6, 9, 11, 14, 12, 10, 7, 13)\n(4, 6, 5, 8, 7, 9, 11, 14, 12, 10, 13)\n");
	printf("(5, 6, 9, 8, 7, 13, 11, 14, 12, 10)\n(6, 7, 9, 8, 10, 13, 11, 14, 12)\n");
	printf("(7, 8, 9, 12, 10, 13, 11, 14)\n(8, 10, 9, 12, 14, 13, 11)\n");
	printf("(9, 10, 11, 12, 14, 13)\n(10, 12, 11, 13, 14)\n");
	printf("(11, 12, 14, 13)\n(12, 13, 14)\n(13, 14)\n(14)\n");

	ptda_afirmar(retorno == EXITO, "Heap válido y con muchos pájaros: Se pueden extraer los elementos hasta que quede uno solo.");
	ptda_subafirmar(heap_elemento_raiz(heap) == pajaros[14], "El elemento restante es el esperado.");
	ptda_subafirmar_fin(heap->cant_elementos == 1, "El heap quedó con la cantidad correcta de elementos.");

	heap_destruir(heap);
	free(pajaros);
}

int main(){
	
	ptda_nueva_categoria("Heap");
	ptda_nuevo_grupo("Operaciones básicas");
	probar_crear_heap();
	probar_insertar_heap();
	probar_eliminar_raiz_heap();

	ptda_nuevo_grupo("Obtener información");
	probar_elemento_raiz_heap();
	
	ptda_mostrar_reporte();
	printf(VERDE_OSCURO);

}