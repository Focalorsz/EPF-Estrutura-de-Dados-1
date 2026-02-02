#ifndef structs
#define structs


typedef struct produto{
    int codigo;
    char *nome;
    float preco;
    int quantidade;
    char *descricao;
    struct produto * prox;
} produtos;


typedef struct carrinho_de_compras{
    int produtos;
    struct carrinho_de_compras *proximo_item;
    struct produto * lista_produtos;
}Carrinho;


typedef struct cliente{
    char cpf[12];
    char nome[100];
    char email[100];
    char telefone[15];
    char data_nascimento[11];
    struct carrinho_de_compras *carrinho;
    struct cliente *prox;
} Cliente;



#endif