#include "clientes.h"

void menuGerenciarClientes(Cliente **listaClientes){
    int opcao = -1;

    do {
        system("cls"); 
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
                cadastrarCliente(listaClientes);
                break;

            case 2:
                listarClientes(*listaClientes);
                break;

            case 3:
                printf("Digite o CPF para busca: ");
                char cpfBusca[12];
                scanf("%s", cpfBusca);
                buscarCliente(*listaClientes, cpfBusca);
                break;

            case 4:
                editarCliente(*listaClientes);
                break;

            case 5:
                removerCliente(listaClientes);
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

void cadastrarCliente(Cliente **lista){

    Cliente *novo = (Cliente *) malloc(sizeof(Cliente));

    if(novo == NULL){
        printf("Erro: Falha na alocacao da memoria!\n");
        sleep(2);
        return;
    }

    system("cls");
    printf("---------- CADASTRO DE CLIENTE ----------\n");
    
    getchar(); //limpa '\n' do scanf
    printf("Nome completo: ");
    scanf(" %[^\n]", novo -> nome);
    getchar();

    printf("Digite a data de nascimento (DD/MM/AAAA): ");
    scanf(" %[^\n]", novo->data_nascimento);
    getchar();

    printf("CPF (apenas numeros): ");
    scanf(" %[^\n]", novo->cpf);
    getchar();

    printf("E-mail: ");
    scanf(" %[^\n]", novo->email);
    getchar();

    printf("Telefone: ");
    scanf(" %[^\n]", novo->telefone);

    novo->prox = *lista;
    *lista = novo;

    printf("\nCliente cadastrado com sucesso!\n");
    sleep(1);
}

void listarClientes(Cliente *lista) {
    Cliente *atual = lista; 
    system("cls");
    printf("----------------- LISTA DE CLIENTES -----------------\n");

    if (atual == NULL) {
        printf("Nenhum cliente cadastrado no momento.\n");
    } else {
        while (atual != NULL) {
            printf("Nome: %s\n", atual->nome);
            printf("Data de Nascimento: %s\n", atual->data_nascimento);
            printf("CPF: %s\n", atual->cpf);
            printf("E-mail: %s\n", atual->email);
            printf("Telefone: %s\n", atual->telefone);
            printf("----------------------------------------------------\n");
            
            atual = atual->prox; 
        }
    }

    printf("\nPressione Enter para voltar ao menu...");
    getchar(); 
    getchar();
}

void buscarCliente(Cliente *lista, char cpf[]) {
    Cliente *atual = lista;
    int encontrado = 0;

    system("cls");
    printf("---------- BUSCAR CLIENTE ----------\n");

    while (atual != NULL) {
        // strcmp compara duas strings. Se retornar 0, elas são iguais.
        if (strcmp(atual->cpf, cpf) == 0) {
            printf("\nCliente Encontrado:\n");
            printf("Nome: %s\n", atual->nome);
            printf("Data de Nascimento: %s\n", atual->data_nascimento);
            printf("Email: %s\n", atual->email);
            printf("Telefone: %s\n", atual->telefone);
            encontrado = 1;
            break; 
        }
        atual = atual->prox;
    }

    if (!encontrado) {
        printf("\nCliente com CPF %s nao encontrado.\n", cpf);
    }

    printf("\nPressione Enter para continuar...");
    getchar(); getchar(); 
}

void removerCliente(Cliente **lista) {
    char cpf[12];
    printf("Digite o CPF para remover: ");
    scanf("%s", cpf);

    Cliente *atual = *lista;
    Cliente *anterior = NULL;

    while (atual != NULL && strcmp(atual->cpf, cpf) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Cliente nao encontrado!\n");
        sleep(1);
        return;
    }

    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual); 
    printf("Cliente removido com sucesso!\n");
    sleep(1);
}

void editarCliente(Cliente *lista) {
    char cpf[12];
    system("cls");
    printf("---------- EDITAR CLIENTE ----------\n");
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);

    Cliente *atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf) == 0) {
            printf("\nCliente encontrado! Deixe em branco para manter o atual.\n");
            
            getchar(); 
            printf("Novo Nome (Atual: %s): ", atual->nome);
            scanf("%[^\n]", atual->nome);

            getchar(); 
            printf("Nova data de Nascimento (Atual: %s): ", atual->data_nascimento);
            scanf("%[^\n]", atual->data_nascimento);
            
            getchar();
            printf("Novo E-mail (Atual: %s): ", atual->email);
            scanf("%[^\n]", atual->email);
            
            getchar();
            printf("Novo Telefone (Atual: %s): ", atual->telefone);
            scanf("%[^\n]", atual->telefone);

            printf("\nDados atualizados com sucesso!\n");
            sleep(1);
            return;
        }
        atual = atual->prox;
    }
    printf("\nCliente nao encontrado!\n");
    sleep(1);
}

