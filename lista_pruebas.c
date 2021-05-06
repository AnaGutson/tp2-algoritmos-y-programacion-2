#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "ptda.h"

#define EXITO	0
#define ERROR	-1

#define STRING_CANT_INSERCION  			"50"
#define CANT_INSERCION  				50
#define STRING_CANT_INSERCION_MENOS_1  	"49"

#define STRING_CANT_BORRAR	  	"30"
#define CANT_BORRAR 	 		30

#define STRING_CANT_BUSCAR  	"50"
#define CANT_BUSCAR  			50


bool se_inserto_bien(lista_t* lista, int* valor, size_t cant_elementos,
	size_t posicion_insertada, bool(*se_puede_seguir)(lista_t*, size_t, size_t, bool),
	bool(*es_valor)(void*, size_t, size_t, void*)){
	
	size_t i = 0;
	bool inserto_bien = true;
	
	if(!lista)
		inserto_bien = false;

	while(se_puede_seguir(lista, i, cant_elementos, inserto_bien)){
	
		if(!es_valor(lista_elemento_en_posicion(lista, i), i, posicion_insertada, &(valor[i])))
			inserto_bien = false;
		i++;
	}

	return inserto_bien;
}

bool nodos_lista_validos(lista_t* lista, nodo_t* nodo_inicio, nodo_t* nodo_fin){

	return ((nodo_inicio->elemento == lista_elemento_en_posicion(lista, 0))
		&& (nodo_fin->elemento == lista_ultimo(lista)));
}

bool puedo_avanzar_iterador(lista_iterador_t **iterador, int cantidad){
	bool avanzo = true;
	int i = 0;

	while(avanzo && i < cantidad){
		
		avanzo = lista_iterador_avanzar(*iterador);
		i++;
	}
	
	return avanzo;
}

bool cantidad_elementos(void* elemento, void* contador){
	bool devolucion = false;

	if(elemento && contador){

		(*(int*)contador)++;
		devolucion = true;
	}

	return devolucion;
}

bool cantidad_digitos_total(void* elemento, void* contador){
	bool devolucion = false;

	if(elemento && contador){

		(*(int*)contador) += cant_digitos(*(int*)elemento);
		devolucion = true;
	}

	return devolucion;
}

bool cantidad_posiciones_impares(void* elemento, void* contador){

	if(elemento && contador && (*(int*)elemento)%2 != 0){

		(*(int*)contador)++;
	}

	return (elemento && contador);
}

bool iterador_inicializado_valido(lista_iterador_t *iterador, lista_t *lista){

	return (iterador->lista == lista && iterador->corriente == lista->nodo_inicio);
}

int* crear_valores_insertar(){
	int *vector = NULL;

	vector = malloc(sizeof(int)*CANT_INSERCION);
	if(!vector)
		return NULL;

	for(int i = 0; i < CANT_INSERCION; i++)
		vector[i] = i;

	return vector;
}

int cant_digitos_con_anteriores(int actual){
	
	if(actual == 0)
		return cant_digitos(actual);

	return cant_digitos(actual) + cant_digitos_con_anteriores(actual - 1);
}

int borrar_muchos(lista_t* lista, int(*eliminar)(lista_t*)){
	int retorno = EXITO, i = 0;

	while(i < CANT_BORRAR && retorno == EXITO){
		
		retorno = eliminar(lista);
		i++;
	}

	return retorno;
}

int insertar_elementos_lista(int* valor, lista_t* lista, int cant_elementos,
	int(*funcion_insertar)(lista_t*, void*)){
	int retorno = EXITO, i = 0;

	while((i < cant_elementos) && (retorno == EXITO)){
		
		retorno = funcion_insertar(lista, &(valor[i]));
		i++;
	}

	return retorno;
}

int accion_invalida_elementos_lista(lista_t* lista, int* valor, int cant_elementos,
	int(*accion)(lista_t*, void*, size_t)){
	int retorno = ERROR;
	size_t i = 0;
	
	while((i < cant_elementos) && (retorno == ERROR)){
		
		retorno = accion(lista, &(valor[i]), i);
		i++;
	}

	return retorno;
}

void* obtener_mal_elementos_lista(lista_t* lista, int cant_elementos){
	void* elemento = NULL;
	size_t i = 0;
	
	while((i < cant_elementos) && !elemento){
		
		elemento = lista_elemento_en_posicion(lista, i);
		i++;
	}

	return elemento;
}

void reiniciar_lista(lista_t* lista){

	while(lista_elementos(lista) != 0)
		lista_borrar_de_posicion(lista, 0);
}

//-----------------------------------------------------------------FUNCIONES PARA PUNTEROS A FUNCIÓN

bool se_puede_seguir_insertar_normal(lista_t* lista, size_t i, size_t cant_elementos, bool inserto_bien){

	return ((i < cant_elementos) && inserto_bien);
}

bool se_puede_seguir_insertar_posicion(lista_t* lista, size_t i, size_t cant_elementos, bool inserto_bien){

	return ((i < cant_elementos) && inserto_bien && lista_elemento_en_posicion(lista, i));
}

bool es_valor_insertar_normal(void* elemento, size_t i, size_t posicion_insertada, void* elemento_correcto){

	return (elemento == elemento_correcto);
}

bool es_valor_insertar_posicion(void* elemento, size_t i, size_t posicion_insertada, void* elemento_correcto){

	return ((i > posicion_insertada) && (elemento == elemento_correcto));
}

int insercion(lista_t* lista, void* elemento, size_t i){

	return lista_insertar_en_posicion(lista, elemento, i);
}

int eliminacion(lista_t* lista, void* elemento, size_t i){

	return lista_borrar_de_posicion(lista, i);
}

//-------------------------------------------------------------------------LISTA

void probar_crear_lista(){
	lista_t* lista;

	lista = lista_crear();

	ptda_nuevo_subgrupo("Creación lista");
	
	ptda_afirmar(lista, "Se puede crear una lista");
	ptda_subafirmar_fin(lista && lista_vacia(lista), "La lista tiene sus campos inicializados correctamente");

	lista_destruir(lista);
}

void probar_insertar_normal_lista(int* valor){
	int retorno;
	bool inserto_bien = true;
	lista_t* lista;

	lista = lista_crear();
	
	retorno = insertar_elementos_lista(valor, NULL, 1, lista_insertar);
	ptda_afirmar(retorno == ERROR, "No se puede insertar en una lista no creada");
	
	retorno = insertar_elementos_lista(valor, lista, 1, lista_insertar);
	ptda_afirmar(retorno == EXITO, "Se puede insertar un elemento en una lista vacía");
	ptda_subafirmar((retorno == EXITO) && (1 == lista_elementos(lista)), "La cantidad de elementos de la lista es correcta");
	ptda_subafirmar((retorno == EXITO) && nodos_lista_validos(lista, lista->nodo_inicio, lista->nodo_fin), "El valor del elemento insertado en la lista es correcto");
	ptda_subafirmar_fin((retorno == EXITO) && (lista->nodo_inicio == lista->nodo_fin) && lista->nodo_inicio, "El inicio y fin de la lista son correctos");

	reiniciar_lista(lista);
	retorno = insertar_elementos_lista(valor, lista, CANT_INSERCION, lista_insertar);	
	ptda_afirmar(retorno == EXITO, "Se puede insertar "STRING_CANT_INSERCION" elementos en una lista vacía");
	ptda_subafirmar((CANT_INSERCION) == lista_elementos(lista), "La cantidad de elementos de la lista es correcta");
	inserto_bien = se_inserto_bien(lista, valor, CANT_INSERCION, 0, se_puede_seguir_insertar_normal, es_valor_insertar_normal);
	ptda_subafirmar_fin(inserto_bien, "El valor de los "STRING_CANT_INSERCION" elementos insertados en la lista es correcto");

	lista_destruir(lista);
}

void probar_insertar_posicion_lista(int* valor){
	int retorno;
	size_t cant_inicial;
	nodo_t *nodo_inicio_inicial, *nodo_fin_inicial;
	lista_t* lista;

	lista = lista_crear();
	
	retorno = accion_invalida_elementos_lista(NULL, valor, CANT_INSERCION, insercion);
	ptda_afirmar(retorno == ERROR, "No se puede insertar en ninguna posición de una lista no creada");

	retorno = lista_insertar_en_posicion(lista, &(valor[0]), 0);
	ptda_afirmar(retorno == EXITO, "Se puede insertar un elemento en la primera posicion de una lista válida");
	ptda_subafirmar((retorno == EXITO) && (lista->nodo_inicio->elemento == &(valor[0]) && lista->nodo_inicio == lista->nodo_fin), "El inicio y fin de la lista son correctos");
	ptda_subafirmar(retorno == EXITO && lista_elemento_en_posicion(lista, 0) == &(valor[0]), "El valor del elemento insertado en la lista es correcto");
	retorno = se_inserto_bien(lista, valor, CANT_INSERCION, 0, se_puede_seguir_insertar_posicion, es_valor_insertar_posicion);
	ptda_subafirmar_fin(retorno == EXITO, "Los siguientes elementos de la lista están correctamente ordenados");

	cant_inicial = lista_elementos(lista);
	retorno = lista_insertar_en_posicion(lista, &(valor[1]), lista_elementos(lista));
	ptda_afirmar(retorno == EXITO, "Se puede insertar un elemento en la última posicion de una lista válida");	
	ptda_subafirmar(retorno == EXITO && lista_elementos(lista) == cant_inicial + 1, "La cantidad de elementos de la lista es correcta");	
	ptda_subafirmar(retorno == EXITO && lista_elemento_en_posicion(lista, lista_elementos(lista) - 1) == &(valor[1]), "El valor del elemento insertado en la lista es correcto");
	ptda_subafirmar_fin(retorno == EXITO && lista_ultimo(lista) == &(valor[1]), "El final de la lista es correcto");

	cant_inicial = lista_elementos(lista);
	retorno = lista_insertar_en_posicion(lista, &(valor[2]), lista_elementos(lista) + 1000);
	ptda_afirmar(retorno == EXITO, "Se puede insertar un elemento en la lista si le mando una posicion mayor a la cantidad de posiciones que posee");
	ptda_subafirmar(retorno == EXITO && lista_elementos(lista) == cant_inicial + 1, "La cantidad de elementos de la lista es correcta");
	ptda_subafirmar(retorno == EXITO && lista_elemento_en_posicion(lista, lista_elementos(lista) - 1) == &(valor[2]), "El valor del elemento insertado en la lista es correcto");
	ptda_subafirmar_fin(retorno == EXITO && lista_ultimo(lista) == &(valor[2]), "El final de la lista es correcto");

	nodo_inicio_inicial = lista->nodo_inicio;
	nodo_fin_inicial = lista->nodo_fin;
	cant_inicial = lista_elementos(lista);
	retorno = lista_insertar_en_posicion(lista, &(valor[3]), 1);
	ptda_afirmar(retorno == EXITO, "Se puede insertar un elemento en la lista en la posición 1");
	ptda_subafirmar(retorno == EXITO && lista_elementos(lista) == cant_inicial + 1, "La cantidad de elementos de la lista es correcta");
	ptda_subafirmar(retorno == EXITO && lista_elemento_en_posicion(lista, 1) == &(valor[3]), "El valor ingresado es correcto");
	ptda_subafirmar_fin(retorno == EXITO && nodos_lista_validos(lista, nodo_inicio_inicial, nodo_fin_inicial), "El final de la lista es correcto");

	lista_destruir(lista);
}

void probar_insertar_lista(int *valor){

	ptda_nuevo_subgrupo("Inserción normal - lista");
	probar_insertar_normal_lista(valor);
	ptda_nuevo_subgrupo("Inserción por posición - lista");
	probar_insertar_posicion_lista(valor);
}

void probar_eliminar_normal_lista(int* valor){
	int retorno;
	nodo_t *nodo_inicio_inicial;
	lista_t* lista;

	lista = lista_crear();

	ptda_afirmar(lista_borrar(NULL) == ERROR, "No se puede borrar en una lista no creada");

	ptda_afirmar(lista_borrar(lista) == ERROR, "No se puede borrar en una lista vacía");
	
	insertar_elementos_lista(valor, lista, 1, lista_insertar);
	retorno = lista_borrar(lista);
	ptda_afirmar(retorno == EXITO, "Se puede borrar un unico elemento en una lista");
	ptda_subafirmar((retorno == EXITO) && (0 == lista_elementos(lista)), "La cantidad de elementos de la lista es correcta");
	ptda_subafirmar_fin((retorno == EXITO) && (lista->nodo_fin == NULL) && (lista->nodo_inicio == lista->nodo_fin), "El inicio y fin de la lista son correctos");

	insertar_elementos_lista(valor, lista, CANT_INSERCION, lista_insertar);
	nodo_inicio_inicial = lista->nodo_inicio;
	retorno = borrar_muchos(lista, lista_borrar);
	ptda_afirmar(retorno == EXITO, "Se puede borrar "STRING_CANT_BORRAR" elementos en la lista");
	ptda_subafirmar(retorno == EXITO && (CANT_INSERCION - CANT_BORRAR) == lista_elementos(lista), "La cantidad de elementos de la lista es correcta");
	ptda_subafirmar_fin(retorno == EXITO && nodo_inicio_inicial == lista->nodo_inicio, "El valor de los elementos no borrados de la lista es correcto");

	while(lista_elementos(lista) != 0 && retorno == EXITO)
		retorno = lista_borrar(lista);
	ptda_afirmar(retorno == EXITO, "Se puede borrar todos los elementos en la lista");
	ptda_subafirmar_fin(retorno == EXITO && lista_vacia(lista), "La lista quedó vacía correctamente");

	lista_destruir(lista);
}

void probar_eliminar_posicion_lista(int* valor){
	int retorno;
	size_t cant_inicial;
	nodo_t *nodo_inicio_inicial, *nodo_fin_inicial, *nodo_a_comparar;
	lista_t* lista;

	lista = lista_crear();

	ptda_afirmar(accion_invalida_elementos_lista(NULL, valor, CANT_BORRAR, eliminacion) == ERROR, "No se puede borrar ninguna posición de una lista no creada");
	
	ptda_afirmar(accion_invalida_elementos_lista(lista, valor, CANT_BORRAR, eliminacion) == ERROR, "No se puede borrar ninguna posición de una lista vacía");
	
	insertar_elementos_lista(valor, lista, 1, lista_insertar);
	retorno = lista_borrar_de_posicion(lista, 0);
	ptda_afirmar(retorno == EXITO, "Se puede borrar el unico elemento mandando la posicion correcta");
	ptda_subafirmar_fin((retorno == EXITO) && lista_vacia(lista), "La lista quedó vacía correctamente");

	insertar_elementos_lista(valor, lista, 1, lista_insertar);
	retorno = lista_borrar_de_posicion(lista, 100);
	ptda_afirmar(retorno == EXITO, "Se puede borrar el unico elemento mandando cualquier posicion");
	ptda_subafirmar_fin((retorno == EXITO) && lista_vacia(lista), "La lista quedó vacía correctamente");

	insertar_elementos_lista(valor, lista, CANT_INSERCION, lista_insertar);
	nodo_inicio_inicial = lista->nodo_inicio;
	cant_inicial = lista_elementos(lista);
	retorno = lista_borrar_de_posicion(lista, lista_elementos(lista)-1);
	ptda_afirmar(retorno == EXITO, "Se puede borrar un elemento en la última posicion");
	ptda_subafirmar(retorno == EXITO && lista_elementos(lista) == cant_inicial - 1, "La cantidad de elementos de la lista es correcta");
	ptda_subafirmar(retorno == EXITO && lista->nodo_inicio == nodo_inicio_inicial, "El inicio de la lista es correcto");
	ptda_subafirmar_fin(retorno == EXITO && lista_ultimo(lista) == &(valor[CANT_INSERCION - 2]), "El final de la lista es correcto");
	
	cant_inicial = lista_elementos(lista);
	nodo_a_comparar = (lista->nodo_inicio)->siguiente;
	nodo_fin_inicial = lista->nodo_fin;
	retorno = lista_borrar_de_posicion(lista, 0);
	ptda_afirmar(retorno == EXITO, "Se puede borrar un elemento en la primera posicion");
	ptda_subafirmar(retorno == EXITO && lista_elementos(lista) == cant_inicial - 1, "La cantidad de elementos de la lista es correcta");
	ptda_subafirmar(retorno == EXITO && lista->nodo_inicio == nodo_a_comparar, "El inicio de la lista es correcto");
	ptda_subafirmar_fin(retorno == EXITO && lista->nodo_fin == nodo_fin_inicial, "El fin de la lista es correcto");

	cant_inicial = lista_elementos(lista);
	nodo_inicio_inicial = lista->nodo_inicio;
	nodo_a_comparar = (lista->nodo_inicio->siguiente)->siguiente;
	nodo_fin_inicial = lista->nodo_fin;
	retorno = lista_borrar_de_posicion(lista, 1);
	ptda_afirmar(retorno == EXITO, "Se puede borrar un elemento en la segunda posicion");
	ptda_subafirmar(retorno == EXITO && lista_elementos(lista) == cant_inicial - 1, "La cantidad de elementos es correcta");
	ptda_subafirmar(retorno == EXITO && lista->nodo_inicio == nodo_inicio_inicial, "El inicio de la lista es correcto");
	ptda_subafirmar(retorno == EXITO && lista->nodo_inicio->siguiente == nodo_a_comparar, "El elemento fue borrado correctamente");
	ptda_subafirmar_fin(retorno == EXITO && lista->nodo_fin == nodo_fin_inicial, "El fin de la lista es correcto");

	lista_destruir(lista);
}

void probar_eliminar_lista(int* valor){
	
	ptda_nuevo_subgrupo("Eliminar normal - lista");
	probar_eliminar_normal_lista(valor);
	ptda_nuevo_subgrupo("Eliminar por posición - lista");
	probar_eliminar_posicion_lista(valor);
}

void probar_obtener_elemento_lista(int* valor){
	void* elemento;
	lista_t* lista;

	lista = lista_crear();

	ptda_afirmar(!obtener_mal_elementos_lista(NULL, CANT_BUSCAR), "No se puede buscar ningún elemento de una lista no creada");

	ptda_afirmar(!obtener_mal_elementos_lista(lista, CANT_BORRAR), "No se puede buscar ningún elemento de una lista vacía");

	insertar_elementos_lista(valor, lista, 1, lista_insertar);
	elemento = lista_elemento_en_posicion(lista, 0);
	ptda_afirmar(elemento, "Se puede buscar el unico elemento mandando la posicion correcta");
	ptda_subafirmar_fin(elemento == &(valor[0]), "El valor del elemento buscado en la lista es correcto");
	
	elemento = lista_elemento_en_posicion(lista, lista_elementos(lista) + 1);
	ptda_afirmar(!elemento, "No se puede buscar un elemento en una posición que no existe");
	
	reiniciar_lista(lista);
	insertar_elementos_lista(valor, lista, CANT_INSERCION, lista_insertar);
	elemento = lista_elemento_en_posicion(lista, lista_elementos(lista)-1);
	ptda_afirmar(elemento, "Se puede obtener un elemento en la última posicion");
	ptda_subafirmar_fin(elemento == &(valor[CANT_INSERCION-1]), "El valor del elemento buscado en la lista es correcto");
	
	elemento = lista_elemento_en_posicion(lista, 0);
	ptda_afirmar(elemento, "Se puede obtener un elemento en la primera posicion");
	ptda_subafirmar_fin(elemento == &(valor[0]), "El valor del elemento buscado en la lista es correcto");

	lista_destruir(lista);
}

void probar_obtener_ultimo_lista(int* valor){
	void* elemento;
	lista_t* lista;

	lista = lista_crear();

	ptda_afirmar(!lista_ultimo(NULL), "No se puede buscar el último elemento de una lista no creada");

	ptda_afirmar(!lista_ultimo(lista), "No se puede buscar el último elemento de una lista vacía");

	insertar_elementos_lista(valor, lista, 1, lista_insertar);
	elemento = lista_ultimo(lista);
	ptda_afirmar(elemento, "Se puede buscar el último elemento de una lista de un elemento");
	ptda_subafirmar_fin(elemento == &(valor[0]), "El valor del elemento buscado en la lista es correcto");
	
	reiniciar_lista(lista);
	insertar_elementos_lista(valor, lista, CANT_INSERCION, lista_insertar);
	elemento = lista_ultimo(lista);
	ptda_afirmar(elemento, "Se puede obtener el último elemento de una lista de muchos elementos");
	ptda_subafirmar_fin(elemento == &(valor[CANT_INSERCION-1]), "El valor del elemento buscado en la lista es correcto");

	lista_destruir(lista);
}

void probar_buscar_lista(int* valor){

	ptda_nuevo_subgrupo("Obtener elemento por posición - lista");
	probar_obtener_elemento_lista(valor);
	ptda_nuevo_subgrupo("Obtener último elemento - lista");
	probar_obtener_ultimo_lista(valor);
}

void probar_esta_vacia_lista(int* valor){
	lista_t* lista;

	lista = lista_crear();

	ptda_nuevo_subgrupo("Esta vacía - lista");
	
	ptda_afirmar(lista_vacia(NULL), "Se puede detectar que una lista nula está vacía")

	ptda_afirmar(lista_vacia(lista), "Se puede detectar que una lista sin elementos está vacía")
	
	insertar_elementos_lista(valor, lista, 1, lista_insertar);
	ptda_afirmar(!lista_vacia(lista), "Se puede detectar que una lista con un elemento no está vacía")

	reiniciar_lista(lista);
	insertar_elementos_lista(valor, lista, CANT_INSERCION, lista_insertar);
	ptda_afirmar(!lista_vacia(lista), "Se puede detectar que una lista con varios elementos no está vacía");

	lista_destruir(lista);
}

void probar_cantidad_elementos_lista(int* valor){
	lista_t* lista;

	lista = lista_crear();

	ptda_nuevo_subgrupo("Obtener cantidad elementos - lista");

	ptda_afirmar(lista_elementos(NULL) == 0, "Se puede detectar la cantidad de elementos en una lista nula");

	ptda_afirmar(lista_elementos(lista) == 0, "Se puede detectar la cantidad de elementos en una lista con 0 elementos");
	
	insertar_elementos_lista(valor, lista, 1, lista_insertar);
	ptda_afirmar(lista_elementos(lista) == 1, "Se puede detectar la cantidad de elementos en una lista con 1 elemento");
	
	reiniciar_lista(lista);
	insertar_elementos_lista(valor, lista, CANT_INSERCION, lista_insertar);
	ptda_afirmar(lista_elementos(lista) == CANT_INSERCION, "Se puede detectar la cantidad de elementos en una lista con muchos elementos");

	lista_destruir(lista);
}

void probar_mostrar_con_funcion_lista(int* valor){
	int contador = 0;
	size_t elementos_recorridos = 0;
	lista_t* lista;

	lista = lista_crear();

	ptda_nuevo_subgrupo("Mostrar elementos - lista");

	elementos_recorridos = lista_con_cada_elemento(NULL, cantidad_elementos, &contador);
	ptda_afirmar(elementos_recorridos == 0 && contador == 0, "No se puede recorrer una lista nula");

	elementos_recorridos = lista_con_cada_elemento(lista, NULL, (void*)&contador);
	ptda_afirmar(elementos_recorridos == 0 && contador == 0, "No se puede recorrer una lista mandandole ninguna función");
	
	ptda_nuevo_subgrupo("Mostrar elementos - lista: recorrer todo");

	elementos_recorridos = lista_con_cada_elemento(lista, cantidad_elementos, (void*)&contador);
	ptda_afirmar(elementos_recorridos == 0 && contador == 0, "Se puede recorrer correctamente una lista vacía");

	insertar_elementos_lista(valor, lista, 1, lista_insertar);
	elementos_recorridos = lista_con_cada_elemento(lista, cantidad_elementos, (void*)&contador);
	ptda_afirmar(elementos_recorridos == 1 && contador == 1, "Se puede recorrer correctamente una lista con un elemento");

	contador = 0;
	insertar_elementos_lista(valor, lista, CANT_INSERCION, lista_insertar);
	elementos_recorridos = lista_con_cada_elemento(lista, cantidad_elementos, (void*)&contador);
	ptda_afirmar(elementos_recorridos == lista_elementos(lista) && contador == lista_elementos(lista), "Se puede recorrer correctamente una lista con muchos elementos");

	ptda_nuevo_subgrupo("Mostrar elementos - lista: obtener cantidad de digitos total");

	reiniciar_lista(lista);
	insertar_elementos_lista(valor, lista, 0, lista_insertar);
	contador = 0;
	elementos_recorridos = lista_con_cada_elemento(lista, cantidad_digitos_total, (void*)&contador);
	ptda_afirmar(elementos_recorridos == 0 && contador == 0, "Se puede recorrer correctamente una lista vacía");

	reiniciar_lista(lista);
	insertar_elementos_lista(valor, lista, CANT_INSERCION, lista_insertar);
	contador = 0;
	elementos_recorridos = lista_con_cada_elemento(lista, cantidad_digitos_total, (void*)&contador);
	ptda_afirmar(elementos_recorridos == CANT_INSERCION && contador == cant_digitos_con_anteriores(CANT_INSERCION-1), "Se puede recorrer correctamente una lista con "STRING_CANT_INSERCION" elementos");

	ptda_nuevo_subgrupo("Mostrar elementos - lista: obtener solo posiciones impares");

	reiniciar_lista(lista);
	insertar_elementos_lista(valor, lista, 0, lista_insertar);
	contador = 0;
	elementos_recorridos = lista_con_cada_elemento(lista, cantidad_posiciones_impares, (void*)&contador);
	ptda_afirmar(elementos_recorridos == 0 && contador == 0, "Se puede recorrer correctamente una lista vacía");

	reiniciar_lista(lista);
	insertar_elementos_lista(valor, lista, CANT_INSERCION, lista_insertar);
	int contador_2 = 0;
	elementos_recorridos = lista_con_cada_elemento(lista, cantidad_posiciones_impares, (void*)&contador_2);
	ptda_afirmar(elementos_recorridos == CANT_INSERCION && contador_2 == (CANT_INSERCION/2 + CANT_INSERCION%2), "Se puede recorrer correctamente una lista con "STRING_CANT_INSERCION" elementos");

	lista_destruir(lista);
}

void probar_lista(){
	int *valor;

	valor = crear_valores_insertar();
	if(!valor)
		return;
	
	ptda_nuevo_grupo("Pruebas: operaciones");
	probar_crear_lista();
	probar_insertar_lista(valor);
	probar_eliminar_lista(valor);
	
	ptda_nuevo_grupo("Pruebas: información");
	probar_buscar_lista(valor);
	probar_esta_vacia_lista(valor);
	probar_cantidad_elementos_lista(valor);
	probar_mostrar_con_funcion_lista(valor);

	free(valor);
}


//-----------------------------------------------------------------ITERADOR

void probar_crear_iterador(int *valor){
	lista_t* lista;
	lista_iterador_t* iterador;

	lista = lista_crear();
	
	ptda_nuevo_subgrupo("Creación - iterador");

	ptda_afirmar(!lista_iterador_crear(NULL), "No se puede crear un iterador con una lista nula");
	
	iterador = lista_iterador_crear(lista);
	ptda_afirmar(iterador, "Se puede crear un iterador con una lista vacía");
	ptda_subafirmar_fin(iterador && iterador_inicializado_valido(iterador, lista), "El iterador está con sus campos correctamente inicializados");

	lista_iterador_destruir(iterador);
	
	insertar_elementos_lista(valor, lista, 1, lista_insertar);
	iterador = lista_iterador_crear(lista);
	ptda_afirmar(iterador, "Se puede crear un iterador con una lista que contiene un elemento");
	ptda_subafirmar_fin(iterador && iterador_inicializado_valido(iterador, lista), "El iterador está con sus campos correctamente inicializados");
	lista_iterador_destruir(iterador);

	reiniciar_lista(lista);
	insertar_elementos_lista(valor, lista, CANT_INSERCION, lista_insertar);	
	iterador = lista_iterador_crear(lista);
	ptda_afirmar(iterador, "Se puede crear un iterador con una lista que contiene muchos elementos");
	ptda_subafirmar_fin(iterador && iterador_inicializado_valido(iterador, lista), "El iterador está con sus campos correctamente inicializados");
	lista_iterador_destruir(iterador);
	
	lista_destruir(lista);
}

void probar_tiene_siguiente_iterador(int *valor){
	lista_t* lista;
	lista_iterador_t* iterador;

	lista = lista_crear();
	
	ptda_nuevo_subgrupo("Tiene siguiente - iterador");

	ptda_afirmar(!lista_iterador_tiene_siguiente(NULL), "Un iterador de una lista nula no tiene siguiente");
	
	iterador = lista_iterador_crear(lista);
	ptda_afirmar(!lista_iterador_tiene_siguiente(iterador), "Un iterador de una lista vacía no tiene siguiente");
	lista_iterador_destruir(iterador);
	
	insertar_elementos_lista(valor, lista, 1, lista_insertar);
	iterador = lista_iterador_crear(lista);
	ptda_afirmar(lista_iterador_tiene_siguiente(iterador), "Un iterador de una lista con un elemento tiene siguiente");
	lista_iterador_destruir(iterador);

	reiniciar_lista(lista);
	insertar_elementos_lista(valor, lista, CANT_INSERCION, lista_insertar);	
	iterador = lista_iterador_crear(lista);
	ptda_afirmar(lista_iterador_tiene_siguiente(iterador), "Un iterador de una lista con varios elementos tiene siguiente");
	lista_iterador_destruir(iterador);
	
	lista_destruir(lista);
}

void probar_avanzar_iterador(int *valor){
	lista_t* lista;
	lista_iterador_t* iterador;
	
	lista = lista_crear();
	
	ptda_nuevo_subgrupo("Tiene siguiente - iterador");

	ptda_afirmar(!lista_iterador_avanzar(NULL), "No se puede avanzar un iterador de una lista nula");
	
	iterador = lista_iterador_crear(lista);
	ptda_afirmar(!lista_iterador_avanzar(iterador), "No se puede avanzar un iterador de una lista vacía");
	lista_iterador_destruir(iterador);
	
	insertar_elementos_lista(valor, lista, 1, lista_insertar);
	iterador = lista_iterador_crear(lista);
	ptda_afirmar(!lista_iterador_avanzar(iterador), "No se puede avanzar un iterador de una lista con un elemento");
	lista_iterador_destruir(iterador);

	reiniciar_lista(lista);
	insertar_elementos_lista(valor, lista, 2, lista_insertar);	
	iterador = lista_iterador_crear(lista);
	ptda_afirmar(lista_iterador_avanzar(iterador), "Se puede avanzar un iterador de una lista con dos elementos");
	
	ptda_afirmar(!lista_iterador_avanzar(iterador), "No se puede avanzar por segunda vez un iterador de una lista de dos elementos");
	lista_iterador_destruir(iterador);

	reiniciar_lista(lista);
	insertar_elementos_lista(valor, lista, CANT_INSERCION, lista_insertar);	
	iterador = lista_iterador_crear(lista);
	ptda_afirmar(iterador && puedo_avanzar_iterador(&iterador, CANT_INSERCION-1), "Se puede avanzar "STRING_CANT_INSERCION_MENOS_1" veces un iterador de una lista con "STRING_CANT_INSERCION" elementos");
	
	ptda_afirmar(!lista_iterador_avanzar(iterador), "No se puede avanzar por "STRING_CANT_INSERCION" vez un iterador de una lista con "STRING_CANT_INSERCION" elementos");
	lista_iterador_destruir(iterador);

	lista_destruir(lista);
}

void probar_obtener_elemento_iterador(int* valor){
	void* elemento;
	lista_t* lista;
	lista_iterador_t* iterador;

	lista = lista_crear();

	ptda_nuevo_subgrupo("Obtener elemento - iterador");

	ptda_afirmar(!lista_iterador_elemento_actual(NULL), "No se puede buscar el elemento de un iterador de una lista nula");

	iterador = lista_iterador_crear(lista);
	ptda_afirmar(!lista_iterador_elemento_actual(iterador), "No se puede buscar el elemento de un iterador de una lista vacía");
	lista_iterador_destruir(iterador);

	insertar_elementos_lista(valor, lista, 1, lista_insertar);
	iterador = lista_iterador_crear(lista);
	elemento = lista_iterador_elemento_actual(iterador);
	ptda_afirmar(elemento, "Se puede buscar el elemento de un iterador de una lista de un elemento");
	ptda_subafirmar_fin(elemento == &(valor[0]), "El valor del elemento buscado en el iterador es correcto");
	lista_iterador_destruir(iterador);

	reiniciar_lista(lista);
	insertar_elementos_lista(valor, lista, CANT_INSERCION, lista_insertar);
	iterador = lista_iterador_crear(lista);
	elemento = lista_iterador_elemento_actual(iterador);
	ptda_afirmar(elemento, "Se puede buscar el elemento de un iterador de una lista de muchos elementos");
	ptda_subafirmar_fin(elemento == &(valor[0]), "El valor del elemento buscado en el iterador es correcto");
	lista_iterador_destruir(iterador);

	iterador = lista_iterador_crear(lista);
	puedo_avanzar_iterador(&iterador, CANT_INSERCION-1);
	elemento = lista_iterador_elemento_actual(iterador);
	ptda_afirmar(elemento, "Se puede buscar el elemento de un iterador que avancé "STRING_CANT_INSERCION_MENOS_1" veces");
	ptda_subafirmar_fin(elemento == &(valor[CANT_INSERCION-1]), "El valor del elemento buscado en el iterador es correcto");
	
	puedo_avanzar_iterador(&iterador, 1);
	elemento = lista_iterador_elemento_actual(iterador);
	ptda_afirmar(!elemento, "No se puede buscar el elemento de un iterador que avancé "STRING_CANT_INSERCION" veces");
	lista_iterador_destruir(iterador);

	lista_destruir(lista);
}

void probar_iterador(){
	int *valor;

	valor = crear_valores_insertar();
	if(!valor)
		return;
	
	ptda_nuevo_grupo("Pruebas: operaciones");
	probar_crear_iterador(valor);
	probar_avanzar_iterador(valor);

	ptda_nuevo_grupo("Pruebas: información");
	probar_tiene_siguiente_iterador(valor);
	probar_obtener_elemento_iterador(valor);

	free(valor);
}

//-------------------------------------------------------------------

int main(){
	
	ptda_nueva_categoria("Pruebas lista");
	probar_lista();

	ptda_nueva_categoria("Pruebas iterador");
	probar_iterador();

	ptda_mostrar_reporte();
}