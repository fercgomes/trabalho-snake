/* MENU - OPCOES */
/*  Carrega um arquivo .bin que contem as opcoes salvas do ultimo jogo.
    Caso o arquivo nao exista, criar um com opcoes padroes */

/*
    Funcionamento:
    cursor:
    1 - Velocidade inicial
    2 - Tamanho maximo
    3 - Itens maximos

    Enter: seleciona e ativa o modo editor
      UP DOWN: alteram valor
      Enter: salvam valor nas opcoes internas e  no arquivo
*/

/*
    imprime_valor_OP:
    Imprime as opcoes correspondentes ao valor do cursor.
*/
void imprime_valor_OP(OPCOES opcoes, int cursor, int selecionado){
  switch(cursor){
    case 1:
      if(selecionado)
        escreve_int_cor(BLACK, WHITE, opcoes.velocidade_inicial, 15, 8);
      else
        escreve_int_cor(WHITE, BLACK, opcoes.velocidade_inicial, 15, 8);
      break;
    case 2:
      if(selecionado)
        escreve_int_cor(BLACK, WHITE, opcoes.tamanho_maximo, 15, 14);
      else
        escreve_int_cor(WHITE, BLACK, opcoes.tamanho_maximo, 15, 14);
    break;
    case 3:
      if(selecionado)
        escreve_int_cor(BLACK, WHITE, opcoes.itens_maximos, 15, 20);
      else
        escreve_int_cor(WHITE, BLACK, opcoes.itens_maximos, 15, 20);
    break;
  }
}

/*
    imprime_cursor_OP:
    Imprime as opcoes do menu de Opcoes.
      selecionado: boolean
*/
void imprime_cursor_OP(int cursor, int selecionado){
  char op1[] = "VELOCIDADE INICIAL";
  char op2[] = "TAMANHO MAXIMO";
  char op3[] = "LIMITE DE ITENS NA TELA";
  char op4[] = "VOLTAR";

  switch(cursor){
    case 1:
      if(selecionado)
        escreve_cor(BLACK, WHITE, op1, X_ANCHOR, Y_ANCHOR);
      else
        escreve_cor(WHITE, BLACK, op1, X_ANCHOR, Y_ANCHOR);
      break;
    case 2:
      if(selecionado)
        escreve_cor(BLACK, WHITE, op2, X_ANCHOR, Y_ANCHOR + 6);
      else
        escreve_cor(WHITE, BLACK, op2, X_ANCHOR, Y_ANCHOR + 6);
      break;
    case 3:
      if(selecionado)
        escreve_cor(BLACK, WHITE, op3, X_ANCHOR, Y_ANCHOR + 12);
      else
        escreve_cor(WHITE, BLACK, op3, X_ANCHOR, Y_ANCHOR + 12);
      break;
    case 4:   /* VOLTAR */
      if(selecionado)
        escreve_cor(BLACK, RED, op4, X_ANCHOR + 30, Y_ANCHOR + 18);
      else
        escreve_cor(WHITE, BLACK, op4, X_ANCHOR + 30, Y_ANCHOR + 18);
      break;
  }
}

/*
    opcoes_editor:
    Seleciona uma opcao do menu de opcoes, altera o valor e o salva.
*/
int opcoes_editor(OPCOES *opcoes, int cursor){
  int valor, escolhendo = 1;
  char tecla;
  imprime_valor_OP(*opcoes, cursor, 1);
  while(escolhendo){
    tecla = getch();
    if(tecla == -32)
          tecla = getch();
    if(tecla != ASCII_ENTER){
      switch(cursor){
        case 1:
          if(tecla == ASCII_UP && opcoes->velocidade_inicial < VELOCIDADE_INICIAL_MAX){
            (opcoes->velocidade_inicial)++;
            imprime_valor_OP(*opcoes, cursor, 1);
          }
          else if(tecla == ASCII_DOWN && opcoes->velocidade_inicial > VELOCIDADE_INICIAL_MIN){
            (opcoes->velocidade_inicial)--;
            imprime_valor_OP(*opcoes, cursor, 1);
          }
          break;
        case 2:
          if(tecla == ASCII_UP && opcoes->tamanho_maximo < TAMANHO_MAXIMO_MAX){
            (opcoes->tamanho_maximo)++;
            imprime_valor_OP(*opcoes, cursor, 1);
          }
          else if(tecla == ASCII_DOWN && opcoes->tamanho_maximo > TAMANHO_MAXIMO_MIN){
            (opcoes->tamanho_maximo)--;
            imprime_valor_OP(*opcoes, cursor, 1);
          }
          break;
        case 3:
          if(tecla == ASCII_UP && opcoes->itens_maximos < ITENS_MAIMOS_MAX){
            (opcoes->itens_maximos)++;
            imprime_valor_OP(*opcoes, cursor, 1);
          }
          else if(tecla == ASCII_DOWN && opcoes->itens_maximos > ITENS_MAXIMOS_MIN){
            (opcoes->itens_maximos)--;
            imprime_valor_OP(*opcoes, cursor, 1);
          }
          break;
      }
    }
    else{
      imprime_valor_OP(*opcoes, cursor, 0);
      escolhendo = 0;
    }
  }
  return 1;
}

/*
    menu_opcoes:
    Retorna 1 se houve sucesso na execucao do programa.
*/
int menu_opcoes(OPCOES *opcoes){
  int cursor = 1,
      cursor_aux = 1,
      escolhendo = 1,
      editor = 0,
      i;

  clrscr();
  for(i = 1; i <= 4; i++){
    imprime_cursor_OP(i, 0);
    imprime_valor_OP(*opcoes, i, 0);
  }
  imprime_cursor_OP(cursor, 1); /* seleciona primeira opcao */

  escreve_cor(BLACK, WHITE, "<ENTER>", 45, 12);
  escreve_cor(BLACK, WHITE, "Altera a opcao selecionada", 45, 13);

  while(escolhendo){
    cursor_aux = seta_cursor(cursor, 1, 4);
    if(cursor_aux != -1){ /* usuario apertou alguma seta */
      /* cursor_aux salva a tecla apertada e cursor a anterior */
      imprime_cursor_OP(cursor, 0);
      imprime_cursor_OP(cursor_aux, 1);
      cursor = cursor_aux;
    }
    else if(cursor != 4)
      opcoes_editor(opcoes, cursor);
      else{
        escolhendo = 0;
        salva_opcoes(*opcoes);
      }
  }
  return 1;
}
