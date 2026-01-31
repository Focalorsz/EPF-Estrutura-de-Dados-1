#ifndef structs
#define structs

typedef struct carrinho_de_compras{
    int produtos;
    struct carrinho_de_compras *next;
    struct produto * lista_produtos;
}Carrinho;


typedef struct produto{
    int *codigo;
    char *nome;
    float preco;
    int quantidade;
    char *descricao;
    struct registro_produto * prox;
} produtos;




#endif