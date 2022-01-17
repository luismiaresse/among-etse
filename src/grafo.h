#ifndef GRAFO_H
#define GRAFO_H
#include "cola.h"
#include "config.h"
#include "colors.h"
/*
 * Implementación estática del TAD grafo con 2 matrices
 * de adyacencia con máximo número de vértices MAXHAB,
 */

/////////////////////////////////////////////////////////// TIPOS DE DATOS

// Tipo de dato para almacenar el coste y la descripción de una tarea. Todos los vértices apuntan al mismo espacio de memoria.
typedef struct {
    char descripcionTarea[MAXCHAR];
    ushort costeTarea;
}atribtareagrafo;

// Información que se almacena en cada vértice
typedef struct {
    char habitacion[MAXCHAR];
    atribtareagrafo tareas[MAXTASK];
    ushort numTareas;
}tipovertice;

typedef struct tipografo * grafo;

//////////////////////////////////////////////////////////////// FUNCIONES


//Creación del grafo con 0 nodos y nombre
void crear_grafo(grafo *G, char * nombre);

//Devuelve la posición del vértice Vert en el vector VERTICES del grafo G
//Si devuelve -1 es porque no encontró el vértice
int posicion(grafo G, tipovertice Vert);

//Devuelve 1 si el grafo G existe y 0 en caso contrario
int existe(grafo G);

//Devuelve 1 si el vértice Vert existe en el grafo G
int existe_vertice(grafo G, tipovertice Vert);

//Inserta un vértice en el grafo
// Devuelve la posición en el que ha sido insertado el
// vértice o -1 si no se ha conseguido insertar el vértice
int insertar_vertice(grafo *G, tipovertice Vert);

//Borra un vértice del grafo
void borrar_vertice(grafo *G, tipovertice Vert);

// Crea el arco de relación entre VERTICES(pos1) y VERTICES(pos2). OPT elige si es para impostor o tripulante
void crear_arco(grafo *G, int pos1, int pos2, int valor, char opt);

// Borra el arco de relación entre VERTICES(pos1) y VERTICES(pos2). OPT elige si es para impostor o tripulante
void borrar_arco(grafo *G, int pos1, int pos2, char opt);

//Devuelve 1 si VERTICES(pos1) y VERTICES(pos2) son vértices adyacentes, -1 si es opción incorrecta. OPT elige si es para impostor o tripulante.
int son_adyacentes(grafo G, int pos1, int pos2, char opt);

//Destruye el grafo
void borrar_grafo(grafo *G);

//Devuelve el número de vértices del grafo G
ushort num_vertices(grafo G);

// Permite modificar el número de vértices del grafo
void cambiar_num_vertices(grafo G, ushort num);

//Devuelve el vector de vértices VERTICES del grafo G
tipovertice* array_vertices(grafo G);

// Devuelve el valor del arco entre los vértices v1 y v2, -1 si es opción incorrecta
int valor_arco(grafo G, int pos1, int pos2, char opt);

// Devuelve el nombre del grafo
char * nombre_grafo(grafo G);

// Permite cambiar el nombre del grafo
void cambiar_nombre_grafo(grafo G, char * nombre);

// Devuelve el no de tareas distintas del grafo
ushort num_tareas(grafo G);

// Permite modificar el número de vértices del grafo
void cambiar_num_tareas(grafo G, ushort num);

// Devuelve el vértice buscado del grafo, 1 si está y 2 si no.
int buscar_vertice(grafo G, char * hab, tipovertice *v);

void insertar_tarea_grafo(grafo *G, tipoelemcola t);

void eliminar_tarea_grafo(grafo *G, tipoelemcola t);

#endif	/* GRAFO_H */
