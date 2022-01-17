/// Archivo con funciones para jugar

#include "AEPlay.h"

// Comprueba que los tripulantes tengan o no tareas
int _hayTareas(abb A, const uint numT, int *colasVacias) {
    tipoelem j;
    if (!es_vacio(A)) {
        leer(A, &j);
        if (j.rol == 'T' && es_vacia_cola(j.tareas)) {
            (*colasVacias)++;
        }
        _hayTareas(izq(A), numT, colasVacias);
        _hayTareas(der(A), numT, colasVacias);
    }
    if (numT != *colasVacias) {
        return 1;
    }
    return 0;
}

// Comprueba las condiciones de fin de partida
int _finPartida(abb A, const uint numT, const uint numI) {
    int colasVacias = 0;
    if (numT <= numI) {
        printf(BOLDRED "\nVictoria para los impostores: no quedan tripulantes suficientes.\n" RESET);
        return 1;
    } else if (numI == 0) {
        printf(BOLDGREEN "\nVictoria para los tripulantes: se expulsaron a todos los impostores.\n" RESET);
        return 2;
    } else if (!_hayTareas(A, numT, &colasVacias)) {
        printf(BOLDGREEN "\nVictoria para los tripulantes: se acabaron las tareas.\n" RESET);
        return 3;
    }
    return 0;
}

// Cuenta el número de impostores y tripulantes
void _contarRoles(abb A, uint *numT, uint *numI) {
    tipoelem j;
    if (!es_vacio(A)) {
        leer(A, &j);
        if (j.rol == 'T') {
            (*numT)++;
        }
        if (j.rol == 'I') {
            (*numI)++;
        }
        _contarRoles(izq(A), numT, numI);
        _contarRoles(der(A), numT, numI);
    }
}

// Devuelve el impostor número num
void _buscarImpostor(abb A, tipoelem *j, int num, int *contador) {
    if (*contador == num) {
        return;
    }
    if (!es_vacio(A)) {
        leer(A, j);
        if (j->rol == 'I') {
            (*contador)++;
        }
        if (*contador != num) {
            _buscarImpostor(izq(A), j, num, contador);
        }
        if (*contador != num) {
            _buscarImpostor(der(A), j, num, contador);
        }
    }
}

// Se ejecuta siempre que costeHab = 0
void _comprobarPosicion(grafo G, tipoelem *j) {
    if (j->tareas != NULL) {
        tipovertice orig, dest, sig;
        int csig = 0;
        buscar_vertice(G, j->ubicacion, &orig);
        if (!es_vacia_cola(j->tareas)) {
            buscar_vertice(G, primero(j->tareas).ubicacionTarea, &dest);
        } else {
            dest = array_vertices(G)[aleatorio(0, num_vertices(G) - 1)]; // Destino aleatorio
        }
        if (distanciaMinima(G, orig, dest, &sig, &csig, j->rol, 0) > 0){
            strncpy(j->siguiente, sig.habitacion, MAXCHAR);                     // Asigna nueva habitación
            j->costeHab = csig;
        } else {
            if (!es_vacia_cola(j->tareas)) {
                j->costeTar = primero(j->tareas).atrib.costeTarea;
            }
            j->siguiente[0] = '\0';
        }
    }
}

// Aleatoriamente decide si mata o no un impostor a un tripulante. Se pasa el impostor por referencia para que se pueda modificar
// (si no, si no está el impostor en el subárbol no se altera y por lo tanto tampoco en el árbol original)
void _matarTripulante(abb A, grafo G, tipoelem *impostor, int *salir) {
    if (impostor->rol == 'I') {
        tipoelem tripulante;
        uint ale;
        ale = aleatorio(0, 3);      // Prob = 75% de matar
        if (!es_vacio(A)) {
            leer(A, &tripulante);
            // Si puede matar y si el jugador leído es un tripulante y está en la habitación actual y no se está moviendo
            if (tripulante.rol == 'T' && impostor->matar && strcmp(impostor->ubicacion, tripulante.ubicacion) == 0 && tripulante.siguiente[0] == '\0' && (ale == 1 || ale == 2 || ale == 3)) {
                impostor->matar = 0;                                                 // No permite que el impostor vuelva a matar a un tripulante en esta ronda
                ale = aleatorio(0, 1);                                               // Prob = 50% de escapar
                if (ale) {      // Si escapa
                    tipovertice *vert = array_vertices(G), orig;
                    buscar_vertice(G, impostor->ubicacion, &orig);
                    for (int i = 0; i < num_vertices(G); i++) {
                        int csig = 0;
                        tipovertice sig;
                        // Si la habitación está a suficientes pasos de la habitación del impostor y no es la misma
                        int pasos = distanciaMinima(G, vert[i], orig, &sig, &csig, 'I', 0);
                        if (pasos <= ESCAPESTEPS && pasos != 0) {       // Si la hab está suficientemente cerca
                            strncpy(impostor->ubicacion, vert[i].habitacion, MAXCHAR);
                            strncpy(impostor->siguiente, sig.habitacion, MAXCHAR);
                            // Si estaba realizando una tarea en la hab de la que escapó
                            if (impostor->costeTar > 0) {
                                impostor->costeTar = 0;
                            } else {
                                _comprobarPosicion(G, impostor);
                            }
                            break;
                        }
                    }
                }
                printf(BOLDRED "%s ha sido asesinado.\n" RESET, tripulante.nombre);
                tripulante.rol = 'K';                                                // Rol de jugador muerto
                if (tripulante.tareas != NULL) {
                    destruir_cola(&tripulante.tareas);                               // Destruye la cola del jugador muerto
                }
                tripulante.tareas = NULL;
                modificar(A, tripulante);
                (*salir) = 1;
            }
            if (*salir == 0) {                                          // Si no mató a nadie aún
                _matarTripulante(izq(A), G, impostor, salir);
            }
            if (*salir == 0) {                                          // Si no mató a nadie aún
                _matarTripulante(der(A), G, impostor, salir);
            }
        }
    } else {
        printf(BOLDRED "Error: No se ha introducido un impostor como parámetro.\n" RESET);
        exit(EXIT_FAILURE);
    }
}



// Reduce el coste de movimiento o de la tarea actual y lo cambia de habitación o tarea
void _actualizarJugador(grafo G, tipoelem *j) {
    tipovertice orig, dest, sig;
    int csig = 0;
    buscar_vertice(G, j->ubicacion, &orig);
    if (j->tareas != NULL && !es_vacia_cola(j->tareas)) {
        buscar_vertice(G, primero(j->tareas).ubicacionTarea, &dest);
        if (j->costeTar > 0 && j->costeHab > 0) {                // No debería poder ocurrir
            printf(BOLDRED "Error: Estado del jugador %s inválido.\n" RESET, j->nombre);
            j->costeHab = 0;                                     // Intenta arreglarlo
        } else if (j->costeHab > 0) {                            // Si se está moviendo
            j->costeHab--;
            if (!j->costeHab) {                                  // Alcanzó la habitación
                strncpy(j->ubicacion, j->siguiente, MAXCHAR);
                _comprobarPosicion(G, j);
            }
        } else if (j->costeTar > 0) {                            // Si está haciendo una tarea
            j->costeTar--;
            if (!j->costeTar) {                                  // Terminó la tarea
                suprimir_cola(&j->tareas);                       // Elimina la tarea
                _comprobarPosicion(G, j);
            }
        } else {                                                 // No se está moviendo ni haciendo tareas
            if (distanciaMinima(G, orig, dest, &sig, &csig, j->rol, 0) > 0) {
                strncpy(j->siguiente, sig.habitacion, MAXCHAR);  // Asigna nueva habitación
                j->costeHab = csig - 1;
                if (!j->costeHab) {
                    strncpy(j->ubicacion, j->siguiente, MAXCHAR);
                    _comprobarPosicion(G, j);
                }
            } else {
                j->siguiente[0] = '\0';
                j->costeTar = primero(j->tareas).atrib.costeTarea - 1;
            }
        }
    } else {
        dest = array_vertices(G)[aleatorio(0, num_vertices(G) - 1)];    // Destino aleatorio
        if (j->costeHab > 0) {
            j->costeHab--;
            if (!j->costeHab) {
                strncpy(j->ubicacion, j->siguiente, MAXCHAR);
            }
        } else {
            if (distanciaMinima(G, orig, dest, &sig, &csig, j->rol, 0) > 0) {
                strncpy(j->siguiente, sig.habitacion, MAXCHAR);  // Asigna nueva habitación
                j->costeHab = csig - 1;
                if (!j->costeHab) {
                    strncpy(j->ubicacion, j->siguiente, MAXCHAR);
                    j->siguiente[0] = '\0';     // Se anula el siguiente porque no recuerda el destino en cada ronda
                }
            } else {
                j->siguiente[0] = '\0';
            }
        }
    }
}

// Mueve a los jugadores siguiendo la ruta de distancia mínima y continúa sus tareas.
void _moverJugadoresTareas(abb A, grafo G) {
    tipoelem j;
    if (!es_vacio(A)) {
        leer(A, &j);
        if (j.rol != 'K') {         // Si no está muerto
            _actualizarJugador(G, &j);
            modificar(A, j);
        }
        _moverJugadoresTareas(izq(A), G);
        _moverJugadoresTareas(der(A), G);
    }
}

// Permite a los impostores matar o no a tripulantes
void _ejecutarRonda(abb A, grafo G, const uint numI, uint *numT, uint ronda) {
    tipoelem imp;
    ushort pasos = NUMSTEPS;
    printf(BOLD "\nRonda %i. Estado de los jugadores:\n" RESET, ronda);
    while (pasos > 0) {
        _moverJugadoresTareas(A, G);
        if (pasos != NUMSTEPS) {                                                        // Si no es el primer paso
            for (int i = 0; i < numI; i++) {
                int contador = -1;                                                      // Empieza en -1 porque i empieza en 0
                _buscarImpostor(A, &imp, i, &contador);
                int salir = 0;
                _matarTripulante(A, G, &imp, &salir);
                modificar(A, imp);                                                      // Modifica el impostor
                if (salir) {                                                            // Si mató a algún tripulante
                    (*numT)--;
                }
            }
        }
        pasos--;
    }
}

void _siguienteRonda(abb A) {
    tipoelem j;
    if (!es_vacio(A)) {
        leer(A, &j);
        if (j.rol == 'I' && !j.matar) {
            j.matar = 1;                              // Restaura la capacidad de matar del impostor
            modificar(A, j);
        }
        _siguienteRonda(izq(A));
        _siguienteRonda(der(A));
    }
}


// Permite al jugador decidir a quién echar, y devuelve el rol del jugador expulsado.
char _eliminarJugador(abb A, const char confirmacion) {
    char nombre[MAXCHAR];
    tipoelem j;
    // Permite saber si se encontró en el árbol tras leerlo
    j.rol = 'K';
    do {
        printf(BOLDYELLOW "\n¿Quién es el impostor? (skip para saltar): " RESET);
        scanf(" %39s", nombre);
        buscar_nodo(A, nombre, &j);
    } while (j.rol == 'K' && strcmp(nombre, "skip") != 0 && strcmp(nombre, "Skip") != 0 && strcmp(nombre, "SKIP") != 0 && strcmp(nombre, "s") != 0 && strcmp(nombre, "S") != 0);

    if (j.rol == 'I') {
        printf(BOLD "Se ha expulsado a %s. " RESET, j.nombre);
        if (confirmacion == 'S' || confirmacion == 's') {
            printf(BOLD "Era un impostor.\n" RESET);
        } else {
            printf("\n");
        }
        j.rol = 'K';
        destruir_cola(&j.tareas);
        j.tareas = NULL;
        modificar(A, j);
        return 'I';
    } else if (j.rol == 'T') {
        printf(BOLD "Se ha expulsado a %s. " RESET, j.nombre);
        if (confirmacion == 'S' || confirmacion == 's') {
            printf(BOLD "Era un tripulante.\n" RESET);
        } else {
            printf("\n");
        }
        j.rol = 'K';
        destruir_cola(&j.tareas);
        j.tareas = NULL;
        modificar(A, j);
        return 'T';
    } else {
        printf(BOLD "Saltando votación...\n" RESET);
        return 0;
    }
}

// Ejecuta el juego
void _jugarPartida(abb A, grafo G, const char confirmacion) {
    uint numT = 0, numI = 0, fin = 0, ronda = 1;
    char rol;
    _contarRoles(A, &numT, &numI);                          // Cuenta el número de tripulantes y impostores para no tener que meterlos como parámetros
    do {
        _ejecutarRonda(A, G, numI, &numT, ronda);
        fin = _finPartida(A, numT, numI);
        if (!fin) {
            printf(BOLD "%-19s %-21s %-30s %-16s", "Jugador", "Ubicación", "Siguiente", "Tarea" RESET);
            imprimirArbol(A, 'J', NULL);
            rol = _eliminarJugador(A, confirmacion);
            if (rol == 'I') {            // Se eliminó un impostor
                numI--;
            } else if (rol == 'T') {     // Se eliminó un tripulante
                numT--;
            }
            _siguienteRonda(A);
            fin = _finPartida(A, numT, numI);
            if (!fin) { ronda++; }
        }
    } while (!fin);
    // Enseña las tareas y roles de los jugadores y espera 3 segundos
    printf(BOLD "Número de rondas: %i\n" RESET, ronda);
    printf(BOLD "Estado final de los jugadores:\n" RESET);
    printf(BOLD "%-19s %-5s %-21s\n" RESET, "Jugador", "Rol", "Ubicación");
    imprimirArbol(A, 'A', NULL);
    sleep(3);
}

// Función que escoge NUMTASK tareas aleatorias para un jugador
void _aleatorioTareas(grafo G, tipoelem *j) {
    tipoelemcola tarea;
    if (j->tareas == NULL) {                            // Si no tiene cola
        crear_cola(&(j->tareas));
    }
    for (int i = 0; i < NUMTASK; i++) {                 // Introduce NUMTASK tareas aleatorias
        int hab;
        tipovertice v;
        do {                          // Selecciona una habitación aleatoria que tenga tareas
            hab = aleatorio(0, num_vertices(G) - 1);
            v = array_vertices(G)[hab];
        } while (!v.numTareas);

        int num = aleatorio(0, v.numTareas - 1);                 // Selecciona una tarea aleatoria de la habitación
        // Asigna los punteros del mapa a los campos de la tarea
        strncpy(tarea.ubicacionTarea, v.habitacion, MAXCHAR);
        strncpy(tarea.atrib.descripcionTarea, v.tareas[num].descripcionTarea, MAXCHAR);
        tarea.atrib.costeTarea = v.tareas[num].costeTarea;
        insertar_cola(&(j->tareas), tarea);               // Inserta la tarea en la cola de tareas del jugador
    }
    strncpy(j->ubicacion, DEFAULTSTARTINGROOM, MAXCHAR);               // Inicializa la sala de inicio a la ubicación actual
    j->siguiente[0] = '\0';
}

// Función que randomiza un rol de jugador e inicializa los campos. Prob = 33% de ser impostor.
char _aleatorioRol(tipoelem *j, const uint numI, uint *contI, const uint numT, uint *contT) {
    if (*contI < numI && *contT < numT) {       // Caso en el que no se han llegado al máximo de impostores ni tripulantes
        int num = aleatorio(0, 2);
        switch (num) {
            case 0: case 1:
                j->rol = 'T';
                (*contT)++;
                j->matar = 0;
                j->costeHab = 0;
                j->costeTar = 0;
                return 'T';
            case 2:
                j->rol = 'I';
                (*contI)++;
                j->matar = 1;
                j->costeHab = 0;
                j->costeTar = 0;
                return 'I';
            default:
                j->rol = 'T';
                (*contT)++;
                j->matar = 0;
                j->costeHab = 0;
                j->costeTar = 0;
                return 'T';
        }
    } else if (*contI < numI) {                 // Caso en el que se han llegado al máximo de tripulantes
        j->rol = 'I';
        (*contI)++;
        j->matar = 1;
        j->costeHab = 0;
        j->costeTar = 0;
        return 'I';
    } else if (*contT < numT) {                 // Caso en el que se han llegado al máximo de impostores
        j->rol = 'T';
        (*contT)++;
        j->matar = 0;
        j->costeHab = 0;
        j->costeTar = 0;
        return 'T';
    } else {
        printf(BOLD "Error: No se pueden crear más jugadores.\n" RESET);
        exit(EXIT_FAILURE);
    }
}

// Elimina los datos de los jugadores en el árbol excepto sus nombres
void _limpiarDatos(abb A) {
    tipoelem j;
    if (!es_vacio(A)) {
        leer(A, &j);
        if (j.tareas != NULL) {                 // Elimina colas basura
            destruir_cola(&j.tareas);           // Elimina la cola anterior para crear otra nueva
        }
        inicializarJugador(&j);
        modificar(A, j);
        _limpiarDatos(izq(A));
        _limpiarDatos(der(A));
    }
}

// Copia los datos de src a dest con recorrido preorden (RID) para que ambos árboles
// sean iguales (excepto en dirección de memoria)
void _pasarDatos(abb src, abb *dest) {
    tipoelem j;
    if (!es_vacio(src)) {
        leer(src, &j);
        if (j.tareas != NULL && !es_vacia_cola(j.tareas)) {
            copiarCola(j.tareas, &j.tareas, 0);
        }
        if (!es_miembro(*dest, j)) {        // Para generarPartida()
            insertar(dest, j);
        }
        modificar(*dest, j);
        _pasarDatos(izq(src), dest);
        _pasarDatos(der(src), dest);
    }
}

// Función recursiva que inicializa todos los jugadores para la partida
void _inicializarJugadoresJugar(abb A, grafo G, const uint numT, uint *contT, const uint numI, uint *contI, ushort *salir) {
    if (!es_vacio(A)) {
        tipoelem j;
        leer(A, &j);
        _aleatorioTareas(G, &j);
        j.rol = _aleatorioRol(&j, numI, contI, numT, contT);    // Inicializa el rol de cada jugador
        modificar(A, j);
        if (*contT == numT && *contI == numI) {                     // Si se han inicializado todos los jugadores
            (*salir) = 1;
        }
        if (!(*salir)) {
            _inicializarJugadoresJugar(izq(A), G, numT, contT, numI, contI, salir);
        }
        if (!(*salir)) {
            _inicializarJugadoresJugar(der(A), G, numT, contT, numI, contI, salir);
        }
    }
}

// Función que genera los datos de una partida: jugadores, roles y tareas. Devuelve el árbol de Jugadores
void generarPartida(abb U, abb *J, grafo G) {
    /*
    CÓDIGO PARA LEER MEDIANTE ARCHIVO DE PARTIDA NO INCLUIDO (NO TIENE SENTIDO PARA EL JUEGO)
    **********************************************************************************************
    tipoelem j;
    FILE *fp;
    tipoelemcola tarea;
    char nombre[MAXCHAR];
    char command[MAXCHAR * 2] = "ls --color ";
    char path[MAXCHAR * 2] = GAMESPATH;
    strncat(command, path, strlen(path));                    // command = "ls --color $GAMESPATH"
    printf("Partidas disponibles para cargar:\n");
    system(command);
    scanf(" %39s", jugador.nombre);
    strncat(path, nombre, MAXCHAR * 2);
    fp = fopen(path, "rt");
    if (fp) { //Si el fichero se abre correctamente
        // Cadena para ir leyendo líneas de código
        char aux[2 * MAXCHAR];
        // Creo el árbol de jugadores y limpio los datos del árbol de Usuarios de la partida anterior
        crear(&J);
        _limpiarDatos(U);
        // Leo la primera línea del archivo, hasta encontrar un cambio de línea
        fscanf(fp," %[^\r\n]", aux);
        // Mientras no encuentre la marca fin de archivo
        while (!feof(fp)) {
            inicializarJugador(&j);
            // Separo la línea en sus campos
            sscanf(aux," %[^-]-%c-%s", j.nombre, &j.rol, j.ubicacion);
            // Lee la primera línea de las tareas
            fscanf(fp," %[^\r\n]", aux);
            // Mientras la siguiente línea no sea un jugador, lee todas las tareas
            do {
                // Separo la línea en sus campos
                sscanf(aux," %[^:]:%[^\r\n]", tarea.ubicacionTarea, tarea.atrib.descripcionTarea);
                // Inserto la tarea en el jugador
                insertar_cola(&j.tareas, tarea);
                // Lee la siguiente línea, puede ser tarea o jugador
                fscanf(fp," %[^\r\n]", aux);
            } while (aux[0] != '@' && !feof(fp));  // Hasta fin de archivo para no entrar en bucle infinito
            // Si j es miembro del árbol de Usuarios, lo inserto en el árbol de Jugadores
            if (es_miembro(U, j)) {
                insertar(&J, j);
            } else if (num_vertices(G) > 0 && numero_nodos(U) > 0){

            } else {
                printf(BOLDRED "%s: El jugador no existe.\n" RESET, j.nombre);
            }
        }
        // Cierra el archivo
        fclose(fp);
    } else
     **********************************************************************************************
     */
    if (G != NULL && num_vertices(G) >= MINHAB && num_tareas(G) >= MINMAPTASK && U != NULL &&
        numero_nodos(U) > MINPLAYERS) {   // Si existe el mapa y hay suficientes jugadores, habitaciones y tareas
        printf(BOLD "Generando partida nueva... \n" RESET);
        // Limpio el árbol de Usuarios y creo el árbol de Jugadores y le paso los jugadores de U.
        crear(J);
        _limpiarDatos(U);
        _pasarDatos(U, J);                      // Pasa los jugadores al árbol de Jugadores
        // Calcula el número de impostores según el número de jugadores y los inicializa aleatoriamente
        uint numI = (uint) roundf((float) numero_nodos(U) / PROPORTION), contI = 0;
        uint numT = numero_nodos(*J) - numI, contT = 0;
        ushort salir = 0;
        _inicializarJugadoresJugar(*J, G, numT, &contT, numI, &contI, &salir);
    } else {
        printf(BOLDRED "Error: No hay suficientes jugadores o el mapa es inválido.\n" RESET);
    }
}

// Contiene todas las funciones para jugar una partida
void jugarPartida(abb U, grafo G) {
    abb J = NULL;
    generarPartida(U, &J, G);                // Genera los datos de la partida
    if (J != NULL) {                         // Si se pudo generar la partida
        char confirmacion;
        do {
            printf("¿Confirmaciones de expulsión? (S/N): ");
            scanf(" %c", &confirmacion);
        } while (confirmacion != 'S' && confirmacion != 'N' && confirmacion != 's' && confirmacion != 'n');
        _jugarPartida(J, G, confirmacion);                 // Jugar la partida
        _pasarDatos(J, &U);                  // Copia datos de Jugadores a Usuarios
        destruir(&J);                        // Destruir el árbol de jugadores
    } else {
        printf(BOLDRED "Error: No se pudo generar una partida nueva.\n" RESET);
        exit(EXIT_FAILURE);
    }
}
