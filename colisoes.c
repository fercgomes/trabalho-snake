/*
    COLISOES
    MODULO DE COLISOES
*/

/* PRECISA REESTRUTURAR */

/* MesmaPosicao:
    Retorna 1 se as coordenadas coincidirem, caso contrario retorna 0. */
int MesmaPosicao(COORDENADA c1, COORDENADA c2){
    if(c1.x == c2.x && c1.y == c2.y)
        return 1;
    else
        return 0;
}

/* FUNCOES DE DETECCAO DE COLISAO */

/* Verifica se uma dada COORDENADA coincide com as COORDENADAs dos obstaculos ('X') de um mapa.
    Retorna 1 caso haja colisao; 0 caso nao haja. */
int Colisao_Obstaculo(char mapa[MAPA_LINHAS][MAPA_COLUNAS+1], COORDENADA coord){
    int l, c;
    COORDENADA coord_mapa;
    for(l = 0; l < MAPA_LINHAS; l++)
        for(c = 0; c < MAPA_COLUNAS; c++){
            coord_mapa.x = c + MAPA_XOFFSET;    /* considera a variacao entre representacao grafica e interna */
            coord_mapa.y = l + MAPA_YOFFSET;
            if(mapa[l][c] == 'X' && MesmaPosicao(coord_mapa, coord))
                return 1;   /* Se encontrar uma coincidencia de coordenadas, retorna 1. */
        }
    return 0;               /* Se passar por todo o mapa e nao houver colisao, retorna 0. */
}

/* Verifica se uma dada COORDENADA coincide com as COORDENADAs dos elementos de um arranjo de tuneis.
    Retorna 1 caso haja colisao; 0 caso nao haja. */
int Colisao_Tunel(TUNEL tuneis[MAX_TUNEIS], COORDENADA coord){
    int i = 0;
    while(i < MAX_TUNEIS){
        if(MesmaPosicao(tuneis[i].pos, coord))
            return 1;   /* Se encontrar uma coincidencia de coordenadas, retorna 1. */
        i++;
    }
    return 0;           /* Se passar por todos os tuneis e nao houver colisao, retorna 0. */
}

/*  Verifica se uma dada COORDENADA coincide com as COORDENADAs dos elementos de um arranjo de itens.
    Caso a COORDENADA entrada seja de um item do arranjo, retorna 1 se coincidir somente com o proprio item, e
    2 se coincidir, alem do proprio, com outro elemento do arranjo. */
int Colisao_Item(ITEM itens[MAX_ITEMS], COORDENADA coord){
    int i = 0, quantos = 0;
    while(i < MAX_ITEMS){
        if(MesmaPosicao(itens[i].pos, coord))
            quantos++;   /* Se encontrar uma coincidencia de coordenadas, soma 1 a variavel de contagem. */
        i++;
    }
    return quantos;           /* Se passar por todos os itens e nao houver colisao, retorna 0.
                                Se houver, retorna o numero de colisoes. */
}

/* Verifica se uma dada COORDENADA coincide com as COORDENADAs dos segmentos da cobra. */
int Colisao_Cobra(COBRA cobra, COORDENADA coord){
    int i = 0;
    while(i < cobra.tamanho_atual){
        if(MesmaPosicao(cobra.pos[i], coord))
            return 1;   /* Se encontrar uma coincidencia de coordenadas, retorna 1. */
        i++;
    }
    return 0;           /* Se passar por todos os segmentos e nao houver colisao, retorna 0. */
}



/* FUNCOES DE TESTE PARA CADA ESTRUTURA
    Retornam 1 caso haja colisao; 0 caso nao haja. */

/* Testa se um item esta na mesma COORDENADA que um mapa, que os elementos de um arranjo de tuneis ou que uma cobra. */
int checacolisoes_item(ITEM item, char mapa[MAPA_LINHAS][MAPA_COLUNAS+1], TUNEL tuneis[MAX_TUNEIS], COBRA cobra, ITEM itens[MAX_ITEMS]){
    int mapa_colidiu, tunel_colidiu, cobra_colidiu, itens_colidiu;
    mapa_colidiu = Colisao_Obstaculo(mapa, item.pos);
    tunel_colidiu = Colisao_Tunel(tuneis, item.pos);
    cobra_colidiu = Colisao_Cobra(cobra, item.pos);
    itens_colidiu = Colisao_Item(itens, item.pos) - 1; /* O retorno da funcao a 1 se nenhum outro item tiver a mesma coordenada. */
    if(mapa_colidiu || tunel_colidiu || cobra_colidiu || itens_colidiu)
        return 1;   /* Houve alguma colisao. */
    else
        return 0;   /* Ha apenas o item nesta COORDENADA. */
}

/* Testa se a cabeca se choca com algum outro segmento do corpo da cobra: */
int Cobra_AutoColidiu(COBRA cobra){
  int i = 1;
  while(i < cobra.tamanho_atual){
      if(MesmaPosicao(cobra.pos[i], cobra.pos[0]))
          return 1;
      i++;
  }
  return 0;
}

/* Testa se a cabeca se choca com algum tunel, tentando entrar numa direcao errada: */
int Cobra_ColidiuTunel(COBRA cobra, TUNEL tuneis[MAX_TUNEIS]){
  int i = 0;
  while(i < MAX_TUNEIS){
      if(MesmaPosicao(tuneis[i].pos, cobra.pos[0]) && tuneis[i].direcao_entrada != cobra.direcao)
          return 1;   /* Se a cabeca se chocar com um tunel numa direcao errada, retorna 1. */
      i++;
  }
  return 0;
}

/*  Verifica se a posicao da cabeca da cobra se choca com algum segmento do seu proprio corpo,
    com algum tunel (na direcao errada) ou com algum obstaculo.
    Caso se choque, retorna 1; caso contrario, retorna 0. */
int checacolisoes_cobra(COBRA cobra, TUNEL tuneis[MAX_TUNEIS], char mapa[MAPA_LINHAS][MAPA_COLUNAS+1]){
    if(Cobra_AutoColidiu(cobra) || Cobra_ColidiuTunel(cobra, tuneis) || Colisao_Obstaculo(mapa, cobra.pos[0]))
      return 1;
    /* Se nenhuma situacao acima ocorrer, o movimento eh valido */
    return 0;

}
