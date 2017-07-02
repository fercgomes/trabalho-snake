/* HIGH SCORES */
/* mostra os 10 maiores scores registrados em ordem decrescente */

/*
  reseta_scores_arquivo:
  Em caso de erro na leitura do arquivo de scores, a funcao reseta o arquivo para os valores padrao */
int reseta_scores_arquivo(){
  FILE *arquivo;
  int i;
  arquivo = fopen("scores.txt", "w");
  for(i = 0; i < MAX_HIGHSCORES; i++)
    fprintf(arquivo, "%d %s\n", 0, "AAA");
  fclose(arquivo);
}

/* imprime_score:
  x e y: posicao do primeiro elemento da lista */
int imprime_score(int x, int y){
    FILE *arquivo;
    char nome[MAX_NOME + 1];
    int pontos, i;
    if(!(arquivo = fopen("scores.txt", "r"))){
      printf("Erro ao abrir o arquivo scores.txt\nPressione qualquer tecla para voltar");
      espera_tecla(1, 3);
      reseta_scores_arquivo();
      return 1;
    }
    else{
      gotoxy(x, y);
      for(i = 0; i < MAX_HIGHSCORES; i++)
        if(!(fscanf(arquivo, "%d%s", &pontos, nome))){
          printf("Erro ao ler o arquivo scores.txt\nPressione qualquer tecla para voltar");
          espera_tecla(1, 3);
          reseta_scores_arquivo();
          return 1;
        }
        else{
          printf("\t%d\t%s", pontos, nome);
          gotoxy(x, y + i*2);
        }
    }
    fclose(arquivo);
    return 0;
}

/* menu_highscores:
  retorna 1 indicando sucesso, e 0 em caso de falha de execucao */
int menu_highscores(){
  clrscr();
  if(!imprime_score(5, 5)){ /* abriu o arquivo com sucesso */
    escreve_cor(BLACK, WHITE, "HIGH SCORES", 9, 3);
    escreve_cor(BLACK, WHITE, "Pressione qualquer", 45, 12);
    escreve_cor(BLACK, WHITE, "tecla para voltar...", 45, 13);
    espera_tecla(45, 15);
  }
  else return 1;
  return 0;
}
