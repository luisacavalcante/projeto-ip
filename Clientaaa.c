
#include "Lib/ClientLibrary.h"
#include "Lib/Matriz.h"
#include "Lib/AllegroCore.h"
#include "Lib/PlayableLibrary.h"
#include "Lib/CharacterLibrary.h"
#include "Lib/MainMenuLibrary.h"


// simple chat client
#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define HIST_MAX_SIZE 200

int num_jogadores=0;


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
          // connect
        player = conectar(xmain,ymain);

        selectYourColorScreen(player,xmain,ymain);

        //Loading...
          int play = 1;
          while(play)
            loadingScreen(&play);
          

          recvMsgFromServer(&num_jogadores,WAIT_FOR_IT);
        //INICIO DO JOGO
          // funcao continua para receber as structs dos personagens

          // antes de comecar o jogo
          strcpy(jogador[player].nome,name);
          corPersonagem(player);
          
          playGame(player,num_jogadores);

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
// INICIO DO JOGO 
// criar um while para a execucao do jogo(ate o usuario sair)
// Client recebe do server o numero de jogadores(server)
// ZOOM 3x
//Client compartilha seu  movimento para o server(struct)
//client recebe localizacao nova de todos os personagens para todos os jogadores
// Client: Checar outros personagens no parametro da tela
//Se houver imprime os respectivos personagens na tela