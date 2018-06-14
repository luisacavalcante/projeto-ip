#ifndef GUARD_H
#define GUARD_H

#include "AllegroCore.h"
#include "CharacterLibrary.h"
#include "MainMenuLibrary.h"

void playGame(int i,int conectados){
jogador[i].id = i;
character person;
int zoom = 3;
    makeZoomedGame(zoom);
    int sair = 0, comando =0;
    double vel=zoom;
    //mostrar o tamanho do sprite do personagem
    if(i%2==0)
        declareFirstAtributes(i,15,20,LARGURA_MAPA/2 + 30+i*10, ALTURA_MAPA/2 + 30);
    else
        declareFirstAtributes(i,16,24,   20, 1360);
    
    int wait,cont;

    jogador[i].bomb.cont=800;
    jogador[i].bomb.isOn=0,jogador[i].bomb.set = 0;
    int px, py;
    //onde ele vai comecar(centralizado na tela zoomificada);
    int whereIsX=LARGURA_TELA/2/zoom;
    int whereIsY=ALTURA_TELA/2/zoom ;
    //esses dois de baixo sao as posicoes finais dos personagens, de (0,0) a (larguramapa,alturamapa)
    jogador[i].x = (LARGURA_TELA/2+jogador[i].posX)/zoom;
    jogador[i].y = (ALTURA_TELA/2+jogador[i].posY)/zoom;
    int j;
    sendMsgToServer(&jogador[i], sizeof(character));

    for(int w=0;w<conectados;w++){
                int resp = recvMsgFromServer(&person, DONT_WAIT);
                    if(resp != NO_MESSAGE){
                    if(jogador[i].id != person.id){
                        jogador[person.id] = person;
                        for (int j = 0; j < 4; j++) {
                            if (person.power[j].aindatem == 0) jogador[i].power[j].aindatem = 0;
                        }
                    } 
                }
            }
    while(!sair){
        cont=0;
        wait=0;
        //checar qual eh o comando
        comando = checkEvent();
        jogador[i].comando=comando;


        while(wait!=10+comando && comando>0&&comando<10 && !sair){
            //enquanto nao soltar a tecla ele continua andando para frente
            wait = checkEvent();

            if(wait>0&&wait <10){
                comando = wait;jogador[i].comando = wait;
                wait = checkEvent();
            }
            
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
                whereIs(map,&whereIsX, &whereIsY, comando, zoom, px, py, vel, i);


                
                
            }
            else{
                whichCommandPlayer(comando, 0, i);

                whereIs(map,&whereIsX, &whereIsY, 0, zoom, px, py, vel, i);
            }
                
            sendMsgToServer(&jogador[i], sizeof(character));

            for(int w=0;w<conectados;w++){
                int resp = recvMsgFromServer(&person, DONT_WAIT);
                    if(resp != NO_MESSAGE){
                    if(jogador[i].id != person.id){
                        jogador[person.id] = person;
                        for (int j = 0; j < 4; j++) {
                            if (person.power[j].aindatem == 0) jogador[i].power[j].aindatem = 0;
                        }
                    } 
                }
            }
            
            isThereAnotherPlayer(conectados,i,whereIsX,whereIsY);

            makeAnimation(i,comando,&sair,cont,2);
            
            if(jogador[i].bomb.isOn)
                drawBomb(i,whereIsX,whereIsY);

            if(jogador[i].immunity>0) jogador[i].immunity--;
            
            printPowerUps(i,whereIsX,whereIsY);

            didIGotPowerUp(i,whereIsX,whereIsY);

            didIGetHurt(i);

            didIGetBurn(i);
            

            if(jogador[i].bomb.cont<700)    jogador[i].bomb.cont+=4;
            if(jogador[i].bomb.cont==700) jogador[i].ihaveweapon=1,jogador[i].bomb.cont+=4,jogador[i].bomb.isOn=0;
            

            //MODIFIQUEI
            if(comando == 5 ){
                if (jogador[i].weapon == 0){
                    if(i%2==0)
                        drawSpriteGuardHit(i,whereIsX,whereIsY);

                }
                
                else if (jogador[i].weapon == 1 ){
                    if(i%2==0)
                        drawSpriteGuard(i,whereIsX,whereIsY);
                    else
                        drawSpriteEnemy(i,whereIsX,whereIsY);
                    jogador[i].bomb.cont=0;
                    jogador[i].bomb.x = jogador[i].x, jogador[i].bomb.y = jogador[i].y;
                    jogador[i].bomb.isOn=1;
                    wait=comando+10;
                }
                
                
            }

            else{
                if(i%2==0)drawSpriteGuard(i,whereIsX,whereIsY);
                
                else drawSpriteEnemy(i,whereIsX,whereIsY);
            }
            whereIs(foremap,&whereIsX, &whereIsY, 0, zoom, px, py, vel, i);
            
            writeName(i,whereIsX,whereIsY);
            printLifeBar(i,whereIsX - 4,whereIsY + 24);

            if(jogador[i].lifeBar==0) sair=1;
            
            al_flip_display();

        }
        //FIM DO WHILE
        if(comando == wait - 10|| comando == wait){

            if (comando == 6 && !jogador[i].bomb.isOn && jogador[i].ihaveweapon){
                if (jogador[i].weapon == 0) jogador[i].weapon = 1;
                else jogador[i].weapon = 0;
            }

            whereIs(map,&whereIsX, &whereIsY, 0, zoom, px, py, vel, i);
            


            for(int w=0;w<conectados;w++){
                int resp = recvMsgFromServer(&person, DONT_WAIT);
                    if(resp != NO_MESSAGE){
                    if(jogador[i].id != person.id){
                        jogador[person.id] = person;
                        for (int j = 0; j < 4; j++) {
                            if (person.power[j].aindatem == 0) jogador[i].power[j].aindatem = 0;
                        }
                    } 
                }
            }

            if(jogador[i].bomb.cont<700)  jogador[i].weapon=0,jogador[i].ihaveweapon=0,jogador[i].bomb.cont+=4;

            if(jogador[i].bomb.cont==700) jogador[i].ihaveweapon=1,jogador[i].bomb.cont+=4,jogador[i].bomb.isOn=0;

            if(jogador[i].immunity>0) jogador[i].immunity--;

            printThings(i,whereIsX,whereIsY,conectados);

            whereIs(foremap,&whereIsX, &whereIsY, 0, zoom, px, py, vel, i);

            didIGotPowerUp(i,whereIsX,whereIsY);

            didIGetHurt(i);

            didIGetBurn(i);

            if(jogador[i].lifeBar==0) sair=1;

            al_flip_display();
        }

    }
    while(jogador[i].lifeBar <= 0) {
	whereIs(foremap,&whereIsX, &whereIsY, 0, zoom, px, py, vel, i);
        al_draw_text(fontesecundaria, jogador[i].cor, LARGURA_TELA/2/3, 250/3, ALLEGRO_ALIGN_CENTRE, "Você Morreu...");
        drawDeadSprite(i,whereIsX,whereIsY);
	al_flip_display();
    }
}


#endif
