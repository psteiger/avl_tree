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

void insert_node(struct node** root, int cod_cliente, int op, int v)
{
	if (op == 's') v = -v; /* se saque, inverte sinal */

	if (!(*root))
		create_terminal_node(root, cod_cliente, v);
	else { 
		/* arvore nao nula. tenta encontrar no existente.
		 * se no nao existe, cria. Depois, balanceia se necessario */
		struct node* existing_node = find_node(*root, cod_cliente);
		struct node* parent;

		if (existing_node && cod_cliente == existing_node->cod_cliente) 
			existing_node->saldo += v; /* encontramos no existente, atualizar saldo apenas */
		else if (!existing_node) /* nao encontramos no existente. criar um */
			existing_node = create_node_at_right_place(root, NULL, cod_cliente, v);

		parent = existing_node->up; /* existing node aqui nao pode ser null */

		/* neste ponto, temos a arvore com o no inserido, mas talvez desbalanceado.
		 * analisamos o balanceamento do pai do no inserido e rotacionamos se necessario. */
		if (parent) {
			printf("balance factor %d parent = %d\n", balance_factor(parent), parent->cod_cliente);
			if (balance_factor(parent) == 2) {

				struct node* right_child = parent->right;
				printf("balance factor right child %d \n", balance_factor(right_child));

				if (balance_factor(right_child) == 1) 
					rotate_left(&existing_node);
			}
				/*else  balance factor == -1 
					rotate_left(&existing_node);
			} else if (balance_factor(existing_node) == -2) {
				struct node* left_child = existing_node->right;

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

struct node* find_node(struct node* root, int cod_cliente)
{
	if (!root || root->cod_cliente == cod_cliente)
		return root;
	else if (cod_cliente <= root->cod_cliente)
		return find_node(root->left, cod_cliente);
	else
		return find_node(root->right, cod_cliente);
}

struct node* create_terminal_node(struct node** parent, int cod_cliente, int saldo)
{
	struct node* n = (struct node*) malloc(sizeof(struct node));

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

struct node* create_node_at_right_place(struct node** n, struct node** parent, int cod_cliente, int saldo)
{
	if (!(*n))
		return create_terminal_node(parent, cod_cliente, saldo);
	else if ((*n)->cod_cliente == cod_cliente) {
		(*n)->saldo += saldo;
		return *n;
	} else if (cod_cliente <= (*n)->cod_cliente)
		return create_node_at_right_place(&(*n)->left, n, cod_cliente, saldo);
	else
		return create_node_at_right_place(&(*n)->right, n, cod_cliente, saldo);

	return NULL;
}

void print_level(struct node* root, int target_level)
{
	print_level_aux(root, target_level, 1);
	printf("\n");
}

void print_level_aux(struct node* n, int target_level, int current_level)
{
	if (!n) return;

	if (current_level == target_level)
		printf("%d ", n->cod_cliente); /* imprime apenas o nivel pedido */
	else if (current_level < target_level) {
		int next_level = ++current_level;
		print_level_aux(n->left, target_level, next_level);
		print_level_aux(n->right, target_level, next_level); 
	}

	return;
}

void in_order(struct node* n)
{
	if (!n) return;
	in_order(n->left);
	printf("%d", n->cod_cliente);
	in_order(n->right);
}

int height(struct node* n)
{
	if (n) printf("height of node %d\n", n->cod_cliente);
	return !n || !n->up ? 0 : 1 + height(n->up);
}

int balance_factor(struct node* n)
{
	return height(n->right) - height(n->left);
}

void balance(struct node** n)
{
	if (balance_factor(*n) == 2) {
		return;
	}
}

void rotate_left(struct node** n)
{
	struct node* pivot = (*n)->right;
	(*n)->right = pivot->left;
	pivot->left = *n;
}

void dispose(struct node** n)
{
	dispose(&(*n)->left);
	dispose(&(*n)->right);
	free(*n);
}
