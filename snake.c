/*
  ============= NaoSei Game Development - copyright 2017 =============

    Snake - versão 0.1 (Beta)

    Problemas na funcionalidade:
      - a cobra não atravessa os tuneis;
      - a apresentação dos highscores não está funcionando corretamente;
      - não há uma tela final de jogo bem definida;

    Membros da equipe:
      - Artur Waquil Campana
      - Fernando Corrêa Gomes

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio2.h>
#include "arte.c"
#include "snake_lib.c"
#include "tutorial.c"
#include "menu_principal.c"
#include "menu_highscores.c"
#include "menu_creditos.c"
#include "menu_opcoes.c"
//#include "debugger.c"
#include "carrega-mapa.c"
#include "verifica-jogo.c"
#include "jogador.c"
#include "colisoes.c"
#include "tuneis.c"
#include "itens.c"
#include "cobra.c"
#include "mecanica.c"



void InicializaJogo(){
  JOGADOR jogador = {0};              /* Informacoes sobre jogador atual - inicializado com 0 para evitar lixo */
  JOGADOR ranking[MAX_HIGHSCORES];    /* Arranjo com os 10 High Scores que vao ser salvos no arquivo */
  OPCOES opcoes;                      /* Opcoes de jogo */

  COBRA cobra = {0};                  /* Cobra - inicializada com 0 para garantir que não há lixo antes da função InicializaCobra ser chamada */
  TUNEL tuneis[MAX_TUNEIS];           /* Arranjo contendo todos os tuneis possiveis */
  ITEM itens[MAX_ITEMS];              /* Arranjo contendo todos os itens possiveis */

  /* MAPAS - 24 x 80 */
  char                /* Coluna extra para o \0 */
        nivel_1[MAPA_LINHAS][MAPA_COLUNAS+1],     /* Nivel 1 */
        nivel_2[MAPA_LINHAS][MAPA_COLUNAS+1],     /* Nivel 2 */
        nivel_3[MAPA_LINHAS][MAPA_COLUNAS+1];     /* Nivel 3 */

  int
      nivel_atual = 1,
      Resultado_Jogo;

  /* Atributos dos itens */
  /* Os atributos sao unicos para cada item. */
  ATRIBUTOS comida, faster, slower, skip;
  InicializaAtributos(&comida, &faster, &slower, &skip);

  if(!MenuHighScores_CarregaArquivo(ranking))
    if(!Opcoes_CarregaArquivo(&opcoes))
      if(!(Mapa_Carrega_e_Converte(nivel_1, "map1.txt")) &&    /* Retorna verdadeiro se os três comandos */
         !(Mapa_Carrega_e_Converte(nivel_2, "map2.txt")) &&    /*  forem nulos - ou seja, se os mapas    */
         !(Mapa_Carrega_e_Converte(nivel_3, "map3.txt"))){     /*  forem carregados corretamente.        */
          /* so inicia jogo se opcoes, HS e os mapas foram carregados com sucesso */

          /* A função MenuPrincipal tem dois possíveis retornos:
              1: opção Novo Jogo foi selecionada, inicia o jogo;
              0: opção Sair foi selecionada, fecha o programa. */
          if(MenuPrincipal(&opcoes, ranking)){
            Tutorial();
            Resultado_Jogo = InicializaNivel(&nivel_atual, &jogador, &opcoes, nivel_1, nivel_2, nivel_3, tuneis, itens, comida, slower, faster, skip, cobra);

            /* A ordenação não está funcionando corretamente */
            MenuFim_VerificaJogo(Resultado_Jogo, &jogador, ranking);

          }
          else{
            clrscr();
            ImprimeCor_String(BLACK, WHITE, "SAINDO DO JOGO. ATE UM OUTRO DIA :)", 23, 3);
            PegaTecla_Animacao(40, 5);
          }
      }
}

void TesteMovimento(){

}

int main(){
  srand(time(NULL)); /* Semente para geração de números aleatórios. */

  InicializaJogo();

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
