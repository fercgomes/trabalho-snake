/*
      Verificacao apos termino de jogo.
      Jogador pode ter apertado ESC, morrido ou ganhado, em todos os casos
      eh verificado se a pontuacao registrada deve entrar nos High Scores.

      Nome do jogador eh inserido no inicio de jogo. Pontuacao comeca zerada.

      Variave sinalizadora:
        cobra_vida (main):
      (0) EM JOGO

      (1) ESC - verifica score e volta pro menu
      (2) GANHOU - mostra mensagem, verifica score e verifica se volta pro menu ou termina
      (3) PERDEU - mostra mensagem, veriica score e verifica se volta pro menu ou termina

*/

#define JOGADOR_PERDEU 0
#define JOGADOR_GANHOU 1
#define JOGADOR_SAIU 2

void MenuFim_JogadorGanhou(){
  clrscr();
  printf("Voce ganhou!\nPressione qualquer tecla para continuar...");
  PegaTecla_Animacao(1, 3);
}

void MenuFim_JogadorPerdeu(){
  clrscr();
  printf("Voce perdeu!\nPressione qualquer tecla para continuar...");
  PegaTecla_Animacao(1, 3);
}

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
  if(!(arquivo = fopen("scores.txt", "w"))){
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
      MenuFim_JogadorGanhou();
      break;
    case JOGADOR_PERDEU:       /* Usuario perdeu o jogo */
      MenuFim_JogadorPerdeu();
      break;
    default:
      break;
  }

  if(MenuFim_VerificaScore(*jogador, ranking) != -1){
    MenuFim_CriaJogador(jogador);
    MenuFim_SetaNovoHighScore(*jogador, ranking, MenuFim_VerificaScore(*jogador, ranking));
    MenuFim_NovoHighScore_SalvaArquivo(ranking);
  }
}
