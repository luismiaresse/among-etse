/// Archivo con funciones comunes a las clases

#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include "config.h"
#include "grafo.h"
#include "abb.h"
#include "colors.h"

// Para el algoritmo de Floyd-Warshall. Sobreescribe la definición de math.h.
#ifdef INFINITY
#undef INFINITY
#endif
#define INFINITY 10000
#define MAXCHAR 40                          // Máximo número de caracteres
#define MINPLAYERS PROPORTION              // Número mínimo de jugadores (ligado a la proporción)



/**
 * Función para inicializar los datos de un jugador, necesaria en varias funciones públicas
 * @param *registro
 */
void inicializarJugador(tipoelem * registro);

/**
 * Función que genera un número aleatorio entre inf y sup
 * @param inf
 * @param sup
 * @return valor aleatorio
 */
unsigned int aleatorio(int inf, int sup);

/**
 * Imprime las tareas de un jugador
 * @param *tareas
 */
void imprimirTareas(cola *tareas);

/**
 * Imprime una tarea
 * @param t
 */
void imprimirTarea(tipoelemcola t);

/**
 * Imprime los datos de un jugador
 */
void imprimirJugador(tipoelem j, char opt);

/**
 * Copia la cola de la fuente al destino (con distinta dirección de memoria) y opcionalmente imprime la tarea
 */
void copiarCola(cola src, cola * dest, char opt);

/**
 * Recorre el árbol de forma inorden (IRD) con capacidad para imprimir todos los jugadores o por habitación
 */
void imprimirArbol(abb A, char opt, const char * hab);

/**
 * Devuelve la distancia mínima entre dos vértices y el vértice siguiente que se tiene que recorrer. FLAG: 1 imprime el camino, 0 no
 */
int distanciaMinima(grafo G, tipovertice orig, tipovertice dest, tipovertice *siguiente, int *costesig, char rol, char flag);

/**
 * Permite pedir una habitación del mapa
 */
char * pedirHabitacion(grafo G);

/**
 * Función que crea una carpeta si no existe
 */
int crearCarpeta(const char *carpeta);

#endif //COMMON_H
