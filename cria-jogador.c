
void cria_jogador_setacursor(int cursor, int selecionado){
  /* Imprime cursor atual e apaga antigo*/
  switch(cursor){
    case 0:
      if(selecionado){
        putchxy(37, 6, '^');
        putchxy(37, 8, 'V');
      }
      else{
        putchxy(37, 6, ' ');
        putchxy(37, 8, ' ');
      }
      break;
    case 1:
      if(selecionado){
        putchxy(39, 6, '^');
        putchxy(39, 8, 'V');
      }
      else{
        putchxy(39, 6, ' ');
        putchxy(39, 8, ' ');
      }
      break;
    case 2:
      if(selecionado){
        putchxy(41, 6, '^');
        putchxy(41, 8, 'V');
      }
      else{
        putchxy(41, 6, ' ');
        putchxy(41, 8, ' ');
      }
      break;
    case 3:
      if(selecionado){
        escreve_cor(BLACK, WHITE, "<ENTER> PARA CONTINUAR", 28, 19);
        escreve_cor(BLACK, WHITE, "<ESC> PARA VOLTAR", 30, 20);
      }
      else{
        escreve_cor(BLACK, BLACK, "                      ", 28, 19);
        escreve_cor(BLACK, BLACK, "                 ", 30, 20);
      }
  }
}

/*
    cria_jogador:
      Cria a estrutura jogador a partir da entrada do usuario.    */
void cria_jogador(JOGADOR *jogador){
  char nome[MAX_NOME+1] = "AAA";
  char tecla;
  int cursor, cursor_aux, escolhendo;
  /*
      CURSOR:
      0 -> Primeira posicao
      1 -> Segunda posicao
      2 -> Terceira posicao
      3 -> ENTER
  */

  clrscr();
  escreve_cor(BLACK, WHITE, "NOME DO JOGADOR", 32, 3);
  escreve_cor(BLACK, WHITE, "UTILIZE AS SETAS PARA ESCOLHER UM NOME", 20, 14);
  escreve_cor(BLACK, WHITE, "PRESSIONE ENTER PARA CONFIRMAR", 24, 16);
  escolhendo = 1;
  cursor = 0;
  while(escolhendo){
    /* Imprime caracteres salvos */
    putchxy(37, 7, nome[0]);
    putchxy(39, 7, nome[1]);
    putchxy(41, 7, nome[2]);

    cria_jogador_setacursor(cursor, 1);

    /* Verifica tecla */
    tecla = getch();
      if(tecla == -32)
        tecla = getch();
    switch(tecla){
      case ASCII_UP:
        if(nome[cursor] < 'Z')
          nome[cursor]++;
        break;
      case ASCII_DOWN:
        if(nome[cursor] > 'A')
          nome[cursor]--;
        break;
      case ASCII_LEFT:
        if(cursor > 0){
          cria_jogador_setacursor(cursor, 0);
          cursor--;
        }
        break;
      case ASCII_RIGHT:
        if(cursor < 2){
          cria_jogador_setacursor(cursor, 0);
          cursor++;
        }
        break;
      case ASCII_ENTER:
        cursor_aux = cursor;
        cursor = 3;
        cria_jogador_setacursor(cursor_aux, 0);
        cria_jogador_setacursor(cursor, 1);
        tecla = getch();
        while(tecla != ASCII_ENTER && tecla != ASCII_ESC)
          tecla = getch();
        if(tecla == ASCII_ENTER)
          escolhendo = 0;
        else if(tecla == ASCII_ESC){
          cria_jogador_setacursor(cursor, 0);
          cursor = cursor_aux;
        }
    }
  }
  strcpy(jogador->nome, nome);
  clrscr(); /* PRECISA? */
}