/* MesmaPosicao:
    Retorna 1 se as coordenadas coincidirem, caso contrário retorna 0. */
int MesmaPosicao(COORDENADA c1, COORDENADA c2){
    if(c1.x == c2.x && c1.y == c2.y)
        return 1;
    else
        return 0;
}

/* FUNÇÕES DE DETECÇÃO DE COLISÃO */

/* Verifica se uma dada COORDENADA coincide com as COORDENADAs dos obstáculos ('X') de um mapa.
    Retorna 1 caso haja colisão; 0 caso não haja. */
int colidiu_mapa(char mapa[MAPA_LINHAS][MAPA_COLUNAS+1], COORDENADA coord){
    int l, c;
    COORDENADA coord_mapa;

    for(l = 0; l < MAPA_LINHAS; l++)
        for(c = 0; c < MAPA_COLUNAS; c++){
            coord_mapa.x = c + MAPA_XOFFSET;
            coord_mapa.y = l + MAPA_YOFFSET;
            if(mapa[l][c] == 'X' && MesmaPosicao(coord_mapa, coord))
                return 1;   /* Se encontrar uma coincidência de coordenadas, retorna 1. */
        }

    return 0;               /* Se passar por todo o mapa e não houver colisão, retorna 0. */
}

/* Verifica se uma dada COORDENADA coincide com as COORDENADAs dos elementos de um arranjo de tuneis.
    Retorna 1 caso haja colisão; 0 caso não haja. */
int colidiu_tuneis(TUNEL tuneis[MAX_TUNEIS], COORDENADA coord){
    int i = 0;

    while(i < MAX_TUNEIS){
        if(MesmaPosicao(tuneis[i].pos, coord))
            return 1;   /* Se encontrar uma coincidência de coordenadas, retorna 1. */
        i++;
    }

    return 0;           /* Se passar por todos os tuneis e não houver colisão, retorna 0. */
}

/* Verifica se uma dada COORDENADA coincide com as COORDENADAs dos elementos de um arranjo de itens.
    Caso a COORDENADA entrada seja de um item do arranjo, retorna 1 se coincidir somente com o próprio item, e
    2 se coincidir, além do próprio, com outro elemento do arranjo. */
int colidiu_itens(ITEM itens[MAX_ITEMS], COORDENADA coord){
    int i = 0, quantos = 0;

    while(i < MAX_ITEMS){
        if(MesmaPosicao(itens[i].pos, coord))
            quantos++;   /* Se encontrar uma coincidência de coordenadas, soma 1 à variável de contagem. */
        i++;
    }

    return quantos;           /* Se passar por todos os itens e não houver colisão, retorna 0.
                                    Se houver, retorna o numero de colisões. */
}

/* Verifica se uma dada COORDENADA coincide com as COORDENADAs dos segmentos da cobra. */
int colidiu_cobra(COBRA cobra, COORDENADA coord){
    int i = 0;

    while(i < cobra.tamanho_atual){
        if(MesmaPosicao(cobra.pos[i], coord))
            return 1;   /* Se encontrar uma coincidência de coordenadas, retorna 1. */
        i++;
    }

    return 0;           /* Se passar por todos os segmentos e não houver colisão, retorna 0. */
}



/* FUNÇÕES DE TESTE PARA CADA ESTRUTURA
    Retornam 1 caso haja colisão; 0 caso não haja. */

/* Testa se um item está na mesma COORDENADA que um mapa, que os elementos de um arranjo de tuneis ou que uma cobra. */
int checacolisoes_item(ITEM item, char mapa[MAPA_LINHAS][MAPA_COLUNAS+1], TUNEL tuneis[MAX_TUNEIS], COBRA cobra, ITEM itens[MAX_ITEMS]){

    int mapa_colidiu, tunel_colidiu, cobra_colidiu, itens_colidiu;

    mapa_colidiu = colidiu_mapa(mapa, item.pos);
    tunel_colidiu = colidiu_tuneis(tuneis, item.pos);
    cobra_colidiu = colidiu_cobra(cobra, item.pos);
    itens_colidiu = colidiu_itens(itens, item.pos) - 1; /* O retorno da função é 1 se nenhum outro item tiver a mesma coordenada. */

    if(mapa_colidiu || tunel_colidiu || cobra_colidiu || itens_colidiu)
        return 1;   /* Houve alguma colisão. */
    else
        return 0;   /* Há apenas o item nesta COORDENADA. */
}

/* Verifica se a posição da cabeça da cobra se choca com algum segmento do seu próprio corpo,
    com algum tunel (na direção errada) ou com algum obstáculo.
    Caso se choque, retorna 1; caso contrário, retorna 0. */
int checacolisoes_cobra(COBRA cobra, TUNEL tuneis[MAX_TUNEIS], char mapa[MAPA_LINHAS][MAPA_COLUNAS+1]){
    int i;

    /* Testa se a cabeça se choca com algum outro segmento do corpo da cobra: */
    i = 1;
    while(i < cobra.tamanho_atual){
        if(MesmaPosicao(cobra.pos[i], cobra.pos[0]))
            return 1;
        i++;
    }

    /* Testa se a cabeça se choca com algum tunel, tentando entrar numa direção errada: */
    i = 0;
    while(i < MAX_TUNEIS){
        if(MesmaPosicao(tuneis[i].pos, cobra.pos[0]) && tuneis[i].direcao_entrada != cobra.direcao)
            return 1;   /* Se a cabeça se chocar com um tunel numa direção errada, retorna 1. */
        i++;
    }

    /* Testa se a cabeça se choca com algum obstáculo do mapa: */
    if(colidiu_mapa(mapa, cobra.pos[0]))
        return 1;

    /* Se nenhuma situação acima ocorrer, o movimento é válido */
    return 0;

}
