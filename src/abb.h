#ifndef ABB_H
#define ABB_H

#include "cola.h"

/**
 * Tipo de dato abstracto para árbol binario con clave de
 * ordenación y elemento de celda.
 */

typedef char * tipoclave;

typedef struct{
    char nombre[MAXCHAR];       // Nombre de jugador (clave primaria)
    char rol;                   // Tipo de jugador
    char ubicacion[MAXCHAR];    // Ubicación actual
    char siguiente[MAXCHAR];    // Habitación a la que se dirige
    cola tareas;                // Cola de tareas
    ushort costeHab;            // Coste de pasos restante para llegar a la siguiente habitación
    ushort costeTar;            // Coste de pasos restante para terminar la tarea actual
    ushort matar;               // Booleano que dice si puede o no matar tripulantes
}tipoelem;

typedef struct celda * abb;     // Tipo opaco

/////////////////////////////// FUNCIONES

//FUNCIONES DE CREACIÓN Y DESTRUCCIÓN DEL ÁRBOL
/**
 * Crea el arbol vacio.
 * @param A Puntero al arbol. Debe estar inicializado.
 */
void crear(abb *A);

/**
 * Destruye el arbol recursivamente
 * @param A El arbol que queremos destruir
 */
void destruir(abb *A);

//FUNCIONES DE INFORMACIÓN
/**
 * Comprueba si el arbol esta vacio
 * @param A El arbol binario
 */
unsigned es_vacio(abb A);

/**
 * Devuelve el subarbol izquierdo de A
 * @param A - Arbol original
 */
abb izq(abb A);
/**
 * Devuelve el subarbol derecho de A
 * @param A - Arbol original
 */
abb der(abb A);
/**
 * Recupera la informacion de la celda de la raiz del arbol
 * @param A
 * @param E Puntero al nodo que apuntara a la informacion
 */
void leer(abb A, tipoelem *E);

/**
 * Comprueba si el elemento <E> existe en el arbol <A>
 * @param A
 * @param E
 */
unsigned es_miembro(abb A, tipoelem E);

/**
 * Busca un nodo con clave <cl> en el arbol y, si existe
 * modifica el puntero <nodo> para que lo apunte.
 * @param A Arbol binario en el que se busca el nodo.
 * @param cl Clave que se buscara.
 * @param nodo Puntero a un tipoelem.
 */
void buscar_nodo(abb A, tipoclave cl, tipoelem *nodo);

//FUNCIONES DE MODIFICACIÓN
/**
 * Inserta un nuevo nodo en el arbol para el elemento E
 * del que toma su clave. Esta clave no debe existir en
 * el arbol.
 * @param A Arbol binario
 * @param E Informacion del nuevo nodo.
 */
void insertar(abb *A, tipoelem E);
/**
 * Suprime el nodo del arbol <A>
 * @param A
 * @param E
 */
void suprimir(abb *A, tipoelem E);
/**
 * Busca el nodo con su clave y lo modifica.
 * @param A
 * @param nodo
 */
void modificar(abb A, tipoelem nodo);

/**
 * Función que devuelve el número de nodos del árbol.
 */
unsigned numero_nodos(abb A);

#endif	// ABB_H

