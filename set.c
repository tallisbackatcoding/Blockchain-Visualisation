#include "set.h"
//set implementation using array

char *my_itoa_base(size_t n, int base){
    if(n == 0){
        char *r = malloc(2*sizeof(char));
        r[0] = '0';
        r[1] = 0;
        return r;
    }
    char str[100];
    int i = 0;
    while(n!=0){
        int temp  = 0;
        temp = n % base;
        if(temp < 10){
            str[i] = temp + 48;
        }
        else{
            str[i] = temp + 87;
        }
        n = n/base;
        i++;
    }
    char *result = malloc((100)*sizeof(char));
    int k = 0;
    for(int j = i - 1; j >= 0; j--, k++){
        result[k] = str[j];
    }
    result[k] = 0;
    return result;
}

int my_strlen(char *s){
    int i = 0;
    while(s[i]){
        i++;
    }
    return i;
}

void my_strcpy(char *s1, char *s2){
    int i;
    for(i = 0; s2[i]; i++){
        s1[i] = s2[i];
    }
    s1[i] = 0;
}

int equal(char *s1, char *s2){

    int i = 0;
    for(; s1[i] != 0 && s2[i] != 0; i++){
        if(s1[i] != s2[i])
            return 0;
    }
    if(s1[i] != s2[i])
        return 0;
    return 1;
}

int insert_to_set(set* s, char *str);

//hand destructor
void free_set(set *s){
    for(int i = 0; i < s->capacity; i++){
        if(s->array[i]){
            free(s->array[i]);
        }
    }
    free(s->array);
    free(s);
}

size_t get_hash(char *str){

    size_t hash = 0;
    for(int i = 0; str[i] != 0; i++){
        hash = hash * 31 + str[i];
    }
    return hash;
}

set* new_set(int capacity){

    set *return_set = malloc(sizeof(set));
    if(return_set == NULL){
        printf("no more resources available on the computer\n");
        return NULL;
    }
    return_set->size = 0;
    return_set->capacity = capacity;
    return_set->array = malloc(sizeof(char*)*capacity);
    for(int i = 0; i < capacity; i++){
        return_set->array[i] = NULL;
    }
    return return_set;
}

void rehash(set* s){

    set *new_s = new_set(s->capacity*2);
    for(int i = 0; i < s->capacity; i++){
        insert_to_set(new_s, s->array[i]);
        free(s->array[i]);
    }

    free(s->array);
    s->array = malloc(sizeof(char*)*new_s->capacity);
    if(s->array == NULL){
        printf("no more resources available on the computer\n");
        return;
    }
    for(int i = 0; i < new_s->capacity; i++){
        s->array[i] = NULL;
    }

    s->size = 0;
    s->capacity *= 2;

    for(int i = 0; i < new_s->capacity; i++){
        if(new_s->array[i])
            insert_to_set(s, new_s->array[i]);
    }

    free_set(new_s);
}

void print_set(set *s){

    int print_count = 0;
    for(int i = 0; i < s->capacity; i++){
        if(s->array[i]){
            printf("%s", s->array[i]);
            if(print_count != s->size - 1){
                printf(", ");
            }
            print_count++;
        }
    }
    printf("\n");
}

int insert_to_set(set* s, char *str){

    size_t index = get_hash(str);
    while(s->array[index % s->capacity]){
        if(equal(s->array[index % s->capacity], str)){
            return 0;
        }
        index++;
    }

    s->array[index % s->capacity] = malloc(sizeof(char)*256);
    my_strcpy(s->array[index%s->capacity], str);
    s->size++;
    if(s->size == s->capacity){
        rehash(s);
    }
    return 1;
}

int remove_from_set(set *s, char *str){

    size_t index = get_hash(str) % s->capacity;
    while(s->array[index % s->capacity]){
        if(equal(s->array[index % s->capacity], str)){

            free(s->array[index % s->capacity]);
            s->array[index % s->capacity] = NULL;
            s->size--;
            return 1;
        }
        index++;
    }
    return 0;
}

int set_contains(set *Set, char *str){

    size_t index = get_hash(str);
    int stop = index%(Set->capacity), i = 0;

    while(i != stop && Set->array[index%(Set->capacity)]){
        if(equal(Set->array[index%Set->capacity], str)){
            return 1;
        }
        i++;
        index++;
    }
    return 0;
}

int are_two_set_equal(set *set1, set *set2){

    if(set1->size != set2->size){
        return 0;
    }
    for(int i = 0; i < set1->capacity; i++){
        if(set1->array[i] && !set_contains(set2, set1->array[i])){
            return 0;
        }
    }
    return 1;
}
