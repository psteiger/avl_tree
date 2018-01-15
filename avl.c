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
	int key, saldo, num_ops;
	struct node *up, *left, *right;	/* ponteiros para pai e filhos */
};

/* forward declaration de funcoes internas da ADT, por isso nao esta no .h */
void print_level_aux(node* root, int target_level, int current_level);
node* create_node_at_right_place(node** n, node** parent, int key, int saldo);
node* create_child_node(node** parent, int key, int saldo);
node* find_node(node* root, int key);
int height(node* n);
int count_num_nodes(node* root);
void rotate_left(node** n);
void rotate_right(node** n);
void rotate_left_right(node** n);
void rotate_right_left(node** n);
int balance_factor(node* n);
int max(int a, int b);

/**
 * insere key com operacao op e valor v na arvore cuja raiz eh root.
 * se no existe, apenas atualiza os valores.
 * se no nao existe, cria no local correto, e se necessario, realiza balanceamento.
 * retorna um node* para caso o root mude.
 */
node* insert_node(node** root, int key, int op, int v)
{
	node* newRoot = NULL;
	/*printf("inserindo %d\n", key);*/
	if (op == 1) v = -v; /* se saque, inverte sinal */

	if (!*root) /* primeira insercao - a arvore eh vazia */
		create_child_node(root, key, v);
	else { 
		/* arvore nao nula. tenta encontrar no existente.
		 * se no nao existe, cria. Depois, balanceia se necessario */
		node* existing_node = find_node(*root, key);
		node* parent = NULL;
		node* grandparent = NULL;

		if (existing_node) {			/* encontramos no existente, atualizar saldo apenas */
			existing_node->saldo += v;
			existing_node->num_ops++;
		} else 							/* nao encontramos no existente. criar um */
			existing_node = create_node_at_right_place(root, NULL, key, v);

		parent = existing_node->up; /* existing node aqui nao pode ser null. se nao existia, foi criado. */
		if (parent)
			grandparent = parent->up;
			/*printf("node %d parent %d", key, parent->key);
			if (grandparent) printf(" grandparent %d", grandparent->key);
			printf("\n");*/

		/* neste ponto, temos a arvore com o no inserido, mas talvez desbalanceado.
		 * analisamos o balanceamento do pai do pai do no inserido e rotacionamos se necessario. */
		while (grandparent) {
			if (balance_factor(grandparent) == 2) {
				if (balance_factor(parent) == 1)
					rotate_left(&grandparent);
				else if (balance_factor(parent) == -1)
					rotate_right_left(&grandparent);
			} else if (balance_factor(grandparent) == -2) {
				if (balance_factor(parent) == -1)
					rotate_right(&grandparent);
				else if (balance_factor(parent) == 1)
					rotate_left_right(&grandparent);
			}

			parent = parent->up;
			if (parent)
				grandparent = parent->up;
			else
				grandparent = NULL;
		}
	}

	newRoot = *root;
	while (newRoot->up) newRoot = newRoot->up;
	return newRoot;
}

node* remove_node(node** root, int key)
{
	node* existing_node = find_node(*root, key);
	node* child_left = NULL;
	node* child_right = NULL;
	node* parent = NULL;
	node* substitute = NULL;
	node* newRoot = NULL;

	if (!existing_node) return *root;

	child_left = existing_node->left;
	child_right = existing_node->right;
	parent = existing_node->up;
	substitute = NULL;

	if (!child_left) {
		if (parent) {
			if (parent->left == existing_node)
				parent->left = child_right;
			else
				parent->right = child_right;
		}

		if (child_right) {
			child_right->up = parent;
			substitute = child_right;
		}
	} else if (!child_right) {
		if (parent) {
			if (parent->left == existing_node)
				parent->left = child_left;
			else
				parent->right = child_left;
		}

		if (child_left) {
			child_left->up = parent;
			substitute = child_left;
		}
	} else if (child_right && child_left) {
		node* next_inorder_node = child_right;
		
		while (next_inorder_node->left != NULL)
			next_inorder_node = next_inorder_node->left;

		substitute = next_inorder_node;

		if (parent) {
			if (parent->left == existing_node)
				parent->left = next_inorder_node;
			else
				parent->right = next_inorder_node;
		}
	
		if (next_inorder_node->up != existing_node) {
			next_inorder_node->up->left = next_inorder_node->right;
			if (next_inorder_node->right)
				next_inorder_node->right->up = next_inorder_node->up;
		}

		next_inorder_node->up = parent;
		if (next_inorder_node != child_right) {
			next_inorder_node->right = child_right;
			child_right->up = next_inorder_node;
		} 
			
		next_inorder_node->left = child_left;
		next_inorder_node->left->up = next_inorder_node;
	}

	existing_node->up = NULL;
	existing_node->right = NULL;
	existing_node->left = NULL;
	free(existing_node);

	if (!substitute) substitute = parent;

	/* rebalance */
	/*printf("substitute = %d\n", substitute->key);*/

	newRoot = substitute;

	while (substitute) {
		node* x = NULL; /* first unbalanced node */
		node* y = NULL; /* x's highest height child */
		
		if (balance_factor(substitute) == 2) {
			x = substitute;
			y = substitute->right;
			if (height(y->left) >= height(y->right))
				rotate_right_left(&x);
			else
				rotate_left(&x);
		} else if (balance_factor(substitute) == -2) {
			x = substitute;
			y = substitute->left;
			if (height(y->right) >= height(y->left))
				rotate_left_right(&x);
			else
				rotate_right(&x);
		}

		substitute = substitute->up;
	}

	while (newRoot && newRoot->up) newRoot = newRoot->up;
	return newRoot;
}

node* find_node(node* root, int key)
{
	if (!root || root->key == key)
		return root;
	else if (key <= root->key)
		return find_node(root->left, key);
	else
		return find_node(root->right, key);
}

/**
 * cria um no terminal cujo pai eh 'parent'.
 * na primeira chamada, a arvore eh vazia e parent eh null.
 */
node* create_child_node(node** parent, int key, int saldo)
{
	node* n = malloc(sizeof(node));

	if (!n) exit(1);

	n->key = key;
	n->saldo = saldo;
	n->num_ops = 1;
	n->up = NULL;
	n->left = NULL;
	n->right = NULL;

	if (*parent) {
		n->up = *parent;

		if (key <= (*parent)->key)
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
node* create_node_at_right_place(node** n, node** parent, int key, int saldo)
{
	if (!(*n)) /* busca percorrida e no nao encontrado. cria um novo! */
		return create_child_node(parent, key, saldo);
	else if ((*n)->key == key) { /* busca percorrida e no encontrado - atualiza */
		(*n)->saldo += saldo;
		return *n;
	} else if (key <= (*n)->key) /* busca nao finalizada */
		return create_node_at_right_place(&(*n)->left, n, key, saldo);
	else /* busca nao finalizada */
		return create_node_at_right_place(&(*n)->right, n, key, saldo);

	return NULL;
}

/**
 * sem estruturas auxiliares. Usa recursão 
 */
void print_level(node* root, int target_level)
{
	print_level_aux(root, target_level, 1);
}

void print_level_aux(node* n, int target_level, int current_level)
{
	if (!n) return;

	if (current_level == target_level) {
		printf("%d %d %d\n", n->key, n->num_ops, n->saldo); /* imprime apenas o nivel pedido */
		/*if (n->up)
			printf(" (pai %d)", n->up->key);
		printf("\n");*/
	} else if (current_level < target_level) {
		int next_level = ++current_level;
		print_level_aux(n->left, target_level, next_level);
		print_level_aux(n->right, target_level, next_level); 
	}
}

void print_node(node* root, int key)
{
	node* node = find_node(root, key);
	if (!node)
		printf("nao ");
	printf("existe no com chave: %d\n", key);
}

void print_and_dispose_tree(node** root)
{
	node* r = *root;
	printf("-+- Inicio relatorio -+-\n");
	printf("%d\n", count_num_nodes(r));
	while (r) {
		printf("%d %d %d\n", r->key, r->num_ops, r->saldo);
		r = remove_node(&r, r->key);
	}
	printf("-+- Fim relatorio -+-\n");
}

int count_num_nodes(node* root)
{	
	if (!root) return 0;
	return 1 + count_num_nodes(root->left) + count_num_nodes(root->right);
}

void in_order(node* n)
{
	if (!n) return;
	in_order(n->left);
	printf("%d %d %d\n", n->key, n->num_ops, n->saldo);
	in_order(n->right);
}

void reverse_in_order(node* n)
{
	if (!n) return;
	reverse_in_order(n->right);
	printf("%d %d %d\n", n->key, n->num_ops, n->saldo);
	reverse_in_order(n->left);
}

int height(node *n)
{
	return !n ? 0 : 1 + max(height(n->right), height(n->left));
}

void print_height(node *n)
{
	printf("%d\n", height(n));
}

int balance_factor(node* n)
{
	return height(n->right) - height(n->left);
}

void rotate_left(node** n)
{
	node* pivot = (*n)->right;
	if ((*n)->up) {	/* atualiza no acima da raiz se existir */
		if ((*n)->up->right == *n)
			(*n)->up->right = pivot;
		else if ((*n)->up->left == *n)
			(*n)->up->left = pivot;
	}

	pivot->up = (*n)->up;
	(*n)->up = pivot;
	(*n)->right = pivot->left;
	if (pivot->left) pivot->left->up = *n;
	pivot->left = *n;
}

void rotate_right(node** n)
{
	node* pivot = (*n)->left;
	if ((*n)->up) {	/* atualiza no acima da raiz se existir */
		if ((*n)->up->right == *n)
			(*n)->up->right = pivot;
		else if ((*n)->up->left == *n)
			(*n)->up->left = pivot;
	}

	pivot->up = (*n)->up;
	(*n)->up = pivot;
	(*n)->left = pivot->right;
	if (pivot->right) pivot->right->up = *n;
	pivot->right = *n;
}

void rotate_left_right(node** n)
{
	node* root = (*n)->left;
	node* pivot = root->right;
	rotate_left(&root);
	root = pivot->up;
	rotate_right(&root);
}

void rotate_right_left(node** n)
{
	node* root = (*n)->right;
	node* pivot = root->left;
	rotate_right(&root);
	root = pivot->up;
	rotate_left(&root);
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}
