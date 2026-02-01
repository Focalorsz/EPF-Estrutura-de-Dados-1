#ifndef FUNCOES_H
#define funcoes.h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include "structs.h"
void cadastrarCliente(Cliente **lista);
void listarClientes(Cliente *lista);
Cliente* buscarCliente(Cliente *lista, char cpf[]);
void editarCliente(Cliente *lista);
void removerCliente(Cliente **lista);
void menuPrincipal(Cliente **listaClientes);
void menuGerenciarClientes(Cliente **listaClientes);


#endif
