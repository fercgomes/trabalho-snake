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

  /* MAPAS - 24 x 80 */
  char                /* Coluna extra para o \0 */
        nivel_1[MAPA_LINHAS][MAPA_COLUNAS+1],     /* Nivel 1 */
        nivel_2[MAPA_LINHAS][MAPA_COLUNAS+1],     /* Nivel 2 */
        nivel_3[MAPA_LINHAS][MAPA_COLUNAS+1];     /* Nivel 3 */

  ATRIBUTOS comida, faster, slower, skip;
  /* Atributos dos itens */
  /* Os atributos sao unicos para cada item. */
  InicializaAtributos(&comida, &faster, &slower, &skip);

  if(!MenuHighScores_CarregaArquivo(ranking))
    if(!Opcoes_CarregaArquivo(&opcoes))
      MenuPrincipal(&opcoes, ranking);
    else return 0;
  else return 0;

  jogador.pontuacao = 90;

  MenuFim_VerificaJogo(0, &jogador, ranking);

  debug(opcoes, jogador, ranking);
  getch();

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
