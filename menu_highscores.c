/* HIGH SCORES */
/* mostra os 10 maiores scores registrados em ordem decrescente */

/*
  MenuHighScores_ResetaArquivo:
  Em caso de erro na leitura do arquivo de scores, a funcao reseta o arquivo para os valores padrao */
int MenuHighScores_ResetaArquivo(){
  FILE *arquivo;
  int i;
  arquivo = fopen("scores.txt", "w");
  for(i = 0; i < MAX_HIGHSCORES; i++)
    fprintf(arquivo, "%d %s\n", 0, "AAA");
  fclose(arquivo);
}

/*
    MenuHighScores_CarregaArquivo:
      Carrega o arquivo scores.txt para o arranjo ranking[]
      Retorna:
        1 -> Erro na execucao
        0 -> Sucesso */
int MenuHighScores_CarregaArquivo(JOGADOR ranking[]){
  FILE *arquivo;
  char nome[MAX_NOME + 1];
  int pontos, i;
  if(!(arquivo = fopen("scores.txt", "r"))){
    printf("Erro ao abrir o arquivo scores.txt\nPressione qualquer tecla para voltar");
    PegaTecla_Animacao(1, 3);
    MenuHighScores_ResetaArquivo();
    return 1;
  }
  else{
    for(i = 0; i < MAX_HIGHSCORES; i++)
      if(!(fscanf(arquivo, "%d%s", &pontos, nome))){
        printf("Erro ao ler o arquivo scores.txt\nPressione qualquer tecla para voltar");
        PegaTecla_Animacao(1, 3);
        MenuHighScores_ResetaArquivo();
        return 1;
      }
      else{
        ranking[i].pontuacao = pontos;
        strcpy(ranking[i].nome, nome);
      }
  }
  fclose(arquivo);
  return 0;
}

/* MenuHighScores_ImprimeRanking:
  x e y: posicao do primeiro elemento da lista */
int MenuHighScores_ImprimeRanking(int x, int y, JOGADOR ranking[]){
    char nome[MAX_NOME + 1];
    int pontos, i;
    gotoxy(x, y);
    for(i = 0; i < MAX_HIGHSCORES; i++){
      printf("\t%d\t%s", ranking[i].pontuacao, ranking[i].nome);
      gotoxy(x, y + i*2);
    }
    return 0;
}

/* menu_highscores:
  retorna 1 indicando sucesso, e 0 em caso de falha de execucao */
int MenuHighScores(JOGADOR ranking[]){
  clrscr();
  if(!MenuHighScores_CarregaArquivo(ranking)){
    MenuHighScores_ImprimeRanking(5, 5, ranking);
    ImprimeCor_String(BLACK, WHITE, "HIGH SCORES", 9, 3);
    ImprimeCor_String(BLACK, WHITE, "Pressione qualquer", 45, 12);
    ImprimeCor_String(BLACK, WHITE, "tecla para voltar...", 45, 13);
    PegaTecla_Animacao(45, 15);
  }
  else return 1; /* envia erro */
  return 0;
}
