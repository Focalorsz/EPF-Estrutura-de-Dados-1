#include "produtos.h"
#include <ctype.h>
#include <string.h> 

static int proximoCodigo = 1;

Produto* criarListaProdutos() {
    return NULL;
}

int adicionarProduto(Produto **lista, char *nome,float preco, int quantidade){
    if (!nome || strlen(nome) == 0) {
        printf("Nome do produto invalido!\n");
        return 0;
    }
    if (preco<0) {
        printf("Preco nao pode ser negativo!\n");
        return 0;
    }
    if (quantidade <0) {
        printf("Quantidade nao pode ser negativa!\n");
        return 0;
    }

    Produto *novo = (Produto*)malloc(sizeof(Produto));
    if (!novo) {
        printf("falha na alocacao de memoria!\n");
        return 0;
    }
    novo->codigo = proximoCodigo++;
    novo->nome = strdup(nome);
    novo->preco = preco;
    novo->quantidade = quantidade;
    novo->prox = NULL;

    if (*lista == NULL){
        *lista = novo;
    } else{
        Produto *atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox=novo;
    }
    printf("Produto devidamente cadastrado. Codigo: %d\n",novo->codigo);
    return 1;
}

int removerProdutoPorCodigo(Produto **lista, int codigo) {
    if (*lista == NULL) {
        printf("Lista de produtos vazia!\n");
        return 0;
    }    

    Produto *anterior = NULL;
    Produto *atual = *lista;

    if (atual != NULL && atual->codigo == codigo){
        *lista = atual->prox;
        printf("Produto: %s (codigo: %d)\n",atual->nome,atual->codigo);
        free(atual->nome);
        free(atual);
        return 1;
    }

    while (atual !=NULL && atual->codigo != codigo) {
        anterior = atual;
        atual= atual->prox;
    }

    if (atual == NULL){
        printf("Produto com codigo %d nao encontrado!\n",codigo);
        return 0;
    }

    anterior->prox = atual->prox;
    printf("Produto removido: %s (Codigo: %d)\n", atual->nome, atual->codigo);
    free(atual->nome);
    free(atual);
    return 1;
}

Produto* buscarProdutoPorCodigo(Produto *lista, int codigo) {
    Produto *atual = lista;

    while (atual != NULL) {
        if (atual->codigo == codigo) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

Produto* buscarProdutoPorNome(Produto *lista, char *nome){
    if (!nome || lista == NULL) return NULL;

    Produto *atual = lista;

    while (atual != NULL){
        if (atual->nome && strstr(atual->nome,nome)!= NULL) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void listarTodosProdutos(Produto *lista){
    if (lista == NULL) {
        printf("Nenhum produto cadastrado. \n");
        return;
    } 

    printf("╔──────────────────────────────────────────╗\n");
    printf("│                  『Lista de Produtos』         │\n");
    printf("│───────────────────────────────────────────│\n");
    printf("%-6s %-30s %-10s %-10s\n", "CODIGO","NOME", "PRECO", "ESTOQUE");
    printf("│───────────────────────────────────────────│\n");

    Produto *atual = lista;
    int contador = 0;

    while (atual != NULL){
        printf("%-6d %-30s R$%-9.2f %-10d\n",
        atual->codigo,
        atual->nome,
        atual->preco,
        atual->quantidade);
        atual = atual->prox;
        contador++;
    }

    printf("╚──────────────────────────────────────────╝\n");
    printf("Total de produtos: %d\n",contador);
}

void editarProduto(Produto *produto){
    if (!produto){
        printf("produto invalido!\n");
        return;
    }

    char buffer[100];
    float novoPreco;
    int novaQuantidade;

    printf("Editando Produto: %s (Codigo: %d)\n",produto->nome, produto->codigo);
    printf("│───────────────────────────────────────────│\n");

    printf("Novo nome (atual: %s): ", produto->nome);
    fgets(buffer,sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0){
        free(produto->nome);
        produto->nome = strdup(buffer);
    }

printf("Novo preco (atual: %.2f): ",produto->preco);
if (scanf("%f",&novoPreco) == 1 && novoPreco >= 0) {
    produto->preco = novoPreco;
}
getchar();

printf("Nova quantidade (atual: %d): ",produto->quantidade);
if (scanf("%d",&novaQuantidade) == 1 && novaQuantidade >=0){
    produto->quantidade = novaQuantidade;
}
getchar();

printf("Produto atualizado com sucesso!\n");
}

int atualizarEstoqueProduto(Produto *produto,int novaQuantidade){
    if (!produto) return 0;
    if (novaQuantidade < 0) return 0;

    produto->quantidade = novaQuantidade;
    return 1;
}

void liberarTodosProdutos(Produto **lista){
    Produto *atual = *lista;
    Produto *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        free(atual->nome);
        free(atual);
        atual = proximo;
    }
    *lista = NULL;
}

ProdutoNavegacao* criarListaNavegacao(Produto *listaProdutos){
    if (!listaProdutos) return NULL;

    ProdutoNavegacao *cabeca = NULL;
    ProdutoNavegacao *ultimo = NULL;
    Produto *atual = listaProdutos;

    while (atual!= NULL){
        ProdutoNavegacao *novo = (ProdutoNavegacao*)malloc(sizeof(ProdutoNavegacao));
        novo->produto = atual;
        novo->ant = ultimo;
        novo->prox = NULL;

        if (ultimo) {
            ultimo->prox = novo;
        }
        
        if (!cabeca){
            cabeca=novo;
        }

ultimo = novo;
atual = atual->prox;
    }
    return cabeca;
}

void navegarProdutos(ProdutoNavegacao *navegacao){
    if (!navegacao){
        printf("Nenhum produto disponivel para navegacao.\n");
        return;
    }

ProdutoNavegacao *atual = navegacao;
char comando;

do{
    system("cls");
    printf("╔──────────────────────────────────────────╗\n");
    printf("│           『Navegacao de Produtos』        │");
    printf("╚──────────────────────────────────────────╝\n");

    Produto *p = atual->produto;
    printf("Codigo: %d\n", p->codigo);
    printf("Nome: %s\n",p->nome);
    printf("Preco: R$ %.2f\n",p->preco);
    printf("Estoque: %d unidades\n", p->quantidade);

    printf("\nComandos:\n");
    printf("[P] Produto anterior\n");
    printf("[N] Proximo produto\n");
    printf("[A] Adicionar ao carrinho\n");
    printf("[H] Voltar ao menu\n");
    printf("╚──────────────────────────────────────────╝\n");
    printf("Comando: ");

    comando = getchar();
    getchar();

    switch(tolower(comando)){
        case 'p':
            if (atual->ant){
                atual = atual->ant;
            } else{
                printf("Primeiro produto da lista.\n");
                system("sleep 2");
            }
            break;
            case 'n':
                if (atual->prox){
                    atual = atual->prox;
                } else{
                    printf("Ultimo produto da lista.\n");
                    system("sleep 2");
            }
            break;
            case 'a':
            printf("Adicionando ao carrinho...\n");
            system("sleep 2");
            break;
            case 'h':
            printf("Voltando ao menu...\n");
            break;
            default:
            printf("Comando invalido\n");
            system("sleep 2");
                }
    }while (tolower(comando) != 'h');
}   

void menuGerenciarProdutos(Produto **lista) {
    int opcao;

    do {
        system("cls");
        printf("========================================\n");
        printf("       GERENCIAMENTO DE PRODUTOS\n");
        printf("========================================\n");
        printf("1. Cadastrar Novo Produto\n");
        printf("2. Listar Todos os Produtos\n");
        printf("3. Buscar Produto por Codigo\n");
        printf("4. Buscar Produto por Nome\n");
        printf("5. Editar Produto\n");
        printf("6. Remover Produto\n");
        printf("7. Navegar Produtos (Modo Visual)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("========================================\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();
        
        switch(opcao) {
            case 1: {
                char nome[100];
                float preco;
                int quantidade;
                
                printf("Nome do produto: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                printf("Preço: ");
                scanf("%f", &preco);
                
                printf("Quantidade em estoque: ");
                scanf("%d", &quantidade);
                getchar();
                
                adicionarProduto(lista, nome, preco, quantidade);
                printf("Pressione Enter para continuar...");
                getchar();
                break;
            }
            case 2:
                listarTodosProdutos(*lista);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 3: {
                int codigo;
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                getchar();
                
                Produto *p = buscarProdutoPorCodigo(*lista, codigo);
                if (p) {
                    printf("\nProduto encontrado:\n");
                    printf("Codigo: %d\n", p->codigo);
                    printf("Nome: %s\n", p->nome);
                    printf("Preço: R$ %.2f\n", p->preco);
                    printf("Estoque: %d\n", p->quantidade);
                } else {
                    printf("Produto nao encontrado.\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            }
            case 4: {
                char nome[100];
                printf("Nome (ou parte) do produto: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                Produto *p = buscarProdutoPorNome(*lista, nome);
                if (p) {
                    printf("\nProduto encontrado:\n");
                    printf("Codigo: %d\n", p->codigo);
                    printf("Nome: %s\n", p->nome);
                    printf("Preço: R$ %.2f\n", p->preco);
                    printf("Estoque: %d\n", p->quantidade);
                } else {
                    printf("Produto nao encontrado.\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            }
            case 5: {
                int codigo;
                printf("Codigo do produto a editar: ");
                scanf("%d", &codigo);
                getchar();
                
                Produto *p = buscarProdutoPorCodigo(*lista, codigo);
                if (p) {
                    editarProduto(p);
                } else {
                    printf("Produto nao encontrado.\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            }
            case 6: {
                int codigo;
                printf("Codigo do produto a remover: ");
                scanf("%d", &codigo);
                getchar();
                
                removerProdutoPorCodigo(lista, codigo);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            }
            case 7: {
                ProdutoNavegacao *nav = criarListaNavegacao(*lista);
                navegarProdutos(nav);
                break;
            }
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcaoo invalida!\n");
                system("sleep 2");
        }
    } while(opcao != 0);
}