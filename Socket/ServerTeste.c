//Teste Server
#include "AllegroCore.h"
#include "GuardLibrary.h"
#include "EnemyLibrary.h"
#include "server.h"
#include <stdio.h>
#include <string.h>

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 16
#define MAX_CLIENTS 8

struct character jogador[MAX_CLIENTS];

//whatIs recebe o id do cliente e checa se é par(guarda) ou ímpar(ladrão)
int whatIs (int x) {
	if (x%2 == 0) return 0;
	else if(x%2 != 0) return 1;
}

int main() 
{
	char str_buffer[BUFFER_SIZE], aux_buffer[BUFFER_SIZE];
	int i, quant_connect = 0;
	int id = 0;
	char start = 'N';

	serverInit(MAX_CLIENTS);
	printf("Server is running!!");

	while (1) {	
	  	//Deve acontecer enquanto o jogo não comecar
	    id = acceptConnection();
	    if (id != NO_CONNECTION) {
	    	//Recebe o nome do cliente
	    	recvMsgFromClient(jogador[id].nome, id, WAIT_FOR_IT);
	    	strcpy(str_buffer, jogador[id].nome);

	    	//Manda o id para o cliente
	    	jogador[id].id = id;
	    	sendMsgToClient(id, sizeof(int), id);

	    	//Checa se o cliente é polícia ou ladrão
	    	//Func whatIs() retorna 0 para polícia e 1 para ladrão
	    	jogador[id].whatis = whaIs(id);

	    	if (jogador[id].whatis == 0) {
	    		strcat(str_buffer, " entrou no jogo e é guarda");
	    	}
	    	else if (client[id].whatis == 1){
	      		strcat(str_buffer, " entrou no jogo e é ladrão");
	      	}

	      	//Manda uma mensagem para todos os jogadores com informacoes dos novos jogadores que se conectarem
	      	broadcast(str_buffer, strlen(str_buffer) + 1);

	      	//Printa no terminal do server o nome do jogadores e seu id
	      	printf("%s connected id = %d\n", client.nome[id], id);

	      	//Aumenta a quantidade de jogadores conectados
	      	quant_connect++;
	    }

	    //Se o jogo não tiver comecado
	    if (start == 'N') {
	    	//Recebe comando do jogador 0 para saber se o jogo comecou
	    	recvMsgFromClient(start, 0, DONT_WAIT);

	    	//Se receber 'q' o jogo comecou, se a quantidade de jogadores for 7, comecou também
	    	if (start == 'q' || quant_connect == 7) {
	    		start = 'q';

	    		//Avisa que o jogo comecou para os jogadores
	    		broadcast(start, sizeof(char));
	    	}
	    }
	    
	    //Deve acontecer quando o jogo comecar
	    if (start == 'q') {
		    //Manda para todos os jogadores a quantidade de jogadores conectados
		    broadcast(quant_connect, sizeof(int));

		    //Recebe as structs de todos os jogadores
		    for (i = 0; i < quant_connect; i++) {
		    	recvMsgFromClient(jogador[i], i, DONT_WAIT);
		    }

		    //Manda a struct atualizada dos jogadores para todos
		    for (i = 0; i < quant_connect; i++) {    
		    	broadcast(jogador[i], sizeof(character));
		    }
		}

	    //Acontece sempre
	    //Saber se o jogador se deconectou
	    struct msg_ret_t msg_ret = recvMsg(aux_buffer);
	    if (msg_ret.status == DISCONNECT_MSG) {
	    	sprintf(str_buffer, "%s disconnected", client_names[msg_ret.client_id]);
	      	printf("%s disconnected, id = %d is free\n", client_names[msg_ret.client_id], msg_ret.client_id);
	      	broadcast(str_buffer, strlen(str_buffer) + 1);
	    }
	}
}