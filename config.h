#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_CARTAS 52 // maximo de cartas en un mazo americano
#define CARTAS_JUGADOR 10 // cantidad maxima de cartas de un jugador/crupier
#define MAX_JUGADORES 4 // máximo de jugadores permitidos

// Estructura para un jugador
typedef struct {
    char nombre[100];
    int mano[CARTAS_JUGADOR];
    int suma; // contador de cartas
    int monto_inicial; // Muestra el Dinero inicial
    int monto_apuesta; // Dinero que se usa para apostar, puede cambiar segun las ganancias y perdidas por partida.
    int dinero_apostado; // Dinero que realmente se aposto en la partida
    int dinero_perdido; // Muestra el dinero que se perdio
    int dinero_ganado; // Muestra el dinero que se gano
    int partidas_ganadas; // contador de partidas ganadas
    int partidas_perdidas; // contador de partidas perdidas
    int partidas_empatadas; // contador de partidas empatadas
    int contador_ganancias;
    int contador_perdidas;
} Jugador;

// funcion 'choose_opt' de seleccion de opciones del juego
void choose_opt(int *opt, Jugador jugadores[], int *numJugadores);
// funcion 'imprimir_jugadores', pensado para su uso cuando hay mas jugadores en juego, en este caso solo se muestra un jugador, dado que optamos por hacer partidas de juego de un usuario vs maquina
void imprimir_jugadores(Jugador jugadores[], int numJugadores);
void saludo_bienvenida(Jugador jugadores[], int numJugadores);
void imprimir_reglas();
void barajar(int cartas[]);
// funcion 'jugar_blackjack' contiene todo lo referente al juego 
void jugar_blackjack(int cartas[], Jugador jugadores[], int numJugadores);
int convertir_valor_carta(int carta, int *sumaActual);
void mostrar_carta(int carta);
void mostrar_mano(int mano[], int cantidad);
// funcion 'mostrar_resultado', muestra ganadores, perdedores, o empates, y los montos ganados o perdidos
void mostrar_resultado(Jugador jugadores[], int numJugadores, Jugador *crupier);
void turno_crupier(Jugador *crupier, int cartas[], int *indiceCarta);

// Funciones para el ranking combinado
void mergeSort(Jugador arr[], int left, int right);
void merge(Jugador arr[], int left, int middle, int right);
void generar_ranking_combinado(Jugador jugadores[], int numJugadores);
void mostrar_ranking_combinado(); 
int leer_ranking_combinado(Jugador jugadores[], int numJugadores);

// funciones para el registro de las partidas
void guardar_registro_partida(Jugador jugadores);
void mostrar_contenido_archivo(const char *nombreArchivo);

#endif
