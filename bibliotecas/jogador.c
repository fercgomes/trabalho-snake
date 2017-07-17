#define MENUJOGADOR_PRIMEIROCHAR 0
#define MENUJOGADOR_SEGUNDOCHAR 1
#define MENUJOGADOR_TERCEIROCHAR 2
#define MENUJOGADOR_CONFIRMAR 3


/* Calcula o valor a ser ganho pela coleta de um item e o soma a pontuacao atual do jogador. */
void SomaPontuacao(JOGADOR *jogador, ITEM item, COBRA cobra){
  int base = item.atributos.altera_basepontos,
      tamanho = cobra.tamanho_atual,
      velocidade = cobra.velocidade_atual;

  jogador->pontuacao += (base * (tamanho / 5) * velocidade);
}

/* Imprime o cursor do menu de criar jogador */
void MenuFim_CriaJogador_SetaCursor(int cursor, int selecionado){
  /* Imprime cursor atual e apaga antigo*/
  switch(cursor){
    case MENUJOGADOR_PRIMEIROCHAR:
      if(selecionado){
        putchxy(37, 6, '^');
        putchxy(37, 8, 'V');
      }
      else{
        putchxy(37, 6, ' ');
        putchxy(37, 8, ' ');
      }
      break;
    case MENUJOGADOR_SEGUNDOCHAR:
      if(selecionado){
        putchxy(39, 6, '^');
        putchxy(39, 8, 'V');
      }
      else{
        putchxy(39, 6, ' ');
        putchxy(39, 8, ' ');
      }
      break;
    case MENUJOGADOR_TERCEIROCHAR:
      if(selecionado){
        putchxy(41, 6, '^');
        putchxy(41, 8, 'V');
      }
      else{
        putchxy(41, 6, ' ');
        putchxy(41, 8, ' ');
      }
      break;
    case MENUJOGADOR_CONFIRMAR:
      if(selecionado){
        ImprimeCor_String(BLACK, WHITE, "<ENTER> PARA CONTINUAR", 28, 19);
        ImprimeCor_String(BLACK, WHITE, "<ESC> PARA VOLTAR", 30, 20);
      }
      else{
        ImprimeCor_String(BLACK, BLACK, "                      ", 28, 19);
        ImprimeCor_String(BLACK, BLACK, "                 ", 30, 20);
      }
  }
}

/* Imprime o texto do menu de criar jogador */
 void MenuFim_InicializaOpcoes(){
   clrscr();
   ImprimeCor_String(BLACK, WHITE, "NOME DO JOGADOR", 32, 3);
   ImprimeCor_String(BLACK, WHITE, "UTILIZE AS SETAS PARA ESCOLHER UM NOME", 20, 14);
   ImprimeCor_String(BLACK, WHITE, "PRESSIONE ENTER PARA CONFIRMAR", 24, 16);
 }

/* Imprime o nome a ser salvo no ranking */
 void MenuFim_ImprimeNome(char nome[MAX_NOME+1]){
   putchxy(37, 7, nome[MENUJOGADOR_PRIMEIROCHAR]);
   putchxy(39, 7, nome[MENUJOGADOR_SEGUNDOCHAR]);
   putchxy(41, 7, nome[MENUJOGADOR_TERCEIROCHAR]);
 }

/* Pergunta ao usuario se ele confirma a escolha */
int MenuFim_ConfirmaEscolha(int *cursor, int cursor_aux){
  char tecla;
  tecla = getch();
  while(tecla != ASCII_ENTER && tecla != ASCII_ESC)
    tecla = getch();
  if(tecla == ASCII_ENTER)
    return 0;
  else if(tecla == ASCII_ESC){
    MenuFim_CriaJogador_SetaCursor(*cursor, NAO_SELECIONADO);
    *cursor = cursor_aux;
    return 1;
  }
}

/* Altera o nome a ser salvo no ranking */
int MenuFim_Escolhendo(int *cursor, int *cursor_aux, char nome[MAX_NOME+1]){
   char tecla;
   /* Verifica tecla */
   tecla = getch();
     if(tecla == -32)
       tecla = getch();
   switch(tecla){
     case ASCII_UP:
       if(nome[*cursor] < 'Z')
         nome[*cursor]++;
       return 1;
     case ASCII_DOWN:
       if(nome[*cursor] > 'A')
         nome[*cursor]--;
       return 1;
     case ASCII_LEFT:
       if(*cursor > MENUJOGADOR_PRIMEIROCHAR){
         MenuFim_CriaJogador_SetaCursor(*cursor, NAO_SELECIONADO);
         (*cursor)--;
       }
       return 1;
     case ASCII_RIGHT:
       if(*cursor < MENUJOGADOR_TERCEIROCHAR){
         MenuFim_CriaJogador_SetaCursor(*cursor, NAO_SELECIONADO);
         (*cursor)++;
       }
       return 1;
     case ASCII_ENTER:
       *cursor_aux = *cursor;
       *cursor = MENUJOGADOR_CONFIRMAR;
       MenuFim_CriaJogador_SetaCursor(*cursor_aux, NAO_SELECIONADO);
       MenuFim_CriaJogador_SetaCursor(*cursor, SELECIONADO);
       return MenuFim_ConfirmaEscolha(cursor, *cursor_aux);
   }
 }

/*
    MenuFim_CriaJogador:
      Cria a estrutura jogador a partir da entrada do usuario.    */
int MenuFim_CriaJogador(JOGADOR *jogador){
  char nome[MAX_NOME+1] = "AAA";
  char tecla;
  int cursor, cursor_aux, escolhendo;

  MenuFim_InicializaOpcoes();

  escolhendo = 1;
  cursor = 0;
  while(escolhendo){
    /* Imprime caracteres salvos */
    MenuFim_ImprimeNome(nome);
    MenuFim_CriaJogador_SetaCursor(cursor, SELECIONADO);
    escolhendo = MenuFim_Escolhendo(&cursor, &cursor_aux, nome);
  }
  strcpy(jogador->nome, nome);
  clrscr(); /* PRECISA? */
  return 0;
}
