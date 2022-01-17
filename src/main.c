
#include <stdio.h>
#include <stdlib.h>
#include <time.h>       // Para utilizar la semilla aleatoria time()
#include "AmongETSE.h"
#include "AEMaps.h"
#include <signal.h>     // Permite utilizar señales

static void handler(int signum);

int main(int argc, char** argv) {
    srand((unsigned int) time(NULL));                  // Semilla para aleatorios, se llama sólo una vez al principio de main
    // Crea e importa el mapa
    grafo mapa;
    if (argc == 2) {
        if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)) {  // Si se pide ayuda
            printf("Uso: %s " BOLD "[MAPA]" RESET ",\n\tdonde " BOLD "[MAPA]" RESET " es el nombre de un mapa en %s.\n", argv[0], MAPSPATH);
            exit(EXIT_SUCCESS);
        }
        crear_grafo(&mapa, argv[1]);
        leerGrafoArchivo(&mapa, argv[1]);
    } else if (argc == 1) {
        crear_grafo(&mapa, DEFAULTMAP);     // Si no se pasa ningún mapa, se usa el mapa por defecto
        cargarGrafo(&mapa);
    } else {
        printf(BOLDRED "Error: Se han introducido demasiados parámetros.\n" RESET);
        exit(EXIT_FAILURE);
    }
    // Crear el árbol de jugadores
    abb arbol;
    crear(&arbol);
    // Leer el archivo de disco
    leerArchivo(&arbol);
    // Aplica la función handler a la señal SIGINT
    sigaction(SIGINT, &(struct sigaction){{handler}}, NULL);

    /** Juego **/
    AmongETSE(&arbol, &mapa);

    // Destruir el árbol y el mapa al finalizar
    destruir(&arbol);
    borrar_grafo(&mapa);
    exit(EXIT_SUCCESS);
}

// Función que maneja la señal de interrupción para evitar cerrar el programa al presionar Ctrl+C la primera vez.
static void handler(int signum) {
    if (signum == SIGINT) {
        char opt;
        printf(BOLDYELLOW "\nAVISO: ¿Quieres salir sin guardar? (S/N): " RESET);
        scanf(" %c", &opt);
        if (opt == 'S' || opt == 's') {
            printf("Saliendo del juego...\n");
            exit(SIGINT);
        }
    }
}