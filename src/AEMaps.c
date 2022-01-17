/// Archivo con funciones de creación de mapas

#include "AEMaps.h"

//FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS

//Opción a del menú, introducir un vertice en el grafo

void introducir_vertice(grafo *G) {
    tipovertice v1;
    printf("Introduce una habitación: ");
    scanf("%39s", v1.habitacion);
    if (existe_vertice(*G, v1))
        printf(BOLD "Error: La habitación %s ya existe en el mapa.\n" RESET, v1.habitacion);
    else {
        insertar_vertice(G, v1);
        printf(BOLDGREEN "Habitación introducida correctamente.\n" RESET);
    }
}

//Opción b del menú, eliminar un vértice del grafo

void eliminar_vertice(grafo *G) {
    tipovertice v1;
    printf("Introduce una habitación: ");
    scanf("%39s", v1.habitacion);
    if (existe_vertice(*G, v1)) {
        borrar_vertice(G, v1);
        printf(BOLDGREEN "habitación eliminada correctamente.\n" RESET);
    } else
        printf(BOLDRED "Error: La habitación %s no existe en el mapa\n" RESET, v1.habitacion);
}

//Opción c del menú, crear una relación entre dos vértices

void nuevo_arco(grafo *G) {
    tipovertice v1, v2;
    ushort valor;
    char opt;
    //Insertamos una nueva relación pidiendo los datos al usuario controlando que existan los vértices
    printf(BOLD "Nueva comunicación habitación1···habitación2\n" RESET);
    //Vértice origen del arco
    printf("Introduce habitación origen: ");
    scanf(" %39s", v1.habitacion);
    if (!existe_vertice(*G, v1)) {
        printf(BOLDRED "Error: La habitación %s no existe en el mapa.\n" RESET, v1.habitacion);
        return;
    }
    //Vértice destino del arco
    printf("Introduce habitación destino: ");
    scanf(" %39s", v2.habitacion);
    if (!existe_vertice(*G, v2)) {
        printf(BOLDRED "Error: La habitación %s no existe en el mapa.\n" RESET, v2.habitacion);
        return;
    }

    // Pedir valor del arco
    do {
        printf("Distancia entre habitaciones: ");
        scanf(" %hi", &valor);
    } while (valor < 1);

    // Pedir rol al que aplicar
    do {
        printf("Rol de jugador a aplicar (T/I/A): ");
        scanf(" %c", &opt);
    } while (opt != 'T' && opt != 'I' && opt != 'A' && opt != 't' && opt != 'i' && opt != 'a');

    //Creación del arco
    if (opt == 'A' || opt == 'a') {
        if (!son_adyacentes(*G, posicion(*G, v1), posicion(*G, v2), 'I')) {
            crear_arco(G, posicion(*G, v1), posicion(*G, v2), valor, 'I');
        }
        if (!son_adyacentes(*G, posicion(*G, v1), posicion(*G, v2), 'T')){
            crear_arco(G, posicion(*G, v1), posicion(*G, v2), valor, 'T');
        }
    } else if (!son_adyacentes(*G, posicion(*G, v1), posicion(*G, v2), opt)) {
        crear_arco(G, posicion(*G, v1), posicion(*G, v2), valor, opt);
        printf(BOLDGREEN "Comunicación creada correctamente.\n" RESET);
    } else {
        printf(BOLD "Comunicación ya existente. No se han realizado cambios.\n" RESET);
    }
}

//Opción d del menú, eliminar una relación entre dos vértices
void eliminar_arco(grafo *G) {
    tipovertice v1, v2;
    char opt;
    //Eliminamos una relación pidiendo los datos al usuario controlando que existan los vértices
    printf(BOLD "Eliminar comunicación habitación1···habitación2\n" RESET);
    //Vértice origen del arco
    printf("Introduce habitación origen: ");
    scanf("%39s", v1.habitacion);
    if (!existe_vertice(*G, v1)) {
        printf(BOLDRED "Error: La habitación %s no existe en el mapa\n" RESET, v1.habitacion);
        return;
    }
    //Vértice destino del arco
    printf("Introduce habitación destino: ");
    scanf("%39s", v2.habitacion);
    if (!existe_vertice(*G, v2)) {
        printf(BOLDRED "Error: La habitación %s no existe en el mapa.\n" RESET, v2.habitacion);
        return;
    }
    // Pedir rol al que aplicar
    do {
        printf("Tipo de jugador a aplicar (T/I/A): ");
        scanf(" %c", &opt);
    } while (opt != 'T' && opt != 'I' && opt != 'A' && opt != 't' && opt != 'i' && opt != 'a');

    //Eliminación del arco
    if (opt == 'A' || opt == 'a') {
        if (son_adyacentes(*G, posicion(*G, v1), posicion(*G, v2), 'I')) {
            borrar_arco(G, posicion(*G, v1), posicion(*G, v2), 'I');
        }
        if (son_adyacentes(*G, posicion(*G, v1), posicion(*G, v2), 'T')) {
            borrar_arco(G, posicion(*G, v1), posicion(*G, v2), 'T');
        }
    } else if (son_adyacentes(*G, posicion(*G, v1), posicion(*G, v2), opt)) {
        borrar_arco(G, posicion(*G, v1), posicion(*G, v2), opt);
        printf(BOLDGREEN "Comunicación eliminada correctamente.\n" RESET);
    } else {
        printf(BOLD "Comunicación no existente. No se han realizado cambios.\n" RESET);
    }
}

//Opción i del menú, imprimir el grafo
//Función que imprime el grafo utilizando num_vertices para saber cuántos vértices tiene
//y array_vertices para recuperar el vector de vértices y recorrerlo

void imprimir_grafo(grafo G) {
    tipovertice *VECTOR; //Para almacenar el vector de vértices del grafo
    int N; //número de vértices del grafo

    //Para recorrerla, simplemente vamos a recorrer la matriz de adyacencia
    N = num_vertices(G);
    VECTOR = array_vertices(G);

    int i, j;
    // Imprime usando la matriz de adyacencia de los tripulantes
    printf(BOLD "\nMapa actual:\n" RESET);
    for (i = 0; i < N; i++) {
        //Imprimo el vértice
        printf(BOLD "\tHabitación(%d): %s\n" RESET, i, VECTOR[i].habitacion);
        //Chequeo sus arcos
        for (j = 0; j < N; j++) {
            if (son_adyacentes(G, i, j, 'T')) {
                printf("\t\t%s " BOLDGREEN "- %i -" RESET " %s\n", VECTOR[i].habitacion, valor_arco(G, i, j, 'T'), VECTOR[j].habitacion);
            }
            if (son_adyacentes(G, i, j, 'I')){ //&& !son_adyacentes(G, i, j, 'T')) {    // Solo se imprime si los tripulantes no tienen camino
                printf("\t\t%s " BOLDRED "• %i •" RESET " %s\n", VECTOR[i].habitacion, valor_arco(G, i, j, 'I'), VECTOR[j].habitacion);
            }
        }
    }
}

// Lee el mapa de archivo. En mi implementación el nombre de mapa se pone al principio del archivo y las tareas antes de las conexiones.
void leerGrafoArchivo(grafo *G, char *archivo) {
    char path[MAXCHAR+MAXMAPSPATH] = MAPSPATH;
    char hab[MAXCHAR];
    if (archivo == NULL) {
        strncpy(archivo, DEFAULTMAP, MAXCHAR);     // Mapa por defecto
    }
    strncat(path, archivo, MAXCHAR+MAXMAPSPATH);
    FILE *fp = fopen(path, "rt");
    if (fp) {
        char linea[MAXCHAR * 2], codigos[3];
        int coste, ind, num = 0;
        // En mi implementación el nombre de mapa se pone al principio del archivo
        fscanf(fp, "%[^\r\n]\n", linea);                  // Leo el nombre del mapa
        cambiar_nombre_grafo(*G, linea);                        // Le cambio el nombre
        fscanf(fp, "%[^\r\n]\n", linea);                  // Lee el *
        tipovertice v1, v2;
        fscanf(fp, "%[^\r\n]\n", linea);                  // Lee la primera habitación
        while (linea[0] != '*') {                               // Lee todas las habitaciones hasta *
            sscanf(linea, "%[^:]:%hu", v1.habitacion, &v1.numTareas);
            fscanf(fp, "%[^\r\n]\n", linea);
            if (v1.numTareas == 0) {                            // Si una habitación no tiene tareas, inicializa sus valores
                strncpy(v1.tareas->descripcionTarea, "No hay tareas", MAXCHAR);
                v1.tareas->costeTarea = 0;
            }
            num++;
            insertar_vertice(G, v1);                            // Inserto la habitación
        }
        cambiar_num_vertices(*G, num);      // Inicializo el número de vertices del grafo
        num = 0;
        fscanf(fp, "%[^\r\n]\n", linea);                  // Lee la primera tarea
        for (int i = 0; i < num_vertices(*G); i++) {
            if (linea[0] == '*') {
                break;                  // Si llego al final de las tareas, salgo
            }
            sscanf(linea, "%[^:]", hab);
            ind = buscar_vertice(*G, hab, &v1);
            if (ind == -1) {
                printf(BOLDRED "Error: No se encontró la habitación %s. Mapa posiblemente corrupto.\n" RESET, v1.habitacion);
                exit(EXIT_FAILURE);
            }
            for (int j = 0; j < array_vertices(*G)[ind].numTareas; j++) {
                // En mi implementación las tareas se guardan como Habitación:Coste:Tarea
                sscanf(linea, "%[^:]:%hi:%[^\r\n]\n", v1.habitacion, &v1.tareas[j].costeTarea, v1.tareas[j].descripcionTarea);
                fscanf(fp, "%[^\r\n]\n", linea);
                num++;
            }
            insertar_vertice(G, v1);        // Inserto la habitación actualizada
        }
        cambiar_num_tareas(*G, num);      // Inicializo el número de tareas del grafo
        while (!feof(fp)) {
            fscanf(fp, "%[^\r\n]\n", linea);
            sscanf(linea, "%[^-.]%[-.]%d-%s", v1.habitacion, codigos, &coste, v2.habitacion);
            if (codigos[0] == '-') {                                                 // ID Tripulante
                crear_arco(G, posicion(*G, v1), posicion(*G, v2), coste, 'T');
            } else {                                                                 // ID Impostor
                crear_arco(G, posicion(*G, v1), posicion(*G, v2), coste, 'I');
            }
        }
        printf(BOLDGREEN "Mapa %s cargado correctamente.\n" RESET, archivo);
        fclose(fp);
    } else {
        printf(BOLDRED "Error: El mapa %s no existe.\n" RESET, archivo);
    }
}


// Guarda el grafo en archivo
void guardarGrafoArchivo(grafo G, char opt) {
    char nMapa[MAXCHAR], path[MAXCHAR+MAXMAPSPATH] = MAPSPATH;
    crearCarpeta(MAPSPATH);
    if (opt) {                  // Opción para guardar el mapa en un archivo diferente
        printf(BOLD "Nombre del mapa: " RESET);
        scanf("%39s", nMapa);
        cambiar_nombre_grafo(G, nMapa);
    } else {
        strncpy(nMapa, nombre_grafo(G), MAXCHAR);
    }
    strncat(path, nMapa, MAXCHAR+MAXMAPSPATH);
    FILE *fp = fopen(path, "w");
    if (fp) {
        tipovertice *vertices   = array_vertices(G);
        int numVertices = num_vertices(G);
        // En mi implementación el nombre de mapa se pone al principio del archivo y después se separa de las habitaciones con *
        fprintf(fp, "%s\n", nombre_grafo(G));
        fprintf(fp, "*\n");
        // Guarda los vértices y el número de tareas de cada uno
        for (int i = 0; i < numVertices; i++) {
            fprintf(fp, "%s:%hi\n", vertices[i].habitacion, vertices[i].numTareas);
        }
        fprintf(fp, "*\n");  // Caracter de separación
        // Guarda las tareas de cada habitación
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < vertices[i].numTareas; j++) {
                fprintf(fp, "%s:%hi:%s\n", vertices[i].habitacion, vertices[i].tareas[j].costeTarea, vertices[i].tareas[j].descripcionTarea);
            }
        }
        fprintf(fp, "*\n");  // Caracter de separación
        // Guarda los arcos
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (son_adyacentes(G, i, j, 'T')) {
                    fprintf(fp, "%s--%i-%s\n", vertices[i].habitacion, valor_arco(G, i, j, 'T'), vertices[j].habitacion);
                }
                if (son_adyacentes(G, i, j, 'I')) {
                    fprintf(fp, "%s..%i-%s\n", vertices[i].habitacion, valor_arco(G, i, j, 'I'), vertices[j].habitacion);
                }
            }
        }
        printf(BOLDGREEN "Mapa %s guardado correctamente.\n" RESET, nMapa);
        fclose(fp);
    } else {
        printf(BOLDRED "Error: El mapa %s no se ha podido crear.\n" RESET, nMapa);
    }
}

// Carga el grafo desde un archivo
void cargarGrafo(grafo *G) {
    char archivo[MAXCHAR];
    if (!crearCarpeta(MAPSPATH)) {
        printf("\nMapas disponibles para cargar:\n");
        system("ls --color ./Mapas");
        printf("Opción: ");
        scanf(" %39s", archivo);
        borrar_grafo(G);                                    // Borra el grafo antes de cargar uno nuevo
        crear_grafo(G, archivo);
        leerGrafoArchivo(G, archivo);
    } else {
        printf(BOLDRED "No hay mapas disponibles para cargar.\n" RESET);
    }
}

// Función para eliminar un mapa
void _eliminarMapa(grafo *mapa) {
    char nMapa[MAXCHAR], command[MAXCHAR+MAXMAPSPATH+4] = "rm ";
    strncat(command, MAPSPATH, MAXMAPSPATH+4);
    printf("\nNombre del mapa a eliminar: ");
    scanf("%39s", nMapa);
    strncat(command, nMapa, MAXCHAR+MAXMAPSPATH+4);
    system(command);
    char path[MAXCHAR+MAXMAPSPATH] = MAPSPATH;
    strncat(path, nMapa, MAXCHAR+MAXMAPSPATH);
    struct stat existe;
    if (stat(path, &existe) == 0) {
        printf(BOLDRED "Error: No se ha podido eliminar el mapa %s.\n" RESET, nMapa);
    } else {
        printf(BOLDGREEN "Mapa %s eliminado correctamente.\n" RESET, nMapa);
    }
    if (strcmp(nombre_grafo(*mapa), nMapa) == 0) {      // Si se quiere eliminar el grafo actual
        borrar_grafo(mapa);
        crear_grafo(mapa, "Mapa1");
    }
}

// Inserta una tarea en una habitación del mapa
void _insertarTareaGrafo(grafo *G) {
    tipoelemcola t;
    strncpy(t.ubicacionTarea, pedirHabitacion(*G), MAXCHAR);
    printf("\nDescripción de la tarea: ");
    scanf(" %39[^\r\n]", t.atrib.descripcionTarea);
    printf("Coste de la tarea: ");
    scanf(" %hu", &t.atrib.costeTarea);
    insertar_tarea_grafo(G, t);
}

// Elimina una tarea de una habitación del mapa
void _eliminarTareaGrafo(grafo *G) {
    tipoelemcola t;
    strncpy(t.ubicacionTarea, pedirHabitacion(*G), MAXCHAR);
    eliminar_tarea_grafo(G, t);
}


// Imprime las tareas del mapa
void _imprimirTareasGrafo(grafo G) {
    int n = num_vertices(G);
    printf("Tareas disponibles:\n");
    for (int i = 0; i < n; i++) {
        printf(BOLD "%s:\n" RESET, array_vertices(G)[i].habitacion);
        // Si no tiene tareas
        if (array_vertices(G)[i].numTareas == 0) {
            printf("\tNo hay tareas disponibles.\n");
        }
        // Si tiene tareas
        for (int j = 0; j < array_vertices(G)[i].numTareas; j++) {
            printf(BOLDYELLOW "\t%-30s" RESET " con coste %hu\n", array_vertices(G)[i].tareas[j].descripcionTarea, array_vertices(G)[i].tareas[j].costeTarea);
        }
    }
}

void _menuExtras() {
    printf(BOLD "\nOpciones avanzadas\n\t" RESET "a) Árbol de expansión de coste mínimo.\n\tr) Ruta más rápida entre dos habitaciones.\n\tq) Atrás.\n");
}

void _extras(grafo mapa) {
    char opt;
    do {
        _menuExtras();
        printf("Opción: ");
        scanf(" %c", &opt);
        switch (opt) {
            case 'a': case 'A':
                // Árbol de expansión de coste mínimo
                arbolExpansionMinimo(mapa);
                opt = 'q';
                break;
            case 'r': case 'R':
                // Ruta más rápida entre dos habitaciones
                rutaMinimaEntreHabitaciones(mapa);
                opt = 'q';
                break;
            case 'q': case 'Q':
                break;
            default:
                printf(BOLDRED "%c: " RESET "Opción incorrecta.\n", opt);
        }
    } while (opt != 'q' && opt != 'Q');
}

void _menuAEMaps(char mapa[]) {
    printf(BOLD "\nMenú edición de mapa\n" RESET "Mapa seleccionado: " BOLDBLUE "%s\n\t" RESET "a) Añadir habitación.\n\t"
           "b) Eliminar habitación.\n\tc) Crear comunicación.\n\td) Eliminar comunicación.\n\tf) Añadir tarea.\n\th) Eliminar tarea.\n\tt) Imprimir tareas.\n\t"
           "i) Imprimir mapa.\n\te) Eliminar mapa.\n\tg) Guardar archivo y salir.\n\ts) Guardar nuevo mapa y salir.\n\t"
           "x) Opciones avanzadas.\n\tq) Salir.\n", mapa);
}


// Función para el submenú de edición de mapa
void AEMaps(grafo *mapa) {
    char opt;
    do {
        _menuAEMaps(nombre_grafo(*mapa));
        printf("Opción: ");
        scanf(" %c", &opt);
        switch (opt) {
            case 'a': case 'A':
                // Añadir habitación
                introducir_vertice(mapa);
                break;
            case 'b': case 'B':
                // Eliminar habitación
                eliminar_vertice(mapa);
                break;
            case 'c': case 'C':
                // Crear comunicación
                nuevo_arco(mapa);
                break;
            case 'd': case 'D':
                // Eliminar comunicación
                eliminar_arco(mapa);
                break;
            case 'E': case 'e':
                _eliminarMapa(mapa);
                break;
            case 'g': case 'G':
                // Sobrescribir mapa seleccionado
                guardarGrafoArchivo(*mapa, 0);
                opt = 'q';
                break;
            case 'i': case 'I':
                // Imprimir mapa
                imprimir_grafo(*mapa);
                sleep(2);
                break;
            case 'f': case 'F':
                _insertarTareaGrafo(mapa);
                break;
            case 'h': case 'H':
                // Eliminar tarea
                _eliminarTareaGrafo(mapa);
                break;
            case 't': case 'T':
                // Imprimir tareas
                _imprimirTareasGrafo(*mapa);
                sleep(2);
                break;

            case 's': case 'S':
                // Guardar en nuevo mapa
                guardarGrafoArchivo(*mapa, 1);
                opt = 'q';
                break;
            case 'x': case 'X':
                // Opciones avanzadas
                _extras(*mapa);
                break;
            case 'q': case 'Q':
                // Salir sin guardar
                opt = 'q';
                break;
            default:
                printf(BOLDRED "%c: " RESET "Opción incorrecta.\n", opt);
        }
    } while (opt != 'q');

}

// Función que imprime el camino mínimo entre dos habitaciones
void rutaMinimaEntreHabitaciones(grafo G) {
    char origen[MAXCHAR], destino[MAXCHAR], opt;
    tipovertice orig, dest;
    printf("Habitación origen: ");
    scanf(" %39s", origen);
    printf("Habitación destino: ");
    scanf(" %39s", destino);
    printf("Tipo de jugador a aplicar (T/I): ");
    scanf(" %c", &opt);
    strncpy(orig.habitacion, origen, strlen(origen)+1);
    strncpy(dest.habitacion, destino, strlen(destino)+1);
    distanciaMinima(G, orig, dest, NULL, NULL, opt, 1);
}

// Función que imprime el árbol de expansión de coste mínimo
void arbolExpansionMinimo(grafo G) {
    char opt;
    printf("Tipo de jugador a aplicar (T/I): ");
    scanf(" %c", &opt);
    int selected[MAXHAB];
    memset(selected, 0, MAXHAB * sizeof(int));  // Inicializa el vector a 0
    tipovertice * vertices = array_vertices(G);
    int numArcos = 0, distanciaTotal = 0, N = num_vertices(G), minimo, vx, vy;
    // Seleccionamos el primer vértice
    selected[0] = 1;
    while (numArcos < N - 1) {
        minimo = INFINITY;
        vx = 0, vy = 0;
        for (int i = 0; i < N; i++) {
            if (selected[i] == 1) {
                for (int j = 0; j < N; ++j) {
                    if (selected[j] != 1)
                        if (son_adyacentes(G, i, j, opt)) {
                        if (minimo > valor_arco(G, i, j, opt)) {
                            minimo = valor_arco(G, i, j, opt);
                            vx = i, vy = j;
                        }
                    }
                }
            }
        }
        selected[vy] = 1, numArcos++;
        // Imprime cada arco
        printf("%15s -- %-15s : %i\n", vertices[vx].habitacion, vertices[vy].habitacion, valor_arco(G, vx, vy, opt));
        distanciaTotal = distanciaTotal + valor_arco(G, vx, vy, opt);
    }
    printf(BOLD "Distancia total del árbol de expansión de coste mínimo: %i\n" RESET, distanciaTotal);
}
