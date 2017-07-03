/*
      Verificacao apos termino de jogo.
      Jogador pode ter apertado ESC, morrido ou ganhado, em todos os casos
      eh verificado se a pontuacao registrada deve entrar nos High Scores.

      Nome do jogador eh inserido no inicio de jogo. Pontuacao comeca zerada.

      Variave sinalizadora:
        cobra_vida (main):
      (0) EM JOGO

      (1) ESC - verifica score e volta pro menu
      (2) GANHOU - mostra mensagem, verifica score e verifica se volta pro menu ou termina
      (3) PERDEU - mostra mensagem, veriica score e verifica se volta pro menu ou termina

      Funcoes necessarias:
        -> verifica_score
        -> novo_highscore
        -> continua_jogo
*/

/*
    salva_novo_ranking:
      Salva no arquivo scores.txt o novo arranjo do Ranking, com o novo score inserido */
int salva_novo_ranking(JOGADOR ranking[]);

/*
    novo_highscore:
      Coloca um novo score no arranjo ranking. */
void novo_highscore(int novo_score, JOGADOR ranking[]);

/*
    verifica_score:
      Verficia se um score deve entrar para o ranking.
      Retorna:
        1 - Insere novo score
        2 - Nao insere novo score */
int verifica_score(JOGADOR jogador);

/*
    verifica_jogo:
      Gerencia o final do jogo, quando o jogador apertou esc, ganhou ou perdeu.
      Retorna:
        1 indicando retorno para o Menu Principal.
        0 indicando fim do programa.   */
int verifica_jogo(int estado, JOGADOR jogador){
  switch(estado){
    case 1:       /* Usuario apertou ESC */
      break;
    case 2:       /* Usuario ganhou o jogo */
      break;
    case 3:       /* Usuario perdeu o jogo */
      break;
  }
}
