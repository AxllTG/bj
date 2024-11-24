#include "config.h"

// Menu principal
void choose_opt(int *opt, Jugador jugadores[], int *numJugadores){  // Función de elegir opción
    do {
        printf("\n\t==========================================================\n");
        printf("\n\tMonto Inicial: %d\t\t\tMonto Final: %d\n", jugadores->monto_inicial, jugadores->monto_apuesta);
        printf("\n\t==========================================================\n");
        printf("\n\t1) Jugar\n");
        printf("\t2) Lista de jugadores\n");
        printf("\t3) Ver reglas\n");
        printf("\t4) Registros de partidas\n");
        // printf("\t5) Ver ranking de perdedores\n");
        printf("\t5) Salir del juego\n");
        printf("\n\tOpción: ");
        scanf("%d", opt);
        getchar(); // limpia el buffer

        switch (*opt) {
            // ------ case 1: funciones de juego contenidos en archivo jugar_bj.c ------
            case 1:
                if(jugadores->monto_apuesta > 50){
                    if (*numJugadores > 0) {
                    printf("\n\tOpción %d elegida: Jugar\n", *opt);
                    // Cargar datos de los jugadores antes de comenzar
                    // cargar_datos_jugadores(jugadores, *numJugadores);
                    int cartas[MAX_CARTAS];
                    barajar(cartas); // Baraja cartas
                    jugar_blackjack(cartas, jugadores, *numJugadores);
                    } else {
                        printf("No hay jugadores para jugar.\n");
                    }
                } else {
                    printf("\n\tGAME OVER! No tienes dinero suficiente para jugar\n");

                }

                break;
      
            case 2:
                printf("\n\tOpción %d elegida: LISTA DE JUGADORES \n", *opt);
                imprimir_jugadores(jugadores, *numJugadores);
                break;

            case 3:
                printf("\n\tOpción %d elegida: VER REGLAS \n", *opt);
                imprimir_reglas();
                break;

            case 4:
                printf("\n\tOpción %d elegida: Registros partidas: \n", *opt);
                printf("\n\t------------------ REGISTROS ------------------\n");
                mostrar_contenido_archivo("registros_partidas.txt");
                break;

            case 5:
                printf("\n\tSALIENDO DEL JUEGO!\n");
                break;

            default:
                printf("\n\tOpción no válida. Por favor, elija nuevamente.\n");
                break;
        }
    } while (*opt != 5);
}

// Imprimir reglas
void imprimir_reglas(){
    printf("\n\t-----------------------------------------------------------------------------------------------------\n");
    printf("\n\t1) Objetivo: Acercarse lo más posible a 21 puntos sin pasarse.\n ");
    printf("\n\t2) Valor de las cartas: Las cartas numéricas valen su número.\n");
    printf("\t\t-> Las figuras (J, Q, K) valen 10 puntos.\n");
    printf("\t\t-> El As vale 1 o 11, según lo que más beneficie al jugador.\n");
    printf("\n\t3) Reparto: El crupier reparte dos cartas al jugador y dos para sí mismo (una boca arriba y otra boca abajo).\n");
    printf("\n\t4) Acciones del jugador: Pedir carta (Hit): Recibir una carta adicional.\n");
    printf("\t\t-> Plantarse (Stand): No recibir más cartas.\n");
    printf("\n\t5) Crupier: Debe pedir cartas hasta tener al menos 17 puntos. Si supera 21, pierde.\n");
    printf("\n\t6) Ganar: Gana quien tenga 21 puntos o esté más cerca sin pasarse. Si se empatan los puntos, es un 'push' (empate).\n");
    printf("\n\t-----------------------------------------------------------------------------------------------------");
}

// Imprimir lista de jugadores
void imprimir_jugadores(Jugador jugadores[], int numJugadores){
    if (numJugadores == 0) {
        printf("No hay jugadores para mostrar.\n");
    } else {
        for (int i = 0; i < numJugadores; i++) {
            printf("\tJugador[%d]: %s\n", i + 1, jugadores[i].nombre);
        }
    }
}

void saludo_bienvenida(Jugador jugadores[], int numJugadores){
    printf("\n\tBienvenido/a %s\n", jugadores[0].nombre);
}
