/*
  ============= NaoSei Game Development - Copyright 2017 =============

    Snake - versao 0.1 (Beta)

    Membros da equipe:
      - Artur Waquil Campana
      - Fernando Correa Gomes
  =====================================================================
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

  COBRA cobra = {0};                  /* Cobra - inicializada com 0 para garantir que nao ha lixo antes da funcao InicializaCobra ser chamada */
  TUNEL tuneis[MAX_TUNEIS];           /* Arranjo contendo todos os tuneis possiveis */
  ITEM itens[MAX_ITEMS];              /* Arranjo contendo todos os itens possiveis */

  /* MAPAS - 24 x 80 */
  char                /* Coluna extra para o \0 */
        nivel_1[MAPA_LINHAS][MAPA_COLUNAS+1],     /* Nivel 1 */
        nivel_2[MAPA_LINHAS][MAPA_COLUNAS+1],     /* Nivel 2 */
        nivel_3[MAPA_LINHAS][MAPA_COLUNAS+1];     /* Nivel 3 */

  int
      nivel_atual,
      ResultadoJogo,
      tutorial_feito = 0,
      EmJogo,
      teste;

  /* Atributos dos itens */
  /* Os atributos sao unicos para cada item. */
  ATRIBUTOS comida, faster, slower, skip;
  InicializaAtributos(&comida, &faster, &slower, &skip);

  if(!MenuHighScores_CarregaArquivo(ranking))                   /* carrega arquivo de HighScores */
    if(!Opcoes_CarregaArquivo(&opcoes))                         /* carrega arquivo de Opcoes */
      if(!(Mapa_Carrega_e_Converte(nivel_1, "map1.txt")) &&     /* Retorna verdadeiro se os tres comandos */
         !(Mapa_Carrega_e_Converte(nivel_2, "map2.txt")) &&     /*  forem nulos - ou seja, se os mapas    */
         !(Mapa_Carrega_e_Converte(nivel_3, "map3.txt"))){      /*  forem carregados corretamente.        */
          /* so inicia jogo se opcoes, HS e os mapas foram carregados com sucesso */
          /* A funcao MenuPrincipal tem dois possiveis retornos:
              1: opcao Novo Jogo foi selecionada, inicia o jogo;
              0: opcao Sair foi selecionada, fecha o programa. */
          EmJogo = 1;
          do{
            if(MenuPrincipal(&opcoes, ranking)){                 /* carrega Menu Principal */
              if(!tutorial_feito){                               /* carrega tutorial (apenas na primeira vez) */
                tutorial_feito = 1;
                Tutorial();
              }

              /* zera nome do jogador, pontuacao e nivel */
              ZeraJogo(&nivel_atual, &jogador);

              /* inicia o jogo, retornando o resultado para a funcao verificadora */
              ResultadoJogo = InicializaNivel(&nivel_atual, &jogador, &opcoes, nivel_1, nivel_2, nivel_3, tuneis, itens, comida, slower, faster, skip, cobra);

              /* se houve problema com os arquivos de HS, retorna erro e o programa termina */
              if(MenuFim_VerificaJogo(ResultadoJogo, &jogador, ranking))
                EmJogo = 0; /* erro com arquivo de scores */
            }
            else MenuFim_Adeus(&EmJogo); /* mostra mensagem de adeus :) */
        }
        while(EmJogo);
      }
}

int main(){
  srand(time(NULL)); /* Semente para geracao de numeros aleatorios. */
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
