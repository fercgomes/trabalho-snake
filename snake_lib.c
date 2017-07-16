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

#define CURSOR_ESC -2
#define CURSOR_ENTER -1

/* CONSTANTES PARA LIMITES */
#define X_MIN 1
#define X_MAX 80
#define Y_MIN 2
#define Y_MAX 25

/* MAXIMOS */
#define MAX_SEGMENTOS 200
#define MAX_OBSTACULOS 380
#define MAX_ITEMS 10
#define MAX_TUNEIS 5
#define MAX_NOME 3
#define MAX_HIGHSCORES 10


/* INICIALIZACOES */
#define TAMANHO_INICIAL 5
#define DIRECAO_INICIAL 4 /* direita */
#define X_INICIAL 40
#define Y_INICIAL 15
#define TAXA_ATUALIZACAO 100

/* ATRIBUTOS */
#define ATRIBUTOS_COMIDA_BASEPONTOS 2
#define ATRIBUTOS_COMIDA_VELOCIDADE 0
#define ATRIBUTOS_COMIDA_NIVEL 0
#define ATRIBUTOS_COMIDA_TAMANHO 1

#define ATRIBUTOS_SLOWER_BASEPONTOS 1
#define ATRIBUTOS_SLOWER_VELOCIDADE -1
#define ATRIBUTOS_SLOWER_NIVEL 0
#define ATRIBUTOS_SLOWER_TAMANHO 0

#define ATRIBUTOS_FASTER_BASEPONTOS 3
#define ATRIBUTOS_FASTER_VELOCIDADE 1
#define ATRIBUTOS_FASTER_NIVEL 0
#define ATRIBUTOS_FASTER_TAMANHO 0

#define ATRIBUTOS_SKIP_BASEPONTOS 40
#define ATRIBUTOS_SKIP_VELOCIDADE 0
#define ATRIBUTOS_SKIP_NIVEL 1
#define ATRIBUTOS_SKIP_TAMANHO 0

#define SELECIONADO 1
#define NAO_SELECIONADO 0


/* ESTRUTURAS */
typedef struct{
  int x;
  int y;
} COORDENADA;

typedef struct{
  COORDENADA pos[MAX_SEGMENTOS];
  int direcao,
      tamanho_atual,
      velocidade_atual;
  char corpo;
} COBRA;

typedef struct{
  COORDENADA pos,
             pos_entrada_e_saida;
  char id,
       id_saida;
  int  direcao_entrada,
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
    ImprimeCor_String:
    Escreve uma string na tela na cor de texto e fundo indicada, na posicao indicada  */
void ImprimeCor_String(int cor, int fundo, char texto[], int x, int y){
  textcolor(cor);
  textbackground(fundo);
  gotoxy(x, y);
  printf(texto);
  textcolor(WHITE);
  textbackground(BLACK);
}

/*
    ImprimeCor_String:
    Escreve uma string na tela na cor de texto e fundo indicada, na posicao indicada  */
void ImprimeCor_Int(int cor, int fundo, int n, int x, int y){
  textcolor(cor);
  textbackground(fundo);
  gotoxy(x, y);
  printf("%.2d", n);
  textcolor(WHITE);
  textbackground(BLACK);
}

/*
    PegaTecla_Animacao:
    Retorna a tecla apertada. //correção: não retorna a tecla, só espera que algo seja apertado.
    Mostra animacao de barras na pos (x, y) indicada.
*/
void PegaTecla_Animacao(int x, int y){
  char icone[4] = {'|', '\\', '-', '/'};
  int segue = 1, i = 0;
  while(segue){
    if(kbhit()){
      getch();
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

/*  SetaCursor:
    Atualiza a posicao do cursor.
    Os limites de posicao sao informados via parametro.
    ENTER: -1
    ESC: -2     */
int SetaCursor(int cursor, int op_min, int op_max){
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
      novo_cursor = CURSOR_ENTER;
      break;
    case ASCII_ESC:
      novo_cursor = CURSOR_ESC;
  }
  return novo_cursor;
}

void InicializaAtributos(ATRIBUTOS *comida, ATRIBUTOS *faster, ATRIBUTOS *slower, ATRIBUTOS *skip){
  /* COMIDA */
  comida->altera_basepontos = ATRIBUTOS_COMIDA_BASEPONTOS;
  comida->altera_velocidade = ATRIBUTOS_COMIDA_VELOCIDADE;
  comida->altera_nivel = ATRIBUTOS_COMIDA_NIVEL;
  comida->altera_tamanho = ATRIBUTOS_COMIDA_TAMANHO;
  comida->corpo = 'C';
  /* SLOWER */
  slower->altera_basepontos = ATRIBUTOS_SLOWER_BASEPONTOS;
  slower->altera_velocidade = ATRIBUTOS_SLOWER_VELOCIDADE;
  slower->altera_nivel = ATRIBUTOS_SLOWER_NIVEL;
  slower->altera_tamanho = ATRIBUTOS_SLOWER_TAMANHO;
  slower->corpo = 'S';
  /* FASTER */
  faster->altera_basepontos = ATRIBUTOS_FASTER_BASEPONTOS;
  faster->altera_velocidade = ATRIBUTOS_FASTER_VELOCIDADE;
  faster->altera_nivel = ATRIBUTOS_FASTER_NIVEL;
  faster->altera_tamanho = ATRIBUTOS_FASTER_TAMANHO;
  faster->corpo = 'F';
  /* SKIP */
  skip->altera_basepontos = ATRIBUTOS_SKIP_BASEPONTOS;
  skip->altera_velocidade = ATRIBUTOS_SKIP_VELOCIDADE;
  skip->altera_nivel = ATRIBUTOS_SKIP_NIVEL;
  skip->altera_tamanho = ATRIBUTOS_SKIP_TAMANHO;
  skip->corpo = 'K';
}

/* gera um numero aleatorio
   no intervalo fechado [minimo, maximo] */
int numeroAleatorio(int minimo, int maximo){
    int r;
    r = minimo + rand()%((maximo-minimo) + 1);
    return r;
}
