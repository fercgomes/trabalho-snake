/* SNAKE - ENGINE */

/* Movimento */

#define COBRA_CABECA

/* arrasta os elementos do arranjo 'pos' de COBRA uma posicao para a direita */
void Cobra_ArrastaPosicao(COBRA *cobra){
    int i;
    for(i = cobra->tamanho_atual; i > 0; i--){
        cobra->pos[i].x = cobra->pos[i - 1].x;
        cobra->pos[i].y = cobra->pos[i - 1].y;
    }
}

/*  Verifica se a cobra colidiu com o mapa
    Retorna 1 se houve colisão da cobra com o mapa */
int Cobra_ColideMapa(char mapa[][MAPA_COLUNAS], COBRA cobra){
  int X_Cabeca = cobra.pos[COBRA_CABECA].x - MAPA_XOFFSET,
      Y_Cabeca = cobra.pos[COBRA_CABECA].y - MAPA_YOFFSET;
  if(mapa[X_Cabeca][Y_Cabeca] == 'X')
    return 1;
  else
    return 0;
}

int Cobra_ColetaItem(ITEM itens[MAX_ITEMS], COBRA *cobra, JOGADOR *jogador){
  int i = 0,
      coletou = 0;
  while(i < MAX_ITEMS && coletou == 0){
    if(cobra->pos[COBRA_CABECA].x == itens[i].pos.x && cobra->pos[COBRA_CABECA].y == itens[i].pos.y)
      coletou = 1;
      // aplica atributos
  }
}


/* inicializa a cobra em uma posicao x e y */
void Cobra_InicializaPosicao(COBRA *cobra, int x, int y){
    int i;
    /* inicializa primeiro segmento com os valores recebidos na funcao */
    cobra->pos[0].x = x;
    cobra->pos[0].y = y;

    /* inicializa os outros segmentos ativos de acordo com a direcao da cobra */
    switch(cobra->direcao){
        case UP:
            for(i = 1; i < cobra->tamanho_atual; i++){
                cobra->pos[i].x = x;
                cobra->pos[i].y = cobra->pos[0].y + i;
            }
            break;
        case DOWN:
            for(i = 1; i < cobra->tamanho_atual; i++){
                cobra->pos[i].x = x;
                cobra->pos[i].y = cobra->pos[0].y - i;
            }
            break;
        case LEFT:
            for(i = 1; i < cobra->tamanho_atual; i++){
                cobra->pos[i].x = cobra->pos[0].x + i;
                cobra->pos[i].y = y;
            }
            break;
        case RIGHT:
            for(i = 1; i < cobra->tamanho_atual; i++){
                cobra->pos[i].x = cobra->pos[0].x - i;
                cobra->pos[i].y = y;
            }
            break;
    }

}

/* Imprime os segmentos vigentes da cobra */
void Cobra_ImprimeSegmentos(COBRA cobra){
      /* inicializacao grafica */
      for(i = 0; i < cobra.tamanho_atual; i++)
          putchxy(cobra.pos[i].x, cobra.pos[i].y, cobra->corpo);
}

/*  */
void moveCobra(COBRA *cobra){
    /* apaga a ultima posicao ativa da cobra */
    putchxy(cobra->pos[cobra->tamanho_atual - 1].x, cobra->pos[cobra->tamanho_atual - 1].y, ' ');
    /* arrasta os elementos para a direita, liberando a primeira posi��o para modifica��o */
    arrastaPosicaoCobra(cobra);

    switch(cobra->direcao){
        case UP:
            (cobra->pos[0].y)--;
            putchxy(cobra->pos[0].x, cobra->pos[0].y, cobra->corpo);
            break;
        case DOWN:
            (cobra->pos[0].y)++;
            putchxy(cobra->pos[0].x, cobra->pos[0].y, cobra->corpo);
            break;
        case LEFT:
            (cobra->pos[0].x)--;
            putchxy(cobra->pos[0].x, cobra->pos[0].y, cobra->corpo);
            break;
        case RIGHT:
            (cobra->pos[0].x)++;
            putchxy(cobra->pos[0].x, cobra->pos[0].y, cobra->corpo);
            break;
    }
}
