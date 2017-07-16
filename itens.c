/* Itens devem aparecer em pontos aleat�rios do mapa que n�o estejam j� ocupados por obst�culos, por t�neis, pela cobra ou por outros itens. */

ATRIBUTOS EscolheAtributo(ATRIBUTOS comida, ATRIBUTOS slower, ATRIBUTOS faster, ATRIBUTOS skip){
    int a = numeroAleatorio(0, 99);

    if(a < 3)
        return skip;   /* 3% de chance  */
    else if(a < 13)
        return slower; /* 10% de chance */
    else if(a < 33)
        return faster; /* 20% de chance */
    else
        return comida; /* 67% de chance */
}

/* CriaeImprimeItem:
    Instancia um item numa posi��o aleat�ria, sendo seu tipo determinado pela tabela de probabilidades. */
void CriaeImprimeItem(ITEM *item, ATRIBUTOS comida, ATRIBUTOS slower, ATRIBUTOS faster, ATRIBUTOS skip,
                      char mapa[MAPA_LINHAS][MAPA_COLUNAS+1], TUNEL tuneis[MAX_TUNEIS], COBRA cobra, ITEM itens[MAX_ITEMS]){
    do{
        item->pos.x = numeroAleatorio(X_MIN, X_MAX-1);  // corre��o para n�o gerar
        item->pos.y = numeroAleatorio(Y_MIN, Y_MAX-1);  // itens fora do mapa
    }while(checacolisoes_item(*item, mapa, tuneis, cobra, itens)); /* Repete o la�o at� que o item seja criado numa coordenada vazia. */

    item->atributos = EscolheAtributo(comida, slower, faster, skip);

    putchxy(item->pos.x, item->pos.y, item->atributos.corpo);
}

/* InicializaItens:
    Inicializa um arranjo de itens em posi��es aleat�rias (somente posi��es que estejam livres),
    com seus tipos sendo determinados pela tabela de probabilidades. */
void InicializaItens(OPCOES opcoes, ITEM itens[], ATRIBUTOS comida, ATRIBUTOS slower, ATRIBUTOS faster, ATRIBUTOS skip,
                     char mapa[MAPA_LINHAS][MAPA_COLUNAS+1], TUNEL tuneis[MAX_TUNEIS], COBRA cobra){
    int i;
    for(i = 0; i < opcoes.itens_maximos; i++){
        CriaeImprimeItem(&itens[i], comida, slower, faster, skip, mapa, tuneis, cobra, itens);
    }
}
