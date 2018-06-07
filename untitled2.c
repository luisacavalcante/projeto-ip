#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "matriz.h"
#include "AllegroCore.h"
#include "GuardLibrary.h"
#include "EnemyLibrary.h"
#include "MainMenuLibrary.h"

// simple chat client
#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define HIST_MAX_SIZE 200


void assertConnection() {
  printHello();
  enum conn_ret_t ans = connectToServer(ip);
  // temos a resposta do tryconnect() no ans.A resposta esperada eh SERVER_UP
  // o while eh pra resolver os problemas ate recebermos SERVER_UP como resposta 
  while (ans != SERVER_UP) {
    if (ans == SERVER_DOWN) {
      puts("Server is down!");
    } else if (ans == SERVER_FULL) {
      puts("Server is full!");
    } else if (ans == SERVER_CLOSED) {
      puts("Server is closed for new connections!");
    } else {
      puts("Server didn't respond to connection!");
    }
    printf("Want to try again? [Y/n] ");
    int res;
    while (res = tolower(getchar()), res != 'n' && res != 'y' && res != '\n'){
      puts("anh???");
    }
    if (res == 'n') {
      exit(EXIT_SUCCESS);
    }
    ans = connectToServer(ip);
  }
}


//FUNÇÃO QUE FAZ A CONEXÃO DO CLIENT COM O SERIDOR
void connect(){
	// IP
  writeYourIPScreen(xmain,ymain);
  assertConnection();

  // NOME
  writeYourNameScreen(xmain,ymain);
  sendMsgToServer(name, sizeof(char)*strlen(name));
}


//FUNÇÃO QUE ESPERA OS JOGADORES ENTRAREM NA SALA ATÉ O INÍCIO DO JOGO
void loadingScreen(int *play){
  int resp;
  char msg[100];
  resp = recvMsgFromServer(msg, DONT_WAIT);
  if(resp == SERVER_DISCONNECTED){
  //tentar conectar de novo
  }
  else if(resp != NO_MESSAGE){
  //passar pro allegro
    if(msg == SERVER_FULL){
      printf("SERVER FULL")
      printf("GAME IS BEGINING...")
      &play = 0;
    }
    else if(msg == START){
      printf("GAME IS BEGINING...")
      &play = 0;
    }
    else{
      printf("%s", msg);
    }
  }
}
// INICIO DO JOGO 
// criar um while para a execucao do jogo(ate o usuario sair)
// Client recebe do server o numero de jogadores(server)
// ZOOM 3x
//Client compartilha seu  movimento para o server(struct)
//client recebe localizacao nova de todos os personagens para todos os jogadores
// Client: Checar outros personagens no parametro da tela
//Se houver imprime os respectivos personagens na tela
