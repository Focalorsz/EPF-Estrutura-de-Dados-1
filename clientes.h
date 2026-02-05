#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct carrinho Carrinho;

typedef struct cliente {
    char cpf[12];
    char nome[100];
    char email[100];
    char telefone[15];
    char data_nascimento[11];
    Carrinho *carrinho;
    struct cliente *prox;
} Cliente;

// Protótipos
void cadastrarCliente(Cliente **lista);
void listarClientes(Cliente *lista);
void buscarCliente(Cliente *lista, char cpf[]);
void editarCliente(Cliente *lista);
void removerCliente(Cliente **lista);
void liberarTodosClientes(Cliente **lista);
void menuGerenciarClientes(Cliente **listaClientes);

#endif