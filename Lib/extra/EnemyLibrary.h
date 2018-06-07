#ifndef ENEMY_H
#define ENEMY_H

#include "AllegroCore.h"
#include "MainMenuLibrary.h"

void drawSpriteGuard(int i, double posX,double posY){
    if(jogador[i].set==2)
        al_draw_bitmap_region(spriteGuard[p[i]],
            (jogador[i].largura+1)*jogador[i].act,    jogador[i].altura+2,
             jogador[i].largura       ,    jogador[i].altura  ,
             posX                      ,    posY              ,0);
    if(jogador[i].set==0)
        al_draw_bitmap_region(spriteGuard[p[i]],
            (jogador[i].largura+1)*jogador[i].act,    0                 ,
             jogador[i].largura       ,    jogador[i].altura ,
             posX                     ,    posY              ,0);
    if(jogador[i].set==1)
        al_draw_bitmap_region(spriteGuard[p[i]],
            (jogador[i].largura+1)*(2+jogador[i].act)+jogador[i].act*1,   0                ,
             jogador[i].largura                 ,   jogador[i].altura,
             posX                               ,   posY             ,0);
    if(jogador[i].set==3)
        al_draw_bitmap_region(spriteGuard[p[i]],
             66 + jogador[i].largura*jogador[i].act,    0                      ,
             jogador[i].largura         ,    jogador[i].altura      ,
             posX                       ,    posY                   ,0);

}

void drawSpriteGuardHit(int i,int posX,int posY){
    if(jogador[i].set==2)//p cima
        al_draw_bitmap_region(spriteGuardHit[p[i]],
             34 + 16*jogador[i].act         ,    1     ,
             15                     ,    24    ,
             posX                   ,    posY - 4,0);
    if(jogador[i].set==0)//p baixo
        al_draw_bitmap_region(spriteGuardHit[p[i]],
             15*jogador[i].act              ,    5     ,
             15                     ,    32    ,
             posX -jogador[i].act              ,    posY  ,0);
    if(jogador[i].set==1)//p esquerda
        al_draw_bitmap_region(spriteGuardHit[p[i]],
             25*jogador[i].act                  ,   61     ,
             25                     ,   19     ,
             posX - 9 - 6*jogador[i].act       ,   posY   ,0);
    if(jogador[i].set==3)//p direita
        al_draw_bitmap_region(spriteGuardHit[p[i]],
             2 + 28*jogador[i].act          ,   41     ,
             26                     ,   19     ,
             posX +3*jogador[i].act            ,   posY+1 ,0);

}

void drawSpriteEnemy(int i, double posX,double posY){
    al_draw_bitmap_region(spriteEnemy[p[i]],
                                (jogador[i].largura+1)*jogador[i].act,   (jogador[i].altura+1)*jogador[i].set,
                                 jogador[i].largura       ,    jogador[i].altura    ,
                                 posX                   ,    posY               ,0);

}

void corPersonagem(int i){
    if(i==0||i==1) jogador[i].cor = al_map_rgb(0,255,0);
    if(i==2||i==3) jogador[i].cor = al_map_rgb(0,0,255);
    if(i==4||i==5) jogador[i].cor = al_map_rgb(255,0,0);
    if(i==6||i==7) jogador[i].cor = al_map_rgb(255,255,0);
}

//Esse comando vai checar  qual foi o comando que recebeu do teclado
void whichCommandPlayer(int comando,int vel,int i){
    //1=cima,2=baixo,3=esquerda,4=direita
    //jogador[i].set é qual jogador[i].set de sprites eu devo usar
    if(comando==1)
        jogador[i].posY-=vel,jogador[i].set=2;

    if(comando==2)
        jogador[i].posY+=vel,jogador[i].set=0;
    
    if(comando==3)
        jogador[i].posX-=vel,jogador[i].set=1;
    
    if(comando==4)
        jogador[i].posX+=vel,jogador[i].set=3;

    
}

//Esse é o comando que dá erro. era para checar se a parte dos pés vai bater no
//rosa, mas nao esta dando certo
int checkifBarrer(int comando,int vel,int x,int y,int type){
    int i,j,a,b,c;
    if(type==0) b=y+20,c=y+17;
    if(type==1) b=y+15,c=y+8;
    for(a=12+x;a>=x;a--)
        for(;b>=c;b--)
            for(i=vel;i>1;i--)
                for(j=vel;j>1;j--){

            if(comando==1&&matriz[b-j][a]==1) { 
                jogador[i].set=2;return 1;
            }
            
            if(comando==2&&matriz[b+j][a]==1) { 
                jogador[i].set=0;return 1;
            }

            if(comando==3&&matriz[b][a-i]==1) { 
                jogador[i].set=1;return 1;
            }
            
            if(comando==4&&matriz[b][a+i]==1) { 
                jogador[i].set=3;return 1;
            }

        }
    return 0;
}
//esse é para checar qual vai ser a animacao, totalmente de fundo estetico
void makeAnimation(int i,int comando, int *sair, int cont,int type){
    if(comando!=0&&cont%8==0) jogador[i].act++;
    
    if(jogador[i].act==type)      jogador[i].act = 0;

    if(comando==6 || comando==-1) *sair = 1;
}

//funcao que desenha o sprite, funciona bem, nao mexer


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

void isThereAnotherPlayer(int i,int zoom){
    for(int j=0;j<8;j++){
        if((jogador[j].x<=LARGURA_TELA/2/zoom+jogador[i].x) &&
           (jogador[j].x>=-LARGURA_TELA/2/zoom+jogador[i].x)&&
           (jogador[j].y<=ALTURA_TELA/2/zoom+jogador[i].y)  &&
           (jogador[j].y>=-ALTURA_TELA/2/zoom+jogador[i].y)){
                if(j%2==0){
                    if(jogador[j].comando!=5)
                        drawSpriteGuard(j,jogador[j].x - jogador[i].x + LARGURA_TELA/2/zoom,jogador[j].y - jogador[i].y + ALTURA_TELA/2/zoom);
                    if(jogador[j].comando==5)
                        drawSpriteGuardHit(j,jogador[j].x - jogador[i].x + LARGURA_TELA/2/zoom,jogador[j].y - jogador[i].y + ALTURA_TELA/2/zoom);
                }
                else{
                    if(jogador[j].comando!=5)
                        drawSpriteEnemy(j,jogador[j].x,jogador[j].y);
                    //if(jogador[j].comando==5)
                    //   drawSpriteEnemyHit(j,jogador[j].x,jogador[j].y);
                }
        }
    }
}

//essa eh como se fossse o main


#endif
