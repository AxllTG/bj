/* tp final de algoritmica y programacion. La fecha de entrega es el día lunes 25/11/2023 y su correspondiente presentación será el miércoles 27
o viernes 29 de noviembre.               */


#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

#define MAX_CARTAS 52 // maximo de cartas en un mazo americano
#define CARTAS_JUGADOR 10 // cantidad maxima de cartas de un jugador/crupier

// prot. de funciones //
void imprimir_saludo(char nombre[]);
void choose_opt(int *opt,char nombre[]);
void imprimir_reglas();
void barajar(int cartas[]);
void jugar_blackjack(int cartas[], char nombre[]);
int convertir_valor_carta(int carta, int *sumaActual);
int mostrar_carta(int carta);
void mostrar_mano(int mano[],int cantidad);
void mostrar_ranking_ganador();
void mostrar_perdedore();
void guardar_ganador(char nombre[]);
void guardar_perdedor(char nombre[]);


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

    choose_opt(&opt,name);

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
void choose_opt(int *opt, char nombre[]){  // funcion de elegir opcion
    do {
        printf("\n1) Jugar\n");
        printf("\n2) Ver reglas\n");
        printf("\n3) Ver ranking de ganadores\n");
        printf("\n4) Ver ranking de perdedores\n");
        printf("\n5) Salir del juego\n");
        printf("\n");
        scanf("%d", opt);
        getchar(); // limpia el buffer
        switch (*opt) {
            case 1:
                printf("\nOpcion 1 elegida: Jugar\n");
                int cartas[MAX_CARTAS];
                barajar(cartas); // baraja cartas
                jugar_blackjack(cartas, nombre);
                break;

            case 2:
                printf("\nOPCION 2 ELEGIDA: VER REGLAS\n");
                imprimir_reglas();
                break;

            case 3:
                printf("\nOPCION 3 ELEGIDA: Ver ranking ganadores:\n");
                mostrar_ranking_ganador();
                break;

            case 4:
            printf("OPCION 4 ELEGIDA: ver ranking perdedores:\n");
            mostrar_perdedore();
            break;

            case 5:
            printf("SALIENDO DEL JUEGO!");
            break;

            default:
                printf("\nOpcion no valida. Por favor, elija nuevamente.");
                break;
        }
    } while (*opt != 5);
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

void jugar_blackjack(int cartas[],char nombre[]){
    int manoJugador[CARTAS_JUGADOR]={0};
    int manoCrupier[CARTAS_JUGADOR]={0};
    int sumaJugador = 0, sumaCrupier= 0;
    srand(time(NULL));

//Reparte cartas iniciales
manoJugador[0] = cartas[(rand()%10)+1];
manoJugador[1]= cartas[(rand()%10)+1];

manoCrupier[0]=cartas[(rand()%10)+1];
manoCrupier[1]=cartas[(rand()%10)+1];

printf("CARTAS DEL CRUPIER:\n");

printf("\n");

mostrar_carta(manoCrupier[50]);

printf("TUS CARTAS:\n");

printf("\n");

mostrar_mano(manoJugador, 2);

for(int i = 0;i < 2 ;i++){
    sumaJugador += convertir_valor_carta(manoJugador[i],&sumaJugador);
}

printf("TU TOTAL: %d\n",sumaJugador);

char opcion;
    while(sumaCrupier < 21){
        printf("Deseas pedir otra carta? (s/n): ");
        opcion=getchar();
        getchar();
        if(opcion == 's'){
            manoJugador[2]=(rand()%10)+1;
            printf("DIBUJASTE: \n");

            printf("\n");

            mostrar_carta(manoJugador[2]);
            sumaJugador += convertir_valor_carta(manoJugador[2],&sumaJugador);
            printf("TU TOTAL: %d\n",sumaJugador);
        }else{
            break; // el jugador no pide cartas;
        }
    }

    if(sumaJugador > 21){
        printf("Te pasaste de 21. GANA EL CRUPIER!\n");
        guardar_perdedor(nombre);
        printf("Nombre del jugador: %s - Resultado: ¡Perdiste!\n", nombre);
        return;
    }

    // turno del crupier
    printf("CARTAS DEL CRUPIER: \n");

    printf("\n");

    mostrar_mano(manoCrupier,2);

    //suma inicial del crupier
    sumaCrupier=convertir_valor_carta(manoCrupier[0],&sumaCrupier)+convertir_valor_carta(manoCrupier[1],&sumaCrupier);

    //juega el crupier
    while(sumaCrupier<17){
        manoCrupier[2] = (rand()%10)+1; // siguiente carta
        printf("EL CRUPIER DIBUJO:\n");

        printf("\n");

        mostrar_carta(manoCrupier[2]);
        sumaCrupier += convertir_valor_carta(manoCrupier[2],&sumaCrupier);
    }

    printf("TOTAL DEL CRUPIER: %d\n",sumaCrupier);

    if(sumaCrupier > 21 || sumaJugador > sumaCrupier){
        printf("FELICIDADES GANASTE!\n");
        guardar_ganador(nombre);
        printf("Nombre del jugador: %s - Resultado: ¡Ganaste!\n", nombre);
    }else if(sumaJugador < sumaCrupier){
        printf("GANA EL CRUPIER!.\n");
        guardar_perdedor(nombre);
        printf("Nombre del jugador: %s - Resultado: ¡Perdiste!\n", nombre);
    }else if(sumaJugador == 21){
    printf("\tBLACKJACK!!!!!!");
    guardar_ganador(nombre);
    printf("Nombre del jugador: %s - Resultado: ¡Ganaste!\n", nombre);
    }else if(sumaCrupier == 21){
    printf("JKASJKASJA TE DIBUJARON UN BLAKJACK!!!!!!");
    guardar_perdedor(nombre);
    printf("Nombre del jugador: %s - Resultado: ¡Perdiste!\n", nombre);
    }else{
        printf("EMPATE??.\n");
        printf("Nombre del jugador: %s - Resultado: Empate.\n", nombre);
    }
}

int convertir_valor_carta(int carta, int *sumaActual){
    int valor = carta % 100;
    if(valor >=11 && valor<=13){ // J, Q, K
        return 10;
    }
    if(valor==1){
        if(*sumaActual+11>21){
            return 1;
        }else{
            return 11;
        }
    }
    return valor;
}

int mostrar_carta(int carta){
    char palo = carta / 100; // Determina el palo de la carta
    int valor = carta %100;

    printf("\t\t*******\n");
    printf("\t\t*     *\n");
    printf("\t\t* %c   *\n", palo);
    ;

    if(valor == 1){
        printf("\t\t*   A *\n");
    }else if(valor >= 2 && valor <= 10){
        printf("\t\t*  %2d *\n", valor);
    }else if(valor == 11){
        printf("\t\t*   J *\n");
    }else if(valor == 12){
        printf("\t\t*   Q *\n");
    }else if(valor == 13){
        printf("\t\t*   K *\n");
    }

printf("\t\t*     *\n");
printf("\t\t*******\n");
}



//mostrar mano del crupier o del jugador
void mostrar_mano(int mano[],int cantidad){
    for(int i = 0;i< cantidad;i++){
        mostrar_carta(mano[i]);
    }
}


void guardar_ganador(char nombre[]){
    FILE *archivo = fopen("ranking.txt","a");
    if(archivo != NULL){
        fprintf(archivo, "%s\n",nombre);
        fclose(archivo);
    }else{
        printf("Error al abrir el archivo de ganadores.\n");
    }
}


void guardar_perdedor(char nombre[]){
    FILE *archivo = fopen("perdedores.txt","a");
    if(archivo != NULL){
        fprintf(archivo, "%s\n",nombre);
        fclose(archivo);
    }else{
        printf("Error al abrir el archibo de perdedores.\n");
    }
}

void mostrar_ranking_ganador(){
    FILE *archivo = fopen("ranking.txt","r");
    if(archivo == NULL){
        printf("Error al abrir el archivo de ranking de ganadores.\n");
        return;
    }

    printf("------------------------------------------------------");
    printf("\n");
    printf("\n RANKING DE GANADORES: \n");
    char linea[100];
    while(fgets(linea,sizeof(linea),archivo)){
        printf(" %s",linea);
    }
    fclose(archivo);
    printf("\n");
    printf("------------------------------------------------------");
}

void mostrar_perdedore(){
    FILE *archivo = fopen("perdedores.txt","r");
    if(archivo==NULL){
        printf("Error al abrir el archibo de ranking de perdedores,\n");
        return;
    }
    printf("-----------------------------------------------------");
    printf("\n");
    printf("\nRANKING DE PERDEDORES:\n");
    char linea[100];
    while(fgets(linea,sizeof(linea),archivo)){
        printf(" %s",linea);
    }
    fclose(archivo);
    printf("\n");
    printf("-----------------------------------------------------");
}
