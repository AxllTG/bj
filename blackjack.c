#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

#define MAX_CARTAS 52 // maximo de cartas en un mazo americano
#define CARTAS_JUGADOR 10

// prot. de funciones //
void imprimir_saludo(char nombre[]);
void choose_opt(int *opt);
void imprimir_reglas();
void barajar(int cartas[]);
void jugar_blackjack(int cartas[]);
int convertir_valor_carta(int carta);
int mostrar_carta(int carta);
void mostrar_mano(int mano[],int cantidad);


int main(){ 
    int opt=0;
    char name[100];

    FILE *archivo;
    char c;
    archivo=fopen("archivo.txt","r");
    if(archivo==NULL){
        printf("el archivo no se puede abrir.\n");
        return 1;
    }
    while((c=fgetc(archivo))!=EOF){
        printf("%c",c);
    }

    printf("\n");
    printf("\n");

    printf("\n ingrese su nombre:");

    fgets(name,sizeof(name),stdin);
    imprimir_saludo(name);

    choose_opt(&opt);

return 0;
}

// saludo del jugador // 
void imprimir_saludo(char nombre[]){   
    size_t len=strlen(nombre);
    if(len>0 && nombre[len-1]=='\n'){    
        nombre[len-1]='\0';
    }
    printf("\n HOLA %s! Bienvenido a BLACKJACK \n",nombre);
}

// menu principal //
void choose_opt(int *opt){  // funcion de elegir opcion
    do {
        printf("\n\n1) Jugar\n");
        printf("\n2) Ver reglas\n");
        printf("\n3) Salir del juego\n");
        printf("\nElija una opcion:");
        scanf("%d", opt);
        getchar();
        switch (*opt) {
            case 1:
                printf("\nOpcion 1 elegida: Jugar");
                break;
            case 2:
                printf("\nOPCION 2 ELEGIDA: VER REGLAS\n");
                imprimir_reglas();
                break;
            case 3:
                printf("\nSaliendo del juego.");
                break;      
            default:
                printf("\nOpcion no válida. Por favor, elija nuevamente.");
                break;
        }
    } while (*opt != 3);
}

// imprimir reglas //
void imprimir_reglas(){
    printf("\n\t-----------------------------------------------------------------------------------------------------\n");
    printf("\n1) Objetivo: Acercarse lo mas posible a 21 puntos sin pasarse.\n ");
    printf("\n2) Valor de las cartas: Las cartas numericas valen su numero.\n");
    printf("\t-> Las figuras (J, Q, K) valen 10 puntos.\n");
    printf("\t-> El As vale 1 o 11, segun lo que mas beneficie al jugador.\n");
    printf("\n3) Reparto: El crupier reparte dos cartas al jugador y dos para si mismo (una boca arriba y otra boca abajo).\n");
    printf("\n4) Acciones del jugador: Pedir carta (Hit): Recibir una carta adicional.\n");
    printf("\t-> Plantarse (Stand): No recibir mas cartas.\n");
    printf("\t-> Doblar (Double Down): Duplicar la apuesta y recibir solo una carta mas.\n");
    printf("\t-> Dividir (Split): Si las dos primeras cartas son iguales, se puede dividir en dos manos separadas.\n");
    printf("\n5) Crupier: Debe pedir cartas hasta tener al menos 17 puntos. Si supera 21, pierde.\n");
    printf("\n6) Ganar: Gana quien tenga 21 puntos o este mas cerca sin pasarse. Si se empatan los puntos, es un 'push'(empate)\n");
    printf("\n\t-----------------------------------------------------------------------------------------------------");
}

void barajar(int cartas[]){
    int mazo[MAX_CARTAS];

    for(int i = 0 ; i<MAX_CARTAS ; i++){
        mazo[i]=(i / 13 + 3) * 100 + i % 13 + 1; // representar cartas con codigo
    }


    srand(time(NULL));
    for(int i = 0; i<MAX_CARTAS; i++){
        int t;
        do{
            t=rand()% MAX_CARTAS;
        }while(mazo[t]==0);

        cartas[i]=mazo[t];
        mazo[t] = 0; // marca la carta como tomada
    }
}

void jugar_blackjack(int cartas[]){







}

int convertir_valor_carta(int carta){
    int valor = carta % 100;
    if(valor >=11 && valor<=13){ // J, Q, K
        return 10;
    }
    if(valor ==1){ // As
        return 11; // As es 11 inicialmente
    }
    return valor; // numeros del 2 al 10
}


