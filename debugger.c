/* DEBUGGING TOOLS */

/*
    cria_log:
    Manda informacao sobre o funcionamento do programa para o arquivo de log.
*/
int cria_log(char msg[]){
  FILE *log;
  log = fopen("log/log.txt", "a");
  fprintf(log, msg);
  fclose(log);
  return 1;
}

int opcoes_log(OPCOES opcoes){
  FILE *arquivo;
  OPCOES buffer;
  if(!(arquivo = fopen("opcoes.bin", "rb"))){
    printf("Erro ao abrir o arquivo opcoes.bin\nPressione qualquer tecla para continuar...");
    return 1;
  }
  else{
    if(!(fread(&buffer, sizeof(OPCOES), 1, arquivo))){
      printf("Erro ao ler o arquivo opcoes.bin\nPressione qualquer tecla para continuar...");
      return 1;
    }
}
  fclose(arquivo);
  mostra_opcoes(buffer);
}
