#include "config.h"

// Comparar jugadores para el ranking combinado
int comparar_combinado(const void *a, const void *b) {
    const Jugador *jugadorA = (const Jugador *)a;
    const Jugador *jugadorB = (const Jugador *)b;

    // Primero, comparar por ganancias
    if (jugadorB->contador_ganancias != jugadorA->contador_ganancias) {
        return jugadorB->contador_ganancias - jugadorA->contador_ganancias;
    }

    // Si las ganancias son iguales, ordenar por menor cantidad de pérdidas
    return jugadorA->contador_perdidas - jugadorB->contador_perdidas;
}

// Mostrar ranking combinado en un archivo
void guardar_ranking_combinado(Jugador jugadores[], int numJugadores) {
    if (numJugadores == 0) {
        printf("No hay jugadores registrados. El ranking está vacío.\n");
        return;
    }

    // Crear una copia para no modificar el arreglo original
    Jugador copiaJugadores[MAX_JUGADORES];
    memcpy(copiaJugadores, jugadores, sizeof(Jugador) * numJugadores);

    // Ordenar jugadores usando la función comparar_combinado
    qsort(copiaJugadores, numJugadores, sizeof(Jugador), comparar_combinado);

    //----------------------------------------------------------------- 
    //----------------------------------------------------------------- 
    //-------- ACA NECESITO QUE REALICES EL ORDENAMIENTO ANTES DE GUARDAR EN EL ARCHIVO ------------------ 
    //----------------------------------------------------------------- 
    //----------------------------------------------------------------- 


    // Abrir el archivo para escribir el ranking
    FILE *archivo = fopen("ranking_combinado.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escribir\n");
        return;
    }

    // Escribir el encabezado solo si el archivo está vacío (primer ranking guardado)
    if (ftell(archivo) == 0) { // Si el archivo está vacío, agregar el encabezado
        fprintf(archivo, "\n\t---------------- RANKING COMBINADO -----------------\n");
        fprintf(archivo, "\tNombre\t\t\tGanancias\tPérdidas\n");
    }

    // Escribir cada jugador en el archivo
    for (int i = 0; i < numJugadores; i++) {
        fprintf(archivo, "\t%-20s\t%d\t\t%d\n",
            // i + 1,  // Posición del jugador (i+1 para numerar desde 1)
            copiaJugadores[i].nombre,  // Nombre del jugador
            copiaJugadores[i].contador_ganancias,  // Número de ganancias del jugador
            copiaJugadores[i].contador_perdidas);  // Número de pérdidas del jugador
    }

    fclose(archivo);
}
