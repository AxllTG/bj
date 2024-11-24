#include "config.h"

// void merge(Jugador jugadores[], int left, int mid, int right) {
//     int n1 = mid - left + 1;
//     int n2 = right - mid;

//     // Asignación dinámica de memoria
//     Jugador *L = (Jugador *)malloc(n1 * sizeof(Jugador));
//     Jugador *R = (Jugador *)malloc(n2 * sizeof(Jugador));

//     // Verificar si la asignación fue exitosa
//     if (L == NULL || R == NULL) {
//         printf("Error al asignar memoria.\n");
//         exit(EXIT_FAILURE); // Terminar el programa en caso de error
//     }

//     // Copiar datos a los arreglos temporales L[] y R[]
//     for (int i = 0; i < n1; i++)
//         L[i] = jugadores[left + i];
//     for (int i = 0; i < n2; i++)
//         R[i] = jugadores[mid + 1 + i];

//     int i = 0, j = 0, k = left;

//     // Mezclar los arreglos L[] y R[] en jugadores[]
//     while (i < n1 && j < n2) {
//         if (L[i].contador_ganancias >= R[j].contador_ganancias) {
//             jugadores[k] = L[i];    
//             i++;
//         } else {
//             jugadores[k] = R[j];
//             j++;
//         }
//         k++;
//     }

//     // Copiar los elementos restantes de L[], si los hay
//     while (i < n1) {
//         jugadores[k] = L[i];
//         i++;
//         k++;
//     }

//     // Copiar los elementos restantes de R[], si los hay
//     while (j < n2) {
//         jugadores[k] = R[j];
//         j++;
//         k++;
//     }

//     // Liberar la memoria dinámica asignada
//     free(L);
//     free(R);
// }


// void merge_sort(Jugador jugadores[], int left, int right) {
//     if (left < right) {
//         int mid = left + (right - left) / 2;

//         merge_sort(jugadores, left, mid);
//         merge_sort(jugadores, mid + 1, right);

//         merge(jugadores, left, mid, right);
//     }
// }

void mostrar_contenido_archivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s para mostrar su contenido.\n", nombreArchivo);
        return;
    }

    char linea[256];
    while (fgets(linea, sizeof(linea), archivo)) {
        printf("%s", linea); // Imprime cada línea del archivo
    }
    printf("\t---------------------------------------------------");
    printf("\n");
    fclose(archivo);
}
