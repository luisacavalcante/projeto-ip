#ifndef GAME_H
#define GAME_H

// Os arquivos de cabeçalho
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Matriz.h"

typedef struct{
    int tipo;
    int x,y;
    int aindatem;

}powerUP;

typedef struct{
    int set;
    int isOn;
    int cont;
    int x, y;
}bomber;

powerUP powerup[5];

typedef struct{
    int whatis;
    int id;
    int lifeBar;
    char nome[16];
    int posX, posY,x,y;
    int altura;//24     //20
    int largura;//16    //15
    ALLEGRO_COLOR cor;
    int set, act;
    int comando;
    int color;
    int weapon, ihaveweapon;
    int immunity;
    powerUP power[5];
    bomber bomb;	
}character;

 

#define fps 30
character jogador[8];
//INICIAR SPRITES

// Atributos da tela
const int LARGURA_TELA = 1440;
const int ALTURA_TELA = 900;

const int LARGURA_MAPA = 1789;
const int ALTURA_MAPA = 1405;

//Eventos
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
//Imagens
ALLEGRO_BITMAP *map = NULL, *logocin = NULL,*mainmap = NULL, *foremap = NULL;
// A nossa janela
ALLEGRO_DISPLAY *janela = NULL;
// O nosso arquivo de fonte

//MODIFIQUEI
ALLEGRO_FONT *fontetitulo = NULL,*fontesecundaria = NULL,*fontemusica = NULL, *fontepersonagem = NULL;
//Musicas
ALLEGRO_SAMPLE *sample = NULL, *sample2 = NULL;

ALLEGRO_LOCKED_REGION *lockmap;

ALLEGRO_BITMAP *spriteEnemy[4],*spriteEnemyHit[4],*spriteGuard[4],*spriteGuardHit[4],
               *spriteShield, *spriteBomb, *spriteExplosion, *spriteLifeBar, *enemyDead;
char name[16], p[8];
char ip[40];
void keyConsequece(int command,int *i){
    if(command==1)
        *i=*i-1;
    else if(command==2)
        *i=*i+1;
    if(*i<0) *i=3;
    if(*i>3) *i=0;

}
int qualComando(int command){
    switch(command){
        case ALLEGRO_KEY_UP:    return 1;
        case ALLEGRO_KEY_W:     return 1;

        case ALLEGRO_KEY_DOWN:  return 2;
        case ALLEGRO_KEY_S:     return 2;

        case ALLEGRO_KEY_LEFT:  return 3;
        case ALLEGRO_KEY_A:     return 3;

        case ALLEGRO_KEY_RIGHT: return 4;
        case ALLEGRO_KEY_D:     return 4;

        case ALLEGRO_KEY_ENTER: return 5;
        case ALLEGRO_KEY_SPACE: return 5;

        case ALLEGRO_KEY_TAB:   return 6;
        case ALLEGRO_KEY_ESCAPE:return-1;

        case ALLEGRO_KEY_P:     return 7;

        default:                return 0;
    }
}

//comando que checa o evento no teclado
int checkEvent(){
    int command = 0;
    ALLEGRO_EVENT evento;
    ALLEGRO_TIMEOUT timeout;
    al_init_timeout(&timeout, 1/fps);
    int tem_eventos = al_wait_for_event_until(fila_eventos, &evento, &timeout);
    if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
        command = qualComando(evento.keyboard.keycode);
    if (evento.type == ALLEGRO_EVENT_KEY_UP)
        command = 10+qualComando(evento.keyboard.keycode);
    if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        command = -1;
    	
    return command;
}

int checkEvent5(){
    int command = 0;
    ALLEGRO_EVENT evento;
    ALLEGRO_TIMEOUT timeout;
    al_init_timeout(&timeout, 1/fps);
    int tem_eventos = al_wait_for_event_until(fila_eventos, &evento, &timeout);
    if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
        command = qualComando(evento.keyboard.keycode);
    if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        command = -1;
        
    return command;
}

void readNameString(ALLEGRO_EVENT evento){
    if (evento.type == ALLEGRO_EVENT_KEY_CHAR){
        if (strlen(name) < 15){
            char temp[] = {evento.keyboard.unichar, '\0'};
            if (evento.keyboard.unichar == ' '      ||
                (evento.keyboard.unichar >= '0'     &&
                 evento.keyboard.unichar <= '9')    ||
                (evento.keyboard.unichar >= 'A'     &&
                 evento.keyboard.unichar<= 'Z')     || 
                (evento.keyboard.unichar >= 'a'     &&
                 evento.keyboard.unichar <= 'z')    )
                strcat(name, temp);
        }
 
        if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(name) != 0)
            name[strlen(name) - 1] = '\0';
    }
}

void makeZoomedGame(double zoom){
    ALLEGRO_TRANSFORM t;
    al_identity_transform(&t);
    al_scale_transform(&t, zoom, zoom);
    al_use_transform(&t);
}


int downloadSprites(){
    //MODIFIQUEI

    //carrega a folha de sprites na variavel
    
    spriteEnemy[0] = al_load_bitmap("Sprites/enemyGreen.png");
    spriteEnemy[1] = al_load_bitmap("Sprites/enemyBlue.png");
    spriteEnemy[2] = al_load_bitmap("Sprites/enemyRed.png");
    spriteEnemy[3] = al_load_bitmap("Sprites/enemyYellow.png");

    spriteEnemyHit[0] = al_load_bitmap("Sprites/enemyGreenHit.png");
//  spriteEnemyHit[1] = al_load_bitmap("Sprites/enemyBlueHit.png");
    spriteEnemyHit[2] = al_load_bitmap("Sprites/enemyRedHit.png");
//  spriteEnemyHit[3] = al_load_bitmap("Sprites/enemyGreenHit.png");

    spriteGuard[0] = al_load_bitmap("Sprites/guardGreen.png");
    spriteGuard[1] = al_load_bitmap("Sprites/guardBlue.png");
    spriteGuard[2] = al_load_bitmap("Sprites/guardRed.png");
    spriteGuard[3] = al_load_bitmap("Sprites/guardYellow.png");

    spriteGuardHit[0] = al_load_bitmap("Sprites/guardGreenHit.png");
    spriteGuardHit[1] = al_load_bitmap("Sprites/guardBlueHit.png");
    spriteGuardHit[2] = al_load_bitmap("Sprites/guardRedHit.png");
    spriteGuardHit[3] = al_load_bitmap("Sprites/guardYellowHit.png");

    spriteShield    = al_load_bitmap("Sprites/guardShield.png");
    spriteBomb      = al_load_bitmap("Sprites/Bomb.png");
    spriteExplosion = al_load_bitmap("Sprites/Explosions.png");
    spriteLifeBar   = al_load_bitmap("Sprites/HealthBar.png");

    enemyDead      = al_load_bitmap("Sprites/enemyDead.png");
    for(int i=0;i<4;i++){
        if (!spriteEnemy[i]|| !spriteGuard[i]){
            fprintf(stderr, "Falha ao carregar sprites.\n");
            return 0;
        }
    
        //usa a cor verde-claro como transparencia
        al_convert_mask_to_alpha(spriteEnemy[i],al_map_rgb(64,176,136));
        //usa a cor verde-escuro como transparencia
        al_convert_mask_to_alpha(spriteEnemy[i],al_map_rgb(32,89,68));
        //
        al_convert_mask_to_alpha(spriteGuard[i],al_map_rgb(0,64,88));

        al_convert_mask_to_alpha(spriteGuardHit[i],al_map_rgb(0,64,88));
    }

        al_convert_mask_to_alpha(spriteBomb,al_map_rgb(112,146,190));
        
        al_convert_mask_to_alpha(spriteExplosion,al_map_rgb(112,146,190));

        al_convert_mask_to_alpha(enemyDead,al_map_rgb(64,176,136));

        al_convert_mask_to_alpha(enemyDead,al_map_rgb(32,89,68));
    
    for (int i = 0; i < 4; i++){
        if(i==0||i==2){
        al_convert_mask_to_alpha(spriteEnemyHit[i],al_map_rgb(64,176,136));
        al_convert_mask_to_alpha(spriteEnemyHit[i],al_map_rgb(32,89,68));

        }
    }
    
    for(int i = 0, j = 0, k = 0;i < 8; i++){
        if(i%2==0) p[i]=k,k++;
        if(i%2!=0) p[i]=j,j++;
    }
    return 1;
}

int downloadFonts(){
    fontetitulo = al_load_font("Fonts/Algol.ttf", 112, 0);
    if (!fontetitulo){
        al_destroy_display(janela);
        fprintf(stderr, "Falha ao carregar fonte.\n");
        return 0;
    }
    fontesecundaria = al_load_font("Fonts/Algol.ttf", 42, 0);
    if (!fontesecundaria){
        al_destroy_display(janela);
        fprintf(stderr, "Falha ao carregar fonte.\n");
        return 0;
    }
    fontepersonagem = al_load_font("Fonts/PixelArial.ttf", 7, 0);
    if (!fontepersonagem){
        al_destroy_display(janela);
        fprintf(stderr, "Falha ao carregar fonte.\n");
        return 0;
    }
    fontemusica = al_load_font("Fonts/Music.ttf", 96, 0);
    if (!fontemusica){
        al_destroy_display(janela);
        fprintf(stderr, "Falha ao carregar fonte.\n");
        return 0;
    }
    return 1;
}

int inicializar(){
    srand(time(NULL));
// Inicialização da biblioteca Allegro

    if (!al_init()){
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return 0;
    }

    if (!al_init_image_addon()){
        fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        return 0;
    }


// Inicialização do add-on para uso de fontes
     al_init_font_addon();
// Inicialização do add-on para uso de fontes True Type
    if (!al_init_ttf_addon()){
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return 0;
    }
 
    

//OBSERVACAO:
//NO UBUNTU USAR al_set_new_display_flags(ALLEGRO_FULLSCREEN);
//NO MACOS USAR al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
//INICIAR JANELA
//    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);

    if (!janela){
        fprintf(stderr, "Falha ao criar janela.\n");
        return 0;
    }
// Configurar o título da janela
    al_set_window_title(janela, "Citadel: A CIn game");

//INICIAR IMAGENS
    mainmap = al_load_bitmap("Maps/mainMapa.png");
    if (!mainmap){
        fprintf(stderr, "Falha ao carregar o arquivo de mainmap.\n");
        al_destroy_display(janela);
        return 0;
    }

    foremap = al_load_bitmap("Maps/ForegroundMap.png");
    if (!foremap){
        fprintf(stderr, "Falha ao carregar o arquivo de ForegroundMap.\n");
        al_destroy_display(janela);
        return 0;
    }

    map = al_load_bitmap("Maps/mapa.png");
    if (!map){
        fprintf(stderr, "Falha ao carregar o arquivo de map.\n");
        al_destroy_display(janela);
        return 0;
    }
    lockmap = al_lock_bitmap(map,al_get_bitmap_format(map), ALLEGRO_LOCK_READONLY);
    if(!lockmap){
        fprintf(stderr,"Erro no lock");
        return 1;
    }

    logocin = al_load_bitmap("Maps/cin.jpg");
   if (!logocin){
        fprintf(stderr, "Falha ao carregar o arquivo de LogoCin.\n");
        al_destroy_display(janela);
        return 0;
    }
//INICIAR EVENTOS
    fila_eventos = al_create_event_queue();
    if (!fila_eventos){
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return 0;
    }
    //INICIAR EVENTOS
    fila_eventos = al_create_event_queue();
    if (!fila_eventos){
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return 0;
    }
    if (!al_install_keyboard()){
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return 0;
    }
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    al_register_event_source(fila_eventos, al_get_keyboard_event_source());

// INICIAR FONTES
    if(!downloadFonts()) return 0;;
    
//INICIAR MUSICAS
    if (!al_install_audio()){
        fprintf(stderr, "Falha ao inicializar áudio.\n");
        return 0;
    }
 
    if (!al_init_acodec_addon()){
        fprintf(stderr, "Falha ao inicializar codecs de áudio.\n");
        return 0;
    }
 
    if (!al_reserve_samples(1)){
        fprintf(stderr, "Falha ao alocar canais de áudio.\n");
        return 0;
    }
    sample = al_load_sample("Songs/theme.wav");
    if (!sample){
        fprintf(stderr, "Falha ao carregar sample.\n");
        return 0;
    }
    sample2 = al_load_sample("Songs/theme2.wav");
    if (!sample2){
        fprintf(stderr, "Falha ao carregar sample 2.\n");
        return 0;
    }
    if(!downloadSprites()) return 0;


    return 1;
}




void destruir(){
    al_destroy_font(fontetitulo);
    al_destroy_font(fontesecundaria);
    al_destroy_bitmap(map);
    al_destroy_bitmap(logocin);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
    al_destroy_sample(sample);
    al_destroy_sample(sample2);
    int i;
    for(i=0;i<4;i++)
        al_destroy_bitmap(spriteEnemy[i]);
}

#endif
