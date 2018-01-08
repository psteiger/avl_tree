#ifndef AVL_H
#include "avl.h"
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

void insert_node(struct node** root, int cod_cliente, int op, int v)
{
	struct node* existing_node = find_node(*root, cod_cliente);

	if (root == NULL) {
		*root = (struct node*) malloc(sizeof(struct node));

		if (*root == NULL) {
			fprintf(stderr, "Out of memory");
			exit(1);
		} else {
			(*root)->up = NULL;
		}
	}
		
}

struct node* find_node(struct node* root, int cod_cliente)
{
	if (root == NULL || root->value == cod_cliente)
		return root;
	else if (cod_cliente <= root->value)
		return find_node(root->left, cod_cliente);
	else
		return find_node(root->right, cod_cliente);
}

/*
void post_order(struct node* node)
{
	if (node == NULL) return;
	post_order(node->right);
	printf("%d", node->cod_cliente);
	post_order(node->left);
}
*/

void print_level(struct node* root, int target_level)
{
	print_level_aux(root, target_level, 1);
}

void print_level_aux(struct node* n, int target_level, int current_level)
{
	if (root == NULL) return;

	if (current_level == target_level)
		printf("%d ", n->cod_cliente); // imprime apenas o nivel pedido
	else if (current_level < target_level) {
		int next_level = ++current_level;
		print_level(n->left, target_level, next_level);
		print_level(n->right, target_level, next_level); 
	}

	return;
}

void in_order(struct node* node)
{
	if (node == NULL) return;
	in_order(node->left);
	printf("%d", node->cod_cliente);
	in_order(node->right);
}

int height(struct node* node)
{
	return node == NULL ? 0 : 1 + height(node->up);
}

