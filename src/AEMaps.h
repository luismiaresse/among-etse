/// Archivo con funciones de creación de mapas

#ifndef AEMAPS_H
#define AEMAPS_H
#include "common.h"
#define MAXMAPSPATH 20                      // Máximos caracteres de la ruta del mapa



//FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS
//Opción a del menú, introducir un vértice en el grafo
void introducir_vertice(grafo *G);

//Opción b del menú, eliminar un vértice del grafo
void eliminar_vertice(grafo *G);

//Opción c del menú, crear una relación entre dos vértices
void nuevo_arco(grafo *G);

//Opción d del menú, eliminar una relación entre dos vértices
void eliminar_arco(grafo *G);

//Opción i del menú, imprimir el grafo
void imprimir_grafo(grafo G);

// Lee el archivo y devuelve el grafo con todos los vértices y arcos.
void leerGrafoArchivo(grafo *G, char *archivo);

// Guarda en archivo el grafo modificado. OPT = 1: guarda en mapa diferente, OPT = 0: sobreescribe el mapa.
void guardarGrafoArchivo(grafo G, char opt);

// Menú principal
void AEMaps(grafo *G);

// Pide los arcos origen y destino e imprime su distancia mínima.
void rutaMinimaEntreHabitaciones(grafo G);

// Devuelve el árbol de expansión mínimo de un grafo.
void arbolExpansionMinimo(grafo G);

// Carga el grafo de un archivo.
void cargarGrafo(grafo *G);


#endif    /* AEMAPS_H */

