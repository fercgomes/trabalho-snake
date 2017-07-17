/* DEBUGGING TOOLS */
void debug_mostrajogador(JOGADOR jogador){
  printf("jogador:\nNOME: %s\nPONTUACAO: %d\n", jogador.nome, jogador.pontuacao);
  printf("\n--------------------------------------------------------------------------------\n");
}

void debug_mostraopcoes(OPCOES opcoes){
  printf("opcoes.velocidade_inicial: %d\n", opcoes.velocidade_inicial);
  printf("opcoes.tamanho_maximo: %d\n", opcoes.tamanho_maximo);
  printf("opcoes.itens_maximos: %d\n", opcoes.itens_maximos);
  printf("\n--------------------------------------------------------------------------------\n");
}

void debug_ranking(JOGADOR ranking[]){
  int i;
  printf("ranking[MAX_HIGHSCORES]:\n");
  for(i = 0; i < MAX_HIGHSCORES; i++){
    printf("%s %d\n", ranking[i].nome, ranking[i].pontuacao);
  }
  printf("\n--------------------------------------------------------------------------------\n");
}

/* ARQUIVOS */

void debug_file_opcoes(){
  FILE *arq;
  OPCOES buffer;
  arq = fopen("opcoes.bin", "rb");
  fread(&buffer, sizeof(OPCOES), 1, arq);
  printf("opcoes.bin:\n");
  printf("velocidade_inicial: %d\n", buffer.velocidade_inicial);
  printf("tamanho_maximo: %d\n", buffer.tamanho_maximo);
  printf("itens_maximos: %d\n", buffer.itens_maximos);
  printf("\n--------------------------------------------------------------------------------\n");
  fclose(arq);
}

void debug_file_scores(){
  FILE *arq;
  JOGADOR buffer[MAX_HIGHSCORES];
  int i;
  printf("scores.txt:\n");
  arq = fopen("scores.txt", "r");
  i = 0;
  for(i = 0; i < MAX_HIGHSCORES; i++)
      fscanf(arq, "%d%s", &buffer[i].pontuacao, buffer[i].nome);
  fclose(arq);
  for(i = 0; i < MAX_HIGHSCORES; i++)
    printf("%d %s\n", buffer[i].pontuacao, buffer[i].nome);
  printf("\n--------------------------------------------------------------------------------\n");
}

void debug(OPCOES opcoes, JOGADOR jogador, JOGADOR ranking[]){
  clrscr();
  printf("VARIAVEIS DO JOGO:\n\n");
  debug_mostrajogador(jogador);
  debug_mostraopcoes(opcoes);
  debug_ranking(ranking);

  printf("ARQUIVOS:\n\n");
  debug_file_opcoes();
  debug_file_scores();

  getch();
}

/* Debugger do arranjo de itens: */
void debug_itens(ITEM itens[MAX_ITEMS]){
  int i;
  gotoxy(1, 10);
  for(i = 0; i < MAX_ITEMS; i++){
    printf("(%d, %d) \t", itens[i].pos.x, itens[i].pos.y);
    printf("%d %d %d %d %c\n", itens[i].atributos.altera_basepontos, itens[i].atributos.altera_velocidade, itens[i].atributos.altera_nivel, itens[i].atributos.altera_tamanho, itens[i].atributos.corpo);
  }
}