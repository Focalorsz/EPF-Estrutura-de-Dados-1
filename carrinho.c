#include "portabilidade.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "carrinho.h"
#include "produtos.h" 
#include "clientes.h"


Carrinho* criarCarrinho(){
    Carrinho *novo = (Carrinho*)malloc(sizeof(Carrinho));
    if (!novo) return NULL;

    novo->itens = NULL;
    novo->total_itens = 0;
    novo->valor_total = 0.0;

    return novo;
}

int adicionarAoCarrinho(Carrinho *carrinho, Produto *produto, int quantidade) {
    if(!carrinho || !produto || quantidade <= 0) return 0;
    
    if (produto->quantidade < quantidade) {
        printf("Estoque insuficiente. Disponível: %d\n", produto->quantidade);
        return 0;
    }
    
    ItemCarrinho *atual = carrinho->itens;
    while (atual != NULL) {
        if (atual->produto->codigo == produto->codigo) {
            atual->quantidade_desejada += quantidade;
            carrinho->valor_total += produto->preco * quantidade;
            carrinho->total_itens += quantidade;
            return 1;
        }
        atual = atual->prox;
    }
    
    ItemCarrinho *novoItem = (ItemCarrinho*)malloc(sizeof(ItemCarrinho));
    if (!novoItem) return 0;
    
    novoItem->produto = produto;
    novoItem->quantidade_desejada = quantidade;
    novoItem->prox = carrinho->itens;  
    carrinho->itens = novoItem;
    carrinho->valor_total += produto->preco * quantidade;
    carrinho->total_itens += quantidade;
    
    return 1;
}

int removerDoCarrinho(Carrinho* carrinho, int codigoProduto) {
    if (!carrinho || !carrinho->itens) return 0;

    ItemCarrinho *anterior = NULL;
    ItemCarrinho *atual = carrinho->itens;

    if(atual->produto->codigo == codigoProduto) {
        carrinho->valor_total -= atual->produto->preco * atual->quantidade_desejada;
        carrinho->total_itens -= atual->quantidade_desejada;
        carrinho->itens = atual->prox;
        free(atual);
        return 1;
    }

    while (atual != NULL && atual->produto->codigo != codigoProduto){
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL){
        printf("Produto nao encontrado no carrinho.\n");
        return 0;
    }

    anterior->prox = atual->prox;
    carrinho->valor_total -= atual->produto->preco * atual->quantidade_desejada;
    carrinho->total_itens -= atual->quantidade_desejada;
    free(atual);

    return 1;
}

static Produto* selecionarProdutoPorNome(Produto *listaProdutos) {
    char nome[100];
    printf("\n  Nome do produto: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    Produto *atual = listaProdutos;
    Produto *encontrados[100];
    int count = 0;
    
    while (atual != NULL && count < 100) {
        if (atual->nome && strcasestr(atual->nome, nome) != NULL) {
            encontrados[count++] = atual;
        }
        atual = atual->prox;
    }
    
    if (count == 0) {
        printf("\n  ❌ Nenhum produto encontrado.\n");
        return NULL;
    }
    
    if (count == 1) {
        printf("\n  Produto encontrado: %s (R$ %.2f)\n", 
               encontrados[0]->nome, encontrados[0]->preco);
        return encontrados[0];
    }
    
    printf("\n   Foram encontrados %d produtos:\n", count);
    for (int i = 0; i < count; i++) {
        printf("  %d. Código: %d - %s (R$ %.2f)\n", 
               i+1, encontrados[i]->codigo, 
               encontrados[i]->nome, encontrados[i]->preco);
    }
    
    printf("\n  Escolha pelo número (1-%d) ou 0 para cancelar: ", count);
    int escolha;
    scanf("%d", &escolha);
    getchar();
    
    if (escolha < 1 || escolha > count) {
        printf("\n  ❌ Seleção cancelada.\n");
        return NULL;
    }
    
    return encontrados[escolha-1];
}

void listarCarrinho(Carrinho *carrinho){
    if (!carrinho || !carrinho->itens){
        printf("Carrinho vazio.\n");
        return;
    }

    printf("========================================\n");
    printf("               CARRINHO\n");
    printf("========================================\n");
    printf("%-6s %-25s %-8s %-10s %-10s\n","CODIGO", "PRODUTO", "QTD", "PREÇO", "SUBTOTAL");
    printf("----------------------------------------\n");

    ItemCarrinho *atual = carrinho->itens;
    while (atual != NULL) {
        Produto *p = atual->produto;
        float subtotal = p->preco * atual->quantidade_desejada;

        printf("%-6d %-25s %-8d R$%-9.2f R$%-9.2f\n",
            p->codigo,
            p->nome,
            atual->quantidade_desejada,
            p->preco,
            subtotal);
        
        atual = atual->prox;
        }
        printf("----------------------------------------\n");
        printf("Total de itens: %d\n", carrinho->total_itens);
        printf("Valor total: R$ %.2f\n", carrinho->valor_total);
    }

int finalizarCompra(Carrinho *carrinho, Cliente * cliente){
    if(!carrinho || !carrinho->itens){
        printf("Carrinho vazio!\n");
        return 0;
    }
    printf("========================================\n");
    printf("           FINALIZAR COMPRA\n");
    printf("========================================\n");
    printf("Cliente: %s\n", cliente->nome);
    printf("CPF: %s\n", cliente->cpf);

    listarCarrinho(carrinho);

    printf("\nConfirmar compra? (S/N): ");
    char confirmacao;
    scanf(" %c",&confirmacao);

     if (tolower(confirmacao) == 's'){
        ItemCarrinho *atual = carrinho->itens;
        while (atual != NULL){
            if(atual->produto->quantidade < atual->quantidade_desejada) {
                printf("Erro: Estoque insuficiente para %s\n", atual->produto->nome);
                return 0;
            }
            atual = atual->prox;
        }
        
        atual = carrinho->itens;
        while (atual != NULL){
            atual->produto->quantidade -= atual->quantidade_desejada;
            atual = atual->prox;
        }

        printf("Compra finalizada com sucesso!\n");

        ItemCarrinho *item = carrinho->itens;
        while (item != NULL){
            ItemCarrinho *prox = item->prox;
            free(item);
            item = prox;
        }

        carrinho->itens = NULL;
        carrinho->total_itens=0;
        carrinho->valor_total = 0.0;

        return 1;
    }

    printf("Compra cancelada.\n");
    return 0;
}

void menuModoCompra(Cliente **listaClientes, Produto **listaProdutos) {
    if (!listaClientes || !listaProdutos) return;

    int opcao;
    Cliente *clienteAtual = NULL;

    do {
        clear_screen();
        printf("\n╔═══════════════════════════════════════════════╗\n");
        printf("║                 MODO COMPRA                   ║\n");
        printf("╠═══════════════════════════════════════════════╣\n");
        
        if (clienteAtual) {
            printf("║  Cliente atual: %-29s ║\n", clienteAtual->nome);
            printf("║  CPF: %-36s ║\n", clienteAtual->cpf);
            printf("║  Itens no carrinho: %-29d ║\n", 
                   clienteAtual->carrinho ? clienteAtual->carrinho->total_itens : 0);
        } else {
            printf("║           Nenhum cliente selecionado          ║\n");
        }
        
        printf("╠═══════════════════════════════════════════════╣\n");
        printf("║  1. Selecionar Cliente                        ║\n");
        printf("║  2. Navegar Produtos                          ║\n");
        printf("║  3. Buscar Produto por Código                 ║\n");
        printf("║  4. Buscar Produto por Nome                   ║\n");
        printf("║  5. Ver Carrinho                              ║\n");
        printf("║  6. Remover Item do Carrinho                  ║\n");
        printf("║  7. Finalizar Compra                          ║\n");
        printf("║  0. Voltar ao Menu Principal                  ║\n");
        printf("╚═══════════════════════════════════════════════╝\n");
        printf("\n  Opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (opcao) {
            case 1: {
                char cpf[12];
                printf("\n  CPF do cliente: ");
                scanf("%11s", cpf);
                getchar();
                
                Cliente *atual = *listaClientes;
                int encontrado = 0;
                
                while (atual != NULL) {
                    if (strcmp(atual->cpf, cpf) == 0) {
                        clienteAtual = atual;
                        printf("\n  Cliente selecionado: %s\n", clienteAtual->nome);
                        encontrado = 1;
                        break;
                    }
                    atual = atual->prox;
                }
                
                if (!encontrado) {
                    printf("\n  Cliente não encontrado!\n");
                }
                
                printf("\n  Pressione Enter para continuar...");
                getchar();
                break;
            }
            
            case 2: {
                if (!clienteAtual) {
                    printf("\n   Selecione um cliente primeiro!\n");
                } else {
                    ProdutoNavegacao *nav = criarListaNavegacao(*listaProdutos);
                    if (nav) {
                        ProdutoNavegacao *atualNav = nav;
                        char comando;
                        
                        do {
                            clear_screen();
                            printf("╔═══════════════════════════════════════════════╗\n");
                            printf("║        NAVEGAÇÃO DE PRODUTOS                  ║\n");
                            printf("╠═══════════════════════════════════════════════╣\n");
                            printf("║  Código: %-36d ║\n", atualNav->produto->codigo);
                            printf("║  Nome: %-38s ║\n", atualNav->produto->nome);
                            printf("║  Preço: R$ %-33.2f ║\n", atualNav->produto->preco);
                            printf("║  Estoque: %-35d ║\n", atualNav->produto->quantidade);
                            printf("╠═══════════════════════════════════════════════╣\n");
                            printf("║  Comandos:                                   ║\n");
                            printf("║  [P] Anterior   [N] Próximo                  ║\n");
                            printf("║  [A] Adicionar  [H] Voltar                   ║\n");
                            printf("╚═══════════════════════════════════════════════╝\n");
                            printf("\n  Comando: ");
                            
                            comando = getchar();
                            getchar();
                            
                            switch (tolower(comando)) {
                                case 'p':
                                    if (atualNav->ant) {
                                        atualNav = atualNav->ant;
                                    } else {
                                        printf("\n   Primeiro produto da lista.\n");
                                        delay(1);
                                    }
                                    break;
                                    
                                case 'n':
                                    if (atualNav->prox) {
                                        atualNav = atualNav->prox;
                                    } else {
                                        printf("\n   Último produto da lista.\n");
                                        delay(1);
                                    }
                                    break;
                                    
                                case 'a': {
                                    int quantidade;
                                    printf("\n  Quantidade (0 para cancelar): ");
                                    
                                    char input[10];
                                    fgets(input, sizeof(input), stdin);
                                    
                                    if (sscanf(input, "%d", &quantidade) == 1) {
                                        if (quantidade > 0) {
                                            if (adicionarAoCarrinho(clienteAtual->carrinho, 
                                                                atualNav->produto, 
                                                                quantidade)) {
                                                printf("\n  Produto adicionado ao carrinho!\n");
                                                delay(1);
                                            } else {
                                                printf("\n  Não foi possível adicionar.\n");
                                                delay(1);
                                            }
                                        } else if (quantidade == 0) {
                                            printf("\n  Operação cancelada.\n");
                                            delay(1);
                                        } else {
                                            printf("\n  Quantidade inválida!\n");
                                            delay(1);
                                        }
                                    } else {
                                        printf("\n  Entrada inválida!\n");
                                        delay(1);
                                    }
                                    break;
                                }
                                
                                case 'h':
                                    printf("\n  Voltando ao menu de compra...\n");
                                    delay(1);
                                    break;
                                    
                                default:
                                    printf("\n  Comando inválido! Use P, N, A ou H.\n");
                                    delay(1);
                                    break;
                            }
                        } while (tolower(comando) != 'h');
                        
                        liberarListaNavegacao(&nav);
                    }
                }
                printf("\n  Pressione Enter para continuar...");
                getchar();
                break;
            }  
            
            case 3: {
                if (!clienteAtual) {
                    printf("\n   Selecione um cliente primeiro!\n");
                } else {
                    int codigo, quantidade;
                    printf("\n  Código do produto: ");
                    scanf("%d", &codigo);
                    getchar();
                    
                    Produto *p = buscarProdutoPorCodigo(*listaProdutos, codigo);
                    if (p) {
                        printf("\n  Produto encontrado: %s (R$ %.2f)\n", p->nome, p->preco);
                        printf("  Quantidade: ");
                        scanf("%d", &quantidade);
                        getchar();
                        
                        if (adicionarAoCarrinho(clienteAtual->carrinho, p, quantidade)) {
                            printf("\n  ✅ Produto adicionado ao carrinho!\n");
                        }
                    } else {
                        printf("\n  Produto não encontrado.\n");
                    }
                }
                printf("\n  Pressione Enter para continuar...");
                getchar();
                break;
            }
            
            case 4: {
                if (!clienteAtual) {
                    printf("\n   Selecione um cliente primeiro!\n");
                } else {
                    Produto *p = selecionarProdutoPorNome(*listaProdutos);
                    if (p) {
                        int quantidade;
                        printf("  Quantidade: ");
                        scanf("%d", &quantidade);
                        getchar();
                        
                        if (adicionarAoCarrinho(clienteAtual->carrinho, p, quantidade)) {
                            printf("\n  Produto adicionado ao carrinho!\n");
                        }
                    }
                }
                printf("\n  Pressione Enter para continuar...");
                getchar();
                break;
            }
            
            case 5:
                if (clienteAtual && clienteAtual->carrinho) {
                    listarCarrinho(clienteAtual->carrinho);
                } else {
                    printf("\n  Carrinho vazio.\n");
                }
                printf("\n  Pressione Enter para continuar...");
                getchar();
                break;
                
            case 6: {
                if (clienteAtual && clienteAtual->carrinho) {
                    int codigo;
                    listarCarrinho(clienteAtual->carrinho);
                    printf("\n  Código do produto a remover: ");
                    scanf("%d", &codigo);
                    getchar();
                    
                    if (removerDoCarrinho(clienteAtual->carrinho, codigo)) {
                        printf("\n   Produto removido do carrinho.\n");
                    }
                } else {
                    printf("\n   Carrinho vazio.\n");
                }
                printf("\n  Pressione Enter para continuar...");
                getchar();
                break;
            }
            
            case 7:
                if (clienteAtual && clienteAtual->carrinho) {
                    finalizarCompra(clienteAtual->carrinho, clienteAtual);
                } else {
                    printf("\n   Selecione um cliente e adicione produtos primeiro!\n");
                }
                printf("\n  Pressione Enter para continuar...");
                getchar();
                break;
                
            case 0:
                printf("\n  🔙 Voltando ao menu principal...\n");
                delay(1);
                break;
                
            default:
                printf("\n  ❌ Opção inválida!\n");
                delay(1);
                break;
        }
    } while (opcao != 0);
}

void liberarCarrinho(Carrinho *carrinho) {
    if (carrinho == NULL) return;

    ItemCarrinho *atual = carrinho->itens;
    while (atual != NULL) {
        ItemCarrinho *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    free(carrinho);
}