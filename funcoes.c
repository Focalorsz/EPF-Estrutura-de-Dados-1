#include "funcoes.h"

void imprime (produtos * Lista_Encadeada_Produtos){
    if (Lista_Encadeada_Produtos != NULL){
        printf("%d\n", *(Lista_Encadeada_Produtos->codigo));
        printf("%s\n", Lista_Encadeada_Produtos->nome);
        printf("%2f\n", Lista_Encadeada_Produtos->preco);
        printf("%d\n", Lista_Encadeada_Produtos->quantidade);
        printf("%s\n", Lista_Encadeada_Produtos->descricao);
    }
}

void main(){
    return 0;
}