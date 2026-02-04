#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "produtos.h"
#include "carrinho.h"



int main() {
    Cliente *listaClientes = NULL;
    Produto *listaProdutos = NULL;

    menuPrincipal(&listaClientes);

    liberarTodosProdutos(&listaProdutos);
    return 0;
}