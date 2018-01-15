#include "parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const uint16_t FILE_LINE_MAX = 1000;
static const uint8_t FILE_MAX_LINES = 255;

/************************/
/*** Create Functions ***/
/************************/

static json_object * gahoodson_create_json_object(char *, int);

json_object * gahoodson_create(const char *json_file) {
    FILE *file = fopen(json_file, "rb");
    if(file != NULL) {
        char buffer[FILE_LINE_MAX];
        char str[FILE_LINE_MAX * FILE_MAX_LINES];
        strcpy(str, ""); 
        while(fgets(buffer, FILE_LINE_MAX, file) != NULL) {
            strcat(str, buffer);
        }
        printf("%s\n", str);
        fclose(file);
        return gahoodson_create_json_object(str, 0);
    }
    else {
        printf("Error: File not found.\n");
        return NULL;
    }
}

json_object * gahoodson_create_json_object(char *file_str, int index) {
    return NULL;
}

/**************************/
/*** Deleting Functions ***/
/**************************/

static void gahoodson_delete_json_obj(json_object *);
static void gahoodson_delete_json_list(json_list *);
static void gahoodson_delete_json_list_element(json_list_element *);
static void gahoodson_delete_json_pair(json_pair *);
static void gahoodson_delete_json_str(json_string *);

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
    
    int i;

    if(list->elements != NULL) {
        for(i = 0; i < list->num_of_elements; i++) {
            gahoodson_delete_json_list_element(list->elements[i]);
        }
        free(list->elements);
        list->elements = NULL;
        list->num_of_elements = 0;
    }

    free(list);
}

void gahoodson_delete_json_list_element(json_list_element *element) {
    if(element == NULL) return;

    int i;

    if(element->json_pairs != NULL) {
        for(i = 0; i < element->num_of_pairs; i++) {
            gahoodson_delete_json_pair(element->json_pairs[i]);
        }
        free(element->json_pairs);
        element->json_pairs = NULL;
        element->num_of_pairs = 0;
    }

    if(element->json_objects != NULL) {
        for(i = 0; i < element->num_of_objects; i++) {
            gahoodson_delete_json_obj(element->json_objects[i]);
        }
        free(element->json_objects);
        element->json_objects = NULL;
        element->num_of_objects = 0;
    }

    free(element);
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
