// virada no cin

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


// enum conn_ret t -- conectar ao servidor
// com essa funcao nos conectamos ao servidor com IP 

enum conn_ret_t tryConnect() {

// server_ip: endereco para uma string contendo o endereco
// IP do servidor
  char server_ip[30];
  printf("Please enter the server IP: ");
  scanf(" %s", server_ip);
 // A função getchar() lê um caracter e retorna um inteiro que é: o código do caracter ,
  getchar();
  /* SERVER_UP, se conexão foi estabelecida
SERVER_DOWN, se não foi possivel encontrar o servidor
SERVER_FULL, se o server está cheio (atingiu o número máximo de clientes)
SERVER_CLOSED, se o server está fechado para conexões
SERVER_TIMEOUT, se o server demorou para dar uma resposta sobre o status da conexão
*/

  //connectToServer?
  return connectToServer(server_ip);
}

void  printHello() {
  puts("Hello! Welcome to simple chat example.");
  puts("We need some infos to start up!");
}

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
//queremos saber o login do usuario
  char login[LOGIN_MAX_SIZE + 4];
  printf("Please enter your login (limit = %d): ", LOGIN_MAX_SIZE);
  scanf(" %[^\n]", login);
  getchar();
  int len = (int)strlen(login);
  // sendMsgToServer--uma funcao ja presente que possui as seguintes caracteristicas:
  // int sendMsgToServer(void *msg,int size);
  sendMsgToServer(login, len + 1);
}

void runChat() {
  char str_buffer[BUFFER_SIZE], type_buffer[MSG_MAX_SIZE] = {0};
  char msg_history[HIST_MAX_SIZE][MSG_MAX_SIZE] = {{0}};
  int type_pointer = 0;
  
  while (1) {
    // LER UMA TECLA DIGITADA
    char ch = getch();
    if (ch == '\n') {
      type_buffer[type_pointer++] = '\0';
      int ret = sendMsgToServer((void *)type_buffer, type_pointer);
      if (ret == SERVER_DISCONNECTED) {
        return;
      }
      type_pointer = 0;
      type_buffer[type_pointer] = '\0';
    } else if (ch == 127 || ch == 8) {
      if (type_pointer > 0) {
        --type_pointer;
        type_buffer[type_pointer] = '\0';
      }
    } else if (ch != NO_KEY_PRESSED && type_pointer + 1 < MSG_MAX_SIZE) {
      type_buffer[type_pointer++] = ch;
      type_buffer[type_pointer] = '\0';
      
    }

    // LER UMA MENSAGEM DO SERVIDOR
    // a funcao recvMsgFromServer eh da forma:
    // recvMsgFromServer(void *msg,int option);
    // msg-- ponteiro onde queremos salvar a mensagem recebida
    //option:
    //DONT_WAIT:nao queremos esperar a mensagem ser recebida
    //
    int ret = recvMsgFromServer(str_buffer, DONT_WAIT);
    if (ret == SERVER_DISCONNECTED) {

      return;
// servidor esta conectado
    }
// NO_MESSAGE== nao existe mensagens pendentes(utillizado com DONT_WAIT)
    else if (ret != NO_MESSAGE) {
      int i;
      for (i = 0; i < HIST_MAX_SIZE - 1; ++i) {

        //copia a mensagem de uma string para outra
        strcpy(msg_history[i], msg_history[i + 1]);
      }
      // buffer espaco na memoria
      strcpy(msg_history[HIST_MAX_SIZE - 1], str_buffer);
    }

    // PRINTAR NOVO ESTADO DO CHAT
    system("clear");
    int i;
    // utilizaremos esse for para mostrar a mensagem salva
    for (i = 0; i < HIST_MAX_SIZE; ++i) {
      printf("%s\n", msg_history[i]);
    }
    printf("\nYour message: %s\n", type_buffer);
  }
}

int main() {
// inicializar as coisas
  if(!inicializar()) return -1;
    //ABERTURA
        int player=4;
//cin
    waitingScreen();

  
    //DECLARAR VARIAVEIS
    int command,exit=0,volume=5;
    int xmain=0,ymain=0,onde=0;
    //TOCAR SAMPLE DO MAIN MENU
    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,NULL);

    while(!exit){

 //main menu
        command = mainMenu(&xmain,&ymain,&onde);

        //START GAME
        if(command==0){
        // IP
          writeYourIPScreen(xmain,ymain);
          assertConnection();

        // NOME
          writeYourNameScreen(xmain,ymain);
          sendMsgToServer(name, sizeof(char)*strlen(name));

        //Loading...
          int play = 1, resp;
          char msg[100];
          while(play){
            resp = recvMsgFromServer(msg, DONT_WAIT);
            if(resp == SERVER_DISCONNECTED){
              //tentar conectar de novo
            }
            else if(resp != NO_MESSAGE){
              //passar pro allegro
              if(msg == SERVER_FULL){
                printf("SERVER FULL")
                printf("GAME IS BEGINING...")
                play = 0;
              }
              else if(msg == START){
                printf("GAME IS BEGINING...")
                play = 0;
              }
              else{
                printf("%s", msg);
              }
            }
          }
        //Paradas loucas do jogo
          strcpy(jogador[player].nome,name);
          corPersonagem(player);
          if(player%2==0)
              walkWithGuard(player);
          if(player%2==1)
              walkWithEnemy(player);
          makeZoomedGame(1);
        }

        //INSTRUCTIONS
        if(command==1)
            mainInstructions(xmain,ymain);

        //OPTIONS
        if(command==2)
            mainOptions(&volume,xmain,ymain);

        //EXIT
        if(command==3)
            exit=1;

    }
    destruir();
  
  
  
  
  
  // socket
  assertConnection();


  getchar();
  while(1) {
    runChat();
    printf("Server disconnected! Want to try again? [Y/N] ");
    int res;
    while (res = tolower(getchar()), res != 'n' && res != 'y' && res != '\n'){
      puts("anh???");
    }
    if (res == 'y' || res == '\n') {
      assertConnection();
    } else {
      break;
    }
  }
  return 0;
}