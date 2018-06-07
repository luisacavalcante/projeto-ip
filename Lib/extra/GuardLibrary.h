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
    jogador[i].act=0,jogador[i].set=0;
    //mostrar o tamanho do sprite do personagem
    jogador[i].largura = 15;
    jogador[i].altura  = 20;
    int pos_inicial_x =LARGURA_MAPA/2;
    int pos_inicial_y =ALTURA_MAPA/2; 
    jogador[i].posX = pos_inicial_x  +30;
    jogador[i].posY = pos_inicial_y  +30;
    int wait,cont;

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
            if(!checkifBarrer(comando, vel, jogador[i].x, jogador[i].y,1)){
                //ai o personagem anda pra frente
                
                whichCommandPlayer(comando, vel, i);
            	

            	px = (-jogador[i].posX)/zoom;
            	py = (- jogador[i].posY)/zoom;

            	jogador[i].x = (LARGURA_TELA/2+jogador[i].posX)/zoom;
            	jogador[i].y = (ALTURA_TELA/2+jogador[i].posY)/zoom;
            
            	//e a tela acompanha seu movimento
            	whereIs(&whereIsX, &whereIsY, comando, zoom, px, py, vel, i);

            	
            	
            }
            else
            	whereIs(&whereIsX, &whereIsY, 0, zoom, px, py, vel, i);

            //for(j=0;j<8;j++){
            //    if(jogador[j].x<=LARGURA_TELA/2/zoom+jogador[i].x && jogador[j].x>=-LARGURA_TELA/2/zoom+jogador[i].x) && jogador[j].y<=ALTURA_TELA/2/zoom+jogador[i].y && jogador[j].y>=-ALTURA_TELA/2/zoom+jogador[i].y{
            //            if(j%2==0){
            //                drawSpriteGuard(j,jogador[j].x - jogador[i].x + LARGURA_TELA/2/zoom,jogador[j].y - jogador[i].y + ALTURA_TELA/2/zoom);
            //            }
            //            else{
            //                drawSpriteEnemy(j,jogador[j].x,jogador[j].y);
            //            }
            //    }
            //}
            makeAnimation(i,comando,&sair,cont,2);
            
			al_draw_textf(fontepersonagem, jogador[i].cor, whereIsX+10, whereIsY-10, ALLEGRO_ALIGN_CENTRE, 
            			      "%s", jogador[i].nome);
			al_draw_textf(fontesecundaria, al_map_rgb(20, 20, 20), LARGURA_TELA/2/zoom, 250/zoom, ALLEGRO_ALIGN_CENTRE, 
            			      "(%d,%d)", jogador[i].x,jogador[i].y);

            if(comando==5)
            	drawSpriteGuardHit(i,whereIsX,whereIsY);
            else
            	drawSpriteGuard(i,whereIsX,whereIsY);

            al_flip_display();
        }
    }
}



void walkWithEnemy(int i){

    int zoom = 3;
    makeZoomedGame(zoom);
    int sair = 0, comando =0;
    double vel=zoom;
    jogador[i].act=0,jogador[i].set=0;
    //mostrar o tamanho do sprite do personagem
    jogador[i].largura = 16;
    jogador[i].altura  = 24;
    int pos_inicial_x =LARGURA_MAPA/2;
    int pos_inicial_y =ALTURA_MAPA/2; 
    jogador[i].posX = pos_inicial_x  +30;
    jogador[i].posY = pos_inicial_y  +30;
    int wait,cont;

    int px, py;
    //onde ele vai comecar(centralizado na tela zoomificada);
    int whereIsX=LARGURA_TELA/2/zoom;
    int whereIsY=ALTURA_TELA/2/zoom ;
    //esses dois de baixo sao as posicoes finais dos personagens, de (0,0) a (larguramapa,alturamapa)
    jogador[i].x = (LARGURA_TELA/2+jogador[i].posX)/zoom;
    jogador[i].y = (ALTURA_TELA/2+jogador[i].posY)/zoom;


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
            if(!checkifBarrer(comando, vel, jogador[i].x, jogador[i].y,1)){
                //ai o personagem anda pra frente
                
                whichCommandPlayer(comando, vel, i);
                

                px = (- jogador[i].posX)/zoom;
                py = (- jogador[i].posY)/zoom;

                jogador[i].x = (LARGURA_TELA/2+jogador[i].posX)/zoom;
                jogador[i].y = (ALTURA_TELA/2+jogador[i].posY)/zoom;
            
                //e a tela acompanha seu movimento
                whereIs(&whereIsX, &whereIsY, comando, zoom, px, py, vel, i);

                
                
            }
            else
                whereIs(&whereIsX, &whereIsY, 0, zoom, px, py, vel, i);
            
            isThereAnotherPlayer(i,zoom);

            makeAnimation(i,comando,&sair,cont,2);
            
            al_draw_textf(fontepersonagem, jogador[i].cor, whereIsX+10, whereIsY-10, ALLEGRO_ALIGN_CENTRE, 
                              "%s", jogador[i].nome);
            al_draw_textf(fontesecundaria, al_map_rgb(20, 20, 20), LARGURA_TELA/2/zoom, 250/zoom, ALLEGRO_ALIGN_CENTRE, 
                              "(%d,%d)", jogador[i].x,jogador[i].y);

            //if(comando==5)
            //    drawSpriteEnemyHit(i,whereIsX,whereIsY);
            //else
                drawSpriteEnemy(i,whereIsX,whereIsY);

            al_flip_display();
        }
    }
}



#endif
