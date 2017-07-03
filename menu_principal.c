/* MENU PRINCIPAL */
/*
    seta_cursor:
    Atualiza a posicao do cursor.
    Os limites de posicao sao informados via parametro.

    ENTER: -1
    ESC: -2
*/
int seta_cursor(int cursor, int op_min, int op_max){
  int novo_cursor = cursor;
  char tecla;
  tecla = getch();
  if(tecla == -32)
    tecla = getch();
  switch(tecla){
    case ASCII_UP:
      if(cursor > op_min)
        novo_cursor--;
        break;
    case ASCII_DOWN:
      if(cursor < op_max)
        novo_cursor++;
        break;
    case ASCII_ENTER:
      novo_cursor = -1;
      break;
    case ASCII_ESC:
      novo_cursor = -2;
  }
  return novo_cursor;
}

/*
    imprime_cursor_MP:
    Imprime as opcoes do menu principal.
      selecionado: boolean
*/
void imprime_cursor_MP(int cursor, int selecionado){
  /* 1 - novo jogo; 2 - high scores; 3 - opcoes; 4 - creditos; 0 - sair */
  char cursor_1[] = "NOVO JOGO";
  char cursor_2[] = "HIGH SCORES";
  char cursor_3[] = "OPCOES";
  char cursor_4[] = "CREDITOS";
  char cursor_5[] = "SAIR";
  switch(cursor){
    case 1:
      if(selecionado)
        escreve_cor(BLACK, WHITE, cursor_1, X_ANCHOR, Y_ANCHOR);
      else
        escreve_cor(WHITE, BLACK, cursor_1, X_ANCHOR, Y_ANCHOR);
      break;
    case 2:
      if(selecionado)
        escreve_cor(BLACK, WHITE, cursor_2, X_ANCHOR, Y_ANCHOR + Y_OFFSET);
      else
        escreve_cor(WHITE, BLACK, cursor_2, X_ANCHOR, Y_ANCHOR + Y_OFFSET);
      break;
    case 3:
      if(selecionado)
        escreve_cor(BLACK, WHITE, cursor_3, X_ANCHOR, Y_ANCHOR + Y_OFFSET*2);
      else
        escreve_cor(WHITE, BLACK, cursor_3, X_ANCHOR, Y_ANCHOR + Y_OFFSET*2);
      break;
    case 4:
      if(selecionado)
        escreve_cor(BLACK, WHITE, cursor_4, X_ANCHOR, Y_ANCHOR + Y_OFFSET*3);
      else
        escreve_cor(WHITE, BLACK, cursor_4, X_ANCHOR, Y_ANCHOR + Y_OFFSET*3);
      break;
    case 5:
      if(selecionado)
        escreve_cor(BLACK, WHITE, cursor_5, X_ANCHOR, Y_ANCHOR + Y_OFFSET*4);
      else
        escreve_cor(WHITE, BLACK, cursor_5, X_ANCHOR, Y_ANCHOR + Y_OFFSET*4);
      break;
  }
}

/*
    menu_principal:
    Interface do menu principal do jogo
    Retorna:
      1 -  para indicar inicio do jogo
      0 -  para sair do programa
       */
int menu_principal(OPCOES *opcoes, JOGADOR ranking[]){
  int cursor = 1,
      cursor_aux = 0,
      escolhendo,
      no_menu,
      status = 1,
      i;
  do{
    clrscr();
    arte_menuprincipal_1();
    arte_menuprincipal_2();
    escolhendo = 1;
    no_menu = 1;
    /* imprime as opcoes */
    for(i = 1; i <= 5; i++)
      imprime_cursor_MP(i, 0);
    imprime_cursor_MP(cursor, 1); /* seleciona primeira opcao */
    while(escolhendo){
      cursor_aux = seta_cursor(cursor, 1, 5);
      if(cursor_aux != -1 && cursor_aux != -2){ /* usuario apertou alguma seta */
        /* cursor_aux salva a tecla apertada e cursor a anterior */
        imprime_cursor_MP(cursor, 0);
        imprime_cursor_MP(cursor_aux, 1);
        cursor = cursor_aux;
      }
      else if(cursor_aux == -1) /* usuario apertou enter */
        switch(cursor){
          case 1: /* novo jogo */
            no_menu = 0;
            escolhendo = 0;
            status = 1;
            break;
          case 2: /* high scores */
            if(!menu_highscores(ranking)) /* montar retorno de erro */
              escolhendo = 0;
            else return 0;
            break;
          case 3: /* opcoes */
            if(!menu_opcoes(opcoes))
              escolhendo = 0; /* segue programa */
            else return 0; /* envia sinal para terminar programa para main */
            break;
          case 4: /* creditos */
            menu_creditos();
            escolhendo = 0;
            break;
          case 5: /* sair */
            no_menu = 0;
            escolhendo = 0;
            status = 0;
            break;
        }
    } /* fim do loop de escolha */
  } /* fim do loop do menu */
  while(no_menu);
  /* retorna o status de jogo para o resto do programa,
    indicando se comeca o jogo ou para o programa
    so sai quando aperta novo jogo ou sair */
  return status;
}
