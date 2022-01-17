#include "grafo.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/////////////////////////////////////////////////////////// TIPOS DE DATOS

// Estructura privada
struct tipografo {
    char nombre[MAXCHAR];               // Nombre del grafo
    struct num{                         // Estructura con campos de tamaño de diferentes aspectos (para no recalcularlos)
        ushort vertices;                       // Número de vértices del grafo
        ushort tareas;                       // Número de tareas del grafo
    }num;
    tipovertice VERTICES[MAXHAB];  // Vector de vértices
    ushort AT[MAXHAB][MAXHAB];   // Matriz de adyacencia de tripulantes
    ushort AI[MAXHAB][MAXHAB];   // Matriz de adyacencia de impostores
};

//////////////////////////////////////////////////////////////// FUNCIONES

//HAY QUE MODIFICAR ESTA FUNCIÓN SI SE CAMBIA EL TIPO DE DATO tipovertice
/* 
 * Esta función devuelve 0 si los dos nodos son iguales
 * -1 si V1 está antes de V2 o 1 en otro caso.
 */
int _comparar_vertices(tipovertice V1, tipovertice V2){
	return strcmp(V1.habitacion, V2.habitacion) == 0 ? 0 : strcmp(V1.habitacion, V2.habitacion) > 0 ? 1 : -1;
}

// Devuelve el nombre del grafo
char * nombre_grafo(grafo G){
    return G->nombre;
}

// Permite modificar el nombre del grafo
void cambiar_nombre_grafo(grafo G, char * nombre){
    strcpy(G->nombre, nombre);
}

// Creación del grafo con 0 nodos
void crear_grafo(grafo *G, char * nombre) {
    *G = (struct tipografo*) malloc(sizeof (struct tipografo));
    (*G)->num.vertices = 0;
    strncpy((*G)->nombre, nombre, MAXCHAR);
}

//Devuelve la posición del vértice Vert en el vector VERTICES del grafo G
//Si devuelve -1 es porque no encontró el vértice
int posicion(grafo G, tipovertice V) {
    int contador = 0;
    //comparo V con todos los vertices almacenados en VERTICES 
    while (contador < G->num.vertices) {
        //if (G->VERTICES[contador]==V)  //encontré la posicion de V
		if (_comparar_vertices(G->VERTICES[contador], V) == 0){
            return contador; 
        }
        contador++;
    }
    return -1;
}

//Devuelve 1 si el grafo G existe y 0 en caso contrario
int existe(grafo G) {
    return (G != NULL);
}

//Devuelve 1 si el vértice Vert existe en el grafo G
int existe_vertice(grafo G, tipovertice V) {
    return (posicion(G, V) >= 0);
}

//Inserta un vértice en el grafo, devuelve -1 si no ha podido insertarlo por estar el grafo lleno
int insertar_vertice(grafo *G, tipovertice Vert) {
    int i;
    if ((*G)->num.vertices == MAXHAB) {
    	// Se ha llegado al maximo numero de vertices
    	return -1;
    }
    if (existe_vertice(*G, Vert)) {
        // Reemplaza el vértice existente por el nuevo
        i = posicion(*G, Vert);
        if (i >= 0) {
            (*G)->VERTICES[i] = Vert;
        }
    } else {
        (*G)->num.vertices++;
        (*G)->VERTICES[((*G)->num.vertices) - 1] = Vert;
        for (i = 0; i < (*G)->num.vertices; i++) {
            (*G)->AT[i][((*G)->num.vertices) - 1] = 0;
            (*G)->AT[((*G)->num.vertices) - 1][i] = 0;
            (*G)->AI[i][((*G)->num.vertices) - 1] = 0;
            (*G)->AI[((*G)->num.vertices) - 1][i] = 0;
        }
    }
	return (*G)->num.vertices - 1;
}

//Borra un vertice del grafo
void borrar_vertice(grafo *G, tipovertice Vert) {
    int F, C, P, N = (*G)->num.vertices;
    P = posicion(*G, Vert);
    if(P == -1){
    	return;
    }
    //if (P >= 0 && P < (*G)->N) {
    for (F = P; F < N - 1; F++){
        (*G)->VERTICES[F] = (*G)->VERTICES[F + 1];
	}
    for (C = P; C < N - 1; C++){
        for (F = 0; F < N; F++){
            (*G)->AT[F][C] = (*G)->AT[F][C + 1];
            (*G)->AI[F][C] = (*G)->AI[F][C + 1];
        }
	}
    for (F = P; F < N - 1; F++){
        for (C = 0; C < N; C++){
            (*G)->AT[F][C] = (*G)->AT[F + 1][C];
            (*G)->AI[F][C] = (*G)->AI[F + 1][C];
        }
	}
    (*G)->num.vertices--;
}

//Crea el arco de relación entre VERTICES(pos1) y VERTICES(pos2) para grafo no dirigido (ambos estan interconectados)
void crear_arco(grafo *G, int pos1, int pos2, int valor, char opt) {
    if (opt == 'I' || opt == 'i') {
        (*G)->AI[pos1][pos2] = valor;
        (*G)->AI[pos2][pos1] = valor;
    } else if (opt == 'T' || opt == 't') {
        (*G)->AT[pos1][pos2] = valor;
        (*G)->AT[pos2][pos1] = valor;
    }
}

//Borra el arco de relación entre VERTICES(pos1) y VERTICES(pos2) para grafo no dirigido (ambos estan interconectados)
void borrar_arco(grafo *G, int pos1, int pos2, char opt) {
    if (opt == 'I' || opt == 'i') {
        (*G)->AI[pos1][pos2] = 0;
        (*G)->AI[pos2][pos1] = 0;
    } else if (opt == 'T' || opt == 't') {
        (*G)->AT[pos1][pos2] = 0;
        (*G)->AT[pos2][pos1] = 0;
    }
}

//Devuelve 1 si VERTICES(pos1) y VERTICES(pos2) son vértices adyacentes, -1 si es opción incorrecta
int son_adyacentes(grafo G, int pos1, int pos2, char opt) {
    if (opt == 'I' || opt == 'i') {
        return (G->AI[pos1][pos2]);
    } else if (opt == 'T' || opt == 't') {
        return (G->AT[pos1][pos2]);
    } else {
        return -1;
    }
}

//Destruye el grafo
void borrar_grafo(grafo *G) {
    free(*G);
    *G = NULL;
}

//Devuelve el número de vértices del grafo G
ushort num_vertices(grafo G) {
    return G->num.vertices;
}

// Permite modificar el número de vértices del grafo
void cambiar_num_vertices(grafo G, ushort num) {
    G->num.vertices = num;
}

//Devuelve el vector de vértices VERTICES del grafo G
tipovertice* array_vertices(grafo G) {
    return G->VERTICES;
}

// Devuelve el valor del arco entre los vértices v1 y v2, -1 si es opción incorrecta
int valor_arco(grafo G, int pos1, int pos2, char opt) {
    if (opt == 'T' || opt == 't') {
        return G->AT[pos1][pos2];
    } else if (opt == 'I' || opt == 'i') {
        return G->AI[pos1][pos2];
    } else {
        return -1;
    }
}

// Devuelve el número de tareas distintas del grafo
ushort num_tareas(grafo G){
    return G->num.tareas;
}

// Permite modificar el número de vértices del grafo
void cambiar_num_tareas(grafo G, ushort num) {
    G->num.tareas = num;
}

// Devuelve el índice y el vértice buscado, -1 y NULL si no existe
int buscar_vertice(grafo G, char * hab, tipovertice *v) {
    for (int i = 0; i < num_vertices(G); i++) {
        if (v != NULL) {
            *v = array_vertices(G)[i];
            if (strcmp(hab, (*v).habitacion) == 0) {
                return i;
            }
        } else {
            tipovertice u;
            u = array_vertices(G)[i];
            if (strcmp(hab, u.habitacion) == 0) {
                return i;
            }
        }

    }
    v = NULL;
    return -1;
}

// Inserta una tarea dada
void insertar_tarea_grafo(grafo *G, tipoelemcola t) {
    tipovertice v;
    int ind = buscar_vertice(*G, t.ubicacionTarea, &v);
    if (v.numTareas < MAXTASK) {
        if (ind != -1) {
            strncpy(v.tareas[v.numTareas].descripcionTarea, t.atrib.descripcionTarea, MAXCHAR);
            v.tareas[v.numTareas].costeTarea = t.atrib.costeTarea;
            v.numTareas++;
            insertar_vertice(G, v);
        } else {
            printf(BOLDRED "Error: La habitación no existe.\n" RESET);
        }
    } else {
        printf(BOLD "Alcanzado el número máximo de tareas por habitación.\n" RESET);
    }
}

// Elimina una tarea dada
void eliminar_tarea_grafo(grafo *G, tipoelemcola t) {
    tipovertice v;
    int ind = buscar_vertice(*G, t.ubicacionTarea, &v);
    if (ind != -1) {
        char opt;
        printf(BOLD "\nTareas de %s:\n" RESET, v.habitacion);
        for (int i = 0; i < v.numTareas; i++) {
            printf("\t%i) " BOLDYELLOW "%-30s" RESET " con coste %hu\n", i+1, v.tareas[i].descripcionTarea, v.tareas[i].costeTarea);
        }
        printf("\tq) Cancelar.\n");
        // Imprime las tareas de la habitación
        do {
            printf("Opción: ");
            scanf(" %c", &opt);
        } while (atoi(&opt) <= 0 && atoi(&opt) > v.numTareas && opt != 'q' && opt != 'Q');
        if (opt == 'q' || opt == 'Q') {
            return;
        }
        for (int i = ind-1; i < v.numTareas; i++) {
            strncpy(v.tareas[i].descripcionTarea, v.tareas[i+1].descripcionTarea, MAXCHAR);
            v.tareas[i].costeTarea = v.tareas[i+1].costeTarea;
        }
        v.numTareas--;
        insertar_vertice(G, v);
    } else {
        printf(BOLDRED "Error: La habitación no existe.\n" RESET);
    }
}