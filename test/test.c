#include "../src/GahoodSON.h"
#include "stdio.h"
#include "stdlib.h"

void print_lists(json_list **, int, int);
void print_objects(json_object **, int, int);
void print_pairs(json_pair **, int, int);

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Incorrect Arguments passed: Needed one file path and nothing else\n");
        exit(EXIT_FAILURE);
    }
    json *obj = gahoodson_create(argv[1]);
    print_pairs(obj->pairs, obj->num_of_pairs, 0);
    print_objects(obj->objects, obj->num_of_objects, 0);
    print_lists(obj->json_lists, obj->num_of_lists, 0);
    gahoodson_delete(obj);
    printf("\n");
    return 0;
}

void print_list_elements(json_list_element **elements, int size, int subset) {
    int i;
    for(i = 0; i < size; i++) {
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
