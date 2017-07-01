/*
      Verificacao apos termino de jogo.
      Jogador pode ter apertado ESC, morrido ou ganhado, em todos os casos
      eh verificado se a pontuacao registrada deve entrar nos High Scores.

      Nome do jogador eh inserido no inicio de jogo. Pontuacao comeca zerada.

      Precisa de uma variavel sinalizadora.
      (0) ESC - verifica score e volta pro menu
      (1) GANHOU - mostra mensagem, verifica score e verifica se volta pro menu ou termina
      (2) PERDEU - mostra mensagem, veriica score e verifica se volta pro menu ou termina

      Funcoes necessarias:
        -> verifica_score
        -> novo_highscore
        -> continua_jogo
*/

/*
    verifica_jogo:
      Gerencia o final do jogo, quando o jogador apertou esc, ganhou ou perdeu.
      Retorna:
        1 indicando retorno para o Menu Principal.
        0 indicando fim do programa.   */
int verifica_jogo(int estado){
  switch(estado){
    case 0:       /* Usuario apertou ESC */
      break;
    case 1:       /* Usuario ganhou o jogo */
      break;
    case 2:       /* Usuario perdeu o jogo */
      break;
  }
}
