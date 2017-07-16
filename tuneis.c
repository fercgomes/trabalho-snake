/* CriaeImprimeTunel:
    Instancia uma estrutura tunel com os parametros passados na função. */
void CriaeImprimeTunel(TUNEL *t, int um_posx, int um_posy, int x_pos_ent, int y_pos_ent, char um_id, char um_id_saida, int uma_dir_ent, int uma_dir_saida, char um_corpo){
    t->pos.x = um_posx;
    t->pos.y = um_posy;
    t->pos_entrada_e_saida.x = x_pos_ent;
    t->pos_entrada_e_saida.y = y_pos_ent;
    t->id = um_id;
    t->id_saida = um_id_saida;
    t->direcao_entrada = uma_dir_ent;
    t->direcao_saida = uma_dir_saida;
    t->corpo = um_corpo;
    putchxy(um_posx, um_posy, um_corpo);
}

/* InicializaTuneis:
    De acordo com o nivel recebido como parâmetro, preenche o arranjo
    de tuneis com instanciações arbitrárias.
    Posteriormente talvez seja preenchido aleatoriamente. */
void InicializaTuneis(int nivel, TUNEL t[MAX_TUNEIS]){
    switch(nivel){
    case 1:
        CriaeImprimeTunel(&t[0], -1, -1, -1, -1, ' ', ' ', 0, 0, ' ');
        CriaeImprimeTunel(&t[1], -1, -1, -1, -1, ' ', ' ', 0, 0, ' ');
        CriaeImprimeTunel(&t[2], -1, -1, -1, -1, ' ', ' ', 0, 0, ' ');
        CriaeImprimeTunel(&t[3], -1, -1, -1, -1, ' ', ' ', 0, 0, ' ');
        CriaeImprimeTunel(&t[4], -1, -1, -1, -1, ' ', ' ', 0, 0, ' ');
        break;
    case 2:
        CriaeImprimeTunel(&t[0], 13, 10, 14, 10, 'A', 'B', LEFT, RIGHT, '<');
        CriaeImprimeTunel(&t[1], 65, 14, 65, 13, 'B', 'A', DOWN, UP, 'V');
        CriaeImprimeTunel(&t[2], -1, -1, -1, -1, ' ', ' ', 0, 0, ' ');
        CriaeImprimeTunel(&t[3], -1, -1, -1, -1, ' ', ' ', 0, 0, ' ');
        CriaeImprimeTunel(&t[4], -1, -1, -1, -1, ' ', ' ', 0, 0, ' ');
        break;
    case 3:
        CriaeImprimeTunel(&t[0], 52, 14, 53, 14, 'A', 'B', LEFT, RIGHT, '<');
        CriaeImprimeTunel(&t[1], 14, 5, 14, 6, 'B', 'C', UP, DOWN, '^');
        CriaeImprimeTunel(&t[2], 67, 3, 66, 3, 'C', 'D', RIGHT, LEFT, '>');
        CriaeImprimeTunel(&t[3], 32, 19, 31, 19, 'D', 'E', RIGHT, LEFT, '>');
        CriaeImprimeTunel(&t[4], 72, 21, 72, 20, 'E', 'A', DOWN, UP, 'V');
    }
}
