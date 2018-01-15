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

#define MAX_ARGS 3

char* readstr(void);
int strlength(char* input);

int main(void) {
    /* a estrutura principal - uma arvore AVL */
    node *tree = NULL;

    /* le stdin em loop */
    char *c, word[100];
    int args[MAX_ARGS]; /* para insercao */
    int arg_count = 0;
    int last_space_pos = 0;
    int i;
    do {
        c = readstr();

        /* extrai os parametros da string lida */
        for (i = 0; i <= strlength(c); i++) {
            word[i-last_space_pos] = c[i];
            if (c[i] == ' ' || c[i] == '\0') {
                if (arg_count == MAX_ARGS) break;
                word[i-last_space_pos] = '\0';
                last_space_pos = i+1;
                if (i > 1) args[arg_count++] = atoi(word);
            }
        }

        last_space_pos = 0;
        arg_count = 0;

        /* realiza operacao definida por c[0] */
        switch(c[0]) {
        case 'i':
            tree = insert_node(&tree, args[0], args[1], args[2]);
            break;
        case 'r':
            tree = remove_node(&tree, args[0]   );
            break;
        case 'c':
            print_node(tree, args[0]);
            break;
        case 'p':
            if (c[2] == 'c') 
                in_order(tree);
            else if(c[2] == 'd')
                reverse_in_order(tree);
        case 'n':
            print_level(tree, args[0]);
            break;
        case 'h':
            print_height(tree);
            break;
        }
    } while(c[0] != 'f');

    print_and_dispose_tree(&tree);
    return 0;
}

char* readstr(void)
{
    int buffer_size = 8;
    int i = 0;
    int input;
    char *string = NULL;

    string = calloc(buffer_size, sizeof(char));

    while ((input = getchar()) != EOF) {
        if (input == '\r' || input == '\n') {
            fflush(stdin);
            break;
        }

        if (i == buffer_size - 1) {
            buffer_size *= 2;
            string = realloc( string, buffer_size * sizeof(char) );
        }

        string[i++] = input;
        string[i] = '\0';
    }

    return string;
}

int strlength(char *input)
{
    int length = 0;
    while (input[length] != '\0')
        length++;
    return length;
}
