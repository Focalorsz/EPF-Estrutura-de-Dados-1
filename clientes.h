#ifndef CLIENTES_H
#define CLIENTES_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <ncurses.h>
#include <stdbool.h>

typedef struct cliente{
    char cpf[12];
    char nome[100];
    char email[100];
    char telefone[15];
    char data_nascimento[11];
    struct carrinho_de_compras *carrinho;
    struct cliente *prox;
} Cliente;

void cadastrarCliente(Cliente **lista);
void listarClientes(Cliente *lista);
void buscarCliente(Cliente *lista, char cpf[]);
void editarCliente(Cliente *lista);
void removerCliente(Cliente **lista);

void menuPrincipal(Cliente **listaClientes);
void menuGerenciarClientes(Cliente **listaClientes);

#endif