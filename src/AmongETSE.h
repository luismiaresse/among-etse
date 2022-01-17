/// Archivo principal

#ifndef AMONGETSE_H
#define AMONGETSE_H

#include "common.h"

/**
 * Menú principal del juego
 * @param *arbol
 * @param *mapa
 */
void AmongETSE(abb *arbol, grafo *mapa);

/**
 * Lee un archivo de jugadores de un fichero
 * @param *A
 */
void leerArchivo(abb *A);

/**
 * Inserta un nuevo jugador en el árbol
 * @param *A
 */
void altaJugador(abb *A);

/**
 * Elimina un jugador en el árbol
 * @param *A
 */
void bajaJugador(abb *A);

/**
 * Imprime en inorden (alfabético) los nodos del árbol
 * @param A
 */
void listadoJugadores(abb A);

/**
 * Consulta los datos de un jugador
 * @param A
 */
void consultarJugador(abb A);

/**
 * Consulta los jugadores que hay en una habitación
 * @param A
 * @param G
 */
void consultarPorHabitacion(abb A, grafo G);

/**
 * Guarda los nombres de la partida en archivo
 * @param A
 */
void guardarJugadores(abb A);




#endif    // AMONGETSE_H

