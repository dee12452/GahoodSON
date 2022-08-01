#include <GahoodSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void unit_test();

void print_bool(json_bool *, int);
void print_str(json_string *, int);
void print_int(json_int *, int);
void print_lists(json_list **, int, int);
void print_objects(json_object **, int, int);
void print_pairs(json_pair **, int, int);

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Running unit tests...\n");
        unit_test();
    } else {
        printf("Printing metrics for json file: %s\n", argv[1]);
        json *obj = gahoodson_create_from_file(argv[1]);
        printf("Printing %d pairs\n", obj->num_of_pairs);
        print_pairs(obj->pairs, obj->num_of_pairs, 0);
        printf("Printing %d objs\n", obj->num_of_objects);
        print_objects(obj->objects, obj->num_of_objects, 0);
        printf("Printing %d lists\n", obj->num_of_lists);
        print_lists(obj->json_lists, obj->num_of_lists, 0);
        gahoodson_delete(obj);
        printf("\n");
    }

    return 0;
}

void unit_test() {
    /********************
     * Test file 3 tests
     ********************/
    const char* test_file3 = "test_json/test3.json";
    json *obj = gahoodson_create_from_file(test_file3);

    if(obj->num_of_objects != 1) {
        printf("TEST FAILURE: expected num objects 1, got %d\n", obj->num_of_objects);
        exit(EXIT_FAILURE);
    }

    const char* abc1 = obj->objects[0]->json_lists[0]->elements[0]->json_pairs[0]->str_val->val;
    const int abc2 = obj->objects[0]->json_lists[0]->elements[1]->json_pairs[0]->int_val->val;
    if(strcmp(abc1, "123")) {
        printf("TEST FAILURE: expected abc1 string pair to equal \"abc\", got \"%s\"\n", abc1);
        exit(EXIT_FAILURE);
    }
    if(abc2 != 123) {
        printf("TEST FAILURE: expected abc2 to equal 123, got %d\n", abc2);
        exit(EXIT_FAILURE);
    }

    json_pair** pairs = obj->objects[0]->pairs;
    int i;
    uint8_t checked = 0;
    for(i = 0; i < obj->objects[0]->num_of_pairs; i++) {
        if(strcmp("false", pairs[i]->key->val)) {
            continue;
        }
        checked = 1;
        if(pairs[i]->bool_val->val != 0) {
            printf("TEST FAILURE: expected pair \"false\" to equal 0 (false), got %d\n", pairs[i]->bool_val->val);
            exit(EXIT_FAILURE);
        }
    }
    if(checked == 0) {
        printf("TEST FAILURE: failed to find target pair: \"false\"\n");
        exit(EXIT_FAILURE);
    }

    gahoodson_delete(obj);


    /********************
     * Test file 7 tests
     ********************/
    const char* test_file7 = "test_json/test7.json";
    obj = gahoodson_create_from_file(test_file7);

    if(obj->num_of_objects != 0 || obj->num_of_pairs != 0 || obj->num_of_lists != 1) {
        printf("TEST FAILURE: Invalid stats gathered for file 7: objs=%d, pairs=%d, lists=%d\n",
               obj->num_of_objects,
               obj->num_of_pairs,
               obj->num_of_lists
               );
        exit(EXIT_FAILURE);
    }

    const float floatVal1 = obj->json_lists[0]->elements[0]->json_pairs[0]->float_val->val;
    const float floatVal2 = obj->json_lists[0]->elements[1]->json_pairs[0]->float_val->val;
    const float floatVal3 = obj->json_lists[0]->elements[2]->json_pairs[0]->float_val->val;
    if(floatVal1 != 0.0) {
        printf("TEST FAILURE: failed to parse float value properly: expected ABOUT 0 got %f\n", floatVal1);
        exit(EXIT_FAILURE);
    }
    if(floatVal2 > -2.09 || floatVal2 < -2.11) {
        printf("TEST FAILURE: failed to parse float value properly: expected ABOUT -2.1 got %f\n", floatVal2);
        exit(EXIT_FAILURE);
    }
    if(floatVal3 > 3.257 || floatVal3 < 3.255) {
        printf("TEST FAILURE: failed to parse float value properly: expected ABOUT 3.256 got %f\n", floatVal3);
        exit(EXIT_FAILURE);
    }

    gahoodson_delete(obj);

    printf("ALL TESTS PASSED\n");
    exit(EXIT_SUCCESS);
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
