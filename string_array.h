
#include <stdio.h>
#include <stdlib.h>
#include "set.h"

typedef struct
{
    int size;
    int capacity;
    char** array;
} string_array;

void free_all(string_array *s);

void print_array(string_array *a);

string_array * new_string_array(int capacity);

void add_string(string_array *s,char *a);

void ensure_capacity(string_array * a);

void new_string(string_array *s,char *a);


