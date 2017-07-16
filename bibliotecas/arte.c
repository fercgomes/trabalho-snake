/*
    ARTE DO JOGO
*/

#define NIVEL_XANCHOR 38
#define NIVEL_YANCHOR 9

#define NIVEL_TEMPOESPERA 10

/* Desenha uma linha horizontal de (x, y) de origem ate o x de destino */
void DesenhaLinhaHorizontal(int x_origem, int y_origem, int x_destino, char corpo, int cor, int fundo){
  int i;
  for(i = x_origem; i <= x_destino; i++){
    textcolor(cor);
    textbackground(fundo);
    putchxy(i, y_origem, corpo);
  }
  textcolor(WHITE);
  textbackground(BLACK);
}

/* Desenha uma linha vertical de (x, y) ate o y de destino */
void DesenhaLinhaVertical(int x_origem, int y_origem, int y_destino, char corpo, int cor, int fundo){
  int i;
  for(i = y_origem; i <= y_destino; i++){
    textcolor(cor);
    textbackground(fundo);
    putchxy(x_origem, i, corpo);
  }
  textcolor(WHITE);
  textbackground(BLACK);
}

/* Desenha uma caixa com ponta superior esquerda em (x, y) de origem e ponta inferior direita em (x, y) de destino */
void DesenhaCaixa(int x_origem, int y_origem, int x_destino, int y_destino, char corpo, int cor, int fundo){
  DesenhaLinhaHorizontal(x_origem, y_origem, x_destino, corpo, cor, fundo);
  DesenhaLinhaHorizontal(x_origem, y_destino, x_destino, corpo, cor, fundo);
  DesenhaLinhaVertical(x_origem, y_origem, y_destino, corpo, cor, fundo);
  DesenhaLinhaVertical(x_destino, y_origem, y_destino, corpo, cor, fundo);
}

/* Dsenha uma cobra no menu principal */
int Arte_MenuPrincipal_1(){
  int i, j;
  gotoxy(1, 3);
  textcolor(WHITE);
  printf("                                        ---_ ......._-_--.      \n");
  printf("                                       (|\\ /      / /| \\  \\     \n");
  printf("                                       /  /     .'  -=-'   `.   \n");
  printf("                                      /  /    .'             )  \n");
  printf("                                    _/  /   .'        _.)   /   \n");
  printf("                                   / o   o        _.-' /  .'    \n");
  printf("                                   \\          _.-'    / .'*|    \n");
  printf("                                    \\______.-'//    .'.' \\*|    \n");
  printf("                                     \\|  \\ | //   .'.' _ |*|    \n");
  printf("                                      `   \\|//  .'.'_ _ _|*|    \n");
  printf("                                       .  .// .'.' | _ _ \\*|    \n");
  printf("                                       \\`-|\\_/ /    \\ _ _ \\*\\   \n");
  printf("                                        `/'\\__/      \\ _ _ \\*\\  \n");
  printf("                                       /^|            \\ _ _ \\*  \n");
  printf("                                      '  `             \\ _ _ \\  \n");
  printf("                                                        \\_      \n");

  /* reseta para padrao */
  textcolor(WHITE);
  textbackground(BLACK);
  return 0;
}

/* Desenha 'snake' no menu principal */
int Arte_MenuPrincipal_2(){
  gotoxy(1, 17);
  textcolor(WHITE);
  printf("                                             _        \n");
  printf("                                            | |       \n");
  printf("                             ___ _ __   __ _| | _____ \n");
  printf("                            / __| '_ \\ / _` | |/ / _ \\\n");
  printf("                            \\__ \\ | | | (_| |   <  __/\n");
  printf("                            |___/_| |_|\\__,_|_|\\_\\___|\n");
  /* reseta para padrao */
  textcolor(WHITE);
  textbackground(BLACK);
  return 0;
}

void ImprimePlacar(){
  ImprimeCor_String(BLUE, WHITE, "Pontuacao:         Nivel:         Tamanho:        Tamanho maximo: ", 7, 1);
}

void ImprimeNivelAtual(int nivel){
  clrscr();
  DesenhaCaixa(10, 5, 70, 20, '#',  BLACK, WHITE);
  gotoxy(40, 10);
  switch(nivel){
    case 1:
      ImprimeCor_String(WHITE, BLACK, " ____ ", NIVEL_XANCHOR, NIVEL_YANCHOR);
      ImprimeCor_String(WHITE, BLACK, "/_   |", NIVEL_XANCHOR, NIVEL_YANCHOR + 1);
      ImprimeCor_String(WHITE, BLACK, " |   |", NIVEL_XANCHOR, NIVEL_YANCHOR + 2);
      ImprimeCor_String(WHITE, BLACK, " |   |", NIVEL_XANCHOR, NIVEL_YANCHOR + 3);
      ImprimeCor_String(WHITE, BLACK, " |___|", NIVEL_XANCHOR, NIVEL_YANCHOR + 4);
      break;
    case 2:
      ImprimeCor_String(WHITE, BLACK, "___    ", NIVEL_XANCHOR, NIVEL_YANCHOR);
      ImprimeCor_String(WHITE, BLACK, "|__ \\ ", NIVEL_XANCHOR, NIVEL_YANCHOR + 1);
      ImprimeCor_String(WHITE, BLACK, "   ) | ", NIVEL_XANCHOR, NIVEL_YANCHOR + 2);
      ImprimeCor_String(WHITE, BLACK, "  / /  ", NIVEL_XANCHOR, NIVEL_YANCHOR + 3);
      ImprimeCor_String(WHITE, BLACK, " / /_  ", NIVEL_XANCHOR, NIVEL_YANCHOR + 4);
      ImprimeCor_String(WHITE, BLACK, "|____| ", NIVEL_XANCHOR, NIVEL_YANCHOR + 5);
      break;
    case 3:
     ImprimeCor_String(WHITE, BLACK, " ____  ", NIVEL_XANCHOR, NIVEL_YANCHOR);
     ImprimeCor_String(WHITE, BLACK, "|___ \\ ", NIVEL_XANCHOR, NIVEL_YANCHOR + 1);
     ImprimeCor_String(WHITE, BLACK, "  __) |", NIVEL_XANCHOR, NIVEL_YANCHOR + 2);
     ImprimeCor_String(WHITE, BLACK, " |__ < ", NIVEL_XANCHOR, NIVEL_YANCHOR + 3);
     ImprimeCor_String(WHITE, BLACK, " ___) |", NIVEL_XANCHOR, NIVEL_YANCHOR + 4);
     ImprimeCor_String(WHITE, BLACK, "|____/ ", NIVEL_XANCHOR, NIVEL_YANCHOR + 5);
     break;
  }
  ImprimeCor_String(BLACK, WHITE, "PRESSIONE <ENTER> PARA INICIAR", 26, 16);
  Sleep(NIVEL_TEMPOESPERA);
  EsperaEnter_Animacao(68, 18);
  clrscr();
}
