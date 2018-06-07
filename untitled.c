#include "Lib/AllegroCore.h"
#include "Lib/PlayableLibrary.h"
#include "Lib/CharacterLibrary.h"
#include "Lib/MainMenuLibrary.h"
int main(void){

    
    
    if(!inicializar()) return -1;
    //ABERTURA
        int player=0;

    waitingScreen();

    //DECLARAR VARIAVEIS
    int command,exit=0,volume=5;
    int xmain=0,ymain=0,onde=0;
    //TOCAR SAMPLE DO MAIN MENU
    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,NULL);

    while(!exit){

        //MAIN MENU
        command = mainMenu(&xmain,&ymain,&onde);

        //START GAME
        if(command==0){
            if(!preparationForGame(&player,xmain,ymain,volume)) return 0;//reassert connection
        //
        if(player==0)
            aleatorizePowerUps();
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

