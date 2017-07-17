/* MENU - OPCOES */
/*  Carrega um arquivo .bin que contem as opcoes salvas do ultimo jogo.
    Caso o arquivo nao exista, criar um com opcoes padroes */

/*
    Funcionamento:
    cursor:
    1 - Velocidade inicial
    2 - Tamanho maximo
    3 - Itens maximos
    4 - Sair

    Enter: seleciona e ativa o modo editor
      UP DOWN: alteram valor
      Enter: salvam valor nas opcoes internas e  no arquivo

    Tratamento de erros:
      Caso o arquivo nao exista, um novo e criado com valores padrao. */

#define VELOCIDADE_INICIAL_PADRAO 1
#define TAMANHO_MAXIMO_PADRAO 10
#define ITENS_MAXIMOS_PADRAO 1

#define MENUOPCOES_CURSOR_VELOCIDADEINICIAL 1
#define MENUOPCOES_CURSOR_TAMANHOMAXIMO 2
#define MENUOPCOES_CURSOR_ITENSMAXIMOS 3
#define MENUOPCOES_CURSOR_SAIR 4

#define VELOCIDADE_INICIAL_MIN 1
#define VELOCIDADE_INICIAL_MAX 10
#define TAMANHO_MAXIMO_MIN 10
#define TAMANHO_MAXIMO_MAX 100
#define ITENS_MAXIMOS_MIN 1
#define ITENS_MAXIMOS_MAX 10

/*
            OPCOES - ARQUIVOS
*/

/*
  OpcoesReset:
  Reseta as opcoes do programa e salva no arquivo.    */
int OpcoesReset(OPCOES *opcoes){
  FILE *arquivo;
  OPCOES buffer;
  buffer.velocidade_inicial = VELOCIDADE_INICIAL_PADRAO;
  buffer.tamanho_maximo = TAMANHO_MAXIMO_PADRAO;
  buffer.itens_maximos = ITENS_MAXIMOS_PADRAO;
  arquivo = fopen("config/opcoes.bin", "wb");
  fwrite(&buffer, sizeof(OPCOES), 1, arquivo);
  *opcoes = buffer;
  fclose(arquivo);
  return 0;
}

/*
    Opcoes_CarregaArquivo:
    Carrega as opcoes o arquvo opcoes.bin para o programa.
    Retorna 1 em caso de erro na abertura do arquivo.
    Retorna 0 em caso de sucesso na abertura do arquivo   */
int Opcoes_CarregaArquivo(OPCOES *opcoes){
  FILE *arquivo;
  OPCOES buffer;
  if(!(arquivo = fopen("config/opcoes.bin", "rb"))){
    printf("Erro ao abrir o arquivo opcoes.bin\nO jogo sera fechado, pressione qualquer tecla para continuar...");
    PegaTecla_Animacao(1, 3);
    OpcoesReset(opcoes);
    return 1; /* retorna erro para main */
  }
  else{
    if(!(fread(&buffer, sizeof(OPCOES), 1, arquivo))){
      printf("Erro ao ler o arquivo opcoes.bin\nO jogo sera fechado, pressione qualquer tecla para continuar...");
      PegaTecla_Animacao(1, 3);
      OpcoesReset(opcoes);
      return 1; /* retorna erro para main */
    }
    else *opcoes = buffer;
  }
  fclose(arquivo);
  return 0; /* retorna sucesso para main */
}

/*
    Opcoes_SalvaArquivo:
    Salva as opcoes alteradas no menu.
    Retorna 1 em caso de erro na execucao.
    Retorna 0 em caso de sucessona execucao   */
int Opcoes_SalvaArquivo(OPCOES opcoes){
  FILE *arquivo;
  if(!(arquivo = fopen("config/opcoes.bin", "wb"))){
    printf("Erro ao abrir o arquivo opcoes.bin\nO jogo sera fechado, pressione qualquer tecla para continuar...");
    PegaTecla_Animacao(1, 3);
    return 1;
  }
  else{
    if(!(fwrite(&opcoes, sizeof(OPCOES), 1, arquivo))){
      printf("Erro ao escrever no arquivo opcoes.bin\nO jogo sera fechado, pressione qualquer tecla para continuar...");
      PegaTecla_Animacao(1, 3);
      return 1;
    }
  }
  fclose(arquivo);
  return 0;
}

/*
              OPCOES - INTERACAO
*/

/*
    MenuOpcoes_ImprimeValor:
    Imprime as opcoes correspondentes ao valor do cursor.     */
void MenuOpcoes_ImprimeValor(OPCOES opcoes, int cursor, int selecionado){
  switch(cursor){
    case MENUOPCOES_CURSOR_VELOCIDADEINICIAL:
      if(selecionado)
        ImprimeCor_Int(BLACK, WHITE, opcoes.velocidade_inicial, 15, 8);
      else
        ImprimeCor_Int(WHITE, BLACK, opcoes.velocidade_inicial, 15, 8);
      break;

    case MENUOPCOES_CURSOR_TAMANHOMAXIMO:
      if(selecionado)
        ImprimeCor_Int(BLACK, WHITE, opcoes.tamanho_maximo, 15, 14);
      else
        ImprimeCor_Int(WHITE, BLACK, opcoes.tamanho_maximo, 15, 14);
    break;

    case MENUOPCOES_CURSOR_ITENSMAXIMOS:
      if(selecionado)
        ImprimeCor_Int(BLACK, WHITE, opcoes.itens_maximos, 15, 20);
      else
        ImprimeCor_Int(WHITE, BLACK, opcoes.itens_maximos, 15, 20);
    break;
  }
}

/*
    MenuOpcoes_ImprimeCursor:
    Imprime as opcoes do menu de Opcoes.
      selecionado: boolean
*/
void MenuOpcoes_ImprimeCursor(int cursor, int selecionado){
  char op1[] = "VELOCIDADE INICIAL";
  char op2[] = "TAMANHO MAXIMO";
  char op3[] = "LIMITE DE ITENS NA TELA";
  char op4[] = "VOLTAR";

  switch(cursor){
    case MENUOPCOES_CURSOR_VELOCIDADEINICIAL:
      if(selecionado)
        ImprimeCor_String(BLACK, WHITE, op1, X_ANCHOR, Y_ANCHOR);
      else
        ImprimeCor_String(WHITE, BLACK, op1, X_ANCHOR, Y_ANCHOR);
      break;
    case MENUOPCOES_CURSOR_TAMANHOMAXIMO:
      if(selecionado)
        ImprimeCor_String(BLACK, WHITE, op2, X_ANCHOR, Y_ANCHOR + 6);
      else
        ImprimeCor_String(WHITE, BLACK, op2, X_ANCHOR, Y_ANCHOR + 6);
      break;
    case MENUOPCOES_CURSOR_ITENSMAXIMOS:
      if(selecionado)
        ImprimeCor_String(BLACK, WHITE, op3, X_ANCHOR, Y_ANCHOR + 12);
      else
        ImprimeCor_String(WHITE, BLACK, op3, X_ANCHOR, Y_ANCHOR + 12);
      break;
    case MENUOPCOES_CURSOR_SAIR:   /* VOLTAR */
      if(selecionado)
        ImprimeCor_String(BLACK, RED, op4, X_ANCHOR + 30, Y_ANCHOR + 18);
      else
        ImprimeCor_String(WHITE, BLACK, op4, X_ANCHOR + 30, Y_ANCHOR + 18);
      break;
  }
}

/*
    MenuOpcoes_Editor:
    Seleciona uma opcao do menu de opcoes, altera o valor e o salva.  */
void MenuOpcoes_Editor(OPCOES *opcoes, int cursor){
  int escolhendo = 1;
  char tecla;
  MenuOpcoes_ImprimeValor(*opcoes, cursor, SELECIONADO);  /* highlight no valor selecionado por ENTER */
  while(escolhendo){
    tecla = getch();
    if(tecla == -32)
          tecla = getch();
    if(tecla != ASCII_ENTER){
      switch(cursor){
        case MENUOPCOES_CURSOR_VELOCIDADEINICIAL:
          if(tecla == ASCII_UP && opcoes->velocidade_inicial < VELOCIDADE_INICIAL_MAX){
            (opcoes->velocidade_inicial)++;
            MenuOpcoes_ImprimeValor(*opcoes, cursor, SELECIONADO);
          }
          else if(tecla == ASCII_DOWN && opcoes->velocidade_inicial > VELOCIDADE_INICIAL_MIN){
            (opcoes->velocidade_inicial)--;
            MenuOpcoes_ImprimeValor(*opcoes, cursor, SELECIONADO);
          }
          break;

        case MENUOPCOES_CURSOR_TAMANHOMAXIMO:
          if(tecla == ASCII_UP && opcoes->tamanho_maximo < TAMANHO_MAXIMO_MAX){
            (opcoes->tamanho_maximo)++;
            MenuOpcoes_ImprimeValor(*opcoes, cursor, SELECIONADO);
          }
          else if(tecla == ASCII_DOWN && opcoes->tamanho_maximo > TAMANHO_MAXIMO_MIN){
            (opcoes->tamanho_maximo)--;
            MenuOpcoes_ImprimeValor(*opcoes, cursor, SELECIONADO);

            /* Para apagar o ultimo 0 do 100 */
            if(opcoes->tamanho_maximo == 99)
                printf(" ");
          }
          break;

        case MENUOPCOES_CURSOR_ITENSMAXIMOS:
          if(tecla == ASCII_UP && opcoes->itens_maximos < ITENS_MAXIMOS_MAX){
            (opcoes->itens_maximos)++;
            MenuOpcoes_ImprimeValor(*opcoes, cursor, SELECIONADO);
          }
          else if(tecla == ASCII_DOWN && opcoes->itens_maximos > ITENS_MAXIMOS_MIN){
            (opcoes->itens_maximos)--;
            MenuOpcoes_ImprimeValor(*opcoes, cursor, SELECIONADO);
          }
          break;
      }
    }
    else{
      MenuOpcoes_ImprimeValor(*opcoes, cursor, NAO_SELECIONADO);
      escolhendo = 0;
    }
  }
}

/* faz as impressoes da tela de opcoes */
void MenuOpcoes_InicializaOpcoes(OPCOES opcoes, int cursor){
  int i;
  clrscr();
  for(i = 1; i <= 4; i++){
    MenuOpcoes_ImprimeCursor(i, NAO_SELECIONADO);
    MenuOpcoes_ImprimeValor(opcoes, i, NAO_SELECIONADO);
  }
  MenuOpcoes_ImprimeCursor(cursor, SELECIONADO); /* seleciona primeira opcao */

  ImprimeCor_String(BLACK, WHITE, "<ENTER>", 45, 12);
  ImprimeCor_String(BLACK, WHITE, "Altera a opcao selecionada", 45, 13);
}

void MenuOpcoes_Arte(){
  DesenhaCaixa(4, 3, 30, 22, '#', BLACK, WHITE);
  DesenhaCaixa(41, 10, 73, 15, '#', BLACK, WHITE);
}

/*
    MenuOpcoes:
    Retorna
      0 = sucesso na execucao
      1 = erro                  */
int MenuOpcoes(OPCOES *opcoes){
  int cursor = 1,
      cursor_aux = 1,
      escolhendo = 1;

  MenuOpcoes_InicializaOpcoes(*opcoes, cursor);
  MenuOpcoes_Arte();

  while(escolhendo){
    cursor_aux = SetaCursor(cursor, 1, 4);
    if(cursor_aux != CURSOR_ENTER && cursor_aux != CURSOR_ESC){ /* usuario apertou alguma seta */
      /* cursor_aux salva a tecla apertada e cursor a anterior */
      MenuOpcoes_ImprimeCursor(cursor, NAO_SELECIONADO);
      MenuOpcoes_ImprimeCursor(cursor_aux, SELECIONADO);
      cursor = cursor_aux;
    }
    else if(cursor != MENUOPCOES_CURSOR_SAIR && cursor_aux == CURSOR_ENTER)
      MenuOpcoes_Editor(opcoes, cursor);
      else{
        if(!Opcoes_SalvaArquivo(*opcoes))
          escolhendo = 0;
        else return 1; /* envia erro de execucao para menu principal */
      }
  }
  return 0; /* envia sucesso de execucao para menu principal */
}
