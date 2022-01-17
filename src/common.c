/// Archivo con funciones comunes a las clases
#include "common.h"

// Guarda el vértice previo y el tipo de camino
typedef struct {
    int valor;
    char tipo;
}elementoP;

// TAD para agrupar las matrices
typedef struct {
    int D[MAXHAB][MAXHAB];
    elementoP P[MAXHAB][MAXHAB];
}matrices;

// Función para inicializar los datos de un jugador, necesaria en varias funciones públicas
void inicializarJugador(tipoelem * registro) { //inicializa los campos rol, ubicacion, tareas y pasos
    registro->rol = '\0';
    registro->ubicacion[0] = '\0';
    crear_cola(&(registro->tareas));
}

// Función que genera un número aleatorio entre inf y sup
uint aleatorio(int inf, int sup) {
    return (rand() % (sup - inf + 1)) + inf;
}

// Imprime una tarea
void imprimirTarea(tipoelemcola t) {
    if (t.atrib.costeTarea != 0) {
        printf(BOLDYELLOW "\t%-30s [%hu]" RESET "%-2s en %-5s", t.atrib.descripcionTarea, t.atrib.costeTarea, "", t.ubicacionTarea);
    } else {
        printf(BOLDYELLOW "\t%-35s" RESET "  en %-5s", t.atrib.descripcionTarea, t.ubicacionTarea);
    }
}


// Copia la cola de la fuente al destino (con distinta dirección de memoria) y opcionalmente imprime la tarea
void copiarCola(cola src, cola * dest, const char opt) {
    crear_cola(dest);
    tipoelemcola t;
    while (!es_vacia_cola(src)) {
        t = primero(src);
        insertar_cola(dest, t);
        if (opt) {                 // Opción de imprimir la tarea
            imprimirTarea(t);
            printf("\n");
        }
        suprimir_cola(&src);
    }
}

// Imprime todas las tareas
void imprimirTareas(cola *tareas) {
    cola aux;
    crear_cola(&aux);
    copiarCola(*tareas, &aux, 1);           // Copia la cola a la vez que la imprime
    destruir_cola(tareas);                      // Destruye la cola ya vaciada
    copiarCola(aux, tareas, 0);             // Vuelve a copiarla a la variable argumento sin imprimir
    destruir_cola(&aux);                        // Destruye la cola auxiliar
}


// Función que imprime los datos de un jugador
void imprimirJugador(tipoelem jugador, const char opt) {
    switch (opt) {
        case 'I': case 'i':
            if (jugador.rol == 'I') {
                printf(BOLDRED "%-20s" "%-6c" RESET BOLDBLUE "%-20s\n" RESET, jugador.nombre, jugador.rol, jugador.ubicacion);
                imprimirTareas(&jugador.tareas);
            }
            break;
        case 'T': case 't':
            if (jugador.rol == 'T') {
                printf(BOLDGREEN "%-20s" "%-6c" RESET BOLDBLUE "%-20s\n" RESET, jugador.nombre, jugador.rol, jugador.ubicacion);
                imprimirTareas(&jugador.tareas);
            }
            break;
        case 'J':  // Para imprimir en partida (sin roles de jugadores vivos)
            if (jugador.rol == 'K') {   // Para listar jugadores muertos
                printf(BOLDMAGENTA "\n%-20s" RESET BOLDBLUE "%-20s" RESET, jugador.nombre, jugador.ubicacion);
            } else {
                printf("\n%-20s" BOLDBLUE "%-20s %-17s" RESET, jugador.nombre, jugador.ubicacion, jugador.siguiente);
                if (jugador.costeHab != 0) {
                    printf(BOLDBLUE "[%hu]\t" RESET, jugador.costeHab);
                } else {
                    printf("\t"); }
                if (jugador.tareas != NULL && !es_vacia_cola(jugador.tareas)) {
                    tipoelemcola t = primero(jugador.tareas);
                    t.atrib.costeTarea = jugador.costeTar;
                    imprimirTarea(t);
                }
            }
            break;
        default:
            if (jugador.rol == 'I') {           // Color para impostor
                printf(BOLDRED "%-20s" "%-6c" RESET BOLDBLUE "%-12s\n" RESET, jugador.nombre, jugador.rol, jugador.ubicacion);
                imprimirTareas(&jugador.tareas);
            }
            else if (jugador.rol == 'T') {      // Color para tripulante
                printf(BOLDGREEN "%-20s" "%-6c" RESET BOLDBLUE "%-12s\n" RESET, jugador.nombre, jugador.rol, jugador.ubicacion);
                imprimirTareas(&jugador.tareas);
            } else if (jugador.rol == 'K') {    // Color para muerto
                printf(BOLDMAGENTA "%-20s" "%-6c" RESET BOLDBLUE "%-12s\n" RESET, jugador.nombre, jugador.rol, jugador.ubicacion);
            } else {
                printf(BOLD "%s" RESET, jugador.nombre);    // Imprime solo nombre si el jugador está sin inicializar
            }
            break;
    }
}

// Recorre el árbol de forma inorden (IRD) con capacidad para imprimir todos los jugadores o por habitación
void imprimirArbol(abb A, const char opt, const char * hab) {
    tipoelem E;
    if (!es_vacio(A)) {
        imprimirArbol(izq(A), opt, hab);
        leer(A, &E);
        if (hab != NULL) {                                  // Opción buscar por habitación
            if (strcmp(hab, E.ubicacion) == 0) {
                imprimirJugador(E, opt);
            }
        } else {                                            // Opción imprimir
            imprimirJugador(E, opt);
        }
        imprimirArbol(der(A), opt, hab);
    }
}

// Crea una carpeta si no existe
int crearCarpeta(const char *carpeta) {
    struct stat existe;
    if (!(stat(carpeta, &existe) == 0 && S_ISDIR(existe.st_mode))) {     // Si no existe
        mkdir(carpeta, 0777);                                            // Crea la carpeta
        return 1;
    }
    return 0;
}


// Imprime recursivamente la ruta desde el destino hasta el origen. FLAG: 1: Imprime el camino, 0: No imprime
void _recorrerCamino(matrices ms, const int origen, const int destino, int *siguiente, tipovertice * habs, const char flag) {
    if (origen != destino) {
        // Empieza en el destino y va hacia el origen mediante sus predecesores
        _recorrerCamino(ms, origen, ms.P[origen][destino].valor, siguiente, habs, flag);
        if ((ms.P[origen][destino].tipo == 'T' || ms.P[origen][destino].tipo == 't') && flag) {
            printf(BOLDGREEN " - %i -" RESET " %s", ms.D[destino][ms.P[origen][destino].valor], habs[destino].habitacion);
        } else if ((ms.P[origen][destino].tipo == 'I' || ms.P[origen][destino].tipo == 'i') && flag) {
            printf(BOLDRED " • %i •" RESET " %s", ms.D[destino][ms.P[origen][destino].valor], habs[destino].habitacion);
        }
        // Devuelve el índice de la siguiente habitación al origen para poder llegar al destino
        if (ms.P[origen][destino].valor == origen) {
            *siguiente = destino;
        }
    } else {
        if (flag) {
            printf("Ruta: %s", habs[destino].habitacion);
        }
    }
}

// Aplica el algoritmo Floyd-Warshall para el cálculo de la distancia mínima.
// Devuelve la distancia, o -1 si alguno de los vértices no existe, y el vértice siguiente al origen (para saber hacia dónde ir).
// FLAG: 1: Imprime mensajes, 0: No imprime (excepto errores)
int distanciaMinima(grafo G, tipovertice origen, tipovertice destino, tipovertice *siguiente, int *costesig, const char rol, const char flag) {
    matrices ms;
    int N = num_vertices(G), iorig, idest;
    tipovertice *vertices = array_vertices(G);
    if ((!existe_vertice(G, origen) || !existe_vertice(G, destino))) {
        printf(BOLDRED "Error: No existe el origen o el destino.\n" RESET);
        return -1;
    }
    if (rol != 'T' && rol != 'I' && rol != 'i' && rol != 't') {
        printf(BOLDRED "Error: Opción incorrecta.\n" RESET);
        return -1;
    }
    if (strcmp(origen.habitacion, destino.habitacion) == 0) {
        if (flag) {
            printf(BOLD "Origen y destino iguales: la distancia mínima es 0.\n" RESET);
        }
        return 0;
    }
    // Inicializa la matriz de distancias y la matriz de predecesores
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {                           // Si está en la diagonal
                ms.D[i][j] = 0;                     // La distancia a sí mismo es 0
                ms.P[i][j].valor = 0;               // No tiene predecesor
                ms.P[i][j].tipo = '-';              // Necesario para imprimir_camino
            } else if (i != j && son_adyacentes(G, i, j, rol)) {            // Si hay arco y no está en la diagonal
                ms.D[i][j] = valor_arco(G, i, j, rol);                      // Tiene una distancia = valor
                ms.P[i][j].valor = i;                                       // Su predecesor es el origen
                if ((rol == 'I' || rol == 'i') && valor_arco(G, i, j, 'I') == valor_arco(G, i, j, 'T')) { // Si es un camino mutuo
                    ms.P[i][j].tipo = 'T';
                } else {
                    ms.P[i][j].tipo = rol;
                }
            } else {                                // Cualquier otro caso
                ms.D[i][j] = INFINITY;              // Por no estar conectado
                ms.P[i][j].valor = 0;               // No tiene predecesor
                ms.P[i][j].tipo = '-';              // Necesario para imprimir_camino
            }
        }
    }
    // Análisis de la matriz de distancias
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (ms.D[i][j] > ms.D[i][k] + ms.D[k][j]) {    // Si la distancia es mayor por este camino que por otro recorriendo 2 habitaciones
                    ms.D[i][j] = ms.D[i][k] + ms.D[k][j];      // Asigna la nueva distancia mínima
                    ms.P[i][j] = ms.P[k][j];                      // Asigna el nuevo predecesor del camino con distancia menor
                }
            }
        }
    }
    // Busca el índice de las habitaciones en el vector de vértices
    iorig = posicion(G, origen);
    idest = posicion(G, destino);
    /*
    printf("Matriz D:\n");
    _printMatrixD(matrizD, N);
    printf("\n");
    printf("Matriz P:\n");
    _printMatrixP(matrizP, N);
    */
    if (ms.D[iorig][idest] != INFINITY) {
        if (flag) {
            printf(BOLD "\nLa distancia mínima desde %s hasta %s es de %i.\n" RESET, origen.habitacion, destino.habitacion, ms.D[iorig][idest]);
        }
        int sig;
        _recorrerCamino(ms, iorig, idest, &sig, vertices, flag);
        if (flag) {
            printf("\n");
        }
        if (siguiente != NULL) {
            *siguiente = vertices[sig];
            *costesig = ms.D[iorig][sig];       // Distancia al siguiente vértice
        }
    } else {
        printf(BOLD "No hay camino posible desde %s hasta %s.\n" RESET, origen.habitacion, destino.habitacion);
        siguiente = NULL;
    }
    return ms.D[iorig][idest];
}

// Permite al usuario pedir una habitación
char * pedirHabitacion(grafo G) {
    unsigned int aux;
    printf("Habitaciones disponibles:\n");
    for (int i = 0; i < num_vertices(G); i++) {
        printf("\t%2i) " BOLDBLUE "%s\n" RESET, i+1, array_vertices(G)[i].habitacion);
    }
    do {
        printf("\nHabitación: ");
        scanf(" %i", &aux);
    } while (aux > num_vertices(G));
    return array_vertices(G)[aux-1].habitacion;
}
