#include "ACore.h"
#include "server.h"
#include <stdio.h>
#include <string.h>

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 16
#define MAX_CLIENTS 8

typedef struct{
    int lifeBar;
    int equipment;
    char nome[LOGIN_MAX_SIZE];
    int posX, posY,x,y;
    int altura;//24     //20
    int largura;//16    //15
    int whatis;
    ALLEGRO_COLOR cor;
}character;

character client[MAX_CLIENT];

int whatIs (int x) {
	if (x%2 == 0) return 0;
	else if(x%2 != 0) return 1;
}

int main() 
{
  char str_buffer[BUFFER_SIZE], aux_buffer[BUFFER_SIZE];
  int i, quant_connect = 0;

  serverInit(MAX_CLIENTS);
  printf("Server is running!!");
  while (1) 
  {
    int id = acceptConnection();
    if (id != NO_CONNECTION) {
      recvMsgFromClient(client.nome[id], id, WAIT_FOR_IT);
      strcpy(str_buffer, client.nome[id]);

      client[id].whatis = whaIs(id);
      if (client[id].whatis == 1) {
      		strcat(str_buffer, " entrou no jogo e é policia");
      }
      else if (client[id].whatis == 0){
      		strcat(str_buffer, " entrou no jogo e é ladrão");
      }
      broadcast(str_buffer, (int)strlen(str_buffer) + 1);
      printf("%s connected id = %d\n", client.nome[id], id);
      quant_connect++;
    }

    //SO RECEBER STRUCT QUANDO O JOGO COMEÇAR
    for (i = 0; i < quant_connect; i++) {
    	recvMsgFromClient(client[i], i, DONT_WAIT);
    }

    struct msg_ret_t msg_ret = recvMsg(aux_buffer);
	if (msg_ret.status == DISCONNECT_MSG) {
      sprintf(str_buffer, "%s disconnected", client_names[msg_ret.client_id]);
      printf("%s disconnected, id = %d is free\n",
             client_names[msg_ret.client_id], msg_ret.client_id);
      broadcast(str_buffer, (int)strlen(str_buffer) + 1);
    }
  }
}
