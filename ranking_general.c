#include "config.h"

// Función para ordenar el ranking alfabéticamente por el nombre de los jugadores
void mergeSort(Jugador arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

void merge(Jugador arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Usamos punteros dinámicos para evitar problemas con la memoria
    Jugador *L = malloc(n1 * sizeof(Jugador));
    Jugador *R = malloc(n2 * sizeof(Jugador));

    if (L == NULL || R == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);  // Si no se pudo asignar memoria, termina el programa
    }

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        // Compara alfabéticamente por el nombre de los jugadores
        if (strcmp(L[i].nombre, R[j].nombre) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Liberamos la memoria
    free(L);
    free(R);
}

// Función para leer los jugadores del archivo ranking_combinado.txt
int leer_ranking_combinado(Jugador jugadores[], int numJugadores) {
    FILE *archivo = fopen("ranking_combinado.txt", "r");
    if (archivo == NULL) {
        return numJugadores; // Si no hay archivo, no hacemos nada
    }

    char linea[256];
    while (fgets(linea, sizeof(linea), archivo)) {
        if (numJugadores >= MAX_JUGADORES) {
            break;  // Evita desbordar el arreglo de jugadores
        }
        Jugador jugador_temp;
        // Asumimos que el archivo tiene el formato: Nombre, Ganancias, Perdidas
        sscanf(linea, "%[^,], %d, %d", jugador_temp.nombre, &jugador_temp.dinero_ganado, &jugador_temp.dinero_perdido);

        jugadores[numJugadores] = jugador_temp;
        numJugadores++;
    }

    fclose(archivo);
    return numJugadores;
}

// Función para generar y guardar el ranking combinado
void generar_ranking_combinado(Jugador jugadores[], int numJugadores) {
    // Leer los jugadores previos
    numJugadores = leer_ranking_combinado(jugadores, numJugadores);

    // Ordenar los jugadores alfabéticamente por nombre
    mergeSort(jugadores, 0, numJugadores - 1);

    // Guardar el ranking combinado en el archivo
    FILE *archivo = fopen("ranking_combinado.txt", "w");
    if (archivo == NULL) {
        printf("Error al guardar el ranking combinado.\n");
        return;
    }

    for (int i = 0; i < numJugadores; i++) {
        fprintf(archivo, "%s, %d, %d\n", jugadores[i].nombre, jugadores[i].dinero_ganado, jugadores[i].dinero_perdido);
    }

    fclose(archivo);
}

// Función para mostrar el ranking combinado con formato
void mostrar_ranking_combinado() {
    FILE *archivo = fopen("ranking_combinado.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de ranking combinado.\n");
        return;
    }

    char linea[256];
    printf("\n------------------- RANKING COMBINADO -------------------\n");
    printf("Nombre\t\t\tGanancias\t\tPerdidas\n");
    while (fgets(linea, sizeof(linea), archivo)) {
        char nombre[100];
        int ganancias, perdidas;
        // Leer los datos del archivo
        sscanf(linea, "%[^,], %d, %d", nombre, &ganancias, &perdidas);
        // Imprimir en formato adecuado
        printf("%-20s\t%-10d\t\t%-10d\n", nombre, ganancias, perdidas);
    }

    fclose(archivo);
}
