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
    node *tree = NULL;

    printf("Inserindo 3\n");
    tree = insert_node(&tree, 3, 'c', 100);

    print_level(tree, 1);
    print_level(tree, 2);
    print_level(tree, 3);
    print_level(tree, 4);

    /*printf("%d", tree->saldo);*/
    printf("Inserindo 4\n");

    tree = insert_node(&tree, 4, 'c', 100);

    print_level(tree, 1);
    print_level(tree, 2);
    print_level(tree, 3);
    print_level(tree, 4);

    printf("Inserindo 5\n");

    tree = insert_node(&tree, 5, 'c', 100);

    print_level(tree, 1);
    print_level(tree, 2);
    print_level(tree, 3);
    print_level(tree, 4);

    tree = insert_node(&tree, 6, 'c', 100);

    print_level(tree, 1);
    print_level(tree, 2);
    print_level(tree, 3);
    print_level(tree, 4);

    tree = insert_node(&tree, 7, 'c', 100);

    print_level(tree, 1);
    print_level(tree, 2);
    print_level(tree, 3);
    print_level(tree, 4);

    tree = insert_node(&tree, 8, 'c', 100);

    print_level(tree, 1);
    print_level(tree, 2);
    print_level(tree, 3);
    print_level(tree, 4);

    tree = insert_node(&tree, 2, 'c', 100);

    print_level(tree, 1);
    print_level(tree, 2);
    print_level(tree, 3);
    print_level(tree, 4);
    tree = insert_node(&tree, 1, 'c', 100);

    print_level(tree, 1);
    print_level(tree, 2);
    print_level(tree, 3);
    print_level(tree, 4);
    print_level(tree, 5);
    print_level(tree, 6);
    tree = insert_node(&tree, 0, 'c', 100);

    print_level(tree, 1);
    print_level(tree, 2);
    print_level(tree, 3);
    print_level(tree, 4);
    print_level(tree, 5);
    print_level(tree, 6);
    return 0;
}