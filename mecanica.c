
void AtualizaInfo(JOGADOR jogador, int nivel, COBRA cobra, OPCOES opcoes){
    ImprimeCor_String(BLUE, WHITE, "Pontuacao:         Nivel:         Tamanho:        Tamanho maximo: ", 7, 1);
    ImprimeCor_Int(BLUE, WHITE, jogador.pontuacao, 17, 1);
    ImprimeCor_Int(BLUE, WHITE, nivel, 32, 1);
    ImprimeCor_Int(BLUE, WHITE, cobra.tamanho_atual, 49, 1);
    ImprimeCor_Int(BLUE, WHITE, opcoes.tamanho_maximo, 72, 1);
}

/* PegaTecla:
    Se o usu�rio pressionar uma das setas, muda a dire��o do movimento;
    Se pressionar ESC, muda a vari�vel saiu para sair do jogo. */
void PegaTecla(COBRA *cobra, int *saiu){
    char tecla;
    if(kbhit()){
        tecla = getch();

        /* Os dois switches aninhados servem para evitar que a mudan�a de dire��o fosse feita somente na chamada seguinte,
            e para permitir que pressionar ESC uma �nica vez fa�a o jogo ser encerrado. */
        switch(tecla){
            case -32:       /* Se for pressionada uma tecla, o valor -32 � retornado e getch() � chamada outra vez. */
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
                }
                break;

            case ASCII_ESC: /* Se ESC for pressionado, muda o valor de saiu. */
                *saiu = 1;
        }
    }
}


int InicializaNivel(int *nivel, JOGADOR *jogador, OPCOES *opcoes, char map1[][MAPA_COLUNAS+1], char map2[][MAPA_COLUNAS+1], char map3[][MAPA_COLUNAS+1],
                     TUNEL tuneis[], ITEM itens[], ATRIBUTOS comida, ATRIBUTOS slower, ATRIBUTOS faster, ATRIBUTOS skip, COBRA cobra){

    int i, tempo;
    int vivo = 1,
        ganhoujogo = 0,
        ganhounivel,
        saiu = 0;
    char mapa[MAPA_LINHAS][MAPA_COLUNAS+1];

    do{ /* ===== LOOP DO NIVEL ATUAL ===== */

        ganhounivel = 0;

        /* De acordo com o nivel atual, carrega o respectivo mapa para a matriz local. */
        switch(*nivel){
            case 1:
                for(i = 0; i < MAPA_LINHAS; i++)
                    strcpy(mapa[i], map1[i]);
                break;
            case 2:
                for(i = 0; i < MAPA_LINHAS; i++)
                    strcpy(mapa[i], map2[i]);
                break;
            case 3:
                for(i = 0; i < MAPA_LINHAS; i++)
                    strcpy(mapa[i], map3[i]);
            }

        /* Imprime os nomes dos placares */
        ImprimeCor_String(BLUE, WHITE, "Pontuacao:         Nivel:         Tamanho:        Tamanho maximo: ", 7, 1);

        Mapa_Imprime(mapa);
        InicializaTuneis(*nivel, tuneis);
        InicializaItens(*opcoes, itens, comida, slower, faster, skip, mapa, tuneis, cobra);
        InicializaCobra(&cobra, *opcoes, *nivel);

        do{ /* === LOOP DA MOVIMENTA��O E DA INTERA��O === */

            /* Imprime os placares atualizados */
            AtualizaInfo(*jogador, *nivel, cobra, *opcoes);

            tempo = 1000/cobra.velocidade_atual;

            PegaTecla(&cobra, &saiu);

            /* Faz a movimenta��o da cobra, tanto no movimento livre quanto na passagem pelos tuneis */
            Movimentacao(&cobra, tuneis);

            /* Se a cobra est� passando por um item, os efeitos dele s�o aplicados sobre ela e um novo item � gerado */
            PegaItemCobra(&cobra, jogador, itens, comida, slower, faster, skip, mapa, tuneis, nivel, &ganhounivel);

            /* Se a cobra colide, ela morre */
            if(checacolisoes_item(cobra, tuneis, mapa))
                vivo = 0;

            /* Quando a cobra chega no tamanho maximo definido, passa de nivel */
            if(cobra.tamanho_atual == opcoes->tamanho_maximo)
                ganhounivel = 1;

            Sleep(tempo);
        }while(vivo == 1 && ganhounivel == 0 && saiu == 0);

        if(ganhounivel){
            jogador->pontuacao += 1000;

            if(*nivel < 3)
                (*nivel)++;
            else
                ganhoujogo = 1;
        }

    }while(vivo == 1 && ganhoujogo == 0 && saiu == 0);

    if(vivo == 0)
        return 0;
    if(ganhoujogo)
        return 1;
    if(saiu)
        return 2;
}
