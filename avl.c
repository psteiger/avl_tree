#ifndef AVL_H
#define AVL_H

#include "avl.h"

#endif

#ifndef STDLIB_H
#define STDLIB_H

#include <stdlib.h>

#endif

#ifndef STDIO_H
#define STDIO_H

#include <stdio.h>

#endif

struct node {
	int cod_cliente, saldo;
	struct node *up, *left, *right;	/* ponteiros para pai e filhos */
};

/**
 * insere cod_cliente com operacao op e valor v na arvore cuja raiz eh root.
 * se no existe, apenas atualiza os valores.
 * se no nao existe, cria no local correto, e se necessario, realiza balanceamento.
 */
void insert_node(node** root, int cod_cliente, int op, int v)
{
	if (op == 's') v = -v; /* se saque, inverte sinal */

	if (!(*root)) /* primeira insercao - a arvore eh vazia */
		create_terminal_node(root, cod_cliente, v);
	else { 
		/* arvore nao nula. tenta encontrar no existente.
		 * se no nao existe, cria. Depois, balanceia se necessario */
		node *existing_node = find_node(*root, cod_cliente);
		node *parent, *grandparent;

		if (existing_node) 
			existing_node->saldo += v; /* encontramos no existente, atualizar saldo apenas */
		else /* nao encontramos no existente. criar um */
			existing_node = create_node_at_right_place(root, NULL, cod_cliente, v);

		parent = existing_node->up; /* existing node aqui nao pode ser null. se nao existia, foi criado. */
		if (parent) 
			grandparent = parent->up;

		/* neste ponto, temos a arvore com o no inserido, mas talvez desbalanceado.
		 * analisamos o balanceamento do pai do pai do no inserido e rotacionamos se necessario. */
		if (grandparent) {
			printf("balance factors: %d %d\n", balance_factor(grandparent), balance_factor(parent));
			if (balance_factor(grandparent) == 2) {
				if (balance_factor(parent) == 1)
					rotate_left(&grandparent);
			}
		
				/*else  balance factor == -1 
					rotate_left(&existing_node);
			} else if (balance_factor(existing_node) == -2) {
				node* left_child = existing_node->right;

				if (balance_factor(left_child) == 1) 
					rotate_left(&existing_node);
				else  balance factor == -1 
					rotate_left(&existing_node);
			}
			else if (cod_cliente <= existing_node->cod_cliente) {
				if (balance_factor(existing_node) == 2) rotate_left(root);
			} else if (cod_cliente > existing_node->cod_cliente) {
				return;
			} */
		}
	}
}

node* find_node(node* root, int cod_cliente)
{
	if (!root || root->cod_cliente == cod_cliente)
		return root;
	else if (cod_cliente <= root->cod_cliente)
		return find_node(root->left, cod_cliente);
	else
		return find_node(root->right, cod_cliente);
}

/**
 * cria um no terminal cujo pai eh 'parent'.
 * na primeira chamada, a arvore eh vazia e parent eh null.
 */
node* create_terminal_node(node** parent, int cod_cliente, int saldo)
{
	node* n = malloc(sizeof(node));

	if (!n) exit(1);

	n->cod_cliente = cod_cliente;
	n->saldo = saldo;
	n->up = NULL;

	if (*parent) {
		n->up = *parent;

		if (cod_cliente <= (*parent)->cod_cliente)
			(*parent)->left = n;
		else
			(*parent)->right = n;
	} else
		*parent = n;

	return n;
}

/**
 * recebe a raiz da arvore e um no n.
 */
node* create_node_at_right_place(node** n, node** parent, int cod_cliente, int saldo)
{
	if (!(*n)) /* busca percorrida e no nao encontrado. cria um novo! */
		return create_terminal_node(parent, cod_cliente, saldo);
	else if ((*n)->cod_cliente == cod_cliente) { /* busca percorrida e no encontrado - atualiza */
		(*n)->saldo += saldo;
		return *n;
	} else if (cod_cliente <= (*n)->cod_cliente) /* busca nao finalizada */
		return create_node_at_right_place(&(*n)->left, n, cod_cliente, saldo);
	else /* busca nao finalizada */
		return create_node_at_right_place(&(*n)->right, n, cod_cliente, saldo);

	return NULL;
}

/**
 * sem estruturas auxiliares. Usa recursão 
 */
void print_level(node* root, int target_level)
{
	print_level_aux(root, target_level, 1);
	printf("\n");
}

void print_level_aux(node* n, int target_level, int current_level)
{
	if (!n) return;

	if (current_level == target_level)
		printf("%d ", n->cod_cliente); /* imprime apenas o nivel pedido */
	else if (current_level < target_level) {
		int next_level = ++current_level;
		print_level_aux(n->left, target_level, next_level);
		print_level_aux(n->right, target_level, next_level); 
	}
}

void in_order(node* n)
{
	if (!n) return;
	in_order(n->left);
	printf("%d", n->cod_cliente);
	in_order(n->right);
}

int height(node *n)
{
	/*if (n) printf("height of node %d %d\n", n->cod_cliente, root->cod_cliente );*/
	return !n ? 0 : 1 + max(height(n->right), height(n->left));
}

int balance_factor(node* n)
{
	if (n) printf("balance factor of node %d : right = %d, left = %d\n", n->cod_cliente, height(n->right), height(n->left));
	return height(n->right) - height(n->left);
}

void balance(node** n)
{
	if (balance_factor(*n) == 2) {
		return;
	}
}

void rotate_left(node** n)
{
	node* pivot = (*n)->right;
	printf("pivot = %d, (*n)->right = %d\n", pivot->cod_cliente, (*n)->right->cod_cliente);
	pivot->up = (*n)->up;
	(*n)->up = pivot;
	(*n)->right = pivot->left;
	pivot->left = *n;
}

void dispose(node** n)
{
	dispose(&(*n)->left);
	dispose(&(*n)->right);
	free(*n);
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}