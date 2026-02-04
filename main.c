#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "produtos.h"
#include "carrinho.h"



int main() {
    Cliente *listaClientes = NULL;
    Produto *listaProdutos = NULL;

    int opcao = -1;
    do {
        system("cls");
        printf("----------------- SISTEMA DE VENDAS -----------------\n");
        printf("* (1) Gerenciamento de Clientes                    *\n");
        printf("* (2) Gerenciamento de Produtos                    *\n");
        printf("* (3) Modo Compra                                  *\n");
        printf("* (0) Sair                                         *\n");
        printf("-----------------------------------------------------\n");
        printf(":: Escolha o modulo --> ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch(opcao) {
            case 1:
                menuGerenciarClientes(&listaClientes); 
                break;
            case 2:
                menuGerenciarProdutos(&listaProdutos);
                break;
            case 3:
                menuModoCompra(&listaClientes, &listaProdutos);
                break;
            case 0:
                printf("\nEncerrando sistema...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                sleep(1);
        }
    } while(opcao != 0);



    liberarTodosProdutos(&listaProdutos);
    return 0;
}