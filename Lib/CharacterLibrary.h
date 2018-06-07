#ifndef ENEMY_H
#define ENEMY_H

#include "AllegroCore.h"
#include "MainMenuLibrary.h"

void aleatorizePowerUps(){
    int forget;
    for(int i = 0; i < 4; i++){
        forget = 1;
        while(forget==1){
            forget = 0;
            int var = rand() % 10;
            for(int j=0 ; j < i; j++)if(powerup[j].tipo == var) forget = 1;
            if (forget == 0) powerup[i].tipo = var;
        }
        if(powerup[i].tipo==0) powerup[i].x = 110, powerup[i].y = 240;
        if(powerup[i].tipo==1) powerup[i].x = 570, powerup[i].y = 425;
        if(powerup[i].tipo==2) powerup[i].x = 750, powerup[i].y = 620;
        if(powerup[i].tipo==3) powerup[i].x =1200, powerup[i].y = 250;
        if(powerup[i].tipo==4) powerup[i].x =1400, powerup[i].y = 700;
        if(powerup[i].tipo==5) powerup[i].x =  80, powerup[i].y = 860;
        if(powerup[i].tipo==6) powerup[i].x =1700, powerup[i].y = 950;
        if(powerup[i].tipo==7) powerup[i].x = 625, powerup[i].y = 725;
        if(powerup[i].tipo==8) powerup[i].x =1400, powerup[i].y = 350;
        if(powerup[i].tipo==9) powerup[i].x = 375, powerup[i].y = 270;
        powerup[i].aindatem=1;
    }
    
}


void didIHitAnyone(int i){

}

void declareFirstAtributes(int i,int largura, int altura,int x, int y){
    jogador[i].largura = largura;
    jogador[i].altura  = altura;
    jogador[i].posX = x;
    jogador[i].posY = y;
    jogador[i].weapon = 0,jogador[i].ihaveweapon=0;
    jogador[i].immunityCounter = 0;
    jogador[i].act=0,jogador[i].set=0;
}

void drawSpriteGuard(int i, double posX,double posY){
    if(jogador[i].set==2)
        al_draw_bitmap_region(spriteGuard[p[i]],
            (jogador[i].largura+1)*jogador[i].act, jogador[i].altura+2,
             jogador[i].largura       ,    jogador[i].altura          ,
             posX                      ,    posY                      ,0);
    if(jogador[i].set==0)
        al_draw_bitmap_region(spriteGuard[p[i]],
            (jogador[i].largura+1)*jogador[i].act,    0      ,
             jogador[i].largura       ,    jogador[i].altura ,
             posX                     ,    posY              ,0);
    if(jogador[i].set==1)
        al_draw_bitmap_region(spriteGuard[p[i]],
            (jogador[i].largura+1)*(2+jogador[i].act)+jogador[i].act*1, 0,
             jogador[i].largura                 ,   jogador[i].altura    ,
             posX                               ,   posY                 ,0);
    if(jogador[i].set==3)
        al_draw_bitmap_region(spriteGuard[p[i]],
             66 + jogador[i].largura*jogador[i].act,    0           ,
             jogador[i].largura         ,    jogador[i].altura      ,
             posX                       ,    posY                   ,0);

}

void printPowerUps(int p,int whereIsX,int whereIsY){
    for(int i = 0; i < 4; i ++) if(powerup[i].aindatem!=0){
        
        al_draw_bitmap_region(spriteBomb,
             0 ,   0                      ,
             16,  16                      ,
             powerup[i].x - jogador[p].x + whereIsX,powerup[i].y - jogador[p].y + whereIsY
                                          ,0);

    }

    

}
void didIGotPowerUp(int p, int whereIsX, int whereIsY){
    for(int i = 0; i < 4; i++){
        if( jogador[p].x+7 >=powerup[i].x   &&
            jogador[p].x+7 <=powerup[i].x+16&&
            jogador[p].y+17>=powerup[i].y   &&
            jogador[p].y+17<=powerup[i].y+16&&
            powerup[i].aindatem    == 1     &&
            jogador[p].ihaveweapon == 0     )
                powerup[i].aindatem=0,jogador[p].ihaveweapon=1;
        }
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
         jogador[i].largura                  ,    jogador[i].altura                  ,
         posX                                ,    posY                               ,0);


}

void drawBomb(int i,int whereIsX, int whereIsY){
    if(bomb[i].cont==500) bomb[i].set = -1;
    if(bomb[i].cont<500){
        if (bomb[i].cont%25==0) bomb[i].set++;
        if(bomb[i].set>=4) bomb[i].set=0;
        al_draw_bitmap_region(spriteBomb,
             17*bomb[i].set , 0,
             16             ,16,
             bomb[i].x - jogador[i].x + whereIsX, bomb[i].y -jogador[i].y + whereIsY, 0);
    }
    else if(bomb[i].cont<=700){
        if((bomb[i].cont-500)%40 == 0) bomb[i].set++;
        if(bomb[i].set>=5) bomb[i].set=0;
        al_draw_bitmap_region(spriteExplosion,
             80*bomb[i].set   , 0,
             80   , 80        ,
             -32 + bomb[i].x - jogador[i].x + whereIsX, -32 + bomb[i].y -jogador[i].y + whereIsY, 0);
    }
}

void drawSpriteGuardShield(int i, int posX, int posY, int contshield){
    contshield=3*contshield/4;
    //p cima
    if(jogador[i].set==2)al_draw_bitmap_region(spriteShield,
             0,    0                      ,
             7,    7                      ,
             posX + 7.5     ,    posY -contshield,0);
    //p baixo
    if(jogador[i].set==0)al_draw_bitmap_region(spriteShield,
             0,    0                      ,
             7,    7                      ,
             posX + 7.5     ,    posY + 20 +contshield,0);
    //p esquerda
    if(jogador[i].set==1)al_draw_bitmap_region(spriteShield,
             0,    0                      ,
             7,    7                      ,
             posX -contshield,    posY + 10 ,0);
    //p direita
    if(jogador[i].set==3)al_draw_bitmap_region(spriteShield,
             0,    0                      ,
             7,    7                      ,
             posX + 15 +contshield ,  posY + 10 ,0);
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
int checkIfBarrer(int comando,int vel,int x,int y,int type){
    int i,j,a,b,c;
    if(type==0) a=x+10,b=y+20,c=y+17;
    if(type==1) a=x+7,b=y+15,c=y+8;

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

    if(comando==-1) *sair = 1;
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

void isThereAnotherPlayer(int i,int whereIsX, int whereIsY){
    for(int j=0;j<8;j++){
        if(j%2==0){
            if(jogador[j].comando!=5)
                drawSpriteGuard(j,jogador[j].x - jogador[i].x + whereIsX,jogador[j].y - jogador[i].y + whereIsY);
            if(jogador[j].comando==5)
                drawSpriteGuardHit(j,jogador[j].x - jogador[i].x + whereIsX,jogador[j].y - jogador[i].y + whereIsY);
        }
        else{
            if(jogador[j].comando!=5)
                drawSpriteEnemy(j,jogador[j].x - jogador[i].x + whereIsX,jogador[j].y - jogador[i].y + whereIsY);
            //if(jogador[j].comando==5)
            //   drawSpriteEnemyHit(j,jogador[j].x,jogador[j].y);
        }
        al_draw_textf(fontepersonagem, jogador[j].cor, whereIsX+10, whereIsY-10, ALLEGRO_ALIGN_CENTRE, 
                              "%s", jogador[j].nome);
    }
}




#endif
