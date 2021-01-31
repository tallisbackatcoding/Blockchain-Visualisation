#include <stdio.h>
#include <stdlib.h>
#include "set.h"

typedef struct Node_t{
    int value;
    struct Node_t *left;
    struct Node_t *right;
    set *Set;
}Node;


void free_nodes(Node *node);

Node * new_node(int value);

Node** find( Node** n, int value );

int insert_to_tree( Node *head, int value );

void rightinsert( Node** into, Node* n );

Node* removerightmost( Node** from );

int remove_from_tree( Node** head, int value );

void print_tree(Node * head);

