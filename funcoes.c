#include "funcoes.h"

void menuGerenciarClientes(){
    int opcao = -1;

    do {
        system("clear"); 
        printf("----------------- GESTAO DE CLIENTES -----------------\n");
        printf("* (1) Cadastrar Cliente                   *\n");
        printf("* (2) Listar Clientes                     *\n");
        printf("* (3) Buscar Cliente (CPF)                *\n");
        printf("* (4) Editar Cliente                      *\n");
        printf("* (5) Excluir Cliente                     *\n");
        printf("* (0) Voltar ao Menu Principal            *\n");
        printf("------------------------------------------------------\n");
        printf(":: Digite a opcao desejada --> ");
        
       
        if (scanf("%d", &opcao) != 1) {
            printf("Erro: Digite apenas numeros!\n");
            while (getchar() != '\n'); 
            sleep(1);
            continue;
        }

        switch(opcao) {
            case 1:
                cadastrarCliente(&listaClientes);
                break;

            case 2:
                listarClientes(listaClientes);
                break;

            case 3:
                printf("Digite o CPF para busca: ");
                char cpfBusca[12];
                scanf("%s", cpfBusca);
                buscarCliente(listaClientes, cpfBusca);
                break;

            case 4:
                editarCliente(listaClientes);
                break;

            case 5:
                removerCliente(&listaClientes);
                break;

            case 0:
                printf("\nSaindo do modulo de clientes...\n");
                sleep(1);
                break;

            default:
                printf("\nOpcao Invalida! Tente novamente.\n");
                sleep(1);
                break;
        }

    } while(opcao != 0);
}
    
produtos * reserva_celula_cabeca() {
    produtos * Lista_Encadeada_Produtos;
    Lista_Encadeada_Produtos = calloc(1,sizeof(produtos));
    Lista_Encadeada_Produtos->prox = NULL;

    return Lista_Encadeada_Produtos;
}

void listar_produtos (produtos * Lista_Encadeada_Produtos){
    produtos *ponteiro_auxiliar;
    for(ponteiro_auxiliar = Lista_Encadeada_Produtos->prox;ponteiro_auxiliar!= NULL; ponteiro_auxiliar = ponteiro_auxiliar->prox){
        printf("%d\n", ponteiro_auxiliar->codigo);
        printf("%s\n", ponteiro_auxiliar->nome);
        printf("%2f\n", ponteiro_auxiliar->preco);
        printf("%d\n", ponteiro_auxiliar->quantidade);
        printf("%s\n", ponteiro_auxiliar->descricao);
    }
}

produtos * busca_codigo(int cod, produtos * Lista_Encadeada_Produtos){
    if(Lista_Encadeada_Produtos->prox == NULL) return NULL;
    if(Lista_Encadeada_Produtos->codigo==cod) return Lista_Encadeada_Produtos;
    return busca_codigo(cod, Lista_Encadeada_Produtos->prox);
}

produtos * busca_nome(char * palavra_chave, produtos * Lista_Encadeada_Produtos){
    if (palavra_chave == NULL || Lista_Encadeada_Produtos->prox == NULL) {
        return NULL;
    }
    produtos * ponteiro_auxiliar = Lista_Encadeada_Produtos->prox;
    while(ponteiro_auxiliar!=NULL){
    if(palavra_chave!=NULL && strstr(ponteiro_auxiliar->nome,palavra_chave)!=NULL){
        return ponteiro_auxiliar;
        }
    
        ponteiro_auxiliar=ponteiro_auxiliar->prox;
    }
    return NULL;
}

void adicionar_produto (int codi,char *nome,float preco,int quant,char *desc, produtos * Lista_Encadeada_Produtos){
    produtos * novo_produto;
    novo_produto = calloc(1,sizeof(produtos));
    novo_produto->codigo = codi;
    novo_produto->nome = nome;
    novo_produto->preco = preco;
    novo_produto->quantidade = quant;
    novo_produto->descricao = desc;
    novo_produto->prox = Lista_Encadeada_Produtos->prox;
    Lista_Encadeada_Produtos->prox = novo_produto;

}

void remove_por_codigo(int cod,produtos * Lista_Encadeada_Produtos){
    produtos * celula_removida,* celula_seguinte;
    celula_seguinte = Lista_Encadeada_Produtos;
    celula_removida = Lista_Encadeada_Produtos->prox;

    while (celula_removida!=NULL && celula_removida->codigo != cod){
        celula_seguinte = celula_removida;
        celula_removida = celula_removida->prox;
    }
    if(celula_removida != NULL){
        celula_seguinte->prox=celula_removida->prox;
        free(celula_removida);
    }
}

void remove_por_nome(char palavra_chave,produtos * Lista_Encadeada_Produtos){
    produtos * celula_removida,* celula_seguinte;
    celula_seguinte = Lista_Encadeada_Produtos;
    celula_removida = Lista_Encadeada_Produtos->prox;

    while (celula_removida!=NULL && strcmp(celula_removida->nome,palavra_chave)!=NULL){
        celula_seguinte = celula_removida;
        celula_removida = celula_removida->prox;
    }
    if(celula_removida != NULL){
        celula_seguinte->prox=celula_removida->prox;
        free(celula_removida);
    }
}

void cadastrarCliente(Cliente **lista){

    Cliente *novo = (Cliente *) malloc(sizeof(Cliente));

    if(novo == NULL){
        printf("Erro: Falha na alocação da memória!\n");
        sleep(2);
        return;
    }

    system("clear");
    printf("---------- CADASTRO DE CLIENTE ----------\n");
    
    getchar(); //limpa '\n' do scanf
    scanf("Nome completo: ");
    scanf("%[^\n]", novo -> nome);
    getchar();

    printf("CPF (apenas números): ");
    scanf("%[^\n]", novo->cpf);
    getchar();

    printf("E-mail: ");
    scanf("%[^\n]", novo->email);
    getchar();

    printf("Telefone: ");
    scanf("%[^\n]", novo->telefone);

    novo->prox = *lista;
    *lista = novo;

    printf("\nCliente cadastrado com sucesso!\n");
    sleep(1);
}

void menuPrincipal(Cliente **listaClientes) {
    int opcao = -1;
    Cliente *listaClientes = NULL; 

    do {
        system("clear");
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
                
                break;
            case 3:
                
                break;
            case 0:
                printf("\nEncerrando sistema...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                sleep(1);
        }
    } while(opcao != 0);
}
