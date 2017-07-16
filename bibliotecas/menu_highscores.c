/* HIGH SCORES */

/*
  MenuHighScores_ResetaArquivo:
  Em caso de erro na leitura do arquivo de scores, a funcao reseta o arquivo para os valores padrao */
int MenuHighScores_ResetaArquivo(){
  FILE *arquivo;
  int i;
  arquivo = fopen("config/scores.txt", "w");
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
  JOGADOR buffer;
  if(!(arquivo = fopen("config/scores.txt", "r"))){
    printf("Erro ao abrir o arquivo scores.txt\nO programa sera terminado.");
    PegaTecla_Animacao(1, 3);
    MenuHighScores_ResetaArquivo();
    return 1;
  }
  else{
    i = 0;
    while(!feof(arquivo) && i < MAX_HIGHSCORES)
      if(!(fscanf(arquivo, "%d%s", &buffer.pontuacao, &buffer.nome))){
        printf("Erro ao ler o arquivo scores.txt\nO programa sera terminado.");
        PegaTecla_Animacao(1, 3);
        fclose(arquivo);
        MenuHighScores_ResetaArquivo();
        return 1;
      }
      else{
        ranking[i] = buffer;
        i++;
      }
  }
  fclose(arquivo);
  return 0;
}

/* MenuHighScores_ImprimeRanking:
  x e y: posicao do primeiro elemento da lista */
int MenuHighScores_ImprimeRanking(int x, int y, JOGADOR ranking[]){
    char nome[MAX_NOME + 1];
    int i;
    gotoxy(x, y);
    for(i = 0; i < MAX_HIGHSCORES; i++){
      printf("\t%d\t%s", ranking[i].pontuacao, ranking[i].nome);
      gotoxy(x, y + (i+1)*2);
    }
    return 0;
}

/* Desenha os detalhes graficos do menu */
void MenuHighScores_Arte(){
  DesenhaCaixa(3, 1, 25, 25, '#', BLACK, WHITE); // Caixa dos HighScores
  DesenhaCaixa(40, 10, 71, 17, '#', BLACK, WHITE); // Caixa de instrucoes
}

/* menu_highscores:
  retorna 1 indicando sucesso, e 0 em caso de falha de execucao */
int MenuHighScores(JOGADOR ranking[]){
  clrscr();
  MenuHighScores_Arte();
  MenuHighScores_ImprimeRanking(5, 5, ranking);
  ImprimeCor_String(BLACK, WHITE, "HIGH SCORES", 9, 3);
  ImprimeCor_String(BLACK, WHITE, "Pressione qualquer", 45, 12);
  ImprimeCor_String(BLACK, WHITE, "tecla para voltar...", 45, 13);
  PegaTecla_Animacao(45, 15);
  return 0;
}
