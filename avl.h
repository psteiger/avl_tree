#ifndef AVL_NODE
#define AVL_NODE
struct avl_node {
	int cod_cliente, saldo;			// valor e peso
	struct avl_node* up, left, right;	// ponteiros para pai e filhos
};

void insert_node(avl_node** tree, int cod_cliente, int op, int v);
void remove_node(avl_node** tree, int cod_cliente);
struct avl_node* find_node(avl_node* tree, int cod_cliente);

#endif
