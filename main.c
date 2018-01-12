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

int main(void) {
    node *tree;

    printf("Inserindo 3\n");
    insert_node(&tree, 3, 'c', 100);

    print_level(tree, 1);
    print_level(tree, 2);
    print_level(tree, 3);
    print_level(tree, 4);

    /*printf("%d", tree->saldo);*/
    printf("Inserindo 4\n");

    insert_node(&tree, 4, 'c', 100);

    print_level(tree, 1);
    print_level(tree, 2);
    print_level(tree, 3);
    print_level(tree, 4);

    printf("Inserindo 5\n");

    insert_node(&tree, 5, 'c', 100);
    /*insert_node(&tree, 6, 'c', 100);
    insert_node(&tree, 1, 'c', 100);
    insert_node(&tree, 2, 'c', 100);
    insert_node(&tree, 1, 'c', 100);*/

    print_level(tree, 1);
    print_level(tree, 2);
    print_level(tree, 3);
    print_level(tree, 4);
    return 0;
}