
/* Inicializa o arranjo de posi��es da cobra, considerando que a sua dire��o inicial � 4 (RIGHT). */
void InicCobraPosicoes(COBRA *cobra, int nivel){
    int i, x_inic, y_inic;

    x_inic = X_INICIAL;
    y_inic = Y_INICIAL;

    /* Inicializa cobra mais � esquerda no nivel 2 */
    if(nivel == 2)
        x_inic -= 20;

    /* Posiciona a cabe�a na coordenada de in�cio. */
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

/* Faz a inicializa��o estrutural e gr�fica da cobra */
void InicializaCobra(COBRA *cobra, OPCOES opcoes, int nivel){

    /* Inicializa��es dos atributos da cobra: */
    cobra->direcao = DIRECAO_INICIAL;                       /* arbitr�ria */
    cobra->tamanho_atual = TAMANHO_INICIAL;                 /* arbitr�rio */
    cobra->velocidade_atual = opcoes.velocidade_inicial;    /* definido nas opc�es */
    InicCobraPosicoes(cobra, nivel);
    cobra->corpo = 'X';

    ImprimeCobra(*cobra);
}

/* Arrasta um �ndice � direita os elementos do arranjo de posi��es da cobra, a partir do [1]. */
void ArrastaPosCobra(COBRA *cobra){
    int i;
    for(i = cobra->tamanho_atual; i > 0; i--){
        cobra->pos[i].x = cobra->pos[i - 1].x;
        cobra->pos[i].y = cobra->pos[i - 1].y;
    }
}

/* Faz a movimenta��o da cobra, tanto estruturalmente quanto graficamente. */
void MoveCobra(COBRA *cobra){
    /* Apaga o �ltimo segmento do corpo da cobra */
    putchxy(cobra->pos[cobra->tamanho_atual - 1].x, cobra->pos[cobra->tamanho_atual - 1].y, ' ');

    /* Arrasta os elementos no arranjo, liberando o elemento [0] (cabe�a) para ser alterado */
    ArrastaPosCobra(cobra);

    /* Determina a nova posi��o da cabe�a de acordo com a dire��o da cobra */
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

/* Verifica se a cabe�a da cobra est� no mesmo lugar que algum item.
    Se est�, a cobra sofre os efeitos do item e um novo item � gerado.
    Se n�o, nada acontece. */
void PegaItemCobra(COBRA *cobra, JOGADOR *jogador, ITEM itens[MAX_ITEMS], ATRIBUTOS comida, ATRIBUTOS slower, ATRIBUTOS faster, ATRIBUTOS skip, char mapa[MAPA_LINHAS][MAPA_COLUNAS+1], TUNEL tuneis[MAX_TUNEIS], int *nivel, int *ganhounivel){
    int i = 0;

    while(i < MAX_ITEMS){
        if(MesmaPosicao(itens[i].pos, cobra->pos[0])){

            SomaPontuacao(jogador, itens[i], *cobra);

            cobra->tamanho_atual += itens[i].atributos.altera_tamanho;
            cobra->velocidade_atual += itens[i].atributos.altera_velocidade;

            /* Se o item for do tipo skip, passa de nivel: */
            if(itens[i].atributos.altera_nivel){
                *nivel++;
                *ganhounivel = 1;
            }

            /* Gera outro item: */
            CriaeImprimeItem(&itens[i], comida, slower, faster, skip, mapa, tuneis, *cobra, itens);
        }
        i++;
    }
}

/* Verifica se a cabe�a da cobra est� na posi��o de entrada e saida de um tunel e se as dire��es s�o as mesmas.
    Se sim, retorna o id do tunel correspondente; se n�o, retorna um caractere padr�o '0'. */
char VaiEntrarNoTunel(COBRA cobra, TUNEL tuneis[MAX_TUNEIS]){
    int i = 0;

    while(i < MAX_TUNEIS){
        if(MesmaPosicao(tuneis[i].pos_entrada_e_saida, cobra.pos[0]) && cobra.direcao == tuneis[i].direcao_entrada)
            return tuneis[i].id;   /* Se houver um t�nel na pr�xima posi��o, retorna seu id. */
        i++;
    }

    return '0';     /* Se n�o houver tunel na pr�xima posi��o, retorna '0'. */
}

/* Dado um char representando o id de um tunel, procura o tunel correspondente num arranjo de tuneis.
    Assume que o id passado como par�metro sempre ser� v�lido (ou seja, a fun��o sempre retornar� um tunel). */
TUNEL ProcuraTunel(TUNEL tuneis[MAX_TUNEIS], char id_procura){
    int i = 0;

    while(i < MAX_TUNEIS){
        if(tuneis[i].id == id_procura)
            return tuneis[i];
        i++;
    }
}

/* Quando a cabe�a da cobra estiver na posi��o de entrada e saida de um tunel e a sua dire��o for a mesma que a dire��o
    de entrada desse tunel, esta fun��o teleporta a cabe�a para a posi��o de entrada e saida e arrasta os outros segmentos */
void AtravessaCabeca(COBRA *cobra, TUNEL tuneis[MAX_TUNEIS], char vai_entrar){
    TUNEL tunel_entrada, tunel_saida;

    /* Instancia os tuneis nas vari�veis locais, de acordo com a id de entrada passada como par�metro (vai_entrar) */
    tunel_entrada = ProcuraTunel(tuneis, vai_entrar);
    tunel_saida = ProcuraTunel(tuneis, tunel_entrada.id_saida);

    /* Apaga o �ltimo segmento do corpo da cobra */
    putchxy(cobra->pos[cobra->tamanho_atual - 1].x, cobra->pos[cobra->tamanho_atual - 1].y, ' ');

    /* Arrasta os elementos no arranjo, liberando o elemento [0] (cabe�a) para ser alterado */
    ArrastaPosCobra(cobra);

    /* Teleporta a cabe�a para a posi��o de entrada e saida do tunel_saida, e muda a dire��o do movimento */
    cobra->pos[0] = tunel_saida.pos_entrada_e_saida;
    cobra->direcao = tunel_saida.direcao_saida;
    putchxy(cobra->pos[0].x, cobra->pos[0].y, cobra->corpo);

}

/* Faz a movimenta��o da cobra, tanto no movimento livre quanto na passagem pelos tuneis */
void Movimentacao(COBRA *cobra, TUNEL tuneis[MAX_TUNEIS]){
    char vai_entrar;

    /* Se a cobra estiver prestes a atravessar um tunel, vai_entrar recebe o id deste tunel */
    /* Se n�o, recebe o caractere '0' como resposta padr�o */
    vai_entrar = VaiEntrarNoTunel(*cobra, tuneis);

    if(vai_entrar == '0')
        /* Faz o movimento normal */
        MoveCobra(cobra);
    else{
        /* Passa a cabe�a da cobra pelo tunel e arrasta os outros segmentos */
        AtravessaCabeca(cobra, tuneis, vai_entrar);
    }
}
