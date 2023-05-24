#ifndef GAHOODSON_H
#define GAHOODSON_H

/*  *** HOW TO USE GahoodSON ***
 * 
 * - To Create a json object that contains all of the data,
 * call the following: 
 *      
 *      json * <variable_name_here> = gahoodson_create(<file_path_here>);
 *
 *   That will create a variable with all of the information stored in order as it appears.
 *
 * - ALWAYS call the following when you are FINISHED using the parsed data object:
 *      
 *      gahoodson_delete(<json_object_you_made>);
 * 
 *   Otherwise you will have memory leaks and for no reason!
 *
 *
 * - The "json" struct stores all of the objects, pairs, and lists in the json file.
 * - Pairs are just pairs and their values. 
 * - Objects have a key id and then carry other objects, lists or pairs.
 * - Lists have list elements and nothing else. Those list elements have no key id but will carry objects, lists, or pairs just like objects
 *
 * - json_string data type contains a null-terminated string as "key" and the size of the string
 * - json_int carries just a 32-bit integer value.
 * - json_bool carries an 8-bit value that SHOULD be only 1 or 0. 1 means TRUE, 0 means FALSE. 
 *
 * - You can traverse the json by using the num_of_<type> int stored in each json list, list element, or object. It is recommended to make a wrapper around this library, but that's up to you.
 *
 *   
 *
 *   Good Luck! ^_^ I hope this library serves you well!
 *
 * */
#ifdef __cplusplus
extern "C" {
#endif

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

/* Float Data */
typedef struct _JSON_Float {
    float val;
} json_float;

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
    json_float *float_val;
} json_pair;

typedef struct _JSON_Obj json_object;

typedef struct _JSON_List json_list;

/* JSON List Element (contains pairs and objects) */
typedef struct _JSON_List_Element {
    json_string *str_val;
    json_int *int_val;
    json_bool *bool_val;
    json_float *float_val;

    json_object **json_objects;
    int num_of_objects;

    json_list **json_lists;
    int num_of_lists;

    json_pair **json_pairs;
    int num_of_pairs;
} json_list_element;

/* JSON List (Array of pairs and objects) */
struct _JSON_List {
    json_string *key;

    json_list_element **elements;
    int num_of_elements;
};

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
json * gahoodson_create_from_file(const char *json_file);
json * gahoodson_create_from_string(char *json_str);
void gahoodson_delete(json *obj);

#ifdef __cplusplus
}
#endif

#endif
