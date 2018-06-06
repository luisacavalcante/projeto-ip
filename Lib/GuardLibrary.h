#ifndef GUARD_H
#define GUARD_H

#include "AllegroCore.h"
#include "EnemyLibrary.h"
#include "MainMenuLibrary.h"


void corPersonagem(int i){
	if(i==0||i==1) jogador[i].cor = al_map_rgb(0,255,0);
	if(i==2||i==3) jogador[i].cor = al_map_rgb(0,0,255);
	if(i==4||i==5) jogador[i].cor = al_map_rgb(255,0,0);
	if(i==6||i==7) jogador[i].cor = al_map_rgb(255,255,0);
}

void drawSpriteGuard(int i, double posX,double posY,int act,int set){
    if(set==2)
        al_draw_bitmap_region(spriteGuard[p[i]],
            (jogador[i].largura+1)*act,    jogador[i].altura+2,
             jogador[i].largura       ,    jogador[i].altura  ,
             posX                      ,    posY                ,0);
    if(set==0)
        al_draw_bitmap_region(spriteGuard[p[i]],
            (jogador[i].largura+1)*act,    0                  ,
             jogador[i].largura       ,    jogador[i].altura ,
             posX                      ,    posY               ,0);
    if(set==1)
        al_draw_bitmap_region(spriteGuard[p[i]],
            (jogador[i].largura+1)*(2+act)+act*1,   0                 ,
             jogador[i].largura                 ,   jogador[i].altura,
             posX                                ,   posY              ,0);
    if(set==3)
        al_draw_bitmap_region(spriteGuard[p[i]],
             66 + jogador[i].largura*act,    0                      ,
             jogador[i].largura         ,    jogador[i].altura     ,
             posX              			 ,    posY                   ,0);

}

void drawSpriteGuardHit(int i,int posX,int posY,int set,int act){
	if(set==2)//p cima
        al_draw_bitmap_region(spriteGuardHit[p[i]],
             34	+ 16*act			,    1	   ,
             15       				,    24    ,
             posX                   ,    posY - 4,0);
   	if(set==0)//p baixo
        al_draw_bitmap_region(spriteGuardHit[p[i]],
             15*act 				,    5     ,
             15				        ,    32	   ,
             posX -act              ,    posY  ,0);
   	if(set==1)//p esquerda
        al_draw_bitmap_region(spriteGuardHit[p[i]],
             25*act					,   61     ,
             25                 	,   19	   ,
             posX - 9 - 6*act       ,   posY   ,0);
    if(set==3)//p direita
        al_draw_bitmap_region(spriteGuardHit[p[i]],
             2 + 28*act 			,   41	   ,
             26       				,   19     ,
             posX +3*act            ,   posY+1 ,0);

}

void drawSpriteGuardShield(int i, int posX, int posY, int set, int contshield){
    contshield=contshield/2;
    //p cima
        al_draw_bitmap_region(spriteShield,
             0,    0                      ,
             7,    7                      ,
             posX + 15     ,    posY + 10 -contshield,0);


}



void walkWithGuard(int i){

    int zoom = 3;
    makeZoomedGame(zoom);
    int sair = 0, comando = 0;
    double vel=zoom;
    int act=0,set=0;
    //mostrar o tamanho do sprite do personagem
    jogador[i].largura = 15;
    jogador[i].altura  = 20;
    int pos_inicial_x =LARGURA_MAPA/2;
    int pos_inicial_y =ALTURA_MAPA/2; 
    jogador[i].posX = pos_inicial_x  +30;
    jogador[i].posY = pos_inicial_y  +30;
    int wait,cont;
    int weapon = 0;
    int px, py,a=0;
    //onde ele vai comecar(centralizado na tela zoomificada);
    int whereIsX=LARGURA_TELA/2/zoom;
    int whereIsY=ALTURA_TELA/2/zoom ;
    //esses dois de baixo sao as posicoes finais dos personagens, de (0,0) a (larguramapa,alturamapa)
    jogador[i].x = (LARGURA_TELA/2+jogador[i].posX)/zoom;
    jogador[i].y = (ALTURA_TELA/2+jogador[i].posY)/zoom;

    int contshield=200;
    while(!sair){
        cont=0;
        wait=0;
        a=0;
        //checar qual eh o comando
        comando = checkEvent();
            contshield++;
            if(contshield<100) comando = 0,drawSpriteGuardShield(i,whereIsX,whereIsY,set,contshield);
            else 
        while(wait!=comando){

            //enquanto nao soltar a tecla ele continua andando para frente
            wait = checkEvent();
            cont++;
            
            //se ele checar a barreira e nao tiver barreira, ele continue esse if
            if(!checkifBarrer(comando, vel,&set, jogador[i].x, jogador[i].y,1)){
                //ai o personagem anda pra frente
                
                whichCommandPlayer(comando, vel,&set, i);
            	

            	px = (-jogador[i].posX)/zoom;
            	py = (- jogador[i].posY)/zoom;

            	jogador[i].x = (LARGURA_TELA/2+jogador[i].posX)/zoom;
            	jogador[i].y = (ALTURA_TELA/2+jogador[i].posY)/zoom;
            
            	//e a tela acompanha seu movimento
            	whereIs(&whereIsX, &whereIsY, comando, zoom, px, py, vel, i);

            	
            	
            }
            else
            	whereIs(&whereIsX, &whereIsY, 0, zoom, px, py, vel, i);

            makeAnimation(comando,&act,&sair,cont,2);
            
			al_draw_textf(fontepersonagem, jogador[i].cor, whereIsX+10, whereIsY-10, ALLEGRO_ALIGN_CENTRE, 
            			      "%s", jogador[i].nome);
			al_draw_textf(fontesecundaria, al_map_rgb(20, 20, 20), LARGURA_TELA/2/zoom, 250/zoom, ALLEGRO_ALIGN_CENTRE, 
            			      "(%d,%d)", jogador[i].x,jogador[i].y);
            

            
            if(comando == 5) {
                if (weapon == 0)
            	   drawSpriteGuardHit(i,whereIsX,whereIsY,set,act);
                else if (weapon == 1 ){
                   drawSpriteGuard(i,whereIsX,whereIsY,act,set);
                   contshield=0;
                }
            }
            

            else drawSpriteGuard(i,whereIsX,whereIsY,act,set);
            
            al_flip_display();
        }       

        if (comando == 6){
                if (weapon == 0) weapon = 1;
                else weapon = 0;
        }
    }
}




#endif
