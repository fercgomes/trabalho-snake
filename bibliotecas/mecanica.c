/*
    MODULO DE MECANICA DO JOGO
*/



/* imprime as informacoes do jogo */
void AtualizaInfo(JOGADOR jogador, int nivel, COBRA cobra, OPCOES opcoes){
    ImprimeCor_String(BLACK, WHITE, "Pontuacao:         Nivel:         Tamanho:        Tamanho maximo: ", PLACAR_XANCHOR, 1);
    ImprimeCor_Int(BLACK, WHITE, jogador.pontuacao, PLACAR_XANCHOR + 11, 1);
    ImprimeCor_Int(BLACK, WHITE, nivel, PLACAR_XANCHOR + 25, 1);
    ImprimeCor_Int(BLACK, WHITE, cobra.tamanho_atual, PLACAR_XANCHOR + 42, 1);
    ImprimeCor_Int(BLACK, WHITE, opcoes.tamanho_maximo, PLACAR_XANCHOR + 65, 1);
}

/* PegaTecla:
    Se o usuario pressionar uma das setas, muda a direcao do movimento;
    Se pressionar ESC, muda a variavel JogadorSaiu para sair do jogo. */
void PegaTecla(COBRA *cobra, int *JogadorSaiu){
    char tecla;
    if(kbhit()){
        tecla = getch();
        /* Os dois switches aninhados servem para evitar que a mudanca de direcao fosse feita somente na chamada seguinte,
            e para permitir que pressionar ESC uma unica vez faca o jogo ser encerrado. */
        switch(tecla){
            case -32:       /* Se for pressionada uma tecla, o valor -32 e retornado e getch() e chamada outra vez. */
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
                }
                break;

            case ASCII_ESC: /* Se ESC for pressionado, muda o valor de JogadorSaiu. */
                *JogadorSaiu = 1;
        }
    }
}

/* De acordo com o nivel atual, carrega o respectivo mapa para a matriz local. */
void CarregaMapa(char map1[][MAPA_COLUNAS+1], char map2[][MAPA_COLUNAS+1], char map3[][MAPA_COLUNAS+1], char mapa_atual[][MAPA_COLUNAS+1], int nivel){
  int i;
  switch(nivel){
      case 1:
          for(i = 0; i < MAPA_LINHAS; i++)
              strcpy(mapa_atual[i], map1[i]);
          break;
      case 2:
          for(i = 0; i < MAPA_LINHAS; i++)
              strcpy(mapa_atual[i], map2[i]);
          break;
      case 3:
          for(i = 0; i < MAPA_LINHAS; i++)
              strcpy(mapa_atual[i], map3[i]);
      }
}

/* verifica se a cobra tem o tamanho necessario para passar de nivel, retornando 1 caso sim */
int VerificaPassagemNivel(COBRA cobra, OPCOES opcoes, int *PassaDeNivel){
  if(cobra.tamanho_atual == opcoes.tamanho_maximo)
    *PassaDeNivel = 1;
}

/* Se houve passagem de nivel, da bonus de pontos e altera variave de nivel */
void PassagemDeNivel(int PassagemNivel, JOGADOR *jogador, int *nivel, int *JogadorGanhou){
  if(PassagemNivel){
      jogador->pontuacao += 1000;
      if(*nivel < 3)
          (*nivel)++;
      else
          *JogadorGanhou = 1;
  }
}

/* retorna o resultado de jogo, de acordo com os valores padroes */
int ResultadoDeJogo(int CobraViva, int JogadorGanhou, int JogadorSaiu){
  if(CobraViva == 0)
      return JOGADOR_PERDEU;
  if(JogadorGanhou)
      return JOGADOR_GANHOU;
  if(JogadorSaiu)
      return JOGADOR_SAIU;
}

/* inicia o jogo no nivel informado */
int InicializaNivel(int *nivel, JOGADOR *jogador, OPCOES *opcoes, char map1[][MAPA_COLUNAS+1],
                    char map2[][MAPA_COLUNAS+1], char map3[][MAPA_COLUNAS+1],
                    TUNEL tuneis[], ITEM itens[], ATRIBUTOS comida, ATRIBUTOS slower,
                    ATRIBUTOS faster, ATRIBUTOS skip, COBRA cobra){

    int i,
        CobraViva = 1,
        JogadorGanhou = 0,
        PassaDeNivel,
        JogadorSaiu = 0;

    char mapa[MAPA_LINHAS][MAPA_COLUNAS+1];

    do{ /* ===== LOOP DO NIVEL ATUAL ===== */
        PassaDeNivel = 0;
        ImprimeNivelAtual(*nivel);                            /* imprime mensagem de nivel */
        CarregaMapa(map1, map2, map3, mapa, *nivel);          /* carrega o mapa atual para as matrizes */
        Mapa_Imprime(mapa);                                   /* imprime o mapa */
        InicializaTuneis(*nivel, tuneis);                     /* inicializa os tuneis */
        InicializaItens(*opcoes, itens, comida, slower, faster, skip, mapa, tuneis, cobra);     /* inicializa os itens */
        InicializaCobra(&cobra, *opcoes, *nivel);             /* inicializa a cobra */
        ImprimePlacar();                                      /* imprime o placar sem valores */
        ImprimeNomeJogo();                                    /* imprime o nome do jogo no placar */
        PegaDirecaoInicial(&cobra.direcao);                   /* pega direcao inicial */
        do{ /* === LOOP DA MOVIMENTACAO E DA INTERACAO === */
            /* Imprime os placares atualizados */
            AtualizaInfo(*jogador, *nivel, cobra, *opcoes);
            PegaTecla(&cobra, &JogadorSaiu);
            /* Faz a movimentacao da cobra, tanto no movimento livre quanto na passagem pelos tuneis */
            Movimentacao(&cobra, tuneis);
            /* Se a cobra esta passando por um item, os efeitos dele sao aplicados sobre ela e um novo item eh gerado */
            PegaItemCobra(&cobra, jogador, itens, comida, slower, faster, skip, mapa, tuneis, nivel, &PassaDeNivel);
            /* Se a cobra colide, ela morre */
            if(PosicaoValidaCobra(cobra, tuneis, mapa))
                CobraViva = 0;
            /* Quando a cobra chega no tamanho maximo definido, passa de nivel */
            VerificaPassagemNivel(cobra, *opcoes, &PassaDeNivel);
            TempoDeEspera(cobra.velocidade_atual);
        }while(CobraViva == 1 && PassaDeNivel == 0 && JogadorSaiu == 0);
        PassagemDeNivel(PassaDeNivel, jogador, nivel, &JogadorGanhou); /* gerencia a passagem de nivel */
    }while(CobraViva == 1 && JogadorGanhou == 0 && JogadorSaiu == 0);
    return ResultadoDeJogo(CobraViva, JogadorGanhou, JogadorSaiu);
}
