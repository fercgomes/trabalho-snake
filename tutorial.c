/* tutorial */

int Tutorial(){
  clrscr();
  DesenhaCaixa(10, 5, 70, 20, '#',  BLACK, WHITE);
  gotoxy(12, 7);
  ImprimeCor_String(BLACK, WHITE, "INSTRUCOES DE JOGO:", 13, 7);
  ImprimeCor_String(WHITE, BLACK, "Utilize as setas do teclado para controlar a cobra.", 13, 9);
  ImprimeCor_String(WHITE, BLACK, "A cobra comeca parada, utilize as setas para", 13, 10);
  ImprimeCor_String(WHITE, BLACK, "iniciar o movimento", 13, 11);
  ImprimeCor_String(WHITE, BLACK, "Itens coletaveis:", 13, 13);
  ImprimeCor_String(WHITE, BLACK, "Comida (C) - Slower (S) - Faster (F) - Skip (K)", 13, 15);
  ImprimeCor_String(WHITE, BLACK, "Pressione qualquer tecla para continuar", 13, 17);
  PegaTecla_Animacao(54, 17);
  return 0;
}
