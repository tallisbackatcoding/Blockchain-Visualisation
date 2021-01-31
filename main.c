#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "set.h"
#include "bst.h"
#include "string_array.h"

static int node_size;

int my_atoi(char* str){

    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    for (; str[i] != '\0'; ++i)
        result = result * 10 + str[i] - '0';
    return sign * result;
}

char* my_itoa(int i){

    int isNegative = i < 0;
    int n = i;
    int len = 0;
    while(n!=0){
        len++;
        n = n/10;
    }
    if(isNegative){
        len++;
    }
    if(i == 0){
        len++;
    }
    char *result;
    if(isNegative){
        result = malloc((len+1)*sizeof(char));
        result[0] = '-';
    }else{
        result = malloc((len+1)*sizeof(char));
    }
    result[len] = 0;
    len--;
    if(isNegative){
        while(len != 0){
            result[len] = 10 - (10 + i%10) + 48;
            i = i / 10;
            len--;
        }
    }else{
        if(i == 0){
            result[0] = '0';
            result[1] = 0;
        }else{
            while(i){
            result[len] = i%10+48;
            i = i / 10;
            len--;
            }
        }
    }
    return result;

}

int add_node( Node **head, int node_name ){

    int inserted = 1;
    if(*head == NULL){
        *head = new_node( node_name );
    }else{
        inserted = insert_to_tree( *head, node_name );
    }
    if(!inserted){
        printf("this node already exists\n");
        return 0;
    }else if(inserted == -1){
        printf("no more resources available on the computer\n");
        return 0;
    }
    node_size++;
    return 1;
}

void add_bids_to_every_node(Node *head, string_array *bids){

    if(!head){
        return;
    }
    add_bids_to_every_node(head->left, bids);
    for(int i = 0; i < bids->size; i++){
        insert_to_set(head->Set, bids->array[i]);
    }
    add_bids_to_every_node(head->right, bids);
}

int add_block( Node **head, char *bid, string_array * nodes, set *total_set){

    for(int i = 0; i < nodes->size; i++){
        int node_name = my_atoi(nodes->array[i]);
        Node **target = find(head, node_name);
        if(*target){
            if(insert_to_set((*target)->Set, bid) == 0){
                printf("this block already exists\n");
            }
            insert_to_set(total_set, bid);
        }else{
            printf("node doesn't exist\n");
            return 0;
        }
    }
    if(nodes->size == 0){
        string_array *bids_array = new_string_array(4);
        new_string(bids_array, bid);
        insert_to_set(total_set, bid);
        add_bids_to_every_node( *head, bids_array);
        free_all(bids_array);
    }
    return 1;
}

int remove_node(Node **head, int node_name){

    Node **target = find(head, node_name);
    if(*target){
        remove_from_tree(head, node_name);
        node_size--;
        return 1;
    }else{
        printf("node doesn't exist\n");
        return 0;
    }

}

//return 1 if block was deleted
int remove_block(Node *head, char *bid, int deleted_count){

    if(!head){
        return 0;
    }
    deleted_count += remove_from_set(head->Set, bid);
    deleted_count += remove_block(head->left, bid, deleted_count);
    deleted_count += remove_block (head->right, bid, deleted_count);
    return deleted_count;
}

void remove_blocks(Node *head, string_array *bids){

    for(int i = 0; i < bids->size; i++){
        int was_removed = remove_block(head, bids->array[i], 0);
        if(!was_removed){
            printf("block doesn't exist\n");
        }
    }

}

void print_blockchain(Node *head, int print_set_needed){

    if(head == NULL)
        return;
    else{
        print_blockchain(head->left, print_set_needed);
        if(print_set_needed){
            printf("%d: ", head->value);
            print_set(head->Set);
        }else{
            printf("%d, ", head->value);
        }

        print_blockchain(head->right, print_set_needed);
    }
}

int my_gets(char buffer[256]){

    int i = 0;
    char read_char;
    while(1){
        read(0, &read_char, 1);
        if(read_char == ' ' || read_char == '\n'){
            break;
        }
        buffer[i] = read_char;
        i++;
    }
    buffer[i] = 0;
    if(read_char == '\n'){
        return 1;
    }
    return 0;
}

//this function saves strings until new line from input to string_array
void query_into_str_array(string_array *queries){

    char buffer[256];
    while(1){
        int new_line_found = my_gets(buffer);
        new_string(queries, buffer);
        if(new_line_found){
            break;
        }
    }
}

void synchronize(Node *head, set* total_set){

    string_array *all_blocks = new_string_array(total_set->capacity);
    for(int i = 0; i < total_set->capacity; i++){
        if(total_set->array[i]){
            new_string(all_blocks, total_set->array[i]);
        }
    }
    add_bids_to_every_node(head, all_blocks);
    free_all(all_blocks);
}

int isSynchronized(Node *head){

    if(!head){
        return 1;
    }
    if(head->left){
        if(are_two_set_equal(head->left->Set, head->Set) == 0){
            return 0;
        }
    }
    if(head->right){
        if(are_two_set_equal(head->right->Set, head->Set) == 0){
            return 0;
        }
    }
    if(isSynchronized(head->left) == 0){
        return 0;
    }
    if(isSynchronized(head->right) == 0){
        return 0;
    }
    return 1;
}

void my_puts(char *s, int new_line_needed){

    write(1, s, my_strlen(s));
    if(new_line_needed){
        write(1, "\n", 1);
    }
}

void my_print_int(int i, int new_line_needed){

    char *str = my_itoa(i);
    my_puts(str, new_line_needed);
    free(str);
}

int main(){

    node_size = 0;
    Node *nodes_tree = NULL;
    string_array *queries;
    set *total_set = new_set(32);
    while(1){
        int sync = isSynchronized(nodes_tree);
        if(sync){
            my_puts("[s", 0);
            my_print_int(node_size, 0);
            my_puts("]> ", 0);
        }else{
            my_puts("[-", 0);
            my_print_int(node_size, 0);
            my_puts("]> ", 0);
        }
        queries = new_string_array(16);
        query_into_str_array(queries);

        if(equal(queries->array[0], "quit")){
            free_all(queries);
            break;
        }else if(queries->size > 2 && (equal(queries->array[0], "add") || equal(queries->array[1], "add"))){
            if((equal(queries->array[0], "node") || equal(queries->array[1], "node")) && queries->size == 3 ){
                if(equal(queries->array[2], "") || equal(queries->array[2], " ")){
                    printf("command not found\n");
                }else{
                    add_node(&nodes_tree, my_atoi(queries->array[2]));
                }
            }
            else if((equal(queries->array[0], "block") || equal(queries->array[1], "block")) && queries->size > 2){
                string_array *nodes = new_string_array(16);
                char bid_name[512];
                my_strcpy(bid_name, queries->array[2]);
                for(int i = 3; i < queries->size; i++){
                    if(queries->array[i][0] == '*' || equal(queries->array[i], "")){
                        break;
                    }
                    new_string(nodes, queries->array[i]);
                }
                add_block(&nodes_tree, bid_name, nodes, total_set);
                free_all(nodes);
            }
        }else if(queries->size > 1 && (equal(queries->array[0], "rm") || equal(queries->array[1], "rm"))){
            if((equal(queries->array[0], "node") || equal(queries->array[1], "node")) ){
                int remove_all = 1;
                for(int i = 2; i < queries->size; i++){
                    if(queries->array[i][0] == '*' || equal(queries->array[i], "")){
                        break;
                    }
                    remove_node(&nodes_tree, my_atoi(queries->array[i]));
                    remove_all = 0;
                }
                if(remove_all){
                    free_nodes(nodes_tree);
                    nodes_tree = NULL;
                    node_size = 0;
                }
            }else if((equal(queries->array[0], "block") || equal(queries->array[1], "block")) && queries->size > 2){
                string_array *bids = new_string_array(16);
                for(int i = 2; i < queries->size; i++){
                    new_string(bids, queries->array[i]);
                }
                remove_blocks(nodes_tree, bids);
                free_all(bids);
            }
        }else if(queries->size > 1 && equal(queries->array[0], "ls") && equal(queries->array[1], "-l")){
            print_blockchain(nodes_tree, 1);
        }else if(queries->size > 0 && equal(queries->array[0], "ls")){
            print_blockchain(nodes_tree, 0);
            if(nodes_tree)
                printf("\n");
        }else if(queries->size > 0 && equal(queries->array[0], "sync")){
            synchronize(nodes_tree, total_set);
        }else{
            printf("command not found\n");
        }
        free_all(queries);
    }
    free_nodes(nodes_tree);
    free_set(total_set);
    return 0;
}
