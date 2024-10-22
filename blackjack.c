#include<stdio.h>
#include<string.h>

typedef struct{
    int valor; // valor de carta(1-11)
    const char*nombre; //nombre de carta("A","2"..."Q","K")
}carta;

typedef struct{
    carta Cartas[10];// cartas max del jugador
    int numeroCartas; // numero de cartas actuales
}jugador;

void imprimirSaludo(char nombre[]);

void choose_opt(int *opt);

void mezclar(){};

int tomarCarta(int *valorCarta);

int calcularPuntos(int mano[],int contadorCarta);

void imprimirReglas();

void jugarBlackJack();



int main(){
    int opt=0;
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

    char name[100];

    printf("\n ingrese su nombre:");

    fgets(name,sizeof(name),stdin);
    imprimirSaludo(name);

    choose_opt(&opt);

return 0;
}

void imprimirSaludo(char nombre[]){   
    size_t len=strlen(nombre);
    if(len>0 && nombre[len-1]=='\n'){        //funcion de imprimir saludo
        nombre[len-1]='\0';
    }
    printf("\n HOLA %s! Bienvenido a BLACKJACK \n",nombre);
}

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
                imprimirReglas();
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
void imprimirReglas(){
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