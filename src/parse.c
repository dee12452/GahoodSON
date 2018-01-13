#include "parse.h"
#include <stdlib.h>
#include <stdio.h>

static void gahoodson_delete_json_obj(json_object *);
static void gahoodson_delete_json_list(json_list *);
static void gahoodson_delete_json_pair(json_pair *);

static void gahoodson_delete_json_str(json_string *);

json_object * gahoodson_create(const char *pathToJson) {
    json_object *obj = NULL;
    int i = 0;
    while(pathToJson[i] != '\0') continue;
    return obj;
}

void gahoodson_delete(json_object *json) {
    gahoodson_delete_json_obj(json);
}

void gahoodson_delete_json_obj(json_object *obj) {
    if(obj == NULL) return;

    /* iterator */
    int i;

    /* delete pairs */
    if(obj->pairs != NULL) {
        for(i = 0; i < obj->num_of_pairs; i++) {
            gahoodson_delete_json_pair(obj->pairs[i]);
        }
        free(obj->pairs);
        obj->pairs = NULL;
        obj->num_of_pairs = 0;
    }

    /* delete lists */
    if(obj->json_lists != NULL) {
        for(i = 0; i < obj->num_of_lists; i++) {
            gahoodson_delete_json_list(obj->json_lists[i]);
        }
        free(obj->json_lists);
        obj->json_lists = NULL;
        obj->num_of_lists = 0;
    }

    /* delete subobjects*/
    if(obj->sub_objects != NULL) {
        for(i = 0; i < obj->num_of_subobjects; i++) {
            gahoodson_delete_json_obj(obj->sub_objects[i]);
        }
        free(obj->sub_objects);
        obj->sub_objects = NULL;
        obj->num_of_subobjects = 0;
    }

    /* delete key */
    gahoodson_delete_json_str(obj->key);
    obj->key = NULL;

    free(obj);
}

void gahoodson_delete_json_list(json_list *list) {
    if(list == NULL) return;
    free(list);
}

void gahoodson_delete_json_pair(json_pair *pair) {
    gahoodson_delete_json_str(pair->key);
    gahoodson_delete_json_str(pair->str_val);
    if(pair->int_val != NULL) free(pair->int_val);
    if(pair->bool_val != NULL) free(pair->bool_val);
}

void gahoodson_delete_json_str(json_string *str) {
    if(str != NULL) {
        if(str->val != NULL) {
            free(str->val);
        }
        free(str);
    }
}
