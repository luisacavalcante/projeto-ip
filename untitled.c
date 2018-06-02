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
	    	connect();

        //Loading...
          int play = 1;
          while(play){
          	loadingScreen(&play){
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
  return 0;
}
