/* MENU PRINCIPAL */

/* MENU - CONSTANTES */
#define Y_ANCHOR 5 /* pos y da primeira opcao do menu */
#define X_ANCHOR 6 /* pos x da primeira opcao do menu */
#define Y_OFFSET 3 /* espacamento das opcoes  do menu */

#define MENUPRINCIPAL_CURSOR_NOVOJOGO 1
#define MENUPRINCIPAL_CURSOR_HIGHSCORES 2
#define MENUPRINCIPAL_CURSOR_OPCOES 3
#define MENUPRINCIPAL_CURSOR_CREDITOS 4
#define MENUPRINCIPAL_CURSOR_SAIR 5

#define SELECIONADO 1
#define NAO_SELECIONADO 0

/*
    MenuPrincipal_ImprimeCursor
    Imprime as opcoes do menu principal.
    selecionado: booleano                  */
void MenuPrincipal_ImprimeCursor(int cursor, int selecionado){
  /* 1 - novo jogo; 2 - high scores; 3 - opcoes; 4 - creditos; 0 - sair */
  char novojogo[] = "NOVO JOGO";
  char highscores[] = "HIGH SCORES";
  char opcoes[] = "OPCOES";
  char creditos[] = "CREDITOS";
  char sair[] = "SAIR";
  switch(cursor){
    case MENUPRINCIPAL_CURSOR_NOVOJOGO:
      if(selecionado)
        ImprimeCor_String(BLACK, WHITE, novojogo, X_ANCHOR, Y_ANCHOR);
      else
        ImprimeCor_String(WHITE, BLACK, novojogo, X_ANCHOR, Y_ANCHOR);
      break;
    case MENUPRINCIPAL_CURSOR_HIGHSCORES:
      if(selecionado)
        ImprimeCor_String(BLACK, WHITE, highscores, X_ANCHOR, Y_ANCHOR + Y_OFFSET);
      else
        ImprimeCor_String(WHITE, BLACK, highscores, X_ANCHOR, Y_ANCHOR + Y_OFFSET);
      break;
    case MENUPRINCIPAL_CURSOR_OPCOES:
      if(selecionado)
        ImprimeCor_String(BLACK, WHITE, opcoes, X_ANCHOR, Y_ANCHOR + Y_OFFSET*2);
      else
        ImprimeCor_String(WHITE, BLACK, opcoes, X_ANCHOR, Y_ANCHOR + Y_OFFSET*2);
      break;
    case MENUPRINCIPAL_CURSOR_CREDITOS:
      if(selecionado)
        ImprimeCor_String(BLACK, WHITE, creditos, X_ANCHOR, Y_ANCHOR + Y_OFFSET*3);
      else
        ImprimeCor_String(WHITE, BLACK, creditos, X_ANCHOR, Y_ANCHOR + Y_OFFSET*3);
      break;
    case MENUPRINCIPAL_CURSOR_SAIR:
      if(selecionado)
        ImprimeCor_String(BLACK, WHITE, sair, X_ANCHOR, Y_ANCHOR + Y_OFFSET*4);
      else
        ImprimeCor_String(WHITE, BLACK, sair, X_ANCHOR, Y_ANCHOR + Y_OFFSET*4);
      break;
  }
}

/*  MenuPrincipal_InicializaOpcoes
    Imprime as cinco opcoes do Menu Principal e seleciona o cursor informado  */
void MenuPrincipal_InicializaOpcoes(int cursor){
  int i;
  for(i = MENUPRINCIPAL_CURSOR_NOVOJOGO; i <= MENUPRINCIPAL_CURSOR_SAIR; i++)                 /* imprime as cinco opcoes do menu */
    MenuPrincipal_ImprimeCursor(i, NAO_SELECIONADO);
  MenuPrincipal_ImprimeCursor(cursor, SELECIONADO); /* seleciona a opcao salva no cursor */
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
    case MENUPRINCIPAL_CURSOR_NOVOJOGO:                                   /* MENU -> NOVO JOGO */
      *status = 1;                            /* sinaliza inicio de jogo */
      return 0;                               /* sinaliza saida do Menu Principal */

    case MENUPRINCIPAL_CURSOR_HIGHSCORES:                                   /* MENU -> HIGH SCORES */
      if(!MenuHighScores(ranking))           /* chama menu de scores */
        return 1;                             /* sinaliza para ficar no Menu Principal */
      else{
        *status = 0;                          /* sinaliza para terminar programa */
        return 0;                             /* em caso de erro no menu de highscores, sinaliza para sair do Menu Principal */
      }

    case MENUPRINCIPAL_CURSOR_OPCOES:                                   /* MENU -> OPCOES */
      if(!MenuOpcoes(opcoes))                /* chama menu de opcoes */
        return 1;                             /* sinaliza para ficar no Menu Principal */
      else{
        *status = 0;                          /* sinaliza para terminar programa */
        return 0;                             /* envia sinal para sair do Menu Prinicipal */
      }

    case MENUPRINCIPAL_CURSOR_CREDITOS:                                   /* MENU -> CREDITOS */
      MenuCreditos();
      return 1;                               /* sinaliza para ficar no Menu Principal */

    case MENUPRINCIPAL_CURSOR_SAIR:                                   /* MENU -> SAIR */
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
    if(cursor_aux != CURSOR_ENTER){          /* usuario apertou alguma seta */
      /* cursor_aux salva a tecla apertada e cursor a anterior */
      MenuPrincipal_ImprimeCursor(cursor, NAO_SELECIONADO);         /* de-seleciona o cursor antigo */
      MenuPrincipal_ImprimeCursor(cursor_aux, SELECIONADO);     /* seleciona cursor atual */
      cursor = cursor_aux;
    }
    else if(cursor_aux == CURSOR_ENTER)
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
