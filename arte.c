/*
ARTE DO JOGO
*/

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

void DesenhaCaixa(int x_origem, int y_origem, int x_destino, int y_destino, char corpo, int cor, int fundo){
  DesenhaLinhaHorizontal(x_origem, y_origem, x_destino, corpo, cor, fundo);
  DesenhaLinhaHorizontal(x_origem, y_destino, x_destino, corpo, cor, fundo);
  DesenhaLinhaVertical(x_origem, y_origem, y_destino, corpo, cor, fundo);
  DesenhaLinhaVertical(x_destino, y_origem, y_destino, corpo, cor, fundo);
}

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
