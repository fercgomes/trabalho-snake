/* CONSTANTES PARA DIRECAO */
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define ASCII_UP 72
#define ASCII_DOWN 80
#define ASCII_LEFT 75
#define ASCII_RIGHT 77
#define ASCII_ENTER 13
#define ASCII_ESC 27

/* CONSTANTES PARA LIMITES */
#define X_MIN 1
#define X_MAX 80
#define Y_MIN 2
#define Y_MAX 25

/* MAXIMOS */
#define MAX_SEGMENTOS 200
#define MAX_OBSTACULOS 380
#define MAX_ITEMS 5
#define MAX_TUNEIS 5
#define MAX_NOME 3
#define MAX_HIGHSCORES 10

#define VELOCIDADE_INICIAL_MIN 1
#define VELOCIDADE_INICIAL_MAX 10
#define TAMANHO_MAXIMO_MIN 10
#define TAMANHO_MAXIMO_MAX 100
#define ITENS_MAXIMOS_MIN 1
#define ITENS_MAIMOS_MAX 10


/* INICIALIZACOES */
#define TAMANHO_INICIAL 5
#define DIRECAO_INICIAL 4 /* direita */
#define X_INICIAL 40
#define Y_INICIAL 15
#define TAXA_ATUALIZACAO 100

/* MENU */
#define Y_ANCHOR 5 /* pos y da primeira opcao do menu */
#define X_ANCHOR 6 /* pos x da primeira opcao do menu */
#define Y_OFFSET 3 /* espacamento das opcoes  do menu */

/* MAPAS */
#define MAPA_LINHAS 24
#define MAPA_COLUNAS 80

/*
    Os mapas representados na matriz de string tem indices de 0-23 (Y - 24 LINHAS) e
    0-80 (X - 81 LINHAS). Graficamente (na funcao putchxy) eles tem indices de 2 - 25 (Y)
    e 1 - 81 (X).
        X OFFSET -> discrepancia do eixo X
        Y OFFSET -> discrepancia do eixo Y    */
#define MAPA_XOFFSET 1
#define MAPA_YOFFSET 2

/* ESTRUTURAS */
typedef struct{
  int x;
  int y;
} COORDENADA;

typedef struct{
  COORDENADA pos[MAX_SEGMENTOS];
  int direcao,
      tamanho_atual,
      velociade_atual;
  char corpo;
} COBRA;

typedef struct{
  COORDENADA pos;
  int id,
      id_saida,
      direcao_entrada,
      direcao_saida;
  char corpo;
} TUNEL;

/* atributos associados a cada tipo de item do jogo
  cada tipo de item tem que ser inicializado junto com o programa */
typedef struct{
  int altera_basepontos,
      altera_velocidade,
      altera_nivel,
      altera_tamanho;
  char corpo;
} ATRIBUTOS;

typedef struct{
  COORDENADA pos;
  ATRIBUTOS atributos;
} ITEM;

/* salvo no arquivo txt */
typedef struct{
  char nome[MAX_NOME + 1];
  int pontuacao;
} JOGADOR;

/* salvo no arquivo bin */
typedef struct{
  int velocidade_inicial,
      tamanho_maximo,
      itens_maximos;
} OPCOES;

/*
    escreve_cor:
    Escreve uma string na tela na cor de texto e fundo indicada, na posicao indicada
*/
void escreve_cor(int cor, int fundo, char texto[], int x, int y){
  textcolor(cor);
  textbackground(fundo);
  gotoxy(x, y);
  printf(texto);
  textcolor(WHITE);
  textbackground(BLACK);
}

/*
    escreve_cor:
    Escreve uma string na tela na cor de texto e fundo indicada, na posicao indicada
*/
void escreve_int_cor(int cor, int fundo, int n, int x, int y){
  textcolor(cor);
  textbackground(fundo);
  gotoxy(x, y);
  printf("%.2d", n);
  textcolor(WHITE);
  textbackground(BLACK);
}

/*
    espera_tecla:
    Retorna a tecla apertada.
    Mostra animacao de barras na pos (x, y) indicada.
*/
char espera_tecla(int x, int y){
  char retorno;
  char icone[4] = {'|', '\\', '-', '/'};
  int segue = 1, i = 0;
  while(segue){
    if(kbhit()){
      retorno = getch();
      segue = 0;
    }
    else{
      putchxy(x, y, icone[i]);
      if(i == 3)
        i = 0;
      else i++;
    }
    Sleep(100);
  }
}

/*
    carrega_opcoes:
    Carrega as opcoes o arquvo opcoes.bin para o programa.
    Retorna 1 em caso de erro na abertura do arquivo.
    Retorna 0 em caso de sucesso na abertura do arquivo.
*/
int carrega_opcoes(OPCOES *opcoes){
  FILE *arquivo;
  OPCOES buffer;
  if(!(arquivo = fopen("opcoes.bin", "rb"))){
    printf("Erro ao abrir o arquivo opcoes.bin\nPressione qualquer tecla para continuar...");
    cria_log("Erro ao abrir o arquivo opcoes.bin\n");
    espera_tecla(1, 3);
    return 1;
  }
  else{
    if(!(fread(&buffer, sizeof(OPCOES), 1, arquivo))){
      printf("Erro ao ler o arquivo opcoes.bin\nPressione qualquer tecla para continuar...");
      cria_log("Erro ao ler o arquivo opcoes.bin\n");
      espera_tecla(1, 3);
      return 1;
    }
    else *opcoes = buffer;
  }
  fclose(arquivo);
  cria_log("opcoes.bin carregado com sucesso\n");
}

/*
    salva_opcoes:
    Salva as opcoes alteradas no menu.
    Retorna 1 em caso de erro na execucao.
    Retorna 0 em caso de sucessona execucao.
*/
int salva_opcoes(OPCOES opcoes){
  FILE *arquivo;
  if(!(arquivo = fopen("opcoes.bin", "wb"))){
    printf("Erro ao abrir o arquivo opcoes.bin\nPressione qualquer tecla para continuar...");
    cria_log("Erro ao abrir o arquivo opcoes.bin\n");
    espera_tecla(1, 3);
    return 1;
  }
  else{
    if(!(fwrite(&opcoes, sizeof(OPCOES), 1, arquivo))){
      printf("Erro ao escrever no arquivo opcoes.bin\nPressione qualquer tecla para continuar...");
      cria_log("Erro ao escrever no arquivo opcoes.bin\n");
      espera_tecla(1, 3);
      return 1;
    }
  }
  fclose(arquivo);
  return 0;
}

/*
  opcoes_reset:
  Reseta as opcoes do programa e salva no arquivo.
*/
int opcoes_reset(OPCOES *opcoes){
  FILE *arquivo;
  OPCOES buffer;
  buffer.velocidade_inicial = 0;
  buffer.tamanho_maximo = 0;
  buffer.itens_maximos = 0;
  if(!(arquivo = fopen("opcoes.bin", "rb"))){
    printf("Erro ao abrir o arquivo opcoes.bin\nPressione qualquer tecla para continuar...");
    cria_log("Erro ao abrir o arquivo opcoes.bin\n");
    espera_tecla(1, 3);
    return 1;
  }
  else{
    if(!(fwrite(&buffer, sizeof(OPCOES), 1, arquivo))){
      printf("Erro ao resetar o arquivo opcoes.bin\nPressione qualquer tecla para continuar...");
      cria_log("Erro ao resetar o arquivo opcoes.bin\n");
      espera_tecla(1, 3);
      return 1;
    }
    else *opcoes = buffer;
  }
  fclose(arquivo);
  return 0;
  cria_log("opcoes.bin resetado com sucesso\n");
}

/*
    DEBBUGING
*/
/*
void debug_opcoes(){
  clrscr();
  FILE *arq;
  OPCOES buffer;
  arq = fopen("opcoes.bin", "rb");
  fread(&buffer, sizeof(OPCOES), 1, arq);
  printf("velocidade:%d\ntamanho maximo: %d\nitens maximos: %d", buffer.velocidade_inicial, buffer.tamanho_maximo, buffer.itens_maximos);
}

void cria_opcoes(){
  FILE *arq;
  OPCOES buffer;
  buffer.velocidade_inicial = 0;
  buffer.tamanho_maximo = 0;
  buffer.itens_maximos = 0;
  arq = fopen("opcoes.bin", "wb");
  fwrite(&buffer, sizeof(OPCOES), 1, arq);
}
*/
void mostra_opcoes(OPCOES opcoes){
  printf("velocidade:%d\ntamanho maximo: %d\nitens maximos: %d", opcoes.velocidade_inicial, opcoes.tamanho_maximo, opcoes.itens_maximos);
}
