/* calculaPontos:  */
int calculaPontos(int base, int velocidade, int tamanho){
  return (base * tamanho) / (5 * velocidade);
}

/* gera um numero aleatorio */
int numeroAleatorio(int limite){
    int controle;
    srand(time(NULL));
    controle = rand();
    while(controle > limite)
        controle = rand();
    return controle;
}

void zeraItems(ITEM *item){
    int i;
    for(i = 0; i < MAX_ITEMS; i++){
        item[i].pos.x = 0;
        item[i].pos.y = 0;
    }
}

/* ************************* */

/* produz a taxa de atualizacao de tela de acordo com a velocidade informada (1~10 movimentos por segundo) */
void taxa_atualizacao(int velocidade){
    Sleep(1000/velocidade);
}

/* zera um arranjo */
void zeraPosCobra(COBRA *c){
    int i;
    for(i = 0; i < MAX_SEGMENTOS; i++){
        c->pos[i].x = 0;
        c->pos[i].y = 0;
    }
}

/* arrasta os elementos do arranjo 'pos' de COBRA uma posicao para a direita */
void arrastaPosicaoCobra(COBRA *c){
    int i;
    for(i = c->tamanho_atual; i > 0; i--){
        c->pos[i].x = c->pos[i - 1].x;
        c->pos[i].y = c->pos[i - 1].y;
    }
}

/* pegaTecla:
    Retorna:
      1 -> uma tecla de controle foi apertada e o jogo segue
      0 -> ESC foi apertada */
int pegaTecla(COBRA *cobra){
    char tecla;
        if(kbhit()){
            tecla = getch();
            switch(tecla){
                case ASCII_UP:
                  if(cobra->direcao != DOWN)
                      cobra->direcao = UP;
                  break;
                case ASCII_DOWN:
                  if(cobra->direcao != UP)
                      cobra->direcao = DOWN;
                  break;
                case ASCII_LEFT:
                  if(cobra->direcao != RIGHT)
                        cobra->direcao = LEFT;
                  break;
                case ASCII_RIGHT:
                  if(cobra->direcao != LEFT)
                      cobra->direcao = RIGHT;
                  break;
                case ASCII_ESC: /* usuario apertou ESC, sai do jogo */
                  return 1;
            }
        }
    return 0;
}

/* detecta colisao com a prppria cobra */
int autoColisao(COBRA cobra){
      int i;
      for(i = 1; i < cobra.tamanho_atual; i++)
            if(cobra.pos[0].x == cobra.pos[i].x && cobra.pos[0].y == cobra.pos[i].y)
                  return 1;
      return 0;
}

/* inicializa a cobra em uma posicao x e y */
void inicializaCobra(COBRA *cobra, int x, int y){
    int i;
    /* inicializa primeiro segmento com os valores recebidos na fun�ao */
    cobra->pos[0].x = x;
    cobra->pos[0].y = y;

    /* inicializa os outros segmentos ativos de acordo com a dire�ao da cobra */
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

    /* inicializacao grafica */
    for(i = 0; i < cobra->tamanho_atual; i++)
        putchxy(cobra->pos[i].x, cobra->pos[i].y, cobra->corpo);
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

/* seta a direcao inicial do primeiro movimento da cobra */
int iniciaMovimento(){
    char tecla;
    do{
        tecla = getch();
        if(tecla == -32)
            tecla = getch();
      }while(tecla != ASCII_UP && tecla != ASCII_DOWN && tecla != ASCII_RIGHT);
    switch(tecla){
        case ASCII_UP:
            return UP;
        case ASCII_DOWN:
            return DOWN;
        case ASCII_RIGHT:
            return RIGHT;
      }
}
