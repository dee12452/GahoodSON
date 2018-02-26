#include "parse.h"
#include "stdio.h"

void print_lists(json_list **, int size);
void print_objects(json_object **, int size);
void print_pairs(json_pair **, int size);

int main() {
    json *obj = gahoodson_create("test.json");
    print_pairs(obj->pairs, obj->num_of_pairs);
    print_objects(obj->objects, obj->num_of_objects);
    print_lists(obj->json_lists, obj->num_of_lists);
    gahoodson_delete(obj);
    return 0;
}

void print_list_elements(json_list_element **elements, int size) {
    int i;
    for(i = 0; i < size; i++) {
        print_pairs(elements[i]->json_pairs, elements[i]->num_of_pairs);
        print_objects(elements[i]->json_objects, elements[i]->num_of_objects);
        print_lists(elements[i]->json_lists, elements[i]->num_of_lists);
    }
}

void print_lists(json_list **lists, int size) {
    int i;
    for(i = 0; i < size; i++) {
        printf("%s\n", lists[i]->key->val);
        print_list_elements(lists[i]->elements, lists[i]->num_of_elements);
        printf("\n");
    }
}

void print_objects(json_object **objs, int size) {
    int i;
    for(i = 0; i < size; i++) {
        printf("%s\n", objs[i]->key->val);
        print_pairs(objs[i]->pairs, objs[i]->num_of_pairs);
        print_objects(objs[i]->sub_objects, objs[i]->num_of_subobjects);
        print_lists(objs[i]->json_lists, objs[i]->num_of_lists);
    }
}

void print_pairs(json_pair **pairs, int size) {
    int i;
    for(i = 0; i < size; i++) {
        printf("%s", pairs[i]->key->val);
        if(pairs[i]->bool_val != NULL) {
            printf(" %d\n", pairs[i]->bool_val->val);
        }
        else if(pairs[i]->int_val != NULL) {
            printf(" %d\n", pairs[i]->int_val->val);
        }
        else if(pairs[i]->str_val != NULL) {
            printf(" %s\n", pairs[i]->str_val->val);
        }
        printf("\n");
    }
}
