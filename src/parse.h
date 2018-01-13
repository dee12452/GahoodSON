#ifndef GAHOODSON_PARSE_H
#define GAHOODSON_PARSE_H

#ifndef NULL
#define NULL 0
#endif

/* Data types */
typedef struct _JSON_Str {
    char *val;
    int size;
} json_string;

typedef struct _JSON_Int {
    int val;
} json_int;

typedef struct _JSON_Bool {
    char val;
} json_bool;
/* End data types */

/* JSON Types */
typedef struct _JSON_Pair {
    json_string *key;
    
    json_string *str_val;
    json_int *int_val;
    json_bool *bool_val;
} json_pair;

typedef struct _JSON_Obj json_object;

typedef struct _JSON_List {
    json_object **json_objects;
    int num_of_objects;

    json_pair **json_pairs;
    int num_of_pairs;
} json_list;

struct _JSON_Obj {
    json_string *key;
    
    json_pair **values;
    int num_of_values;

    json_list *json_list;

    struct _JSON_Obj **sub_objects;
    int num_of_subobjects;
};
/* End JSON Types */

/* Constructor / Destructor */
json_object * gahoodson_create(const char *pathToJson);
void gahoodson_delete(json_object *json);

#endif
