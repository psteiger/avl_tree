#ifndef AVL_H
#define AVL_H
struct node {
	int cod_cliente, saldo;	// valor e peso
	struct node *up, *left, *right;	// ponteiros para pai e filhos
};

// funcoes principais
void insert_node(struct node** root, int cod_cliente, int op, int v);
void remove_node(struct node** root, int cod_cliente);
struct node* find_node(struct node* root, int cod_cliente);
void print_tree(struct node* root, char order); 	// order = 'c' ou 'd'
void print_level(struct node*, int); 	// root -> level == 1

// funcoes auxiliares
void print_level_aux(struct node*, int, int);
int height(struct node*);
int balance_factor(struct node*);
void in_order(struct node*);
void post_order(struct node*);
void rotate_left(struct node**);
void rotate_right(struct node**);
void rotate_double_left(struct node**);
void rotate_double_right(struct node**);
#endif
