//Teste Server
#include "Lib/AllegroCore.h"

#include "Lib/ServerLibrary.h"

#include <stdio.h>
#include <string.h>

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 16
#define MAX_CLIENTS 8

void aleatorizePowerUps(){
    int forget;
    for(int i = 0; i < 5; i++){
        forget = 1;
        while(forget==1){
            forget = 0;
            int var = rand() % 10;
            for(int j=0 ; j < i; j++)if(powerup[j].tipo == var) forget = 1;
            if (forget == 0) powerup[i].tipo = var;
        }
        if(powerup[i].tipo==0) powerup[i].x = 110, powerup[i].y = 240;
        if(powerup[i].tipo==1) powerup[i].x = 570, powerup[i].y = 425;
        if(powerup[i].tipo==2) powerup[i].x = 750, powerup[i].y = 620;
        if(powerup[i].tipo==3) powerup[i].x =1200, powerup[i].y = 250;
        if(powerup[i].tipo==4) powerup[i].x =1400, powerup[i].y = 700;
        if(powerup[i].tipo==5) powerup[i].x =  80, powerup[i].y = 860;
        if(powerup[i].tipo==6) powerup[i].x =1700, powerup[i].y = 950;
        if(powerup[i].tipo==7) powerup[i].x = 625, powerup[i].y = 725;
        if(powerup[i].tipo==8) powerup[i].x =1400, powerup[i].y = 350;
        if(powerup[i].tipo==9) powerup[i].x = 375, powerup[i].y = 270;
        powerup[i].aindatem=1;
    }

    /*for (int i = 0; i < 8; i++) {
    	for (int j = 0; j < 4; j++) {
    		jogador[i].power[j].x = powerup[j].x;
    		jogador[i].power[j].y = powerup[j].y;
    		jogador[i].power[j].aindatem = powerup[i].aindatem;
    	}
    }*/
    
}

//whatIs recebe o id do cliente e checa se é par(guarda) ou ímpar(ladrão)
int whatIs (int x) {
	if (x%2 == 0) return 0;
	return 1;
}

int main() {
	
	if (!al_init()){
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return 0;
    }
    
    //INICIAR EVENTOS
    fila_eventos = al_create_event_queue();
    if (!fila_eventos){
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return 0;
    }

	char str_buffer[BUFFER_SIZE], aux_buffer[BUFFER_SIZE];
	int i, quant_connect = 0,conectados=0;
	int id = 0;
	char start = 'N';
	int aleatorizar = 1;
	if (aleatorizar) {
		aleatorizePowerUps();
		aleatorizar = 0;
	}

	serverInit(MAX_CLIENTS);
	fprintf(stderr,"Server is running!!\n");

	while (1) {	
	//Deve acontecer enquanto o jogo não comecar


	  	//Recebe conexão
	    id = acceptConnection();
	    if (id != NO_CONNECTION) {
	    	//Recebe o nome do cliente
	    	recvMsgFromClient(&jogador[id].nome, id, WAIT_FOR_IT);
	    	strcpy(str_buffer, jogador[id].nome);

	    	//Manda o id para o cliente
	    	jogador[id].id = id;
	    	sendMsgToClient(&id, sizeof(int), id);
	    	//Manda a localizacao das bombas para o cliente
	    	for (int j = 0; j < 5; j++){
	    		sendMsgToClient(&powerup[j], sizeof(powerUP), id);
	    	}


	    	//Checa se o cliente é polícia ou ladrão
	    	//Func whatIs() retorna 0 para polícia e 1 para ladrão
	    	jogador[id].whatis = whatIs(id);

	    	if (jogador[id].whatis == 0)
	    		strcat(str_buffer, " entrou no jogo e é um Guarda\n");
	    	
	    	else if (jogador[id].whatis == 1)
	      		strcat(str_buffer, " entrou no jogo e é um Ladrão\n");
	      	

	      	//Manda uma mensagem para todos os jogadores com informacoes dos novos jogadores que se conectarem
	      	broadcast(&str_buffer, strlen(str_buffer) + 1);

	      	//Printa no terminal do server o nome do jogadores e seu id
	      	fprintf(stderr,"%s connected, with id = %d\n", jogador[id].nome, id);

	      	//Aumenta a quantidade de jogadores conectados
	      	quant_connect++;
	    }
	    
	    	//Recebe comando do jogador 0 para saber se o jogo comecou
	    	recvMsgFromClient(&start, 0, DONT_WAIT);

	    	//Se receber 'q' o jogo comecou, se a quantidade de jogadores for 7, comecou também
		if (start == 'q' || quant_connect == 7) {
			start = 'q';
			//Avisa que o jogo comecou para os jogadores
			broadcast(&start, sizeof(char));

			//Manda o numero de jogadores conectados para os jogadores
			broadcast(&quant_connect, sizeof(int));
			conectados = quant_connect;

			//Printa, no terminal, quantos jogadores estão no jogo 
			fprintf(stderr,"jogo comecou, com %d jogadores", quant_connect);
		}
	    
	    
	    int b;
	    character comando; 	
	    //Deve acontecer quando o jogo comecar
	    while(start == 'q'){	
			//Recebe as structs de todos os jogadores
			struct msg_ret_t person = recvMsg(&comando);
			if(person.status == MESSAGE_OK){
		    	b = person.client_id;

		    	//Atualiza a struct do jogador b
		    	jogador[b] = comando;
		    	printf("%d\n", jogador[b].comando);

		    	//Manda a struct do jogador b para os outros jogadores se o camando for diferente de 0(parado)
		    	if(jogador[b].comando != 0) broadcast(&jogador[b], sizeof(character));   
			    
			}    	
		    if (person.status == DISCONNECT_MSG) {
		    	sprintf(str_buffer, "%s disconnected\n", jogador[person.client_id].nome);
		      	fprintf(stderr,"%s disconnected, id = %d is free\n", jogador[person.client_id].nome, person.client_id);
		      	broadcast(&str_buffer, strlen(str_buffer) + 1);
			}
		}
	}
}
