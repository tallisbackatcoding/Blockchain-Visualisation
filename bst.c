#include "bst.h"

void free_nodes(Node *node){
    if(!node){
        return;
    }
    free_nodes(node->left);
    free_nodes(node->right);
    free_set(node->Set);
    node->Set = NULL;
    free(node);
}

//binary tree with Set in each node
Node * new_node(int value){
    Node* node = malloc(sizeof(Node));
    if(!node){
        return NULL;
    }
    node->value = value;
    node->Set = new_set(16);
    node->right = NULL;
    node->left = NULL;
    return node;
}

Node** find( Node** n, int value )
{

    if((*n) == NULL)
    {
        return n;
    }
    else if((*n)->value == value)
    {
        return n;
    }
    else if(value < (*n)->value)
    {
        return find(&((*n)->left), value);
    }
    else
    {
        return find(&((*n)->right), value);
    }
}

int insert_to_tree( Node *head, int value ){

    if(head == NULL){
        head = new_node(value);
        if(!head){
            return -1;
        }
        return 1;
    }
    if (*find(&head, value) != NULL)
    {
        return 0;
    }
    else
    {
        Node ** n = find(&head, value);
        *n = new_node(value);
        return 1;
    }
}

Node* removerightmost( Node** from )
{
    if((*from)->right == NULL)
    {
        return *from;
    }
    return removerightmost(&((*from)->right));
}

int remove_from_tree( Node** head, int value )
{
    Node **del = find(head, value);
    if((*del) == NULL)
    {
        return 0;
    }

    if((*del)->left == NULL && (*del)->right == NULL)
    {
        free_set((*del)->Set);
        free(*del);
        *del = NULL;
        return 1;
    }
    else if((*del)->left == NULL)
    {
        Node *temp = *del;
        *del = (*del)->right;
        free_set(temp->Set);
        free(temp);
        temp = NULL;
        return 1;
    }
    else if((*del)->right == NULL)
    {
        Node *temp = *del;
        *del = (*del)->left;
        free_set(temp->Set);
        free(temp);
        temp = NULL;
        return 1;
    }
    else
    {
        Node *right = removerightmost(&((*del)->left));
        int v = right -> value;
        remove_from_tree(head, v);
        (*del)->value = v;
        return 1;
    }
    return 1;
}

void print_tree(Node * head) {
    if(head == NULL)
        return;
    print_tree(head->left);
    printf("%d ", head->value);
    print_tree(head->right);
}


