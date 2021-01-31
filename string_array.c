#include "string_array.h"


//hand-made destructor
void free_all(string_array *s)
{
    for(int i = 0; i < s->size; i++){
        free(s->array[i]);
    }
    free(s->array);
    free(s);
}
//function which prints elements of string_array
void print_array(string_array *a)
{
    for(int i = 0; i < a->size; i++)
    {
        printf("%s", a->array[i]);

        if(i != a->size - 1){
            printf("  ");
        }
    }
}
//function which creates new stuct string_array object with needed capacity
string_array * new_string_array(int capacity)
{
    string_array * str_array = malloc(sizeof(string_array));
    str_array->size = 0;
    str_array->capacity = capacity;
    str_array->array = malloc(sizeof(char*)*capacity);
    return str_array;
}
//this function keeps track of whether our string_array is full and needs a capacity increase

//function adds string 'a' to string_array 's'
void add_string(string_array *s, char *a)
{
    s->array[s->size] = malloc(sizeof(char)*(my_strlen(a)+1));
    my_strcpy(s->array[s->size],a);
    s->size++;
}
void ensure_capacity(string_array * a)
{
    if(a->size >= a->capacity)
    {
        string_array *new_arr = new_string_array(a->capacity*2);
        for(int i = 0; i < a->size; i++){
            add_string(new_arr,a->array[i]);
            free(a->array[i]);
        }
        free(a->array);
        a->array = malloc(sizeof(char*)*new_arr->capacity);
        a->size = 0;
        for(int i = 0; i < new_arr->size; i++){
            add_string(a,new_arr->array[i]);
        }
        a->capacity *= 2;
        free_all(new_arr);
    }
}
//this function calls add_string() and ensure_capacity()
void new_string(string_array *s,char *a)
{
    ensure_capacity(s);
    add_string(s, a);
}
