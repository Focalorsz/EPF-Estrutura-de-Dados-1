#include "carrinho.h"

Carrinho* criarCarrinho(){
    Carrinho *novo = (Carrinho*)malloc(sizeof(Carrinho));
    if (!novo) return NULL;

    novo->itens = NULL;
    novo->total_itens = 0;
    novo->valor_total = 0.0;
    novo->prox = NULL;

    return novo;
}

int adicionarAoCarrinho(Carrinho *carrinho,Produto *produto, int quantidade){
    if(!carrinho || !produto || quantidade <=0) return 0;

    if (produto->quantidade < quantidade) {
        printf("Ta em falta no estoque. Disponivel: %d\n",produto->quantidade);
        return 0;
    }

    ItemCarrinho *atual = carrinho->itens;
    while (atual !=NULL){
        if (atual->produto->codigo == produto->codigo){
            atual->quantidade_desejada += quantidade;
            carrinho->valor_total += produto->preco * quantidade;
            carrinho ->total_itens += quantidade;
            return 1;
        }
        atual = atual->prox;
    }

    ItemCarrinho *novoItem = (ItemCarrinho*)malloc(sizeof(ItemCarrinho));
    if (!novoItem) return 0;

    novoItem->produto = produto;
    novoItem->quantidade_desejada = quantidade;
    carrinho->valor_total += produto->preco * quantidade;

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

void listarCarrinho(Carrinho *carrinho){
    if (!carrinho || !carrinho->itens){
        printf("Carrinho vazio.\n");
        return;
    }

    printf("========================================\n");
    printf("               CARRINHO\n");
    printf("========================================\n");
    printf("%-6s %-25s %-8s %-10s %-10s\n","CÓDIGO", "PRODUTO", "QTD", "PREÇO", "SUBTOTAL");
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
            atual->produto->quantidade -=atual->quantidade_desejada;
            atual = atual ->prox;
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

void menuModoCompra(Cliente **listaClientes, Produto **listaProdutos){
    if (!listaClientes || !listaProdutos) return;

    int opcao;
    Cliente *clienteAtual = NULL;
    Carrinho *carrinhoAtual = NULL;

    do{
        system("clear");
        printf("========================================\n");
        printf("               MODO COMPRA\n");
        printf("========================================\n");

        if(clienteAtual){
            printf("Cliente atual: %s (CPF: %s)\n", clienteAtual->nome,clienteAtual->cpf);
            printf("Itens no carrinho: %d\n",carrinhoAtual ? carrinhoAtual->total_itens : 0);
        }else{
            printf("Nenhum cliente selecionado.\n");
        }

        printf("\n1. Selecionar Cliente\n");
        printf("2. Navegar Produtos\n");
        printf("3. Buscar Produto por Código\n");
        printf("4. Buscar Produto por Nome\n");
        printf("5. Ver Carrinho\n");
        printf("6. Remover Item do Carrinho\n");
        printf("7. Finalizar Compra\n");
        printf("0. Voltar\n");
        printf("========================================\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: {
                char cpf[12];
                printf("CPF do cliente: ");
                scanf("%11s", cpf);
                
                Cliente *atual = *listaClientes;
                while (atual != NULL) {
                    if (strcmp(atual->cpf, cpf) == 0) {
                        clienteAtual = atual;
                        // (Nesse momentos descobrimos que a lógica de carrinho devia cosiderar que ele esta contido em clientes.)
                        carrinhoAtual = criarCarrinho();
                        printf("Cliente selecionado: %s\n", clienteAtual->nome);
                        break;
                    }
                    atual = atual->prox;
                }
                
                if (!clienteAtual) {
                    printf("Cliente não encontrado!\n");
                }
                
                printf("Pressione Enter para continuar...");
                getchar();
                break;
            }
            case 2: {
                if (!clienteAtual) {
                    printf("Selecione um cliente primeiro!\n");
                } else {
                    ProdutoNavegacao *nav = criarListaNavegacao(*listaProdutos);
                    if (nav) {
                        ProdutoNavegacao *atualNav = nav;
                        char comando;
                        
                        do {
                            system("clear");
                            printf("NAVEGAÇÃO - Adicione produtos com 'A'\n");
                            Produto *p = atualNav->produto;
                            printf("\nProduto atual:\n");
                            printf("Código: %d\n", p->codigo);
                            printf("Nome: %s\n", p->nome);
                            printf("Preço: R$ %.2f\n", p->preco);
                            printf("Estoque: %d\n", p->quantidade);
                            
                            printf("\nComandos: [P] Anterior, [N] Próximo, [A] Adicionar, [H] Voltar\n");
                            printf("Comando: ");
                            comando = getchar();
                            getchar();
                            
                            switch(tolower(comando)) {
                                case 'p':
                                    if (atualNav->ant) atualNav = atualNav->ant;
                                    break;
                                case 'n':
                                    if (atualNav->prox) atualNav = atualNav->prox;
                                    break;
                                case 'a': {
                                    int quantidade;
                                    printf("Quantidade: ");
                                    scanf("%d", &quantidade);
                                    getchar();
                                    
                                    if (adicionarAoCarrinho(carrinhoAtual, p, quantidade)) {
                                        printf("Produto adicionado ao carrinho!\n");
                                    }
                                    system("sleep 1");
                                    break;
                                }
                            }
                        } while(tolower(comando) != 'h');
                        
                        // tem que liberar a memória da navegação
                        // (lembrar de implementar função: liberarListaNavegacao)
                    }
                }
                break;
            }
            case 3: {
                if (!clienteAtual) {
                    printf("Selecione um cliente primeiro!\n");
                } else {
                    int codigo, quantidade;
                    printf("Código do produto: ");
                    scanf("%d", &codigo);
                    
                    Produto *p = buscarProdutoPorCodigo(*listaProdutos, codigo);
                    if (p) {
                        printf("Produto: %s (R$ %.2f)\n", p->nome, p->preco);
                        printf("Quantidade: ");
                        scanf("%d", &quantidade);
                        
                        if (adicionarAoCarrinho(carrinhoAtual, p, quantidade)) {
                            printf("Produto adicionado ao carrinho!\n");
                        }
                    } else {
                        printf("Produto não encontrado.\n");
                    }
                }
                printf("Pressione Enter para continuar...");
                getchar();
                getchar();
                break;
            }
            case 4: {
                if (!clienteAtual) {
                    printf("Selecione um cliente primeiro!\n");
                } else {
                    char nome[100];
                    int quantidade;
                    
                    printf("Nome do produto: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    
                    Produto *p = buscarProdutoPorNome(*listaProdutos, nome);
                    if (p) {
                        printf("Produto: %s (R$ %.2f)\n", p->nome, p->preco);
                        printf("Quantidade: ");
                        scanf("%d", &quantidade);
                        
                        if (adicionarAoCarrinho(carrinhoAtual, p, quantidade)) {
                            printf("Produto adicionado ao carrinho!\n");
                        }
                    } else {
                        printf("Produto não encontrado.\n");
                    }
                }
                printf("Pressione Enter para continuar...");
                getchar();
                break;
            }
            case 5:
                if (carrinhoAtual) {
                    listarCarrinho(carrinhoAtual);
                } else {
                    printf("Carrinho vazio.\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 6: {
                if (carrinhoAtual) {
                    int codigo;
                    listarCarrinho(carrinhoAtual);
                    printf("\nCódigo do produto a remover: ");
                    scanf("%d", &codigo);
                    
                    if (removerDoCarrinho(carrinhoAtual, codigo)) {
                        printf("Produto removido do carrinho.\n");
                    }
                } else {
                    printf("Carrinho vazio.\n");
                }
                printf("Pressione Enter para continuar...");
                getchar();
                getchar();
                break;
            }
            case 7:
                if (clienteAtual && carrinhoAtual) {
                    finalizarCompra(carrinhoAtual, clienteAtual);
                } else {
                    printf("Selecione um cliente e adicione produtos ao carrinho primeiro!\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 0:
                if (carrinhoAtual) {
                    liberarCarrinho(carrinhoAtual);
                }
                printf("Voltando ao menu principal...\n");
                break;
        }
    } while(opcao != 0);
}