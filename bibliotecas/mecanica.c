/*
    MODULO DE MECANICA DO JOGO
*/

void AtualizaInfo(JOGADOR jogador, int nivel, COBRA cobra, OPCOES opcoes){
    ImprimeCor_String(BLUE, WHITE, "Pontuacao:         Nivel:         Tamanho:        Tamanho maximo: ", 7, 1);
    ImprimeCor_Int(BLUE, WHITE, jogador.pontuacao, 17, 1);
    ImprimeCor_Int(BLUE, WHITE, nivel, 32, 1);
    ImprimeCor_Int(BLUE, WHITE, cobra.tamanho_atual, 49, 1);
    ImprimeCor_Int(BLUE, WHITE, opcoes.tamanho_maximo, 72, 1);
}

/* PegaTecla:
    Se o usuArio pressionar uma das setas, muda a direcao do movimento;
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
int VerificaPassagemNivel(COBRA cobra, OPCOES opcoes){
  if(cobra.tamanho_atual == opcoes.tamanho_maximo)
    return 1;
  else return 0;
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

int ResultadoDeJogo(int CobraViva, int JogadorGanhou, int JogadorSaiu){
  if(CobraViva == 0)
      return 0;
  if(JogadorGanhou)
      return 1;
  if(JogadorSaiu)
      return 2;
}

int InicializaNivel(int *nivel, JOGADOR *jogador, OPCOES *opcoes, char map1[][MAPA_COLUNAS+1],
                    char map2[][MAPA_COLUNAS+1], char map3[][MAPA_COLUNAS+1],
                    TUNEL tuneis[], ITEM itens[], ATRIBUTOS comida, ATRIBUTOS slower,
                    ATRIBUTOS faster, ATRIBUTOS skip, COBRA cobra){

    int i,
        tempo,
        CobraViva = 1,
        JogadorGanhou = 0,
        PassaDeNivel,
        JogadorSaiu = 0;

    char mapa[MAPA_LINHAS][MAPA_COLUNAS+1];

    do{ /* ===== LOOP DO NIVEL ATUAL ===== */
        PassaDeNivel = 0;
        /* Mensagem de Nivel */
        ImprimeNivelAtual(*nivel);
        /* --- */
        CarregaMapa(map1, map2, map3, mapa, *nivel);
        ImprimePlacar();
        Mapa_Imprime(mapa);
        InicializaTuneis(*nivel, tuneis);
        InicializaItens(*opcoes, itens, comida, slower, faster, skip, mapa, tuneis, cobra);
        InicializaCobra(&cobra, *opcoes, *nivel);
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
            PassaDeNivel = VerificaPassagemNivel(cobra, *opcoes);
            TempoDeEspera(cobra.velocidade_atual);
        }while(CobraViva == 1 && PassaDeNivel == 0 && JogadorSaiu == 0);
        PassagemDeNivel(PassaDeNivel, jogador, nivel, &JogadorGanhou); /* gerencia a passagem de nivel */
    }while(CobraViva == 1 && JogadorGanhou == 0 && JogadorSaiu == 0);
    return ResultadoDeJogo(CobraViva, JogadorGanhou, JogadorSaiu);
}
