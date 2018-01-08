#ifndef AVL_H
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

	if (!root) { 	// no atual eh nulo - criar
		*root = (struct node*) malloc(sizeof(struct node));

		if (!(*root)) {
			fprintf(stderr, "Out of memory");
			exit(1);
		} else
			(*root)->cod_cliente = cod_cliente;
	} else { 	// arvore nao nula. tenta encontrar no existente
		//struct node* existing_node = find_node(*root, cod_cliente);

		if (cod_cliente == (*root)->cod_cliente) {
			// aplica operacao 'op' apenas
		} else if (cod_cliente < (*root)->cod_cliente) {
			(*root)->left = insert_node(&(*root)->left, cod_cliente, op, v);
			if (balance_factor(*root) == 2) rotate_left(root) else 
		} else if (cod_cliente > (*root)->cod_cliente) {
	
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

void print_level(struct node* root, int target_level)
{
	print_level_aux(root, target_level, 1);
}

void print_level_aux(struct node* n, int target_level, int current_level)
{
	if (!n) return;

	if (current_level == target_level)
		printf("%d ", n->cod_cliente); // imprime apenas o nivel pedido
	else if (current_level < target_level) {
		int next_level = ++current_level;
		print_level_aux(n->left, target_level, next_level);
		print_level_aux(n->right, target_level, next_level); 
	}

	return;
}

void in_order(struct node* node)
{
	if (!node) return;
	in_order(node->left);
	printf("%d", node->cod_cliente);
	in_order(node->right);
}

int height(struct node* n)
{
	return !n ? 0 : 1 + height(n->up);
}

int balance_factor(struct node* n) // como visto em sala
{
	return height(n->right) - height(n->left);
}

void balance(struct node** n)
{
	if (balance_factor(*n) == 2) {
		return;
	}
}

void dispose(struct node** n)
{
	dispose(&(*n)->left);
	dispose(&(*n)->right);
	free(*n);
}

