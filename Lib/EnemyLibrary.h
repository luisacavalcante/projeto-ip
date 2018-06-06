#ifndef ENEMY_H
#define ENEMY_H

#include "AllegroCore.h"
#include "GuardLibrary.h"
#include "MainMenuLibrary.h"

//Esse comando vai checar  qual foi o comando que recebeu do teclado
void whichCommandPlayer(int comando,int vel,int *set,int i){
    //1=cima,2=baixo,3=esquerda,4=direita
    //set é qual set de sprites eu devo usar
    if(comando==1)
        jogador[i].posY-=vel,*set=2;

    if(comando==2)
        jogador[i].posY+=vel,*set=0;
    
    if(comando==3)
        jogador[i].posX-=vel,*set=1;
    
    if(comando==4)
        jogador[i].posX+=vel,*set=3;

    
}

//Esse é o comando que dá erro. era para checar se a parte dos pés vai bater no
//rosa, mas nao esta dando certo
int checkifBarrer(int comando,int vel,int *set,int x,int y,int type){
    int i,j,a,b,c;
    if(type==0) b=y+20,c=y+17;
    if(type==1) b=y+15,c=y+8;
    for(a=12+x;a>=x;a--)
        for(;b>=c;b--)
            for(i=vel;i>1;i--)
                for(j=vel;j>1;j--){

            if(comando==1&&matriz[b-j][a]==1) { 
                *set=2;return 1;
            }
            
            if(comando==2&&matriz[b+j][a]==1) { 
                *set=0;return 1;
            }

            if(comando==3&&matriz[b][a-i]==1) { 
                *set=1;return 1;
            }
            
            if(comando==4&&matriz[b][a+i]==1) { 
                *set=3;return 1;
            }

        }
    return 0;
}
//esse é para checar qual vai ser a animacao, totalmente de fundo estetico


void makeAnimation(int comando, int *act, int *sair, int cont,int type){
    if(comando!=0&&cont%8==0) *act=*act+1;
    
    if(*act==type)      *act = 0;

    if(comando==-1) *sair = 1;
}



//funcao que desenha o sprite, funciona bem, nao mexer
void drawSpriteEnemy(int i, double posX,double posY,int act,int set){
    al_draw_bitmap_region(spriteEnemy[p[i]],
                                (jogador[i].largura+1)*act,   (jogador[i].altura+1)*set,
                                 jogador[i].largura       ,    jogador[i].altura    ,
                                 posX                   ,    posY               ,0);

}

//funcao que checa onde esta o personagem. ele normalmente estaria centralizado na tela,
//mas se chegar nas pontas ou lados, antes ele acompanharia e ficava uma parte toda bugada.
//entao serve para checar onde vai estar o personagem na tela.

// se ele chegar nos limites, a tela para e o personagem continua
void whereIs(int *whereIsX, int *whereIsY,int comando, int zoom, int px, int py,int vel,int i){
    if(px>=0 && py>=0){
        al_draw_bitmap(map, 0, 0, 0);
        if(comando==1)
            *whereIsY-=vel/zoom;
        if(comando==2)
            *whereIsY+=vel/zoom;
    
        if(comando==3)
            *whereIsX-=vel/zoom;
    
        if(comando==4)
            *whereIsX+=vel/zoom;
    }

    else if(px<=-LARGURA_MAPA+LARGURA_TELA/zoom && py>=0){
        al_draw_bitmap(map, -LARGURA_MAPA+LARGURA_TELA/zoom, 0, 0);
        if(comando==1)
            *whereIsY-=vel/zoom;
        if(comando==2)
            *whereIsY+=vel/zoom;
    
        if(comando==3)
            *whereIsX-=vel/zoom;
    
        if(comando==4)
            *whereIsX+=vel/zoom;
    
    }


    else if(px>=0 && py<=-ALTURA_MAPA+ALTURA_TELA/zoom){
        al_draw_bitmap(map, 0, -ALTURA_MAPA+ALTURA_TELA/zoom, 0);
        if(comando==1)
            *whereIsY-=vel/zoom;
        if(comando==2)
            *whereIsY+=vel/zoom;
    
        if(comando==3)
            *whereIsX-=vel/zoom;
    
        if(comando==4)
            *whereIsX+=vel/zoom;
    
    }

    else if(px<=-LARGURA_MAPA+LARGURA_TELA/zoom &&
            py<=-ALTURA_MAPA +ALTURA_TELA/zoom){
        al_draw_bitmap(map,-LARGURA_MAPA+LARGURA_TELA/zoom,
                           -ALTURA_MAPA+ALTURA_TELA/zoom, 0);
        if(comando==1)
            *whereIsY-=vel/zoom;
        if(comando==2)
            *whereIsY+=vel/zoom;
    
        if(comando==3)
            *whereIsX-=vel/zoom;
    
        if(comando==4)
            *whereIsX+=vel/zoom;
    
    }

    else if(px>=0 && py<0){
        al_draw_bitmap(map, 0, py, 0);

        if(comando==3)
            *whereIsX-=vel/zoom;
    
        if(comando==4)
            *whereIsX+=vel/zoom;
    }

    

    else if(px<0 && py>=0){
        al_draw_bitmap(map, px, 0, 0);
        if(comando==1)
            *whereIsY-=vel/zoom;
        if(comando==2)
            *whereIsY+=vel/zoom;
    
    }

    else if(px>-LARGURA_MAPA+LARGURA_TELA/zoom && 
            py<=-ALTURA_MAPA+ALTURA_TELA/zoom){
        al_draw_bitmap(map, px, -ALTURA_MAPA+ALTURA_TELA/zoom, 0);
        if(comando==1)
            *whereIsY-=vel/zoom;
        if(comando==2)
            *whereIsY+=vel/zoom;

    }

    else if(px<=-LARGURA_MAPA+LARGURA_TELA/zoom &&
            py>-ALTURA_MAPA+ALTURA_TELA/zoom){
        al_draw_bitmap(map, -LARGURA_MAPA+LARGURA_TELA/zoom, py, 0);
    
        if(comando==3)
            *whereIsX-=vel/zoom;
    
        if(comando==4)
            *whereIsX+=vel/zoom;
    }

    else
        al_draw_bitmap(map, px, py, 0);
}

//essa eh como se fossse o main
void walkWithEnemy(int i){

    int zoom = 3;
    makeZoomedGame(zoom);
    int sair = 0, comando =0;
    double vel=zoom;
    int act=0,set=0;
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
        if(comando==5){

        }
        else 
            while(wait!=comando){
            //enquanto nao soltar a tecla ele continua andando para frente
            wait = checkEvent();
            cont++;

            //se ele checar a barreira e nao tiver barreira, ele continue esse if
            if(!checkifBarrer(comando, vel,&set, jogador[i].x, jogador[i].y,0)){
                //ai o personagem anda pra frente
                whichCommandPlayer(comando, vel,&set, i);
            
            px = (-jogador[i].posX)/zoom;
            py = (- jogador[i].posY)/zoom;

            jogador[i].x = (LARGURA_TELA/2+jogador[i].posX)/zoom;
            jogador[i].y = (ALTURA_TELA/2+jogador[i].posY)/zoom;
            
            //e a tela acompanha seu movimento
            whereIs(&whereIsX, &whereIsY, comando, zoom, px, py, vel, i);
            }
            makeAnimation(comando,&act,&sair,cont,4);
            // no final o sprite dele eh desenhado 
            drawSpriteEnemy(i,whereIsX,whereIsY,act,set);
            //essa funcao serve para ver a posicao, eh descartável ao jogo
            al_draw_textf(fontesecundaria, al_map_rgb(20, 20, 20), LARGURA_TELA/2/zoom, 250/zoom, ALLEGRO_ALIGN_CENTRE, 
                "(%d,%d)", LARGURA_TELA/2/zoom+jogador[i].posX/zoom,ALTURA_TELA/2/zoom+jogador[i].posY/zoom);
            al_flip_display();
        }
    }
}

#endif
