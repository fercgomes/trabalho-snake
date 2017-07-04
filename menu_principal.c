/* MENU PRINCIPAL */

/*
    MenuPrincipal_ImprimeCursor
    Imprime as opcoes do menu principal.
    selecionado: booleano                  */
void MenuPrincipal_ImprimeCursor(int cursor, int selecionado){
  /* 1 - novo jogo; 2 - high scores; 3 - opcoes; 4 - creditos; 0 - sair */
  char cursor_1[] = "NOVO JOGO";
  char cursor_2[] = "HIGH SCORES";
  char cursor_3[] = "OPCOES";
  char cursor_4[] = "CREDITOS";
  char cursor_5[] = "SAIR";
  switch(cursor){
    case 1:
      if(selecionado)
        ImprimeCor_String(BLACK, WHITE, cursor_1, X_ANCHOR, Y_ANCHOR);
      else
        ImprimeCor_String(WHITE, BLACK, cursor_1, X_ANCHOR, Y_ANCHOR);
      break;
    case 2:
      if(selecionado)
        ImprimeCor_String(BLACK, WHITE, cursor_2, X_ANCHOR, Y_ANCHOR + Y_OFFSET);
      else
        ImprimeCor_String(WHITE, BLACK, cursor_2, X_ANCHOR, Y_ANCHOR + Y_OFFSET);
      break;
    case 3:
      if(selecionado)
        ImprimeCor_String(BLACK, WHITE, cursor_3, X_ANCHOR, Y_ANCHOR + Y_OFFSET*2);
      else
        ImprimeCor_String(WHITE, BLACK, cursor_3, X_ANCHOR, Y_ANCHOR + Y_OFFSET*2);
      break;
    case 4:
      if(selecionado)
        ImprimeCor_String(BLACK, WHITE, cursor_4, X_ANCHOR, Y_ANCHOR + Y_OFFSET*3);
      else
        ImprimeCor_String(WHITE, BLACK, cursor_4, X_ANCHOR, Y_ANCHOR + Y_OFFSET*3);
      break;
    case 5:
      if(selecionado)
        ImprimeCor_String(BLACK, WHITE, cursor_5, X_ANCHOR, Y_ANCHOR + Y_OFFSET*4);
      else
        ImprimeCor_String(WHITE, BLACK, cursor_5, X_ANCHOR, Y_ANCHOR + Y_OFFSET*4);
      break;
  }
}

/*  MenuPrincipal_InicializaOpcoes
    Imprime as cinco opcoes do Menu Principal e seleciona o cursor informado  */
void MenuPrincipal_InicializaOpcoes(int cursor){
  int i;

  for(i = 1; i <= 5; i++)                 /* imprime as cinco opcoes do menu */
    MenuPrincipal_ImprimeCursor(i, 0);

  MenuPrincipal_ImprimeCursor(cursor, 1); /* seleciona a opcao salva no cursor */
}
/*  MenuPrincipal_Enter
    Verifica o cursor ativo quando o usuario apertou ENTER.
      NOVO JOGO:
        Seta a saida da funcao Menu Principal para 1.
        Retorna 0 para sinalizar a saida do Menu Prinicpal.
      SAIR:
        Seta a saida funcao Menu Prinicipal para 0.
        Retorna 0 para sinalizar a saida do Menu Prinicipal.
      HIGH SCORES | OPCOES:
        Retorna 1 para sinalizar a continuacao do Menu Principal.
        Caso a abertura dos arquivos falhe:
          Seta a saida da funcao Menu Principal para 0.
          Retorna 0 para sinalizar saida do Menu Principal.
      CREDITOS:
        Retorna 1 para sinalizar a continuacao no Menu Principal.   */
int MenuPrincipal_Enter(OPCOES *opcoes, JOGADOR ranking[], int cursor, int *status){
  switch(cursor){
    case 1:                                   /* MENU -> NOVO JOGO */
      *status = 1;                            /* sinaliza inicio de jogo */
      return 0;                               /* sinaliza saida do Menu Principal */

    case 2:                                   /* MENU -> HIGH SCORES */
      if(!menu_highscores(ranking))           /* chama menu de scores */
        return 1;                             /* sinaliza para ficar no Menu Principal */
      else{
        *status = 0;                          /* sinaliza para terminar programa */
        return 0;                             /* em caso de erro no menu de highscores, sinaliza para sair do Menu Principal */
      }

    case 3:                                   /* MENU -> OPCOES */
      if(!MenuOpcoes(opcoes))                /* chama menu de opcoes */
        return 1;                             /* sinaliza para ficar no Menu Principal */
      else{
        *status = 0;                          /* sinaliza para terminar programa */
        return 0;                             /* envia sinal para sair do Menu Prinicipal */
      }

    case 4:                                   /* MENU -> CREDITOS */
      menu_creditos();
      return 1;                               /* sinaliza para ficar no Menu Principal */

    case 5:                                   /* MENU -> SAIR */
      *status = 0;                            /* sinaliza para terminar programa */
      return 0;                               /* sinaliza para sair do Menu Principal */
  }
}

/*  MenuPrincipal_Escolhe
    Retorna:
      1 -> continua no Menu Principal
      0 -> sai do Menu Principal       */
int MenuPrincipal_Escolhe(OPCOES *opcoes, JOGADOR ranking[], int *status){
  int escolhendo = 1,
      cursor = 1,
      cursor_aux = 1;

  MenuPrincipal_InicializaOpcoes(cursor);              /* inicializa o cursor na posicao atual */

  while(escolhendo){                                   /* enquanto usuario estiver escolhendo uma opcao do menu */
    cursor_aux = SetaCursor(cursor, 1, 5);            /* pega novo cursor */
    if(cursor_aux != -1 && cursor_aux != -2){          /* usuario apertou alguma seta */
      /* cursor_aux salva a tecla apertada e cursor a anterior */
      MenuPrincipal_ImprimeCursor(cursor, 0);         /* de-seleciona o cursor antigo */
      MenuPrincipal_ImprimeCursor(cursor_aux, 1);     /* seleciona cursor atual */
      cursor = cursor_aux;
    }
    else if(cursor_aux == -1)
      escolhendo = 0;
  }

  /* Retorna 1 para continuar no Menu Principal, e 0 para sair */
  return MenuPrincipal_Enter(opcoes, ranking, cursor, status);
}

/*  MenuPrincipal_Arte:
    Limpa a tela e desenha a arte do Menu Principal */
void MenuPrincipal_Arte(){
  clrscr();
  Arte_MenuPrincipal_1();
  Arte_MenuPrincipal_2();
}

/*  MenuPrincipal:
    Interface do menu principal do jogo.
    Retorna:
      1 -  para indicar inicio do jogo
      0 -  para sair do programa  */
int MenuPrincipal(OPCOES *opcoes, JOGADOR ranking[]){
  int NoMenu = 1,
      EmJogo = 1,
      i;

  do{
    MenuPrincipal_Arte();                                       /* limpa a atela e desenha arte do jogo */
    NoMenu = MenuPrincipal_Escolhe(opcoes, ranking, &EmJogo);  /* se usuario nao iniciar jogo ou sair, continuar no menu */
  }
  while(NoMenu);

  /* Retorna:
      1 -> iniciar jogo
      0 -> terminar programa    */
  return EmJogo;
}
