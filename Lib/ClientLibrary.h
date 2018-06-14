#ifndef CLIENT_H
#define CLIENT_H

#include "client.h"
#include "AllegroCore.h"
#include "MainMenuLibrary.h"
#include <ctype.h>

// simple chat client
#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define HIST_MAX_SIZE 200

int my_id; // ID do proprio jogador
character send_struct; 

void assertConnection() {
  enum conn_ret_t ans = connectToServer(ip);
  // temos a resposta do tryconnect() no ans.A resposta esperada eh SERVER_UP
  // o while eh pra resolver os problemas ate recebermos SERVER_UP como resposta 
  while (ans != SERVER_UP) {
    if (ans == SERVER_DOWN) {
      puts("Server is down!\n");
    } else if (ans == SERVER_FULL) {
      puts("Server is full!\n");
    } else if (ans == SERVER_CLOSED) {
      puts("Server is closed for new connections!\n");
    } else {
      puts("Server didn't respond to connection!\n");
    }
    printf("Want to try again? [Y/n]\n");
    int res;
    while (res = tolower(getchar()), res != 'n' && res != 'y' && res != '\n'){
      puts("anh???\n");
    }
    if (res == 'n') {
      exit(EXIT_SUCCESS);
    }
    ans = connectToServer(ip);
  }
}


//FUNÇÃO QUE FAZ A CONEXÃO DO CLIENT COM O SERIDOR
int conectar(int xmain, int ymain){
	my_id = 0;
  // IP
  writeYourIPScreen(xmain,ymain);
  assertConnection(ip);

  // NOME
  writeYourNameScreen(xmain,ymain);

  sendMsgToServer(name, sizeof(char)*strlen(name));
  recvMsgFromServer(&my_id, WAIT_FOR_IT);

  powerUP aux;
  for (int j= 0; j < 5; j++) {
    recvMsgFromServer(&aux, WAIT_FOR_IT);
    jogador[my_id].power[j].x = aux.x;
    jogador[my_id].power[j].y = aux.y;
    jogador[my_id].power[j].aindatem = 1;
  }
  

  return my_id;
}


//FUNÇÃO QUE ESPERA OS JOGADORES ENTRAREM NA SALA ATÉ O INÍCIO DO JOGO
void loadingScreen(int *play){
  enum conn_ret_t resp;
  char msg[100],start;
  resp = recvMsgFromServer(msg, DONT_WAIT);
  if(resp == SERVER_DISCONNECTED){
  //tentar conectar de novo
  }
  else if(resp != NO_MESSAGE){
  //passar pro allegro
    if(resp == SERVER_FULL){
      printf("SERVER IS FULL\n");
      printf("GAME IS BEGINNING...\n");
      *play = 0;
    }
    else if(msg[0] == 'q'){ //Start
      printf("GAME IS BEGINNING...\n");
      *play = 0;
    }
    else{
      printf("%s", msg); //terminal
    }
  }
  if(my_id == 0){
    start = getch();
    if(start != NO_KEY_PRESSED){
      //manda msg para o server comecar o jogo
      if(start == 'q') sendMsgToServer(&start, sizeof(char));
    }
  }
}
//
void atualizarPersonagens(int player){
  character person;
  int c;
  sendMsgToServer(&jogador[player],sizeof(character));
  for(int i=0; i<8; i++){
    //recvMsgFromServer(&c, DONT_WAIT);
    recvMsgFromServer(&person, DONT_WAIT);
    jogador[person.id] = person; 
  }

}

#endif
