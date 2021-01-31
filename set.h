#ifndef INCLUDED
#define INCLUDED  1

#include <stdio.h>
#include <stdlib.h>

char *my_itoa_base(size_t n, int base);

int my_strlen(char *s);

void my_strcpy(char *s1, char *s2);

int equal(char *s1,char *s2);

typedef struct{
    int size;
    int capacity;
    char **array;
}set;

int insert_to_set(set* s, char *str);

void free_set(set *s);

size_t get_hash(char *str);

set* new_set(int capacity);

void rehash(set* s);

void print_set(set *s);

int insert_to_set(set* s, char *str);

int remove_from_set(set *s, char *str);

int are_two_set_equal(set *set1, set *set2);

int set_contains(set *Set, char *str);

#endif
