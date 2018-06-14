#ifndef ENEMY_H
#define ENEMY_H

#include "AllegroCore.h"
#include "MainMenuLibrary.h"
#include "ClientLibrary.h"
void writeName(int i, int whereIsX,int whereIsY){
    al_draw_textf(fontepersonagem, jogador[i].cor, whereIsX+10, whereIsY-10, ALLEGRO_ALIGN_CENTRE, 
                              "%s", jogador[i].nome);
}

/*void aleatorizePowerUps(){
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
    
}*/


void didIGetHurt(int i){
    for(int j=0; j<8; j++){
        if(j%2!=i%2 && jogador[j].comando == 5&&jogador[i].immunity<=0){
            if(jogador[j].set==2){
                if( jogador[j].y - jogador[i].y <= 24 &&
                    jogador[j].y - jogador[i].y >= 17 &&
                    jogador[j].x - jogador[i].x <= 15 &&
                    jogador[j].x - jogador[i].x >=  7)
                    jogador[i].lifeBar--,jogador[i].immunity = 90;
            }
            else if(jogador[j].set==0){
                if( jogador[j].y - jogador[i].y >= -31 &&
                    jogador[j].y - jogador[i].y <= -18 &&
                    jogador[j].x - jogador[i].x >=   7 &&
                    jogador[j].x - jogador[i].x <=  15)
                    jogador[i].lifeBar--,jogador[i].immunity = 90;
            }
            else if(jogador[j].set==1){
                if( jogador[j].x - jogador[i].x <= 27 &&
                    jogador[j].x - jogador[i].x >=  8 &&
                    jogador[j].y - jogador[i].y <=  8 &&
                    jogador[j].y - jogador[i].y >= -8 )
                    jogador[i].lifeBar--,jogador[i].immunity = 90;
            }
            else if(jogador[j].set==3){
                if( jogador[j].x - jogador[i].x >= -27 &&
                    jogador[j].x - jogador[i].x <= -8 &&
                    jogador[j].y - jogador[i].y <=  8 &&
                    jogador[j].y - jogador[i].y >= -8 )
                    jogador[i].lifeBar--,jogador[i].immunity = 90;
            }
        }
    }

 }

 void printLifeBar(int i,int posX, int posY){
    if(jogador[i].lifeBar == 5) al_draw_bitmap_region(spriteLifeBar,
             0,0,
             23, 6   ,
             posX,  posY,0);
    if(jogador[i].lifeBar == 4) al_draw_bitmap_region(spriteLifeBar,
             22,0,
             23, 6 ,
             posX,  posY,0);
    if(jogador[i].lifeBar == 3) al_draw_bitmap_region(spriteLifeBar,
             45,0,
             22, 6   ,
             posX,  posY,0);
    if(jogador[i].lifeBar == 2) al_draw_bitmap_region(spriteLifeBar,
             67,0,
             23, 6   ,
             posX,  posY,0);
    if(jogador[i].lifeBar == 1) al_draw_bitmap_region(spriteLifeBar,
             67,0,
             23, 6   ,
             posX,  posY,0);
 }

void declareFirstAtributes(int i,int largura, int altura,int x, int y){
    jogador[i].largura = largura;
    jogador[i].altura  = altura;
    jogador[i].posX = x;
    jogador[i].posY = y;
    jogador[i].weapon = 0,jogador[i].ihaveweapon=0;
    jogador[i].immunity = 0;
    jogador[i].act=0,jogador[i].set=0;
    jogador[i].lifeBar = 5;
}

void drawSpriteGuard(int i, double posX,double posY){
    if(jogador[i].set==2)
        al_draw_bitmap_region(spriteGuard[jogador[i].color],
            (jogador[i].largura+1)*jogador[i].act, jogador[i].altura+2,
             jogador[i].largura       ,    jogador[i].altura          ,
             posX                      ,    posY                      ,0);
    if(jogador[i].set==0)
        al_draw_bitmap_region(spriteGuard[jogador[i].color],
            (jogador[i].largura+1)*jogador[i].act,    0      ,
             jogador[i].largura       ,    jogador[i].altura ,
             posX                     ,    posY              ,0);
    if(jogador[i].set==1)
        al_draw_bitmap_region(spriteGuard[jogador[i].color],
            (jogador[i].largura+1)*(2+jogador[i].act)+jogador[i].act*1, 0,
             jogador[i].largura                 ,   jogador[i].altura    ,
             posX                               ,   posY                 ,0);
    if(jogador[i].set==3)
        al_draw_bitmap_region(spriteGuard[jogador[i].color],
             66 + jogador[i].largura*jogador[i].act,    0           ,
             jogador[i].largura         ,    jogador[i].altura      ,
             posX                       ,    posY                   ,0);

}

void printPowerUps(int p,int whereIsX,int whereIsY){
    for(int i = 0; i < 4; i ++) if(jogador[p].power[i].aindatem!=0){
        
        al_draw_bitmap_region(spriteBomb,
             0 ,   0                      ,
             16,  16                      ,
             jogador[p].power[i].x - jogador[p].x + whereIsX,jogador[p].power[i].y - jogador[p].y + whereIsY
                                          ,0);

    }

    
}
void didIGotPowerUp(int p, int whereIsX, int whereIsY){
    for(int i = 0; i < 5; i++){
        if((p%2) == 1 && jogador[p].x+7 >=jogador[p].power[i].x   &&
            jogador[p].x+7 <=jogador[p].power[i].x+16&&
            jogador[p].y+17>=jogador[p].power[i].y   &&
            jogador[p].y+17<=jogador[p].power[i].y+16&&
            jogador[p].power[i].aindatem    == 1     &&
            jogador[p].ihaveweapon == 0 && i==5){
                jogador[p].power[i].aindatem=0,jogador[p].ihaveweapon=2;
        }
        if( jogador[p].x+7 >=jogador[p].power[i].x   &&
            jogador[p].x+7 <=jogador[p].power[i].x+16&&
            jogador[p].y+17>=jogador[p].power[i].y   &&
            jogador[p].y+17<=jogador[p].power[i].y+16&&
            jogador[p].power[i].aindatem    == 1     &&
            jogador[p].ihaveweapon == 0   && i!=5)
                jogador[p].power[i].aindatem=0,jogador[p].ihaveweapon=1;
        }
    }


void drawSpriteGuardHit(int i,int posX,int posY){
    if(jogador[i].set==2)//p cima
        al_draw_bitmap_region(spriteGuardHit[jogador[i].color],
             34 + 16*jogador[i].act         ,    1     ,
             15                     ,    24    ,
             posX                   ,    posY - 4,0);
    if(jogador[i].set==0)//p baixo
        al_draw_bitmap_region(spriteGuardHit[jogador[i].color],
             15*jogador[i].act              ,    5     ,
             15                     ,    32    ,
             posX -jogador[i].act              ,    posY  ,0);
    if(jogador[i].set==1)//p esquerda
        al_draw_bitmap_region(spriteGuardHit[jogador[i].color],
             25*jogador[i].act                  ,   61     ,
             25                     ,   19     ,
             posX - 9 - 6*jogador[i].act       ,   posY   ,0);
    if(jogador[i].set==3)//p direita
        al_draw_bitmap_region(spriteGuardHit[jogador[i].color],
             2 + 28*jogador[i].act          ,   41     ,
             26                     ,   19     ,
             posX +3*jogador[i].act            ,   posY+1 ,0);

}

void drawSpriteEnemy(int i, double posX,double posY){
    al_draw_bitmap_region(spriteEnemy[jogador[i].color],
        (jogador[i].largura+1)*jogador[i].act,   (jogador[i].altura+1)*jogador[i].set,
         jogador[i].largura                  ,    jogador[i].altura                  ,
         posX                                ,    posY                               ,0);


}

void drawBomb(int i,int whereIsX, int whereIsY){
    if(jogador[i].bomb.cont==500) jogador[i].bomb.set = -1;
    if(jogador[i].bomb.cont<500){
        if (jogador[i].bomb.cont%25==0) jogador[i].bomb.set++;
        if(jogador[i].bomb.set>=4) jogador[i].bomb.set=0;
        al_draw_bitmap_region(spriteBomb,
             17*jogador[i].bomb.set , 0,
             16             ,16,
             jogador[i].bomb.x - jogador[i].x + whereIsX, jogador[i].bomb.y -jogador[i].y + whereIsY, 0);
    }
    else if(jogador[i].bomb.cont<=700){
        if((jogador[i].bomb.cont-500)%40 == 0) jogador[i].bomb.set++;
        if(jogador[i].bomb.set>=5) jogador[i].bomb.set=0;
        al_draw_bitmap_region(spriteExplosion,
             80*jogador[i].bomb.set   , 0,
             80   , 80        ,
             -32 + jogador[i].bomb.x - jogador[i].x + whereIsX, -32 + jogador[i].bomb.y -jogador[i].y + whereIsY, 0);
    }
}

void didIGetBurn(int j){
    int i;
    for(i=0; i<8; i++){
        if(jogador[i].bomb.isOn&&jogador[i].bomb.cont>=500 && jogador[j].immunity <= 0){
                if( jogador[j].y - jogador[i].bomb.y >= -32 &&  //checa se esta dentro de todo sprite bomba
                    jogador[j].y - jogador[i].bomb.y <=  40 &&
                    jogador[j].x - jogador[i].bomb.x >= -32 &&
                    jogador[j].x - jogador[i].bomb.x <=  48){
                    if( jogador[j].x + jogador[j].largura - jogador[i].bomb.x <= 4      && //checa o primeiro quadrante
                        jogador[j].y + jogador[j].altura - jogador[i].bomb.y <= 4       )
                        break;
                    else if( jogador[j].x - jogador[i].bomb.x >= 16                      && //segundo quadrante
                             jogador[j].y + jogador[j].altura - jogador[i].bomb.y <= 4   )
                        break;
                    else if( jogador[j].x + jogador[j].largura - jogador[i].bomb.x < 0  && //terceiro quadrante
                             jogador[j].y - jogador[i].bomb.y > 16                      )
                        break;
                    else if( jogador[j].x - jogador[i].bomb.x > 16                      && // quarto quadrante
                             jogador[j].y - jogador[i].bomb.y > 16                      )
                        break;
                    
                    else jogador[j].lifeBar--,jogador[j].immunity = 90 ;

                }    
            
        }
    }
     //caso ele nao esteja em nenhum dos quadrantes, se encontra na area afetada pela bomba e sofre dano
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

    if(comando==9||comando==-1) *sair = 1;
}

//funcao que desenha o sprite, funciona bem, nao mexer


//funcao que checa onde esta o personagem. ele normalmente estaria centralizado na tela,
//mas se chegar nas pontas ou lados, antes ele acompanharia e ficava uma parte toda bugada.
//entao serve para checar onde vai estar o personagem na tela.

// se ele chegar nos limites, a tela para e o personagem continua
void whereIs(ALLEGRO_BITMAP *mapa ,int *whereIsX, int *whereIsY,int comando, int zoom, int px, int py,int vel,int i){
    if(px>=0 && py>=0){
        al_draw_bitmap(mapa, 0, 0, 0);
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
        al_draw_bitmap(mapa, -LARGURA_MAPA+LARGURA_TELA/zoom, 0, 0);
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
        al_draw_bitmap(mapa, 0, -ALTURA_MAPA+ALTURA_TELA/zoom, 0);
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
        al_draw_bitmap(mapa,-LARGURA_MAPA+LARGURA_TELA/zoom,
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
        al_draw_bitmap(mapa, 0, py, 0);

        if(comando==3)
            *whereIsX-=vel/zoom;
    
        if(comando==4)
            *whereIsX+=vel/zoom;
    }

    

    else if(px<0 && py>=0){
        al_draw_bitmap(mapa, px, 0, 0);
        if(comando==1)
            *whereIsY-=vel/zoom;
        if(comando==2)
            *whereIsY+=vel/zoom;
    
    }

    else if(px>-LARGURA_MAPA+LARGURA_TELA/zoom && 
            py<=-ALTURA_MAPA+ALTURA_TELA/zoom){
        al_draw_bitmap(mapa, px, -ALTURA_MAPA+ALTURA_TELA/zoom, 0);
        if(comando==1)
            *whereIsY-=vel/zoom;
        if(comando==2)
            *whereIsY+=vel/zoom;

    }

    else if(px<=-LARGURA_MAPA+LARGURA_TELA/zoom &&
            py>-ALTURA_MAPA+ALTURA_TELA/zoom){
        al_draw_bitmap(mapa, -LARGURA_MAPA+LARGURA_TELA/zoom, py, 0);
    
        if(comando==3)
            *whereIsX-=vel/zoom;
    
        if(comando==4)
            *whereIsX+=vel/zoom;
    }

    else
        al_draw_bitmap(mapa, px, py, 0);
}
void drawDeadSprite(int i,int posX,int posY){
    if(i%2==0) {

    }

    else al_draw_bitmap_region(enemyDead,
         69 + jogador[i].color*17,   0,
         16  , 16,
         posX    ,    posY,0);
}
//MUDEI
void isThereAnotherPlayer(int conectados,int i,int whereIsX, int whereIsY){
    for(int j=0;j<conectados;j++){
	if(i!=j)
        if(jogador[i].lifeBar>0){
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
                //drawSpriteEnemyHit(j,jogador[j].x,jogador[j].y);
            }

        writeName   (j,jogador[j].x - jogador[i].x + whereIsX,jogador[j].y - jogador[i].y + whereIsY);
        printLifeBar(j,jogador[j].x - jogador[i].x + whereIsX - 4 ,jogador[j].y - jogador[i].y + whereIsY + 24);
        }
        else drawDeadSprite(j,jogador[j].x - jogador[i].x + whereIsX + 10,jogador[j].y - jogador[i].y + whereIsY + 10);
    }
}

//ADICIONEI
void printThings(int i,int whereIsX,int whereIsY,int conectados){
            
    isThereAnotherPlayer(conectados,i,whereIsX,whereIsY);

    if(i%2==0)drawSpriteGuard(i,whereIsX,whereIsY);

       else drawSpriteEnemy(i,whereIsX,whereIsY);

    if(jogador[i].bomb.cont < 700) drawBomb(i,whereIsX,whereIsY);

    printPowerUps(i,whereIsX,whereIsY);
    
    writeName(i,whereIsX,whereIsY);
    printLifeBar(i,whereIsX - 4,whereIsY + 24);
}



#endif
