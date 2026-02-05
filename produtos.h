#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produto{
    int codigo;
    char *nome;
    float preco;
    int quantidade;
    struct produto *prox;
} Produto;

typedef struct produto_navegacao{
    Produto *produto;
    struct produto_navegacao *ant;
    struct produto_navegacao *prox;
}ProdutoNavegacao;

Produto * criarListaProdutos();
void liberarTodosProdutos(Produto **lista);

int adicionarProduto(Produto **lista, char *nome, float preco, int quantidade);
int removerProdutoPorCodigo(Produto **lista, int codigo);
Produto* buscarProdutoPorCodigo(Produto *lista, int codigo);
Produto* buscarProdutoPorNome(Produto *lista, char *nome);
void listarTodosProdutos(Produto *lista);
void editarProduto(Produto *produto);
int atualizarEstoqueProduto(Produto *produto, int novaQuantidade);

ProdutoNavegacao* criarListaNavegacao(Produto *listaProdutos);
void liberarListaNavegacao(ProdutoNavegacao **lista);
void navegarProdutos(ProdutoNavegacao *navegacao);

void menuGerenciarProdutos(Produto **lista);

#endif