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
      if(fprintf(arquivo, "%d %s", ranking[i].pontuacao, ranking[i].nome)){
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
  for(i = MAX_HIGHSCORES - 1; i > indice; i--)
    ranking[i] = ranking[i - 1];
  ranking[indice] = jogador;
}

/*
    MenuFim_VerificaScore:
      Verficia se um score deve entrar para o ranking.
      Retorna:
        ??? */
int MenuFim_VerificaScore(JOGADOR jogador, JOGADOR ranking[]){
  int i, achou = 0;
  while(jogador.pontuacao < ranking[i].pontuacao && i < MAX_HIGHSCORES){
    if(jogador.pontuacao < ranking[i].pontuacao)
      i++;
    else achou = 1;
  }
  if(achou)
    return i;
  else
    return -1;
}

/*  MenuFim_VerificaJogo:
    Gerencia o final do jogo, quando o jogador apertou esc, ganhou ou perdeu.
    Retorna:
        1 indicando retorno para o Menu Principal.
        0 indicando fim do programa.   */
int MenuFim_VerificaJogo(int estado, JOGADOR *jogador, JOGADOR ranking[]){
  switch(estado){
    case 1:       /* Usuario apertou ESC */
      if(MenuFim_VerificaScore(*jogador, ranking) != -1){
        MenuFim_CriaJogador(jogador);
        MenuFim_SetaNovoHighScore(*jogador, ranking, MenuFim_VerificaScore(*jogador, ranking));
      }
      break;
    case 2:       /* Usuario ganhou o jogo */

      break;
    case 3:       /* Usuario perdeu o jogo */

      break;
  }
}
