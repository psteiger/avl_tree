struct node {
	int cod_cliente, saldo;
	struct node *up, *left, *right;	/* ponteiros para pai e filhos */
};

void insert_node(struct node** root, int cod_cliente, int op, int v);
void remove_node(struct node** n, int cod_cliente);
struct node* find_node(struct node* root, int cod_cliente);
void print_tree(struct node* root, char c); 	/* order = 'c' ou 'd' */
void print_level(struct node* root, int target_level); 	/* root -> level == 1 */
struct node* create_node_at_right_place(struct node** n, struct node** parent, int cod_cliente, int saldo);
struct node* create_terminal_node(struct node** parent, int cod_cliente, int saldo);
void print_level_aux(struct node* root, int target_level, int current_level);
int height(struct node* n);
void balance(struct node** n);
int balance_factor(struct node* n);
void in_order(struct node* n);
void rotate_left(struct node** n);
void rotate_right(struct node** n);
void rotate_double_left(struct node** n);
void rotate_double_right(struct node** n);
void dispose(struct node** n);
