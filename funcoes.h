#ifndef FUNCOES_H
#define funcoes.h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <ncurses.h>
#include <stdbool.h>
#include "structs.h"
void cadastrarCliente(Cliente **lista);
void listarClientes(Cliente *lista);
Cliente* buscarCliente(Cliente *lista, char cpf[]);
void editarCliente(Cliente *lista);
void removerCliente(Cliente **lista);
void menuPrincipal(Cliente **listaClientes);
void menuGerenciarClientes(Cliente **listaClientes);
produtos * reserva_celula_cabeca;
void listar_produtos (produtos * Lista_Encadeada_Produtos);
produtos * busca_codigo(int cod, produtos * Lista_Encadeada_Produtos);
produtos * busca_nome(char * palavra_chave, produtos * Lista_Encadeada_Produtos);
void adicionar_produto (int codi,char nom,float prec,int quant,char *desc, produtos * Lista_Encadeada_Produtos);
void remove_por_codigo(int cod,produtos * Lista_Encadeada_Produtos);
void remove_por_nome(char palavra_chave,produtos * Lista_Encadeada_Produtos);



#endif