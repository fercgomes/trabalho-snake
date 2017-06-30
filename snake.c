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

int main(){
  JOGADOR jogador;
  OPCOES opcoes;

  strcpy(jogador.nome, "FCG");
  jogador.pontuacao = 0;

  opcoes.velocidade_inicial = 5;
  opcoes.tamanho_maximo = 50;
  opcoes.itens_maximos = 5;

  carrega_opcoes(&opcoes);
  menu_principal(&opcoes);

  //menu_opcoes();

  //debug_opcoes();
  return 0;
}
