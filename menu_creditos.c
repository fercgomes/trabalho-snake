/* CREDITOS */
/*
    menu_creditos:
    Retorna 1 em caso de sucesso na execucao.
*/
int menu_creditos(){
  clrscr();
  escreve_cor(BLACK, WHITE, "EQUIPE:", 10, 3);
  escreve_cor(WHITE, BLACK, "Fernando Gomes", 10, 5);
  escreve_cor(WHITE, BLACK, "Artur Campana", 10, 7);
  escreve_cor(BLACK, WHITE, "Pressione qualquer tecla para voltar...", 10, 10);
  espera_tecla(10, 12);
  return 1;
}
