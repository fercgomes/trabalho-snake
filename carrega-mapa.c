/*
      Carrega os arquivos txt dos mapas para uma matriz de strings.
      Tamanho fixo da linha. 80 caracteres por linha. 24 caracteres por coluna.
*/

/* MAPAS - CONSTANTES */
#define MAPA_LINHAS 24
#define MAPA_COLUNAS 80

/*
    Os mapas representados na matriz de string tem indices de 0-23 (Y - 24 LINHAS) e
    0-80 (X - 81 LINHAS). Graficamente (na funcao putchxy) eles tem indices de 2 - 25 (Y)
    e 1 - 81 (X).
        X OFFSET -> discrepancia do eixo X
        Y OFFSET -> discrepancia do eixo Y    */
#define MAPA_XOFFSET 1
#define MAPA_YOFFSET 2

/*
    Mapa_Carrega:
    Carrega os arquivos txt dos mapas para as 3 matrizes de string do programa principal.
    map1.txt    ->    nivel_1
    map2.txt    ->    nivel_2
    map3.txt    ->    nivel_3   */
int Mapa_Carrega(char mapa[][MAPA_COLUNAS+1], char nome_arq[]){
  FILE *arquivo;
  int i;
  if(!(arquivo = fopen(nome_arq, "r"))){
    printf("Erro ao abrir o arquivo %s\n", nome_arq);
    return 1;
  }
  else{
    i = 0;
    while(!feof(arquivo) && i < MAPA_LINHAS){
      if(!(fgets(mapa[i], sizeof(mapa[i]), arquivo))){
        printf("Erro ao ler o arquivo %s\n", nome_arq);     /* TRATAMENTO DE ERRO ? */
        return 1;
      }
      else{
        i++;
      }
    }
  }
  fclose(arquivo);
  return 0;
}
/*
    Mapa_Converte:
    Converte uma matriz de strings de 1's e 0's para:
        1 -> 'X' (obstaculo)
        0 -> ' ' (espaco em branco)     */
void Mapa_Converte(char mapa[][MAPA_COLUNAS+1]){
  int i, j;
  for(i = 0; i < MAPA_COLUNAS+1; i++)
    for(j = 0; j < MAPA_LINHAS; j++)
      if(mapa[j][i] == '1') mapa[j][i] = 'X';
      else if(mapa[j][i] == '0') mapa[j][i] = ' ';
}

/*
    Mapa_Carrega_e_Converte:
    Carrega um mapa de um arquivo txt para uma matriz do programa principal,
    e já converte os '1's e '0's para 'X's e ' 's, respectivamente.
    Retorna 1 se falhar, 0 se obtiver êxito. */
int Mapa_Carrega_e_Converte(char mapa[][MAPA_COLUNAS+1], char nome_arq[]){
  if(Mapa_Carrega(mapa, nome_arq) == 1) /* erro no carregamento do mapa */
    return 1;
  Mapa_Converte(mapa);
  return 0;
}


/*
    Mapa_Imprime:
    Imprime na tela a matriz de strings que representa o mapa   */
void Mapa_Imprime(char mapa[][MAPA_COLUNAS+1]){
  int i, j;
  for(i = 0; i < MAPA_COLUNAS; i++)
    for(j = 0; j < MAPA_LINHAS; j++)
      putchxy(i + MAPA_XOFFSET, j + MAPA_YOFFSET, mapa[j][i]);
      gotoxy(1, 1);
}
