
#include "AmongETSE.h"
#include "AEMaps.h"
#include "AEPlay.h"


// Función que imprime las opciones del juego
void _menuAmongETSE() {
    printf(BOLDBLUE "\n--- Among ETSE ---" RESET "\n" BOLD "Menú principal" RESET "\n\ta) Da de alta un jugador.\n\tb) Da de baja un jugador.\n\t"
           "c) Carga un mapa diferente.\n\tj) Empieza la partida.\n\tl) Listado de jugadores por tipo.\n\t"
           "u) Consulta las tareas a realizar de un jugador.\n\th) Consulta jugadores filtrando por su habitación.\n\t"
           "m) Modo edición de mapa.\n\ts) Salir del juego.\n");
}

// Menú principal del juego
void AmongETSE(abb *arbol, grafo *mapa) {
    char opt;
    do {
        _menuAmongETSE();
        printf("Opción: ");
        scanf(" %c", &opt);
        printf("\n");
        switch (opt) {
            case 'A':
            case 'a':
                // Alta de jugador
                altaJugador(arbol);
                break;
            case 'B':
            case 'b':
                // Baja de jugador
                bajaJugador(arbol);
                break;
            case 'c':
            case 'C':
                // Carga de mapa
                cargarGrafo(mapa);
                break;
            case 'J':
            case 'j':
                // Jugar
                jugarPartida(*arbol, *mapa);
                break;
            case 'L':
            case 'l':
                // Listar por orden alfabético
                listadoJugadores(*arbol);
                sleep(2);
                break;
            case 'U':
            case 'u':
                // Consultar la última tarea de un jugador
                consultarJugador(*arbol);
                break;
            case 'H':
            case 'h':
                // Consultar la habitación en la que se encuentran todos, solo tripulantes o solo impostores
                consultarPorHabitacion(*arbol, *mapa);
                break;
            case 'M':
            case 'm':
                // Modo edición de mapa
                AEMaps(mapa);
                break;
            case 'S':
            case 's':
                // Salir del programa
                printf("Saliendo del juego...\n");
                break;
            default:
                printf("\n" BOLDRED "%c:" RESET " Opción incorrecta. Inténtalo de nuevo.\n", opt);
                break;
        }
    } while (opt != 's' && opt != 'S');
}

// Función pública que imprime los nombres de los jugadores por orden alfabético
void listadoJugadores(abb A) {
    char opt;
    do {
        printf("Filtrar por rol (A - todos, T - tripulantes, I - impostores): ");
        scanf(" %c", &opt);
    } while (opt != 'A' && opt != 'a' && opt != 'T' && opt != 't' && opt != 'I' && opt != 'i');
    printf(BOLD "%-19s %-5s %-20s\n", "Jugador", "Rol", "Ubicación" RESET);
    imprimirArbol(A, opt, NULL);
}

// Función para leer el archivo de disco
void leerArchivo(abb *A) {
    tipoelem registro;
    FILE *fp;
    fp = fopen(PLAYERSFILE, "rt");
    if (fp) {
        fscanf(fp, " %s", registro.nombre);
        while (!feof(fp)) {
            if (!es_miembro(*A, registro)) {
                inicializarJugador(&registro);
                insertar(A, registro);
                fscanf(fp, " %s", registro.nombre);
            } else {  // Si un jugador es repetido en el archivo
                printf(BOLDRED "%s:" RESET " Nombre repetido. Vuelve a intentarlo.\n", registro.nombre);
            }
        }
        printf(BOLDGREEN "Jugadores cargados correctamente.\n" RESET);
        fclose(fp);
    } else {
        printf(BOLDRED "Error: No existe un fichero de jugadores." RESET);
    }
}

// Función que añade un jugador al árbol
void altaJugador(abb *Arbol) {
    tipoelem jugador;
    do {
        printf("Nombre del jugador a añadir (de la forma " BOLD "@xxxxx" RESET "): " );
        scanf(" %39s", jugador.nombre);
        if (es_miembro(*Arbol, jugador)) {
            printf(BOLDRED "%s:" RESET " Nombre repetido. Vuelve a intentarlo.\n", jugador.nombre);
        }
    } while (jugador.nombre[0] != '@' || strlen(jugador.nombre) >= MAXCHAR || strlen(jugador.nombre) < 2 || es_miembro(*Arbol, jugador));
    inicializarJugador(&jugador);
    insertar(Arbol, jugador);
    printf(BOLDGREEN "%s:" RESET " Jugador añadido.\n", jugador.nombre);
    guardarJugadores(*Arbol);
}

// Función que elimina un jugador del árbol
void bajaJugador(abb *Arbol) {
    tipoelem jugador;
    printf("Nombre del jugador a eliminar (de la forma " BOLD "@xxxxx" RESET "): ");
    scanf(" %39s", jugador.nombre);
    buscar_nodo(*Arbol, jugador.nombre, &jugador);
    if (es_miembro(*Arbol, jugador)) {
        suprimir(Arbol, jugador);
        printf(BOLDRED "%s:" RESET " Jugador eliminado.\n", jugador.nombre);
        guardarJugadores(*Arbol);
    } else {
        printf(BOLDRED "%s:" RESET " El jugador no existe.\n", jugador.nombre);
    }
}

// Función que imprime los datos de un jugador y sólo la primera tarea
void consultarJugador(abb Arbol) {
    tipoelem jugador;
    char nombre[MAXCHAR];
    printf("Nombre del jugador a consultar: ");
    scanf(" %39s", nombre);
    buscar_nodo(Arbol, nombre, &jugador);
    if (jugador.rol == 'I' || jugador.rol == 'T' || jugador.rol == 'K') {
        printf(BOLD "%-19s %-5s %-20s\n", "Jugador", "Rol", "Ubicación" RESET);
        imprimirJugador(jugador, jugador.rol);
    } else {
        printf(BOLDRED "%s:" RESET " El jugador no existe.\n", nombre);
    }
}

//Función que imprime todos los usuarios que están en una habitación determinada
void consultarPorHabitacion(abb Arbol, grafo G) {
    char hab[MAXCHAR];
    printf("Filtrar por habitación. ");
    strncpy(hab, pedirHabitacion(G), MAXCHAR);
    printf("Jugadores en la habitación " BOLDBLUE "%s:\n" RESET, hab);
    printf(BOLD "%-19s %-5s %-20s\n", "Jugador", "Rol", "Ubicación" RESET);
    imprimirArbol(Arbol, 'A', hab);
}

// Recorre el árbol para obtener los nombres de los jugadores y los imprime en el archivo
void _guardarJugadores(FILE *fp, abb A) {
    tipoelem E;
    if (!es_vacio(A)) {
        leer(A, &E);
        fprintf(fp, "%s\n", E.nombre);
        _guardarJugadores(fp, izq(A));
        _guardarJugadores(fp, der(A));
    }
}

// Guarda los nombres de los jugadores en un archivo
void guardarJugadores(abb A) {
    FILE *fp = fopen(PLAYERSFILE, "w");
    _guardarJugadores(fp, A);
    fclose(fp);
}
