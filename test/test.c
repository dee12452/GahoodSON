#include "../src/GahoodSON.h"
#include "stdio.h"
#include "stdlib.h"

void print_bool(json_bool *, int);
void print_str(json_string *, int);
void print_int(json_int *, int);
void print_lists(json_list **, int, int);
void print_objects(json_object **, int, int);
void print_pairs(json_pair **, int, int);

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Incorrect Arguments passed: Needed one file path and nothing else\n");
        exit(EXIT_FAILURE);
    }
    json *obj = gahoodson_create(argv[1]);
    printf("Printing %d pairs\n", obj->num_of_pairs);
    print_pairs(obj->pairs, obj->num_of_pairs, 0);
    printf("Printing %d objs\n", obj->num_of_objects);
    print_objects(obj->objects, obj->num_of_objects, 0);
    printf("Printing %d lists\n", obj->num_of_lists);
    print_lists(obj->json_lists, obj->num_of_lists, 0);
    gahoodson_delete(obj);
    printf("\n");
    return 0;
}

void print_bool(json_bool *boolean, int subset) {
    if(boolean == NULL) return;
    int j;
    for(j = 0; j < subset; j++) printf(" ");
    if(boolean->val == 0) {
        printf("bool : false\n");
    }
    else {
        printf("bool : true\n");
    }
}

void print_int(json_int *int_val, int subset) {
    if(int_val == NULL) return;
    int j;
    for(j = 0; j < subset; j++) printf(" ");
    printf("int : %d\n", int_val->val);
}

void print_str(json_string *str_val, int subset) {
    if(str_val == NULL) return;
    int j;
    for(j = 0; j < subset; j++) printf(" ");
    printf("string : %s\n", str_val->val);
}

void print_list_elements(json_list_element **elements, int size, int subset) {
    int i;
    for(i = 0; i < size; i++) {
        print_bool(elements[i]->bool_val, subset + 1);
        print_int(elements[i]->int_val, subset + 1);
        print_str(elements[i]->str_val, subset + 1);
        print_pairs(elements[i]->json_pairs, elements[i]->num_of_pairs, subset + 1);
        print_objects(elements[i]->json_objects, elements[i]->num_of_objects, subset + 1);
        print_lists(elements[i]->json_lists, elements[i]->num_of_lists, subset + 1);
    }
}

void print_lists(json_list **lists, int size, int subset) {
    int i, j;
    for(i = 0; i < size; i++) {
        for(j = 0; j < subset; j++) printf(" ");
        printf("list: %s\n", lists[i]->key->val);
        print_list_elements(lists[i]->elements, lists[i]->num_of_elements, subset + 1);
    }
}

void print_objects(json_object **objs, int size, int subset) {
    int i, j;
    for(i = 0; i < size; i++) {
        for(j = 0; j < subset; j++) printf(" ");
        printf("object: %s\n", objs[i]->key->val);
        print_pairs(objs[i]->pairs, objs[i]->num_of_pairs, subset + 1);
        print_objects(objs[i]->sub_objects, objs[i]->num_of_subobjects, subset + 1);
        print_lists(objs[i]->json_lists, objs[i]->num_of_lists, subset + 1);
    }
}

void print_pairs(json_pair **pairs, int size, int subset) {
    int i, j;
    for(i = 0; i < size; i++) {
        for(j = 0; j < subset; j++) printf(" ");
        printf("pair: %s : ", pairs[i]->key->val);
        if(pairs[i]->bool_val != NULL) {
            printf("%d\n", pairs[i]->bool_val->val);
        }
        else if(pairs[i]->int_val != NULL) {
            printf("%d\n", pairs[i]->int_val->val);
        }
        else if(pairs[i]->str_val != NULL) {
            printf("%s\n", pairs[i]->str_val->val);
        }
    }
}
