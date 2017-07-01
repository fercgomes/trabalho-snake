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

int main(){
  JOGADOR jogador;      /* Informacoes sobre jogador */
  OPCOES opcoes;        /* Opcoes de jogo */

  int
      nivel,          /* Nivel do jogo */
      fim_jogo;       /* Sinalizador de estado para o fim do jogo */
      /*
          0 - ESC
          1 - GANHOU
          2 - PERDEU
      */

  /* MAPAS - 24 x 80 */
  char                      /* Coluna extra para o \0 */
        nivel_1[MAPA_LINHAS][MAPA_COLUNAS];

  strcpy(jogador.nome, "FCG");
  jogador.pontuacao = 0;

  //carrega_opcoes(&opcoes);      /* carrega a estrutura OPCOES salva em opcoes.bin para a variavel opcoes */
  //menu_principal(&opcoes);      /* carrega o menu principal */

  if(!carrega_mapa(nivel_1)){
    converte_mapa(nivel_1);
    imprime_mapa(nivel_1);
  }

  getch();
  return 0;
}
