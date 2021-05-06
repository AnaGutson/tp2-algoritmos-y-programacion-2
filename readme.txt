────────────────────────────────────────────────────────────────────Convenciones────────────────────────────────────────────────────────────────────

● Las convenciones que se utilizan en el trabajo son con base en qué me parece más legible, siempre respetando el uso del ​snake_case​.

● Con respecto al código, se separa en tres partes:

...{
	declaraciones​;

	código​;

	return​;
}

En caso de no haber una de las partes, se hace lo siguiente:

● Si no hay declaraciones:
...{
	código​;

	return​;
}

● Si no hay return:
...{
	declaraciones​;

	código​;
}

● Si solo hay código:
...{

	código​;
}

● Si solo hay return:
...{

	return;
}

La razón por la que se deja un enter arriba de "código" pero no debajo es debido a que cuando se minimiza el bloque, no resulta agradable que quede una línea en blanco, ya que si hubiera un enter abajo quedaría como:
...{​░░

}

Y es preferible que quede sin el espacio:
...{​░░
}

-esto es más entendible con colores y dibujos pero no se puede, para más información consultar por privado-

Añado: Dentro de bloques de código se suele seguir la misma regla, es decir, dentro de funciones de control por ejemplo, a excepción de un caso:
En funciones recursivas, que se autoinvocan, suelo proceder de esta manera:

if(condicion){

	declaraciones;
	codigo;
	return;
}

En vez de hacer:

if(condicion){
	declaraciones;

	codigo;

	return;
}

● Y dentro de funciones, si la función recibe muchos parámetros, como se trata de respetar el uso de 80 caracteres máximo por línea, se procede de la siguiente manera:

void* funcion(int ..., char ..., double ..., size_t ..., const int ..., char* ...,
	void (*funcion)(int, int)){

	declaraciones​;

	código​;

	return​;
}

Es decir, se deja una línea de separación para que se entienda dónde comienzan las declaraciones.

● Se prefiere escribir sin corchetes si es posible, como

for(...)
	...;

o

if(...)
	...;

Tratando de respetar, siempre que sea posible, una acción por línea.

● Para escribir funciones de control, se escribe la función y al lado los paréntesis, sin dejar espacio, por ejemplo:

while(...){
	...;
}

● Para escribir un booleano (ya sea función o variable) dentro de una condición, se prefiere sin el "==", sino que con el mero nombre alcanza, y en caso de querer negarlo, un "!" antes del mismo. Por ejemplo:

while(es_rojo(tateti_suerte_pa_mi) || !termino){
	...;
}

● En caso de haber varias operaciones de comparación:
if((condicion_1 > 0) && (condicion_2 > 0))
 ➜ se respetan las buenas prácticas de cada comparación -acción- en un paréntesis, además no se dejan espacios entre el primer y último paréntesis.

● En caso de haber funciones booleanas y operaciones de comparación:
if(es_valido(condicion_1) && (condicion_2 > 0))
 ➜ las funciones no se separan entre paréntesis, se respetan las buenas prácticas de cada comparación -acción- en un paréntesis, además no se dejan espacios entre el primer y último paréntesis.

● En caso de haber funciones booleanas solamente:
if(es_valido(condicion_1) && es_valido(condicion_1))
 ➜ las funciones no se separan entre paréntesis, además no se dejan espacios entre el primer y último paréntesis.

● En caso de que haya punteros con campos:
if(((condicion_1->tata) > 0) && ...)
 ➜ toda la variable se coloca entre paréntesis, para evitar confusiones.

● Para declarar punteros, se prefiere hacerlo así
nodo_t* nodo;

En vez de:
nodo_t *nodo;
 ➜ el asterisco al lado del tipo de dato.

De la misma manera se procede en la declaración de funciones, al emplear el uso del "*" para indicar que el valor se actualizará, por ejemplo:
void batalla(juego_t* juego);

● Se prefiere escribir de precondiciones razones por las que no se podría cumplir el cometido de una función. Se procede a mostrar un ejemplo (línea 1516, entrenamiento pokemon.c):

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

En esta función se pone como pre-condición que "accion" debe ser alguna de las 4 mencionadas (LETRA_MOSTRAR_PERSONAJE, LETRA_MOSTRAR_GIMNASIOS, LETRA_CAMBIAR_PARTY o LETRA_COMENZAR_BATALLA). Sin embargo, la función admite la posibilidad de que "accion" sea algo diferente, por eso se deja el case default. Sin embargo, si eso
sucediera, no estaría cumpliendose el cometido de la función, que es accionar frente a una accion del gimnasio, ya que un valor diferente para "accion" implicaría
algo no previsto por este programa.

Es decir, las pre-condiciones son las que garantizan el funcionamiento óptimo del programa (bajo las indicaciones impuestas por el enunciado y las restricciones decididas para su
creación), no las que garantizan que no se rompa.

● Se prefiere hacer un return en medio de una función solo si es debido a que no se cumplieron las pre condiciones. También, si surge un problema al pedir memoria dinámica. El último posible caso donde se realiza un return en medio de la función es en las funciones recursivas. Sino, SOLO se realiza al final de todo, nunca se hacen varios return: gusto personal, y no cuesta nada hacerlo como gusta.

● Uso del​ ​"do while​": Para el ingreso de resulta muy práctico que vuelva a preguntar exactamente lo mismo que siempre, por eso se utiliza "do while" en vez de "while", además de que este
último implicaría repetir una línea.

● Uso del ​"if​" y del ​"switch​": En caso de tener más de dos situaciones se utiliza el "switch", sino el "if".

● Para asegurar la correcta legibilidad del código, y a consejo del anterior corrector Mauro (Algoritmos 2, corrector TP1), se ha tratado, en lo posible, de que cada línea no
supere los 80 caracteres.

● Para asegurar la correcta legibilidad del código, y a consejo del anterior corrector Nicolás (Algoritmos 1, corrector TP2), se ha tratado, en lo posible, de que no figuren "magic
numbers", sino que estén todos como constantes.

● Para asegurar la correcta legibilidad del código, y a consejo del anterior corrector Nicolás (Algoritmos 1, corrector TP2), se escribieron todas las funciones booleanas en modo
afirmativo, sin importar que siempre sean usadas en modo de negación.

● Ya que la extensión de archivo no simboliza nada (según Lucas -vos-), se ha desistido de chequear la extensión de cada archivo ingresado. Sin embargo, y por preferencia personal, todos los
archivos entregados son con extensión ".txt" (por gusto), aunque el programa admita cualquier extensión siempre y cuando el archivo sea de texto.

● Las constantes se tienen alineadas en grupos, así resulta más fácil organizarse. Es decir, los valores de cada una se tienen a la misma altura solo si son del mismo grupo. Por ejemplo:

#define LEER						"r"
#define ESCRIBIR					"w"

#define EXITO			 0
#define ERROR			-1

● Si solo hay números, en el grupo de constantes, se tratará de ordenar de la siguiente manera:

#define MAX_CANT_POKEMONES_COMBATE		  6
#define MAX_NOMBRE_POKEMON				 21
#define CANT_TIPOS_POKEMONES			 18
#define MAX_TIPO						 50
#define MAX_MASA						 50
#define EBULLICION_AGUA					100

Es decir, respetando una posición para la unidad, otra para la decena, otra para la centena... (ordenamiento por dígito).

● En cambio, si están los números mezclados con otra cosa, se tratará de ordenar de la siguiente manera:

#define FORMATO_GIMNASIO					"%100[^;];%5i;%5i\n"
#define CANT_FORMATO_GIMNASIO				3
#define MAX_NOMBRE_GIMNASIO					101
#define MAX_DIGITOS_DIFICULTAD_GIMNASIO		6

Es decir, simplemente con "tabs" y sin respetar posiciones de unidades.

● Sobre la declaración de la mayoría de las funciones a lo largo del programa, se ha escrito un:
/* número */
El número simboliza la cantidad de líneas que contiene dicha función: la política interna es no superar las 20 líneas en lo posible, a partir de ahí se tiene cuidado y se
intenta modularizar. El límite son 40 líneas, no hay funciones de más de dicha cantidad de líneas, a excepción de las que evalúan posibilidades, como:
int buscar_primera_posicion_tipo_en_supereficacia(int posicion, int* cantidad)
la cual posee 79 líneas.

● Las funciones en cada archivo están separadas por categoría, y dentro de la categoría por tipo de retorno: resulta más cómodo.

● Los colores a lo largo del programa fueron elegidos adrede: la paleta de colores se basa en CELESTE y AMARILLO, aunque hay algunos otros como el ROJO_FUERTE para indicar errores en
los ingresos o sucesos malos, o VERDE_FUERTE para indicar el éxito a lo largo de la ejecución.

● Para la creación de pruebas se eligieron los colores adrede, de la misma forma que para el programa: las fallas en ROJO_FUERTE mientras que las pruebas aprobadas en VERDE_FUERTE.

● Los colores pueden tener un "_FUERTE" o un "_SUAVE" en su nombre: simboliza si se engrosa la letra o no.

● Se lamenta la fealdad del título, luego de horas tratando de encontrar uno lindo, no se pudo.

● Se ha tratado de solucionar todos los posibles problemas de compilación que puedas tener, recordando la experiencia con el TP pasado. Esto se ha hecho mediante el uso del comando:
"cppcheck --enable=all *.c" (consejo cortesía del compañero Borja).

● Se ha reutilizado una animación de El Señor De Los Anillos ya que no se han tenido ni tiempo ni ganas de actualizarla poniendo un dibujito de un pokémon. Igualmente, se cree que no es necesario, ya que es sólo simbólico.

● Se exhorta usar el programa en pantalla completa, sino no se podrá asegurar la correcta visualización del mismo (y si no se está leyendo esto en pantalla completa, se exhorta a hacerlo, y en Sublime, de ser posible).


─────────────────────────────────────────────────────────────────────────Entrega─────────────────────────────────────────────────────────────────────────


La entrega de este trabajo práctico consiste en:
	● cuatro bibliotecas de tipos de datos abstractos (nodo, lista, pila y heap), incluyendo los .c, cada una con sus respectivas pruebas;
	● un archivo para visualizar las pruebas efectuadas ("ptda.h");
	● cuatro bibliotecas de las estructuras del juego (pokemon, entrenador, gimnasio y personaje), incluyendo los ".c";
	● una biblioteca donde se encuentra la parte gráfica del programa (interfaz_grafica), incluyendo su ".c";
	● una biblioteca donde se encuentran las funciones generales usadas a lo largo de la materia (funciones_generales), incluyendo su ".c";
	● muuuchos archivos de gimnasios, cortesía del compañero Martín Fraile.


─────────────────────────────────────────────────────────────────Pruebas del TDA─────────────────────────────────────────────────────────────────


En este trabajo se entregan tres archivos de pruebas.

Dentro de las pruebas, se valida que cada función del TDA funcione tal como corresponde: para esto, se ha decidido asumir que todas las funciones del TDA andan menos la que se está probando (previamente preguntado en clase si se podía proceder así).

Las pruebas están divididas (visualmente) en "categoría", "grupo" y "subgrupo": la categoría es el tipo de TDA a probar, el grupo es de qué van a ser las pruebas (información del TDA o operaciones en el mismo), y el subgrupo es sobre qué función del TDA se está probando.

Las pruebas principales empiezan con la situación actual, seguida de "Se puede" o "No se puede": es por gusto personal.

Para las pruebas relacionadas con una prueba anterior, se decidió ponerlo como "subprueba".

Para las pruebas que devuelven la misma información, se decidió poner el mismo texto.

Es posible que dentro de cada prueba capaz se vuelva a validar lo mismo que lo anterior y algo más.


──────────────────────────────────────────────────────────Ejecución Pruebas TDAs──────────────────────────────────────────────────────────


Para ver el funcionamiento de las pruebas sobre un TDA hay que compilar todos los .c correspondientes y ejecutar lo compilado.

La línea de compilación recomendada es:
gcc funciones_generales.c ptda.h nodo.c "nombre_TDA".c "nombre_TDA_pruebas".c -o NOMBRE_TDA -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

● Si se quiere compilar la lista:
gcc funciones_generales.c ptda.h nodo.c lista.c lista_pruebas.c -o lista -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

● Si se quiere compilar la pila:
gcc funciones_generales.c ptda.h nodo.c pila.c pila_pruebas.c -o pila -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

● Si se quiere compilar el heap:
gcc funciones_generales.c ptda.h nodo.c heap.c heap_pruebas.c -o heap -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

Es decir, se quieren compilar los .c con todos los warnings posibles, leyendo estos como error, y mostrando todas las conversiones que pueden generar cambios en el valor de una variable, y que el ejecutable se llame "NOMBRE_TDA" (a elección del usuario).

Para usar el TDA, basta con hacer dentro de un ".c" un "#include "TDA.h"" y ya se pueden usar sus funciones.

Para ver el uso de memoria, correr con valgrind. Se recomienda correr con: valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./NOMBRE_TDA

Antes de correr con valgrind, recordar que hay que tener el ejecutable creado.

Sino, ejecutar normal: "./NOMBRE_TDA".

-En este ejemplo se llamó "NOMBRE_TDA" al ejecutable: es irrelevante el nombre, se puede usar otro si uno lo prefiere, pero si se decide cambiarlo, recordar cambiarlo al compilar y al ejecutar (usar el mismo)-


──────────────────────────────────────────────────────────────Ejecución Programa──────────────────────────────────────────────────────────────


Objetivo:
    
    El objetivo de esta entrega es realizar un programa en el que el usuario busca convertirse en maestro pokémon (concepto del famoso "Pokémon"), con ayuda del azar, claro. Para esto, lucha contra los pokemones de los entrenadores de diversos gimnasios, hasta que venza todos los gimnasios (condecoración a maestro pokémon) o hasta que sea vencido (derrota).

Cómo compilar el programa y ejecutarlo:

    La línea de compilación recomendada es: gcc nodo.c funciones_generales.c pokemon.c entrenador.c gimnasio.c personaje.c batallas.c interfaz_grafica.c heap.c entrenamiento_pokemon.c pila.c lista.c -o juego -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

    Es decir, se quieren compilar los ".c" con todos los warnings posibles, leyendo estos como error, y mostrando todas las conversiones que pueden generar cambios en el valor de una variable, y que el ejecutable se llame "juego".

    Para ver el uso de memoria, correr con valgrind. Se recomienda correr con: valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./juego

    Antes de correr con valgrind, recordar que hay que tener el ejecutable creado (en este caso "juego").
    
    Sino, ejecutar normal: "./juego".

-En este ejemplo se llamó "juego" al ejecutable: es irrelevante el nombre, se puede usar otro si uno lo prefiere, pero si se decide cambiarlo, recordar cambiarlo al compilar y al ejecutar (usar el mismo).-


──────────────────────────────────────────────────────────────────Uso de los TDA──────────────────────────────────────────────────────────────────


Cada forma de almacenar datos fue planificada, ya que a lo largo de la materia se estudió las diferencias entre cada forma (estática, dinámica, y diferentes TDAs). A continuación, se
explicará cada decisión tomada.


    ●    Pokemones de batalla del entrenador: LISTA - MEMORIA DINÁMICA

Se ha tomado la decisión de que los pokemones de los entrenadores sean guardados en una lista dinámica, debido a varias razones, entre ellas, la facilidad que genera a la hora de consultar la cantidad de pokemones que posee, si está vacía o no, y qué pokémon está en cierta posición.
La pregunta es: si son siempre menos de 6 pokemones, ¿por qué no usar un vector? La respuesta radica en el uso de memoria: el entrenador podría tener menos de seis pokemones, en dicho caso, al declarar un vector de 6 posiciones, se perdería memoria. Esa memoria sería totalmente desperdiciada, ya que la cantidad de pokemones del entrenador nunca va a cambiar a lo largo del programa.
Es por lo mencionado anteriormente, que se decidió utilizar un tipo de dato adaptable a la cantidad, optimizando al máximo el uso de memoria.


    ●    Entrenadores del gimnasio: PILA - MEMORIA DINÁMICA

Se ha tomado la decisión de que los entrenadores del gimnasio sean guardados en una pila dinámica, debido principalmente a que pueden ser ingresados infinitos entrenadores (por eso en memoria dinámica). Además de que el profesor Manuel recomendó el uso de pila en una clase, se ha usado ya que siempre se necesita acceder solamente al último valor guardado. El único momento a lo largo del programa que se engaña la lógica de la pila es cuando se recorren los entrenadores y se muestran, lo cual se hace mediante una función recursiva.


    ●    Pokemones totales del personaje: LISTA - MEMORIA DINÁMICA

Se ha tomado la decisión de que los pokemones del personaje sean guardados en una lista dinámica, debido a varias razones:
    - Se pueden ingresar infinitos pokemones (teóricamente) y por eso se guardan en memoria dinámica.
    - Se tiene mucha facilidad a la hora de consultar la cantidad de pokemones que posee, si está vacía o no, y qué pokémon está en cierta posición.


    ●    Pokemones de batalla del personaje: VECTOR - MEMORIA DINÁMICA

Se ha tomado la decisión de que los pokemones de batalla del personaje sean guardados en un vector estático (no es la realidad del vector), ya que al ser usado como un contenedor auxiliar
(el principal es la "caja"), es mucho más práctico su uso de esta forma. Además, a diferencia de la lista de pokemones de los entrenadores, se puede modificar su contenido a lo largo del juego (cambiando el party o agregando pokemones a medida que se gana una batalla contra un entrenador), por lo cual es mejor manejar los datos con un vector en vez de una lista: su contenido no es fijo pero tiene un máximo.
Se pensó estático ya que al tener un tamaño fijo, sería impráctico guardarlo en la memoria dinámica.
Igualmente, teniendo en cuenta toda la anterior consideración, se hizo dinámico, para que se evalúe el uso de datos en la memoria dinámica. Pero quería dejarse sentado el por qué originalmente se hizo estático y por qué, se sigue creyendo, hubiera sido mejor de esa forma.


●    Gimnasios del juego: HEAP MINIMAL- MEMORIA DINÁMICA

Los gimnasios del juego son almacenados en un heap por enunciado, no había elección. Igualmente, esta elección de tipo de dato es sumamente válida: se requiere la utilización solamente del gimnasio "menor", por lo que el requerimiento cumple a la perfección con el uso de heap.


────────────────────────────────────────────────────────────Desarrollo del Programa────────────────────────────────────────────────────────────


La lógica del programa es en modo cascada. Al ejecutar el programa, se muestra una animación, una barra de carga y comienza el juego. Internamente, en el main, se crea una variable de tipo juego_t que va a contener la información del juego. De ahí, directamente, se invoca a la función de menú inicio, y recién se vuelve al main cuando se termine el juego.

Todos los menús tienen la misma dinámica, pero para que sea legible y entendible, se prefirió no reutilizar una misma función para todos los menús, sino que hacer una por menú. La dinámica es la siguiente: se muestra el menú (la parte visual), el cuál si está generalizado para todos los menús, se determina la acción a realizar (asegurándose que la letra ingresada sea la correcta), se realiza la acción, si la siguiente pantalla (según la acción) no es el menú actual se muestra una barra de carga, y por último, se va a la siguiente pantalla. Así con cada menú. Es por esto, que es en cascada, a excepción de las acciones, que son invocadas y al finalizarse la acción, se vuelve a donde fueron invocadas, no se invoca una nueva función.

Si el usuario se encuentra en el menú de derrota, además, verá un texto que busca ayudarle a ganar la batalla, si decide reintentarla. 

Para más información sobre los menús, ir a "ANEXO 1: MENÚ".

Cada menú tiene entre 2 y 4 acciones posibles, para más información, ir a "ANEXO 2: ACCIONES".

El juego tiene tres campos:

	- Heap: donde se guardaran el o los gimnasios a usar a lo largo del juego;
	- Personaje: donde se guardará la información del personaje;
	- Gimnasio Actual: donde se irá actualizando el gimnasio actual contra el que se está batallando.

Respecto a las estructuras del juego:

	- El personaje, jugador, tiene un lugar donde guardar todos sus pokemones (caja), y otro donde van los que combaten (party). Los pokemones del party también están en la caja.
	- Cada gimnasio, donde competirá el jugador, tiene un líder, y puede tener entrenadores. Cada entrenador tiene hasta 6 pokemones.

Además, tiene dos formas de jugarse: dinámicamente o simulando un juego, sin interacción por parte del usuario.

Se juega combatiendo contra gimnasios (del más fácil al más difícil), batallando contra los entrenadores de cada gimnasio hasta llegar al líder.

Cada partida es única ya que cada pokémon posee tres características totalmente random: su tipo, su color y su masa; y al usar esas características para las batallas (para más información ir a "ANEXO 3: BATALLAS"), el juego es más estratégico: mientras el usuario va jugando, tiene que decidir qué pokemones le conviene tener en su party. 

Al finalizar, se libera toda la memoria utilizada, y se termina el juego, mostrando el resultado con ascii art.


──────────────────────────────────────────────────────────────────────────Teoría──────────────────────────────────────────────────────────────────────────


─────────────────────────────────────────────────────────────────¿Qué es un TDA?


TDA hace referencia a Tipo de Dato Abstracto. Un Tipo de Dato Abstracto en programación se le considera al modelo que define valores y operaciones que se pueden realizar sobre él. Se crea una biblioteca con una o varias estructuras relacionadas a este tipo de dato, buscando que quien lo utilice no necesite conocer internamente cómo funciona: necesita saber qué hace, no cómo se hace. A este concepto se lo conoce como "caja blanca".

Se le llama abstracto ya que se busca concentrarse solo en lo que se necesita e importa a la hora de implementarlo.

El objetivo de usar un TDA es poder proveer de mayor flexibilización a la hora de programar: si una parte cambia, las demás no se ven afectadas. Esto nos lo brinda la abstracción.

Además, algo muy importante, al menos para mi, es que el usuario al no tener acceso al código, no puede romperlo, sabemos que la parte interna del mismo estará bien en todo momento, los casos bordes solo pueden ser generados por los parámetros recibidos en cada función.

En esta entrega, están "abb.c" junto a "abb.h", los cuales nos brindan las funciones necesarias para poder usar un árbol binario de búsqueda. Lo ideal es que el usuario reciba el .h y un .o para utilizarlo, sin nada más.

Lista, Pila, Nodo y Heap son tipos de TDA.


───────────────────────────────────────────────────────¿Qué es un Árbol Binario?


Un árbol binario (AB) es un tipo de dato abstracto, cuya idea es la siguiente: dentro de la misma, hay nodos, cada uno con la siguiente información: su nodo izquierdo y su nodo derecho. Solo está relacionado con dos nodos (por eso "binario"). Justamente, de esta forma las búsquedas ya no son lineales y se genera una menor complejidad del código.

Cada nodo del árbol, además es la raíz de un árbol binario.

Cuando un nodo no tiene relación con otros subnodos, se lo denomina "nodo hoja".

El árbol binario puede estar o no equilibrado: en el peor de los casos, actúa como una lista enlazada.

Mientras que un árbol tiene bastantes desventajas, entre ellas que no podemos buscar fácilmente información en él: pues no está ordenado, también posee sus ventajas, y más al compararlo con una lista: recorrerlo es mucho menos complejo.

Además, otra desventaja de este tipo de dato es que se trabaja con punteros y memoria dinámica, lo cual incrementa la dificultad de programarlos.

Las operaciones de un árbol binario son:
● Creación.
● Inserción (en cualquier lugar).
● Eliminación (en cualquier lugar).
● Búsqueda.
● Recorrido.
● Está vacío.
● Destrucción.

Un ejemplo sería:
                    
                  ________90__________
            _____0_____            _____91_____    
            1            6__        9          __0__
                            2            90        18
                    
Este concepto se extrapola a uno nuevo que es el recreado en este trabajo: un heap.


────────────────────────────────────────────────────────────────¿Qué es un Heap?


Un heap es un tipo de dato abstracto del tipo árbol binario.

Lo que caracteriza a este tipo de árbol es:

    - Todas sus hojas se sitúan en los dos últimos niveles del mismo: es casi completo.
    - Los niveles se van llenando de derecha a izquierda.
    - En su antepenúltimo nivel existe a lo sumo un nodo con un solo hijo, que será su hijo izquierdo.
    - El elemento almacenado en un nodo cualquiera es menor/mayor (según el tipo de Heap) o igual que los elementos de sus nodos hijos.
    - No hay relación de orden entre nodos hermanos.

Las operaciones de un heap son:

    - Creación.
    - Heapify.
    - Búsqueda Máximo/Mínimo.
    - Inserción.
    - Extracción Máximo/Mínimo.
    - Eliminación Máximo/Mínimo.
    - Fusión.
    - Unión.
    - Cantidad de elementos.
    - Está vacío.

Las utilizadas en este trabajo son:

    - Creación.
    - Inserción.
    - Eliminación de raíz.
    - Visualización de raíz.
    - Destrucción.


─────────────────────────────────────¿Por qué el heap se crea con un destructor?


Cuando el usuario crea un heap, puede decidir si lo hace con un destructor o no. Si lo hace sin, tendrá que encargarse de los elementos que insertó en el árbol después de que el mismo se destruya; en cambio, si el árbol tiene destructor, al borrarse cada nodo con su respectivo elemento, se invocará al destructor para que se actúe de determinada manera con el elemento.

La ventaja de tener un destructor es que al finalizar el uso del ABB no hay que preocuparse por los elementos. Sin embargo, no podremos reutilizarlos tan fácilmente en otro árbol: se debe recordar que han sido cambiados de alguna forma por el destructor.

Un Heap generalmente trabaja con elementos cuya memoria está reservada en el heap (memoria dinámica): esto amplifica la cantidad de datos con los que se puede trabajar, al saber que no se necesita espacio contiguo de memoria y prácticamente se tiene infinita memoria.

Se sabe que para poder reservar espacio para un elemento en la memoria dinámica, hay que solicitarlo al sistema. Del mismo modo, hay que avisarle al sistema cuando queremos que libere esa memoria.

De ahí surge tener un destructor en el árbol: cuando se inserta un elemento en el árbol, hay que preocuparse solamente por la reserva de memoria para el elemento (en palabras básicas, nos alcanza con hacer un simple "malloc()"): el TDA se encarga de la liberación de la memoria reservada para el mismo.

Es entonces que se decide crear un Árbol Binario de Búsqueda con o sin destructor: si se quiere utilizar el elemento solo en ese Heap, y luego, al eliminar el árbol, que se elimine el elemento, creamos el árbol con el destructor. Sino, no.

En el caso de tener elementos almacenados en la memoria estática (stack), el destructor se utiliza para un fin muy similar, pero sin liberar la memoria. Por ejemplo, reiniciando los elementos (booleanos en "false", números a 0, char = '\0', etc).

Se presenta el mismo dilema: el usuario creará un árbol con un destructor si desea no tener que hacerse problemas por el reinicio de los elementos. Si necesita utilizar los datos para otra cosa, no podrá hacerlo tan fácilmente una vez invocado el destructor para dicho elemento.


──────────────────────────────────────────────────────────────────────────Anexos──────────────────────────────────────────────────────────────────────────


───────────────────────────────────────────────────────────────────Anexo 1: Menú

Los menús usados a lo largo del programa son:


	● El Menú Inicio.

Es el primero de todos los menús. Ahí se carga toda la información del juego.

Las acciones posibles son:

		- Cargar Personaje.
		- Cargar Gimnasio.
		- Comenzar Partida.
		- Simular Partida.


	● El Menú Gimnasio.

Es el menú del gimnasio actual, ahí se elige combatir. 

Las acciones posibles son:

		- Mostrar Personaje.
		- Mostrar Gimnasio.
		- Cambiar Party.
		- Comenzar Batalla.


	● El Menú Victoria Con Tomar Prestado.

Es el menú al que se va si uno obtiene la victoria en la batalla, pero quedan gimnasios en los que combatir. 

Las acciones posibles son:

		- Tomar Prestado.
		- Cambiar Party.
		- Siguiente Gimnasio.


	● El Menú Victoria Sin Tomar Prestado.

Es el menú al que se va si uno ya tomó prestado un pokémon del líder del gimnasio vencido. 

Las acciones posibles son:

		- Cambiar Party.
		- Siguiente Gimnasio.


	● El Menú Derrota.

Es el menú al que se va si uno obtiene la derrota en la batalla, pero es la primera vez que te derrotaron en ese gimnasio. 

Las acciones posibles son:

		- Cambiar Party.
		- Reintentar.
		- Finalizar.


───────────────────────────────────────────────────────────────Anexo 2: Acciones


Las acciones posibles a ejecutar a lo largo del juego son:


	● Cargar Personaje

Se ingresará el archivo del que se quiere cargar la información del personaje.
Si ya se ha cargado información, se consultará si se desea sobreescribir, o volver al menú de inicio. Según la respuesta recibida, se liberará la memoria reservada por el personaje guardado y se sobreescribirá, o se volverá al menú.
Si en algún momento, no se puede leer el personaje, ya sea los datos de la estructura del personaje o los datos de sus pokemones, se avisará del problema, se borrará toda la información guardada y se volverá al menú.
El archivo se leerá tal cual se ingresa. No serán válidos archivos que no existan.


	● Cargar Gimnasios

Se ingresará el archivo del que se quiere cargar la información de los gimnasios. La idea es poder ingresar la cantidad de archivos que se deseen (hasta informar que se terminó de cargar archivos), y a la vez, poder tener varios gimnasios por archivo.
Si ya se ha cargado información, se consultará si se desea continuar cargando a partir de lo guardado, o se desea cargar desde cero. Según la respuesta recibida, se continuará normal, o se liberará la memoria reservada por los gimnasios guardados y se comenzará desde cero.
Si en algún momento, no se puede leer el gimnasio, ya sea los datos de la estructura del mismo, de los entrenadores o los datos de sus pokemones, se avisará del problema, se borrará toda la información guardada de ese gimnasio y se volverá al menú. Si ya se habían guardado gimnasios, estos permanecerán intactos, solo borrando el que falló.
Para leer un archivo, debe respetarse este orden:

Línea Gimnasio
Línea Líder
Línea Pokemones
//Opcional:
Línea Entrenador |_ estas dos se pueden repetir "infinitamente"
Línea Pokemones  |
//Opcional:
Línea Gimnasio... todo de nuevo.

Es decir, por cada gimnasio, al menos tiene que haber un entrenador, siendo este, el primero del gimnasio, el LIDER, no cabe otra posibilidad, y este conteniendo la cantidad de pokemones que quiera, siendo la mínima cantidad posible 1. En caso de contener más de 6, se los ignorará, y se guardará sólo estos primeros 6 pokemones.

El archivo se leerá tal cual se ingresa. No serán válidos archivos que no existan.


	● Comenzar Partida

Redirigirá al usuario al menú de gimnasios, siempre y cuando haya ingresado el archivo del personaje y de los gimnasios. 


	● Simular Partida

Invocará a la función de batalla hasta que se termine la partida.


	● Mostrar Personaje

Se mostrará el nombre del personaje y sus pokemones.


	● Mostrar Gimnasio

Se mostrará el nombre del gimnasio, sus entrenadores y sus pokemones.


	● Comenzar Batalla

Se competirá contra los pokemones de los entrenadores del gimnasio actual. Cada vez que un pokémon pierda, se pasa al siguiente:
	si el pokémon de mi personaje pierde, batallo con mi siguiente pokémon, los mismo para el entrenador oponente.
Se competirá hasta que uno de los dos no tenga "siguiente pokémon".
Los pokemones que combaten, al perder, se van al hospital a curarse. Apenas termina la batalla, ya volvieron al party y están en perfecto estado de salud.
El ganador será decidido por una batalla, la cual se ingresa mediante archivo (el id, que va de 0 a 4), y se ejecuta internamente (sin conocimiento del usuario).
Puede invocarla el juego dinámico, o el simulado: dependiendo de la situación, se interactúa con el usuario o no.
Cada vez que se comienza a batallar con un nuevo entrenador, se mostrará su información.
Por cada batalla, se mostrará información de los competidores y cómo va la batalla (un contador).


	● Tomar Prestado

Será invocada siempre y cuando se haya obtenido la victoria contra un gimnasio: su función es permitir al usuario adquirir un pokémon del líder.
Se le mostrará al usuario los pokemones a elegir, éste elegirá uno, y automáticamente se incorporará a la lista de pokemones del personaje:
	si en su party había menos de 6 pokemones, se incorporará automáticamente a la lista de pokemones para batallar.


	● Cambiar Party

Permitirá al usuario cambiar los pokemones con los que va a batallar.
Se le mostrará al usuario los pokemones que tiene, y cuáles están en su party, éste tendrá que ingresar los 6 nuevos que quiere en su party, y automáticamente se incorporarán a la misma.
Se le mostrará al usuario cómo se redistribuyeron los pokemones.
Si el personaje no tiene suficientes pokemones como para elegir con cuál pelear y con cuál no, no se podrá realizar la acción.


	● Siguiente Gimnasio

Actualiza los valores del gimnasio actual, siendo las posibilidades que este sea nulo o que contenga un gimnasio válido. Si es nulo, le informa al usuario que es un maestro pokémon (y uno muy bueno, la verdad), sino, lo redirige al menú de gimnasios. 


	● Reintentar

Permite batallar de nuevo, aunque sabiendo que si se sufre la derrota, no hay forma de salvarse: el juego está perdido.


	● Reintentar

Informa al usuario de que ha fracasado en su intento de ser un maestro pokémon.


───────────────────────────────────────────────────────────────Anexo 3: Batallas


Las batallas pueden ser sobre:


	● FUNCION_SUENA_CHETO

Analiza el pokémon cuyo nombre tiene más letras y tiene un color que vale más puntos (implementado con vector de colores y puntos por color).


	● FUNCION_TRABALENGUAS

Analiza el pokémon cuyo nombre tiene más consonantes y cuyo tipo tiene más consonantes.


	● FUNCION_MOMENTO_LINEAL

Analiza el pokémon cuyo valor de masa por su velocidad es mayor.


	● FUNCION_EFICACIA_PELEA

Analiza el pokémon que pelea mejor (su defensa menos el ataque del contrincante).


	● FUNCION_TIPO_POKEMON

Analiza si hay algún pokémon supereficaz contra el otro, y si no, analiza los puntos del pokémon por tipo.


─────────────────────────────────────────────────────────────────AGRADECIMIENTOS


Esta sección es para agradecerte a vos, como corrector por ayudarme siempre, aún pensando que no eras mi corrector, por solucionar todas mis dudas, y aunque no te pregunte, explicarme cosas con + de 70 mensajes.

Además, para agradecer a varios compañeros que me ayudaron a encontrar errores a la madrugada, a lo largo, no solo del TP, sino que del cuatrimestre, como los compañeros Rosario, "Patineta", Mateo B., Joaco S., Agus B. y Borja.

En especial, luego de que al terminar el juego, compilé, ejecuté y tenía, como dijo un compañero, Indiana Jones y el Bloque Perdido: 

HEAP SUMMARY:
==10220==	  in use at exit: 4 bytes in 1 blocks
==10220==	total heap usage: 67 allocs, 66 frees, 16,436 bytes allocated

Y al segundo un compañero, Mateo, me dijo cuál era el problema, sino hubiera estado debuggeando por horas.

Y bueno, agradecerles por esforzarse tanto para que entendamos la materia, a vos como a todo el equipo de los profes y colaboradores.


────────────────────────────────────────────────────────────────────BIBLIOGRAFÍA


- https://www.asciiart.eu
- https://www.pokemon.com/el/pokedex
- https://www.algoritmos7541mendez.com.ar
- https://www.pokemon.fandom.com/es/wiki
- https://es.qaz.wiki/wiki/Heap_(data_structure)#Operations
- https://pokemon.fandom.com/es/wiki/Lista_de_Pok%C3%A9mon_por_tipo
- https://hablamosdegamers.com/analisis/pokemon-go-tipos-debilidades/
- http://www.patorjk.com/software/taag/#p=display&f=JS%20Stick%20Letters&t=
- https://theasciicode.com.ar/extended-ascii-code/box-drawings-double-vertical-line-character-ascii-code-186.html

______________________________________________________________________________FIN______________________________________________________________________________

