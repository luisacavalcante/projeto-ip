#include "AllegroCore.h"


#define FPS 60.0

void error_msg(char *text){
	fprintf(stderr, "%s",text);
}

int main(void){
    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,NULL);
    if (!inicializar()) return -1;
    int sair = 0;
    int comando =0;
    
//ESSA FUNCAO DA ZOOM
    int zoom = 3;
    ALLEGRO_TRANSFORM t;
    al_identity_transform(&t);
    al_scale_transform(&t, zoom, zoom);
    al_use_transform(&t);


    int i=1;
    double vel_enemy=0.8;
    int act=0,set=0;
 	enemy[i].largura = 16;
 	enemy[i].altura = 24;
 	enemy[i].posX = (LARGURA_TELA/2)/zoom;
 	enemy[i].posY = (ALTURA_TELA/2)/zoom;
    int wait;
    int px, py;
    while(!sair){
 		wait=0;
		comando = checkEvent();
        while(wait!=comando){
            wait = checkEvent();
        	if(comando==1){ 
        		enemy[i].posY-=vel_enemy;
                act++;
                set=2;
        	}
            if(comando==2){ 
                enemy[i].posY+=vel_enemy;
                act++;
                set=0;
            }
            if(comando==3){
                enemy[i].posX-=vel_enemy;
                act++;
                set=1;
            }
            if(comando==4){
                enemy[i].posX+=vel_enemy;
                act++;
                set=3;
            }
            if(act==4) act = 0;
    		if(comando==6) sair=1;	
    
            if(comando==-1)
                sair = 1;
            px = zoom*((LARGURA_TELA/2)-enemy[i].posX);
            py = zoom*((ALTURA_TELA/2)-enemy[i].posY);
            if(px>=0 && py>=0)
                al_draw_bitmap(map, 0, 0, 0);

            else if(px>=0 && py<0)
                al_draw_bitmap(map, 0, py, 0);

            else if(px<0 && py>=0)
                al_draw_bitmap(map, px, 0, 0);

            else if(px<=-LARGURA_MAPA && py<=-ALTURA_MAPA)
                al_draw_bitmap(map, LARGURA_MAPA, ALTURA_MAPA, 0);

            else if(px>-LARGURA_MAPA && py<=-ALTURA_MAPA)
                al_draw_bitmap(map, px, ALTURA_MAPA, 0);

            else if(px<=-LARGURA_MAPA && py>-ALTURA_MAPA)
                al_draw_bitmap(map, LARGURA_MAPA, py, 0);

            else if(px<=-LARGURA_MAPA && py>=0)
                al_draw_bitmap(map, LARGURA_MAPA, 0, 0);

            else if(px>=0 && py<=-LARGURA_MAPA)
                al_draw_bitmap(map, 0, ALTURA_MAPA, 0);

            else
            al_draw_bitmap(map, px, py, 0);
            al_draw_bitmap_region(spriteEnemy[i],
                                (enemy[i].largura+1)*act,	(enemy[i].altura+1)*set,
                                 enemy[i].largura 		,	 enemy[i].altura 	,
                                 enemy[i].posX   		,	 enemy[i].posY 	  	,0);
     
            al_flip_display();
        }
    }
 
 	
    destruir();
 
    return 0;
}


//int main(void){
//    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,NULL);
//    if (!inicializar()) return -1;
//    int sair = 0;
//    int comando =0;
//
//    int i=0;
//    int act=0,set=0;
//    enemy[i].largura = 16;
//    enemy[i].altura = 24;
//    enemy[i].posX = LARGURA_TELA/2;
//    enemy[i].posY = ALTURA_TELA/2;
//    int wait;
//    
//    while(!sair){
//        al_draw_bitmap(map, 0, 0, 0);
//        wait=-1;
//        comando = checkEvent();
//        while(wait==comando){
//            wait = checkEvent();
//            if(comando==1){ 
//                enemy[i].posY--;
//                act++;
//                set=2;
//            }
//            if(comando==2){ 
//                enemy[i].posY++;
//                act++;
//                set=0;
//            }
//            if(comando==3){
//                enemy[i].posX--;
//                act++;
//                set=1;
//            }
//            if(comando==4){
//                enemy[i].posX++;
//                act++;
//                set=3;
//            }
//            if(act==4) act = 0;
//            if(comando==6) sair=1;  
//    
//            if(comando==-1) sair = 1;
//            al_draw_bitmap(map, 0, 0, 0);
//            al_draw_bitmap_region(spriteEnemy[i],
//                                (enemy[i].largura+1)*act,   (enemy[i].altura+1)*set,
//                                 enemy[i].largura       ,    enemy[i].altura    ,
//                                 enemy[i].posX          ,    enemy[i].posY      ,0);
//     
//            al_flip_display();
//        }
//    }



