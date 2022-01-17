/// Archivo con funciones para jugar

#ifndef AEPLAY_H
#define AEPLAY_H
#include "common.h"

/**
 * Genera una nueva partida, asignando valores aleatorios a cada jugador
 * @param U     Árbol de usuarios
 * @param *J    Puntero a un árbol de jugadores
 * @param G     Mapa
 */
void generarPartida(abb U, abb *J, grafo G);

/**
 * Genera y ejecuta la partida
 * @param A
 * @param G
 */
void jugarPartida(abb A, grafo G);


#endif //AEPLAY_H
