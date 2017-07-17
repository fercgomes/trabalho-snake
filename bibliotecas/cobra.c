/*
    COBRA
    MODULO DE MOVIMENTACAO
*/

/* Inicializa o arranjo de posicoes da cobra, considerando que a sua direcao inicial eh 4 (RIGHT). */
void InicCobraPosicoes(COBRA *cobra, int nivel){
    int i, x_inic, y_inic;

    x_inic = X_INICIAL;
    y_inic = Y_INICIAL;

    /* Inicializa cobra mais a esquerda no nivel 2 */
    if(nivel == 2)
        x_inic -= 20;

    /* Posiciona a cabeca na coordenada de inicio. */
    cobra->pos[0].x = x_inic;
    cobra->pos[0].y = y_inic;

    /* Inicializa os outros segmentos da cobra */
    for(i = 1; i < cobra->tamanho_atual; i++){
        cobra->pos[i].x = x_inic - i;
        cobra->pos[i].y = y_inic;
    }
}

/* Imprime na tela os segmentos do corpo da cobra. */
void ImprimeCobra(COBRA cobra){
    int i;
    for(i = 0; i < cobra.tamanho_atual; i++)
        putchxy(cobra.pos[i].x, cobra.pos[i].y, cobra.corpo);
}

/* Faz a inicializacao estrutural e grafica da cobra */
void InicializaCobra(COBRA *cobra, OPCOES opcoes, int nivel){
    /* Inicializacoes dos atributos da cobra: */
    cobra->direcao = DIRECAO_INICIAL;                       /* arbitraria */
    cobra->tamanho_atual = TAMANHO_INICIAL;                 /* arbitrario */
    cobra->velocidade_atual = opcoes.velocidade_inicial;    /* definido nas opcoes */
    InicCobraPosicoes(cobra, nivel);
    cobra->corpo = 'X';
    ImprimeCobra(*cobra);
}

/* Arrasta um indice a direita os elementos do arranjo de posicoes da cobra, a partir do [1]. */
void ArrastaPosCobra(COBRA *cobra){
    int i;
    for(i = cobra->tamanho_atual; i > 0; i--){
        cobra->pos[i].x = cobra->pos[i - 1].x;
        cobra->pos[i].y = cobra->pos[i - 1].y;
    }
}

/* Faz a movimentacao da cobra, tanto estruturalmente quanto graficamente. */
void MoveCobra(COBRA *cobra){
    /* Apaga o ultimo segmento do corpo da cobra */
    putchxy(cobra->pos[cobra->tamanho_atual - 1].x, cobra->pos[cobra->tamanho_atual - 1].y, ' ');

    /* Arrasta os elementos no arranjo, liberando o elemento [0] (cabe�a) para ser alterado */
    ArrastaPosCobra(cobra);

    /* Determina a nova posicao da cabeca de acordo com a direcao da cobra */
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

/* Aplica os efetos de um item que foi pego pelo jogador */
void AplicaItem(ITEM item, COBRA *cobra, JOGADOR *jogador, int *nivel, int *PassaDeNivel){
  SomaPontuacao(jogador, item, *cobra);

  cobra->tamanho_atual += item.atributos.altera_tamanho;
  cobra->velocidade_atual += item.atributos.altera_velocidade;

  /* Se o item for do tipo skip, passa de nivel: */
  if(item.atributos.altera_nivel){
      *nivel++;
      *PassaDeNivel = 1;
  }
}

/* Verifica se a cabeca da cobra esta no mesmo lugar que algum item.
    Se esta, a cobra sofre os efeitos do item e um novo item eh gerado.
    Se nao, nada acontece. */
void PegaItemCobra(COBRA *cobra, JOGADOR *jogador, ITEM itens[MAX_ITEMS], ATRIBUTOS comida, ATRIBUTOS slower, ATRIBUTOS faster, ATRIBUTOS skip, char mapa[MAPA_LINHAS][MAPA_COLUNAS+1], TUNEL tuneis[MAX_TUNEIS], int *nivel, int *PassaDeNivel){
    int i = 0;
    while(i < MAX_ITEMS){
        if(MesmaPosicao(itens[i].pos, cobra->pos[0])){
            AplicaItem(itens[i], cobra, jogador, nivel, PassaDeNivel);                               /* Aplica efeitos do item pego */
            CriaeImprimeItem(&itens[i], comida, slower, faster, skip, mapa, tuneis, *cobra, itens); /* Gera outro item: */
        }
        i++;
    }
}

/* Verifica se a cabeca da cobra esta na posicao de entrada e saida de um tunel e se as direcoes sao as mesmas.
    Se sim, retorna o id do tunel correspondente; se nao, retorna um caractere padrao '0'. */
char VaiEntrarNoTunel(COBRA cobra, TUNEL tuneis[MAX_TUNEIS]){
    int i = 0;
    while(i < MAX_TUNEIS){
        if(MesmaPosicao(tuneis[i].pos_entrada_e_saida, cobra.pos[0]) && cobra.direcao == tuneis[i].direcao_entrada)
            return tuneis[i].id;   /* Se houver um t�nel na pr�xima posi��o, retorna seu id. */
        i++;
    }
    return '0';     /* Se nao houver tunel na proxima posicao, retorna '0'. */
}

/* Dado um char representando o id de um tunel, procura o tunel correspondente num arranjo de tuneis.
    Assume que o id passado como parametro sempre sera valido (ou seja, a funcao sempre retornara um tunel). */
TUNEL ProcuraTunel(TUNEL tuneis[MAX_TUNEIS], char id_procura){
    int i = 0;
    while(i < MAX_TUNEIS){
        if(tuneis[i].id == id_procura)
            return tuneis[i];
        i++;
    }
}

/* Quando a cabeca da cobra estiver na posicao de entrada e saida de um tunel e a sua direcao for a mesma que a direcao
    de entrada desse tunel, esta funcao teleporta a cabeca para a posicao de entrada e saida e arrasta os outros segmentos */
void AtravessaCabeca(COBRA *cobra, TUNEL tuneis[MAX_TUNEIS], char vai_entrar){
    TUNEL tunel_entrada, tunel_saida;

    /* Instancia os tuneis nas variaveis locais, de acordo com a id de entrada passada como parametro (vai_entrar) */
    tunel_entrada = ProcuraTunel(tuneis, vai_entrar);
    tunel_saida = ProcuraTunel(tuneis, tunel_entrada.id_saida);

    /* Apaga o ultimo segmento do corpo da cobra */
    putchxy(cobra->pos[cobra->tamanho_atual - 1].x, cobra->pos[cobra->tamanho_atual - 1].y, ' ');

    /* Arrasta os elementos no arranjo, liberando o elemento [0] (cabeca) para ser alterado */
    ArrastaPosCobra(cobra);

    /* Teleporta a cabeca para a posicao de entrada e saida do tunel_saida, e muda a direcao do movimento */
    cobra->pos[0] = tunel_saida.pos_entrada_e_saida;
    cobra->direcao = tunel_saida.direcao_saida;
    putchxy(cobra->pos[0].x, cobra->pos[0].y, cobra->corpo);

}

/* Faz a movimentacao da cobra, tanto no movimento livre quanto na passagem pelos tuneis */
void Movimentacao(COBRA *cobra, TUNEL tuneis[MAX_TUNEIS]){
    char vai_entrar;

    /* Se a cobra estiver prestes a atravessar um tunel, vai_entrar recebe o id deste tunel */
    /* Se nao, recebe o caractere '0' como resposta padrao */
    vai_entrar = VaiEntrarNoTunel(*cobra, tuneis);

    if(vai_entrar == '0')
      MoveCobra(cobra);                               /* Faz o movimento normal */
    else
      AtravessaCabeca(cobra, tuneis, vai_entrar);     /* Passa a cabeca da cobra pelo tunel e arrasta os outros segmentos */
}
