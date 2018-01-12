typedef struct node node;

void insert_node(node** root, int cod_cliente, int op, int v);
void remove_node(node** n, int cod_cliente);
node* find_node(node* root, int cod_cliente);
void print_tree(node* root, char c); 	/* order = 'c' ou 'd' */
void print_level(node* root, int target_level); 	/* root -> level == 1 */
node* create_node_at_right_place(node** n, node** parent, int cod_cliente, int saldo);
node* create_terminal_node(node** parent, int cod_cliente, int saldo);
void print_level_aux(node* root, int target_level, int current_level);
int height(node* n);
int balance_factor(node* n);
void balance(node** n);
void in_order(node* n);
void rotate_left(node** n);
void rotate_right(node** n);
void rotate_double_left(node** n);
void rotate_double_right(node** n);
void dispose(node** n);
int max(int a, int b);