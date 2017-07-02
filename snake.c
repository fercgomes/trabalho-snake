/*
    ARQUIVO principal

    Padrao de retorno de funcao:
      Funcoes que tratam arquivos:
        Retornam 0 para indicar sucesso e não-zero para indicar erro.

*/

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

int main(){
  JOGADOR jogador;                    /* Informacoes sobre jogador atual */
  JOGADOR ranking[MAX_HIGHSCORES];    /* Arranjo com os 10 High Scores que vao ser salvos no arquivo */
  OPCOES opcoes;                       /* Opcoes de jogo */

  COBRA cobra;
  TUNEL tuneis[MAX_TUNEIS];
  ITEM itens[MAX_ITEMS];

  int
      nivel,          /* Nivel do jogo */
      status;       /* Sinalizador de estado para o fim do jogo */
      /*
          0 - ESC
          1 - GANHOU
          2 - PERDEU
      */

  /* MAPAS - 24 x 80 */
  char                      /* Coluna extra para o \0 */
        nivel_1[MAPA_LINHAS][MAPA_COLUNAS+1],
        nivel_2[MAPA_LINHAS][MAPA_COLUNAS+1],
        nivel_3[MAPA_LINHAS][MAPA_COLUNAS+1];

  ATRIBUTOS comida, faster, slower, skip;

  /* Inicializacoes iniciais */

  /* Atributos dos itens */
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

  if(!carrega_opcoes(&opcoes))        /* carrega a estrutura OPCOES salva em opcoes.bin para a variavel opcoes */
    if(menu_principal(&opcoes)){    /* carrega o menu principal */
      cria_jogador(&jogador);       /* insere o nome do jogador */
      jogador.pontuacao = 0;        /* zera pontuacao */
    }
  debug(opcoes, jogador, ranking, nivel, status);
  return 0;
}
