#include "AllegroCore.h"



void makeZoomedGame(int zoom){
    ALLEGRO_TRANSFORM t;
    al_identity_transform(&t);
    al_scale_transform(&t, zoom, zoom);
    al_use_transform(&t);
}

void whichCommandEnemy(int comando,int vel_enemy,int *set,int *act,int *sair,int cont,int i){
    if(comando==1)
        enemy[i].posY-=vel_enemy,set=2;

    if(comando==2)
        enemy[i].posY+=vel_enemy,set=0;
    
    if(comando==3)
        enemy[i].posX-=vel_enemy,set=1;
    
    if(comando==4)
        enemy[i].posX+=vel_enemy,set=3;

    if(comando!=0&&cont%5==0) *act=*act+1;
    
    if(*act==2)      *act = 0;

    if(comando==6 || comando==-1) *sair = 1;
}

void drawSpriteEnemy(int i, double posX,double posY,int act,int set){
    al_draw_bitmap_region(spriteEnemy[i],
                                (enemy[i].largura+1)*act,   (enemy[i].altura+1)*set,
                                 enemy[i].largura       ,    enemy[i].altura    ,
                                 posX                   ,    posY               ,0);

}

void whereIsEnemy(int *whereIsEnemyX, int *whereIsEnemyY,int comando, int zoom, int px, int py,int vel_enemy,int i){
    if(px>=0 && py>=0){
        al_draw_bitmap(map, 0, 0, 0);
        if(comando==1)
            *whereIsEnemyY-=vel_enemy/zoom;
        if(comando==2)
            *whereIsEnemyY+=vel_enemy/zoom;
    
        if(comando==3)
            *whereIsEnemyX-=vel_enemy/zoom;
    
        if(comando==4)
            *whereIsEnemyX+=vel_enemy/zoom;
    }

    else if(px<=-LARGURA_MAPA+LARGURA_TELA/zoom && py>=0){
        al_draw_bitmap(map, -LARGURA_MAPA+LARGURA_TELA/zoom, 0, 0);
        if(comando==1)
            *whereIsEnemyY-=vel_enemy/zoom;
        if(comando==2)
            *whereIsEnemyY+=vel_enemy/zoom;
    
        if(comando==3)
            *whereIsEnemyX-=vel_enemy/zoom;
    
        if(comando==4)
            *whereIsEnemyX+=vel_enemy/zoom;
    
    }


    else if(px>=0 && py<=-ALTURA_MAPA+ALTURA_TELA/zoom){
        al_draw_bitmap(map, 0, -ALTURA_MAPA+ALTURA_TELA/zoom, 0);
        if(comando==1)
            *whereIsEnemyY-=vel_enemy/zoom;
        if(comando==2)
            *whereIsEnemyY+=vel_enemy/zoom;
    
        if(comando==3)
            *whereIsEnemyX-=vel_enemy/zoom;
    
        if(comando==4)
            *whereIsEnemyX+=vel_enemy/zoom;
    
    }

    else if(px<=-LARGURA_MAPA+LARGURA_TELA/zoom &&
            py<=-ALTURA_MAPA +ALTURA_TELA/zoom){
        al_draw_bitmap(map,-LARGURA_MAPA+LARGURA_TELA/zoom,
                           -ALTURA_MAPA+ALTURA_TELA/zoom, 0);
        if(comando==1)
            *whereIsEnemyY-=vel_enemy/zoom;
        if(comando==2)
            *whereIsEnemyY+=vel_enemy/zoom;
    
        if(comando==3)
            *whereIsEnemyX-=vel_enemy/zoom;
    
        if(comando==4)
            *whereIsEnemyX+=vel_enemy/zoom;
    
    }

    else if(px>=0 && py<0){
        al_draw_bitmap(map, 0, py, 0);

        if(comando==3)
            *whereIsEnemyX-=vel_enemy/zoom;
    
        if(comando==4)
            *whereIsEnemyX+=vel_enemy/zoom;
    }

    

    else if(px<0 && py>=0){
        al_draw_bitmap(map, px, 0, 0);
        if(comando==1)
            *whereIsEnemyY-=vel_enemy/zoom;
        if(comando==2)
            *whereIsEnemyY+=vel_enemy/zoom;
    
    }

    else if(px>-LARGURA_MAPA+LARGURA_TELA/zoom && 
            py<=-ALTURA_MAPA+ALTURA_TELA/zoom){
        al_draw_bitmap(map, px, -ALTURA_MAPA+ALTURA_TELA/zoom, 0);
        if(comando==1)
            *whereIsEnemyY-=vel_enemy/zoom;
        if(comando==2)
            *whereIsEnemyY+=vel_enemy/zoom;

    }

    else if(px<=-LARGURA_MAPA+LARGURA_TELA/zoom &&
            py>-ALTURA_MAPA+ALTURA_TELA/zoom){
        al_draw_bitmap(map, -LARGURA_MAPA+LARGURA_TELA/zoom, py, 0);
    
        if(comando==3)
            *whereIsEnemyX-=vel_enemy/zoom;
    
        if(comando==4)
            *whereIsEnemyX+=vel_enemy/zoom;
    }

    else
        al_draw_bitmap(map, px, py, 0);
}

void walkWithEnemy(){

    int zoom = 3;
    makeZoomedGame(zoom);
    int sair = 0, comando =0, i=0;
    double vel_enemy=zoom;
    int act=0,set=0;
    enemy[i].largura = 16;
    enemy[i].altura  = 24;
    int pos_inicial_x =(LARGURA_MAPA/2);
    int pos_inicial_y =(ALTURA_MAPA/2); 
    enemy[i].posX = pos_inicial_x  ;
    enemy[i].posY = pos_inicial_y  ;
    int wait,cont;
    int px, py;
    int whereIsEnemyX=LARGURA_TELA/2/zoom;
    int whereIsEnemyY=ALTURA_TELA/2/zoom;



    while(!sair){
        cont=0;
        wait=0;
        comando = checkEvent();
        while(wait!=comando){
            wait = checkEvent();
            cont++;
            whichCommandEnemy(comando, vel_enemy, &set, &act, &sair, cont, i);

            px = (-enemy[i].posX)/zoom;
            py = (- enemy[i].posY)/zoom;

            whereIsEnemy(&whereIsEnemyX, &whereIsEnemyY, comando, zoom, px, py, vel_enemy, i);
            
            drawSpriteEnemy(i,whereIsEnemyX,whereIsEnemyY,act,set);
            
     
            al_flip_display();
        }
    }
}

