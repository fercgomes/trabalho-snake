/*
    Verificacao de termino de jogo
*/

/* Valores padrao de resultado de jogo */
#define JOGADOR_PERDEU 0
#define JOGADOR_GANHOU 1
#define JOGADOR_SAIU 2

#define MENSAGEM_TEMPOESPERA 100

/* mensagem de fim de jogo */
void MenuFim_Adeus(int *status){
  clrscr();
  ImprimeCor_String(BLACK, WHITE, "SAINDO DO JOGO. ATE UM OUTRO DIA :)", 23, 3);
  PegaTecla_Animacao(40, 5);
  *status = 0;
}

/* mensagem de pausa de jogo */
void MenuFim_JogadorPausou(int score){
  clrscr();
  DesenhaCaixa(10, 5, 70, 20, '#',  BLACK, WHITE);
  ImprimeCor_String(BLACK, WHITE, "SCORE:", 37, 8);
  ImprimeScore(BLACK, WHITE, score, 38, 9);
  ImprimeCor_String(BLACK, WHITE, "PRESSIONE <ENTER> PARA", 29, 12);
  ImprimeCor_String(BLACK, WHITE, "VOLTAR AO MENU...", 32, 14);
  Sleep(MENSAGEM_TEMPOESPERA);
  EsperaEnter_Animacao(68, 18);
}

/* mensagem de vitoria */
void MenuFim_JogadorGanhou(int score){
  clrscr();
  DesenhaCaixa(10, 5, 70, 20, '#',  BLACK, WHITE);
  ImprimeCor_String(BLACK, WHITE, "SCORE:", 37, 11);
  ImprimeScore(BLACK, WHITE, score, 38, 13);
  ImprimeCor_String(BLACK, WHITE, "PARABENS!", 36, 7);
  ImprimeCor_String(BLACK, WHITE, "VOCE VENCEU!", 34, 8);
  ImprimeCor_String(BLACK, WHITE, "PRESSIONE <ENTER> PARA CONTINUAR", 24, 16);
  Sleep(MENSAGEM_TEMPOESPERA);
  EsperaEnter_Animacao(68, 18);
}

/* mensagem de derrota do jogo */
void MenuFim_JogadorPerdeu(int score){
  clrscr();
  DesenhaCaixa(10, 5, 70, 20, '#',  BLACK, WHITE);
  ImprimeCor_String(BLACK, WHITE, "SCORE:", 37, 11);
  ImprimeScore(BLACK, WHITE, score, 38, 13);
  ImprimeCor_String(BLACK, WHITE, "AAAAH  :/", 36, 7);
  ImprimeCor_String(BLACK, WHITE, "VOCE  PERDEU!", 34, 8);
  ImprimeCor_String(BLACK, WHITE, "PRESSIONE ENTER PARA CONTINUAR", 25, 16);
  Sleep(MENSAGEM_TEMPOESPERA);
  EsperaEnter_Animacao(68, 18);
}

/* insere um jogador em uma posicao do ranking */
void InsereJogador(JOGADOR jogador, JOGADOR ranking[], int i){
  ranking[i].pontuacao = jogador.pontuacao;
  strcpy(ranking[i].nome, jogador.nome);
}

/*
    MenuFim_NovoHighScore_SalvaArquivo:
      Salva no arquivo scores.txt o novo arranjo do Ranking, com o novo score inserido */
int MenuFim_NovoHighScore_SalvaArquivo(JOGADOR ranking[]){
  FILE *arquivo;
  int i;
  if(!(arquivo = fopen("config/scores.txt", "w"))){
    printf("Erro ao abrir o arquivo scores.txt\nPressione qualquer tecla para voltar");
    PegaTecla_Animacao(1, 3);
    MenuHighScores_ResetaArquivo();
    return 1;
  }
  else{
    for(i = 0; i < MAX_HIGHSCORES; i++){
      if(!fprintf(arquivo, "%d %s\n", ranking[i].pontuacao, ranking[i].nome)){
        printf("Erro ao escrever no arquivo scores.txt\nPressione qualquer tecla para voltar");
        PegaTecla_Animacao(1, 3);
        MenuHighScores_ResetaArquivo();
        return 1;
      }
    }
  }
  fclose(arquivo);
  return 0;
}

/*
    MenuFim_SetaNovoHighScore:
      Coloca um novo score no arranjo ranking. */
void MenuFim_SetaNovoHighScore(JOGADOR jogador, JOGADOR ranking[], int indice){
  int i;
  for(i = MAX_HIGHSCORES - 1; i > indice; i--){
    ranking[i].pontuacao = ranking[i - 1].pontuacao;
    strcpy(ranking[i].nome, ranking[i - 1].nome);
  }
  InsereJogador(jogador, ranking, indice);
}

/*
    MenuFim_VerificaScore:
      Verifica se um score deve entrar para o ranking.
      Retorna:
        ??? */
int MenuFim_VerificaScore(JOGADOR jogador, JOGADOR ranking[]){
  int i = 0, achou = 0;

  while(jogador.pontuacao < ranking[i].pontuacao && i < MAX_HIGHSCORES)
    i++;
  if(i == MAX_HIGHSCORES) /* chegou no ultimo elemento */
    return -1; /* nao tem lugar no ranking */
  else return i; /* pertence a alguma posicao da lista */
}

/*  MenuFim_VerificaJogo:
    Gerencia o final do jogo, quando o jogador apertou esc, ganhou ou perdeu.
    Retorna:
        1 indicando retorno para o Menu Principal.
        0 indicando fim do programa.   */
int MenuFim_VerificaJogo(int estado, JOGADOR *jogador, JOGADOR ranking[]){
  switch(estado){
    case JOGADOR_GANHOU:       /* Usuario ganhou o jogo */
      MenuFim_JogadorGanhou(jogador->pontuacao);
      break;
    case JOGADOR_PERDEU:       /* Usuario perdeu o jogo */
      MenuFim_JogadorPerdeu(jogador->pontuacao);
      break;
    case JOGADOR_SAIU:
      MenuFim_JogadorPausou(jogador->pontuacao);
      break;
  }

  if(MenuFim_VerificaScore(*jogador, ranking) != -1 && jogador->pontuacao != 0){
    MenuFim_CriaJogador(jogador);
    MenuFim_SetaNovoHighScore(*jogador, ranking, MenuFim_VerificaScore(*jogador, ranking));
    if(!MenuFim_NovoHighScore_SalvaArquivo(ranking))
      return 0; /* sucesso com arquivo */
    else
      return 1; /* erro ao salvar no arquivo */
  }
  else return 0;
}
