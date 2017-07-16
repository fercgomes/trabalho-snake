/* MesmaPosicao:
    Retorna 1 se as coordenadas coincidirem, caso contr�rio retorna 0. */
int MesmaPosicao(COORDENADA c1, COORDENADA c2){
    if(c1.x == c2.x && c1.y == c2.y)
        return 1;
    else
        return 0;
}

/* FUN��ES DE DETEC��O DE COLIS�O */

/* Verifica se uma dada COORDENADA coincide com as COORDENADAs dos obst�culos ('X') de um mapa.
    Retorna 1 caso haja colis�o; 0 caso n�o haja. */
int colidiu_mapa(char mapa[MAPA_LINHAS][MAPA_COLUNAS+1], COORDENADA coord){
    int l, c;
    COORDENADA coord_mapa;

    for(l = 0; l < MAPA_LINHAS; l++)
        for(c = 0; c < MAPA_COLUNAS; c++){
            coord_mapa.x = c + MAPA_XOFFSET;
            coord_mapa.y = l + MAPA_YOFFSET;
            if(mapa[l][c] == 'X' && MesmaPosicao(coord_mapa, coord))
                return 1;   /* Se encontrar uma coincid�ncia de coordenadas, retorna 1. */
        }

    return 0;               /* Se passar por todo o mapa e n�o houver colis�o, retorna 0. */
}

/* Verifica se uma dada COORDENADA coincide com as COORDENADAs dos elementos de um arranjo de tuneis.
    Retorna 1 caso haja colis�o; 0 caso n�o haja. */
int colidiu_tuneis(TUNEL tuneis[MAX_TUNEIS], COORDENADA coord){
    int i = 0;

    while(i < MAX_TUNEIS){
        if(MesmaPosicao(tuneis[i].pos, coord))
            return 1;   /* Se encontrar uma coincid�ncia de coordenadas, retorna 1. */
        i++;
    }

    return 0;           /* Se passar por todos os tuneis e n�o houver colis�o, retorna 0. */
}

/* Verifica se uma dada COORDENADA coincide com as COORDENADAs dos elementos de um arranjo de itens.
    Caso a COORDENADA entrada seja de um item do arranjo, retorna 1 se coincidir somente com o pr�prio item, e
    2 se coincidir, al�m do pr�prio, com outro elemento do arranjo. */
int colidiu_itens(ITEM itens[MAX_ITEMS], COORDENADA coord){
    int i = 0, quantos = 0;

    while(i < MAX_ITEMS){
        if(MesmaPosicao(itens[i].pos, coord))
            quantos++;   /* Se encontrar uma coincid�ncia de coordenadas, soma 1 � vari�vel de contagem. */
        i++;
    }

    return quantos;           /* Se passar por todos os itens e n�o houver colis�o, retorna 0.
                                    Se houver, retorna o numero de colis�es. */
}

/* Verifica se uma dada COORDENADA coincide com as COORDENADAs dos segmentos da cobra. */
int colidiu_cobra(COBRA cobra, COORDENADA coord){
    int i = 0;

    while(i < cobra.tamanho_atual){
        if(MesmaPosicao(cobra.pos[i], coord))
            return 1;   /* Se encontrar uma coincid�ncia de coordenadas, retorna 1. */
        i++;
    }

    return 0;           /* Se passar por todos os segmentos e n�o houver colis�o, retorna 0. */
}



/* FUN��ES DE TESTE PARA CADA ESTRUTURA
    Retornam 1 caso haja colis�o; 0 caso n�o haja. */

/* Testa se um item est� na mesma COORDENADA que um mapa, que os elementos de um arranjo de tuneis ou que uma cobra. */
int checacolisoes_item(ITEM item, char mapa[MAPA_LINHAS][MAPA_COLUNAS+1], TUNEL tuneis[MAX_TUNEIS], COBRA cobra, ITEM itens[MAX_ITEMS]){

    int mapa_colidiu, tunel_colidiu, cobra_colidiu, itens_colidiu;

    mapa_colidiu = colidiu_mapa(mapa, item.pos);
    tunel_colidiu = colidiu_tuneis(tuneis, item.pos);
    cobra_colidiu = colidiu_cobra(cobra, item.pos);
    itens_colidiu = colidiu_itens(itens, item.pos) - 1; /* O retorno da fun��o � 1 se nenhum outro item tiver a mesma coordenada. */

    if(mapa_colidiu || tunel_colidiu || cobra_colidiu || itens_colidiu)
        return 1;   /* Houve alguma colis�o. */
    else
        return 0;   /* H� apenas o item nesta COORDENADA. */
}

/* Verifica se a posi��o da cabe�a da cobra se choca com algum segmento do seu pr�prio corpo,
    com algum tunel (na dire��o errada) ou com algum obst�culo.
    Caso se choque, retorna 1; caso contr�rio, retorna 0. */
int checacolisoes_cobra(COBRA cobra, TUNEL tuneis[MAX_TUNEIS], char mapa[MAPA_LINHAS][MAPA_COLUNAS+1]){
    int i;

    /* Testa se a cabe�a se choca com algum outro segmento do corpo da cobra: */
    i = 1;
    while(i < cobra.tamanho_atual){
        if(MesmaPosicao(cobra.pos[i], cobra.pos[0]))
            return 1;
        i++;
    }

    /* Testa se a cabe�a se choca com algum tunel, tentando entrar numa dire��o errada: */
    i = 0;
    while(i < MAX_TUNEIS){
        if(MesmaPosicao(tuneis[i].pos, cobra.pos[0]) && tuneis[i].direcao_entrada != cobra.direcao)
            return 1;   /* Se a cabe�a se chocar com um tunel numa dire��o errada, retorna 1. */
        i++;
    }

    /* Testa se a cabe�a se choca com algum obst�culo do mapa: */
    if(colidiu_mapa(mapa, cobra.pos[0]))
        return 1;

    /* Se nenhuma situa��o acima ocorrer, o movimento � v�lido */
    return 0;

}
