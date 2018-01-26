#ifndef GAHOODSON_PARSE_H
#define GAHOODSON_PARSE_H

#include <stdint.h>

/******************/
/*** Data types ***/
/******************/

/* String Data */
typedef struct _JSON_Str {
    char *val;
    int size;
} json_string;

/* Integer Data */
typedef struct _JSON_Int {
    int val;
} json_int;

/* Boolean Data */
typedef struct _JSON_Bool {
    uint8_t val;
} json_bool;

/**********************/
/*** End data types ***/
/**********************/

/******************/
/*** JSON Types ***/
/******************/

/* JSON Pair (key : val) */
typedef struct _JSON_Pair {
    json_string *key;
    
    json_string *str_val;
    json_int *int_val;
    json_bool *bool_val;
} json_pair;

typedef struct _JSON_Obj json_object;

/* JSON List Element (contains pairs and objects) */
typedef struct _JSON_List_Element {
    json_object **json_objects;
    int num_of_objects;

    json_pair **json_pairs;
    int num_of_pairs;
} json_list_element;

/* JSON List (Array of pairs and objects) */
typedef struct _JSON_List {
    json_string *key;
    
    json_list_element **elements;
    int num_of_elements;
} json_list;

/* JSON Object defined by key (Contains lists and data types) */
struct _JSON_Obj {
    json_string *key;
    
    json_pair **pairs;
    int num_of_pairs;

    json_list **json_lists;
    int num_of_lists;

    struct _JSON_Obj **sub_objects;
    int num_of_subobjects;
};

typedef struct _JSON {
    json_pair **pairs;
    int num_of_pairs;

    json_list **json_lists;
    int num_of_lists;

    struct _JSON_Obj **objects;
    int num_of_objects;
} json;

/**********************/
/*** End JSON Types ***/
/**********************/

/* Constructor / Destructor */
json * gahoodson_create(const char *json);
void gahoodson_delete(json *obj);

#endif
