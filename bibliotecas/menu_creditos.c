/* CREDITOS */
/* Imprime os creditos do jogo */
int MenuCreditos(){
  clrscr();
  ImprimeCor_String(BLACK, WHITE, "EQUIPE:", 10, 3);
  ImprimeCor_String(WHITE, BLACK, "Fernando Gomes", 10, 5);
  ImprimeCor_String(WHITE, BLACK, "Artur Campana", 10, 7);
  ImprimeCor_String(BLACK, WHITE, "Pressione qualquer tecla para voltar...", 10, 10);
  PegaTecla_Animacao(10, 12);
  return 0;
}
