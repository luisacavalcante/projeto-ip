
      // Funcao :void Game
      // COMUNICACAO DENTRO DO JOGO

void game(){
  int i;
  int num;//numero de jogadores
    
  // so vai ser usado uma vez: recebe o numero de jogadores no inicio do jogo
  recvMsgFromServer(num, WAIT_FOR_IT);
       
  //Sair do jogo == 0
  while(1){
  sendMsgToServer(jogador[id], sizeof(character));
  recvMsgFromServer(jogador, DONT_WAIT);

  for(i=0;i<num;i++){
    //printa na tela as atualizacoes
    }
  }
}

//sair do jogo: FIM DO JOGO
//              MORTE