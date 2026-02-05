#ifndef CARRINHO_H
#define CARRINHO_H

typedef struct cliente Cliente;
typedef struct produto Produto;

typedef struct item_carrinho {
    Produto *produto;
    int quantidade_desejada;
    struct item_carrinho *prox;
} ItemCarrinho;

typedef struct carrinho {
    ItemCarrinho *itens;
    int total_itens;
    float valor_total;
} Carrinho;

Carrinho* criarCarrinho();
void liberarCarrinho(Carrinho *carrinho);
int adicionarAoCarrinho(Carrinho *carrinho, Produto *produto, int quantidade);
int removerDoCarrinho(Carrinho *carrinho, int codigoProduto);
void listarCarrinho(Carrinho *carrinho);
int finalizarCompra(Carrinho *carrinho, Cliente *cliente);
void menuModoCompra(Cliente **listaClientes, Produto **listaProdutos);

#endif