/* CREDITOS */
/* Imprime os creditos do jogo */

#define CREDITOS_XANCHOR 14

int MenuCreditos(){
  clrscr();
  DesenhaCaixa(10, 5, 70, 20, '#',  BLACK, WHITE);
  ImprimeCor_String(BLACK, WHITE, "EQUIPE:", CREDITOS_XANCHOR, 7);
  ImprimeCor_String(WHITE, BLACK, "Fernando Gomes", CREDITOS_XANCHOR, 9);
  ImprimeCor_String(WHITE, BLACK, "Artur Campana", CREDITOS_XANCHOR, 11);
  ImprimeCor_String(BLACK, WHITE, "Pressione qualquer tecla para voltar...", 20, 15);
  PegaTecla_Animacao(67, 18);
  return 0;
}
