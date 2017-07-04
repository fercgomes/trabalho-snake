#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio2.h>
#include "snake_lib.c"
#include "menu_principal.c"
#include "menu_highscores.c"
#include "menu_creditos.c"
#include "menu_opcoes.c"
#include "debugger.c"
#include "carrega-mapa.c"
#include "verifica-jogo.c"
#include "cria-jogador.c"
#include "arte.c"
#include "cobra-engine.c"

int main(){
  JOGADOR jogador;                    /* Informacoes sobre jogador atual */
  JOGADOR ranking[MAX_HIGHSCORES];    /* Arranjo com os 10 High Scores que vao ser salvos no arquivo */
  OPCOES opcoes;                      /* Opcoes de jogo */

  COBRA cobra;                        /* Cobra */
  TUNEL tuneis[MAX_TUNEIS];           /* Arranjo contendo todos os tuneis possiveis */
  ITEM itens[MAX_ITEMS];              /* Arranjo contendo todos os itens possiveis */

  int
      nivel,            /* Nivel do jogo */
      /*  nivel:
          1 -> Nivel 1
          2 -> Nivel 2
          3 -> Nivel 3
      */
      cobra_vida,       /* Sinalizador de estado para o fim do jogo */
      /*  cobra_vida:
          0 - ESC
          1 - GANHOU
          2 - PERDEU
      */
      jogo_ativo,
      /*  jogo_ativo:
          0 -> Jogo inativo, termina programa
          1 -> Jogo ativo, volta para menu principal apos fim de jogo
      */
      nivel_ativo,
      /*  nivel_ativo:
          0 -> Nivel inativo, jogador terminou o jogo, ganhou ou perdeu
          1 -> Nivel ativo, jogador ainda esta jogando
      */
      base_pontos,
      /*  base_pontos:
          Base de pontos para calculo de pontuacao.
          Eh alterada pelos itens coletados pelo jogador
      */
      tutorial;
      /*  tutorial:
          0 -> Jogador ja fez tutorial
          1 -> Jogador ainda nao fez o tutorial
      */

  /* MAPAS - 24 x 80 */
  char                /* Coluna extra para o \0 */
        nivel_1[MAPA_LINHAS][MAPA_COLUNAS+1],     /* Nivel 1 */
        nivel_2[MAPA_LINHAS][MAPA_COLUNAS+1],     /* Nivel 2 */
        nivel_3[MAPA_LINHAS][MAPA_COLUNAS+1];     /* Nivel 3 */

  ATRIBUTOS comida, faster, slower, skip;
  /* Atributos dos itens */
  /* Os atributos sao unicos para cada item. */
  /* COMIDA */
  comida.altera_basepontos = 2;
  comida.altera_velocidade = 0;
  comida.altera_nivel = 0;
  comida.altera_tamanho = 1;
  comida.corpo = '0';
  /* SLOWER */
  slower.altera_basepontos = 1;
  slower.altera_velocidade = -1;
  slower.altera_nivel = 0;
  slower.altera_tamanho = 0;
  slower.corpo = '0';
  /* FASTER */
  faster.altera_basepontos = 3;
  faster.altera_velocidade = 1;
  faster.altera_nivel = 0;
  faster.altera_tamanho = 0;
  faster.corpo = '0';
  /* SKIP */
  skip.altera_basepontos = 40;
  skip.altera_velocidade = 0;
  skip.altera_nivel = 1;
  skip.altera_tamanho = 1;
  skip.corpo = '0';

  jogo_ativo = 1;       /* ativa o jogo */
  nivel_ativo = 1;      /* ativa os niveis */
  nivel = 1;            /* inicializa primeiro nivel */
  cobra_vida = 0;       /* inicializa vida da cobra */
  base_pontos = 0;      /* inicializa base de pontos */
  tutorial = 0;         /* */

  MenuPrincipal(&opcoes, ranking);

  return 0;
}

/*
    Engine do Jogo:
    LOOP 0:
      Menu principal

      LOOP 1:
          Inicializacao de nivel
          LOOP 2:
              Movimentacao da cobra
              Verificacao de estado
          ??
      Verifica fim de jogo
      Volta para menu?
*/
