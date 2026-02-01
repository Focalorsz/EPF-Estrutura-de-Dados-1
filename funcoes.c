#include "funcoes.h"

void imprime (produtos * Lista_Encadeada_Produtos){
    if (Lista_Encadeada_Produtos != NULL){
        printf("%d\n", *(Lista_Encadeada_Produtos->codigo));
        printf("%s\n", Lista_Encadeada_Produtos->nome);
        printf("%2f\n", Lista_Encadeada_Produtos->preco);
        printf("%d\n", Lista_Encadeada_Produtos->quantidade);
        printf("%s\n", Lista_Encadeada_Produtos->descricao);
    }
}

int main(){
    Cliente *listaClientes = NULL;
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

    return 0;
}
    
    