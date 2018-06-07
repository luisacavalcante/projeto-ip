#ifndef GUARD_H
#define GUARD_H

#include "AllegroCore.h"
#include "CharacterLibrary.h"
#include "MainMenuLibrary.h"








void walkWithGuard(int i){

int zoom = 3;
    makeZoomedGame(zoom);
    int sair = 0, comando =0;
    double vel=zoom;
    //mostrar o tamanho do sprite do personagem
    declareFirstAtributes(i,15,20,LARGURA_MAPA/2 + 30, ALTURA_MAPA/2 + 30);

    
    int wait,cont;
    bomb[i].cont=800;
    bomb[i].isOn=0,bomb[i].set = 0;
    int px, py;
    //onde ele vai comecar(centralizado na tela zoomificada);
    int whereIsX=LARGURA_TELA/2/zoom;
    int whereIsY=ALTURA_TELA/2/zoom ;
    //esses dois de baixo sao as posicoes finais dos personagens, de (0,0) a (larguramapa,alturamapa)
    jogador[i].x = (LARGURA_TELA/2+jogador[i].posX)/zoom;
    jogador[i].y = (ALTURA_TELA/2+jogador[i].posY)/zoom;
    int j;

    while(!sair){
        cont=0;
        wait=0;
        //checar qual eh o comando
        comando = checkEvent();
        jogador[i].comando=comando;


        while(wait!=comando){
            //enquanto nao soltar a tecla ele continua andando para frente
            wait = checkEvent();
            cont++;

            //se ele checar a barreira e nao tiver barreira, ele continue esse if
            if(!checkIfBarrer(comando, vel, jogador[i].x, jogador[i].y,1)){
                //ai o personagem anda pra frente
                
                whichCommandPlayer(comando, vel, i);
                

                px = (-jogador[i].posX)/zoom;
                py = (- jogador[i].posY)/zoom;

                jogador[i].x = (LARGURA_TELA/2+jogador[i].posX)/zoom;
                jogador[i].y = (ALTURA_TELA/2+jogador[i].posY)/zoom;
            
                //e a tela acompanha seu movimento
                whereIs(&whereIsX, &whereIsY, comando, zoom, px, py, vel, i);

                
                
            }
            else{
                whichCommandPlayer(comando, 0, i);
                whereIs(&whereIsX, &whereIsY, 0, zoom, px, py, vel, i);
            }

            isThereAnotherPlayer(i,whereIsX,whereIsY);

            makeAnimation(i,comando,&sair,cont,2);
            
            if(bomb[i].isOn)
                drawBomb(i,whereIsX,whereIsY);
            
            printPowerUps(i,whereIsX,whereIsY);

            didIGotPowerUp(i,whereIsX,whereIsY);

            al_draw_textf(fontepersonagem, jogador[i].cor, whereIsX+10, whereIsY-10, ALLEGRO_ALIGN_CENTRE, 
                              "%s", jogador[i].nome);

            if(bomb[i].cont<700)    bomb[i].cont+=4;
            if(bomb[i].cont==700) jogador[i].ihaveweapon=1,bomb[i].cont+=4,bomb[i].isOn=0;
            
            if(comando == 5 ){
                if (jogador[i].weapon == 0)
                drawSpriteGuardHit(i,whereIsX,whereIsY),didIHitAnyone(i);
                
                else if (jogador[i].weapon == 1 ){
                drawSpriteGuard(i,whereIsX,whereIsY);
                bomb[i].cont=0;
                bomb[i].x = jogador[i].x, bomb[i].y = jogador[i].y;
                bomb[i].isOn=1;
                wait=comando;
                }
                
            }
         

            else drawSpriteGuard(i,whereIsX,whereIsY);


            al_flip_display();
        }
        if(wait == comando){
            whereIs(&whereIsX, &whereIsY, 0, zoom, px, py, vel, i);

            if(bomb[i].cont<700)  jogador[i].weapon=0,jogador[i].ihaveweapon=0,bomb[i].cont+=4;

            if(bomb[i].cont==700) jogador[i].ihaveweapon=1,bomb[i].cont+=4,bomb[i].isOn=0;

            drawSpriteGuard(i,whereIsX,whereIsY);

            printPowerUps(i,whereIsX,whereIsY);

            didIGotPowerUp(i,whereIsX,whereIsY);

            

            al_draw_textf(fontepersonagem, jogador[i].cor, whereIsX+10, whereIsY-10, ALLEGRO_ALIGN_CENTRE, 
                              "%s", jogador[i].nome);
            if(bomb[i].cont < 700) drawBomb(i,whereIsX,whereIsY);
        
            if (comando == 6 && !bomb[i].isOn && jogador[i].ihaveweapon){
                if (jogador[i].weapon == 0) jogador[i].weapon = 1;
                else jogador[i].weapon = 0;
            }
            al_flip_display();
        }

    }
}



void walkWithEnemy(int i){

    int zoom = 3;
    makeZoomedGame(zoom);
    int sair = 0, comando =0;
    double vel=zoom;
    //mostrar o tamanho do sprite do personagem
    declareFirstAtributes(i,16,24,LARGURA_MAPA/2 + 30, ALTURA_MAPA/2 + 30);

    
    int wait,cont;
    bomb[i].cont=800;
    bomb[i].isOn=0,bomb[i].set = 0;
    int px, py;
    //onde ele vai comecar(centralizado na tela zoomificada);
    int whereIsX=LARGURA_TELA/2/zoom;
    int whereIsY=ALTURA_TELA/2/zoom ;
    //esses dois de baixo sao as posicoes finais dos personagens, de (0,0) a (larguramapa,alturamapa)
    jogador[i].x = (LARGURA_TELA/2+jogador[i].posX)/zoom;
    jogador[i].y = (ALTURA_TELA/2+jogador[i].posY)/zoom;
    int j;
    //sendMyStructToServer(i,struct);
    //getServerInfo(i)
    while(!sair){
        cont=0;
        wait=0;
        //checar qual eh o comando
        comando = checkEvent();
        jogador[i].comando=comando;


        while(wait!=comando){
            //enquanto nao soltar a tecla ele continua andando para frente
            wait = checkEvent();
            cont++;

            //se ele checar a barreira e nao tiver barreira, ele continue esse if
            if(!checkIfBarrer(comando, vel, jogador[i].x, jogador[i].y,1)){
                //ai o personagem anda pra frente
                
                whichCommandPlayer(comando, vel, i);
                

                px = (-jogador[i].posX)/zoom;
                py = (- jogador[i].posY)/zoom;

                jogador[i].x = (LARGURA_TELA/2+jogador[i].posX)/zoom;
                jogador[i].y = (ALTURA_TELA/2+jogador[i].posY)/zoom;
            
                //e a tela acompanha seu movimento
                whereIs(&whereIsX, &whereIsY, comando, zoom, px, py, vel, i);

                
                
            }
            else{
                whichCommandPlayer(comando, 0, i);
                whereIs(&whereIsX, &whereIsY, 0, zoom, px, py, vel, i);
            }
            //sendMyStructToServer(i,struct);
            //getServerInfo(i)

            isThereAnotherPlayer(i,whereIsX,whereIsY);

            makeAnimation(i,comando,&sair,cont,2);
            
            if(bomb[i].isOn)
                drawBomb(i,whereIsX,whereIsY);
            
            printPowerUps(i,whereIsX,whereIsY);

            didIGotPowerUp(i,whereIsX,whereIsY);

            al_draw_textf(fontepersonagem, jogador[i].cor, whereIsX+10, whereIsY-10, ALLEGRO_ALIGN_CENTRE, 
                              "%s", jogador[i].nome);

            if(bomb[i].cont<700)    bomb[i].cont+=4;
            if(bomb[i].cont==700) jogador[i].ihaveweapon=1,bomb[i].cont+=4,bomb[i].isOn=0;
            
            if(comando == 5 ){
                if (jogador[i].weapon == 0)
                drawSpriteGuardHit(i,whereIsX,whereIsY),didIHitAnyone(i);
                
                else if (jogador[i].weapon == 1 ){
                drawSpriteEnemy(i,whereIsX,whereIsY);
                bomb[i].cont=0;
                bomb[i].x = jogador[i].x, bomb[i].y = jogador[i].y;
                bomb[i].isOn=1;
                wait=comando;
                }
                
            }
         

            else drawSpriteEnemy(i,whereIsX,whereIsY);


            al_flip_display();
        }
        if(wait == comando){
            whereIs(&whereIsX, &whereIsY, 0, zoom, px, py, vel, i);

            //sendMyStructToServer(i,struct);
            //getServerInfo(i)

            if(bomb[i].cont<700)  jogador[i].weapon=0,jogador[i].ihaveweapon=0,bomb[i].cont+=4;

            if(bomb[i].cont==700) jogador[i].ihaveweapon=1,bomb[i].cont+=4,bomb[i].isOn=0;

            drawSpriteEnemy(i,whereIsX,whereIsY);

            printPowerUps(i,whereIsX,whereIsY);

            didIGotPowerUp(i,whereIsX,whereIsY);

            

            al_draw_textf(fontepersonagem, jogador[i].cor, whereIsX+10, whereIsY-10, ALLEGRO_ALIGN_CENTRE, 
                              "%s", jogador[i].nome);
            if(bomb[i].cont < 700) drawBomb(i,whereIsX,whereIsY);
        
            if (comando == 6 && !bomb[i].isOn && jogador[i].ihaveweapon){
                if (jogador[i].weapon == 0) jogador[i].weapon = 1;
                else jogador[i].weapon = 0;
            }
            al_flip_display();
        }

    }
}



#endif
