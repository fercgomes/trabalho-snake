/*
      Carrega os arquivos txt dos mapas para uma matriz de strings.
      Tamanho fixo da linha. 80 caracteres por linha. 24 caracteres por coluna.
*/

/*
    carrega_mapa:
    Carrega os arquivos txt dos mapas para as 3 matrizes de string do programa principal.
    map1.txt    ->    nivel_1
    map2.txt    ->    nivel_2
    map3.txt    ->    nivel_3   */
int carrega_mapa(char mapa1[][MAPA_COLUNAS]){
  FILE *arquivo;
  int i, j;
  /* map1.txt */
  if(!(arquivo = fopen("map1.txt", "r"))){
    printf("Erro ao abrir map1.txt\n");
    return 1;
  }
  else{
    for(j = 0; j < MAPA_COLUNAS; j++)
      for(i = 0; i < MAPA_LINHAS; i++)
        mapa1[i][j] = getc(arquivo);    /* VERIFICACAO DE SUCESSO ? */
  }
  fclose(arquivo);
  return 0;
}

void converte_mapa(char mapa[][MAPA_COLUNAS]){
  int i, j;
  for(i = 0; i < MAPA_COLUNAS; i++)
    for(j = 0; j < MAPA_LINHAS; j++)
      if(mapa[j][i] == '1') mapa[j][i] = 'X';
      else if(mapa[j][i] == '0') mapa[j][i] = ' ';
}

/* DEBUG */
void imprime_mapa(char mapa[MAPA_LINHAS][MAPA_COLUNAS]){
  int i, j;
  for(i = 0; i < MAPA_COLUNAS; i++)
    for(j = 0; j < MAPA_LINHAS; j++)
      putchxy(i, j, mapa[j][i]);
}
