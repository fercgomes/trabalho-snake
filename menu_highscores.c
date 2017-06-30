/* HIGH SCORES */
/* mostra os 10 maiores scores registrados em ordem decrescente */

/* imprime_score:
  x e y: posicao do primeiro elemento da lista */
int imprime_score(int x, int y){
    FILE *arquivo;
    char nome[MAX_NOME + 1];
    int pontos, i;
    if(!(arquivo = fopen("scores.txt", "r"))){
      printf("Erro ao abrir o arquivo scores.txt\nPressione qualquer tecla para voltar");
      getch();
      return 0;
    }
    else{
      gotoxy(x, y);
      for(i = 0; i < MAX_HIGHSCORES; i++)
        if(!(fscanf(arquivo, "%d%s", &pontos, nome))){
          printf("Erro ao ler o arquivo scores.txt\nPressione qualquer tecla para voltar");
          getch();
          return 0;
        }
        else{
          printf("\t%d\t%s", pontos, nome);
          gotoxy(x, y + i*2);
        }
    }
    fclose(arquivo);
    return 1;
}

/* menu_highscores:
  retorna 1 indicando sucesso, e 0 em caso de falha de execucao */
int menu_highscores(){
  clrscr();
  if(imprime_score(5, 5)){ /* abriu o arquivo com sucesso */
    escreve_cor(BLACK, WHITE, "HIGH SCORES", 9, 3);
    escreve_cor(BLACK, WHITE, "Pressione qualquer", 45, 12);
    escreve_cor(BLACK, WHITE, "tecla para voltar...", 45, 13);
    espera_tecla(45, 15);
  }
  else return 0;
  return 1;
}
