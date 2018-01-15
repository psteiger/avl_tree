typedef struct node node;

node* insert_node(node** root, int key, int op, int v);
node* remove_node(node** root, int key);
void print_node(node* root, int key);
void print_and_dispose_tree(node** root);
void print_level(node* root, int target_level); 	/* root -> level == 1 */
void print_height(node* n);
void in_order(node* n);
void reverse_in_order(node* n);

