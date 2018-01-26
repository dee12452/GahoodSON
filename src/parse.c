#include "parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

static const uint16_t FILE_LINE_MAX = 1000;
static const uint8_t FILE_MAX_LINES = 255;

/* Skip one char past the given character */
uint8_t skip_past_char(char *text, int *index, char target) {
    while(text[*index] != target 
            && text[*index] != '\0'
            && text[*index] != EOF) (*index)++;
    int result = text[*index] == '\0' || text[*index] == EOF ? FALSE : TRUE;
    (*index)++;
    return result;
}

/* Skip to the index of the given character */
uint8_t find_char(char *text, int *index, char target) {
    int result = skip_past_char(text, index, target);
    (*index)--;
    return result;
}

/* Runs through the string and checks equality to the comparator */
uint8_t equals_string(char *text, int *index, const char *compare) {
    int iterator = 0;
    while(text[*index] == compare[iterator] 
            && compare[iterator] != '\0'
            && text[*index] != '\0' && text[*index] != EOF) {
        (*index)++; iterator++;
    }
    if(compare[iterator] == '\0') return TRUE;
    return FALSE;
}

json_string * create_string(char *text, int *index) {
    char * str = (char *) malloc(sizeof(char) * FILE_LINE_MAX);
    strcpy(str, "");
    int size = 0;
    json_string *j_str = (json_string *) malloc(sizeof(json_string));
    j_str->val = NULL; j_str->size = 0;
    if(*index == 0) {
        j_str->val = str; j_str->size = size;
        return j_str;
    }
    while(text[*index] != '"' && text[*index - 1] != '\\') {
        char buf[2];
        buf[0] = text[*index];
        buf[1] = '\0';
        strcat(str, buf);
        (*index)++;
        size++;
    }
    (*index)++;
    char *temp = (char *) realloc(str, size + 1);
    if(temp == NULL) {
        j_str->val = str; j_str->size = size;
        return j_str;
    }
    else {
        str = NULL;
        j_str->val = temp; j_str->size = size;
        return j_str;
    }
}

json_bool * create_bool(uint8_t val) {
    /* Should only be passing in 1 or 0 */
    if(val != TRUE && val != FALSE) {
        return NULL;
    }
    json_bool *boolean = (json_bool *) malloc(sizeof(json_bool));
    boolean->val = val;
    return boolean;
}

json_int * create_int(int val) {
    json_int *integer = (json_int *) malloc(sizeof(json_int));
    integer->val = val;
    return integer;
}

/**************************/
/*** Deleting Functions ***/
/**************************/

static void gahoodson_delete_json_obj(json_object *);
static void gahoodson_delete_json_list(json_list *);
static void gahoodson_delete_json_list_element(json_list_element *);
static void gahoodson_delete_json_pair(json_pair *);
static void gahoodson_delete_json_str(json_string *);

void gahoodson_delete(json *obj) {
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
    if(obj->objects != NULL) {
        for(i = 0; i < obj->num_of_objects; i++) {
            gahoodson_delete_json_obj(obj->objects[i]);
        }
        free(obj->objects);
        obj->objects = NULL;
        obj->num_of_objects = 0;
    }

    free(obj);
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

/************************/
/*** Create Functions ***/
/************************/

static json * gahoodson_create_json(char *, int *);
static json_object * gahoodson_get_next_object(json_string *key, char *, int *);
static json_list * gahoodson_get_next_list(json_string *key, char *, int *);
static json_list_element * gahoodson_get_next_list_element(char *, int *);
static json_pair * gahoodson_get_next_pair(json_string *key, char *, int *);

json * gahoodson_create(const char *json_file) {
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
        int index = 0;
        return gahoodson_create_json(str, &index);
    }
    else {
        printf("Error: File not found.\n");
        return NULL;
    }
}

json * gahoodson_create_json(char *file_str, int *index) {
    json *obj = (json *) malloc(sizeof(json));
    obj->num_of_objects = 0; obj->objects = NULL;
    obj->num_of_lists = 0; obj->json_lists = NULL;
    obj->num_of_pairs = 0; obj->pairs = NULL;
    
    if(skip_past_char(file_str, index, '{') == TRUE) {
        while(skip_past_char(file_str, index, '"') == TRUE) {
            json_string *key = create_string(file_str, index);
            if(skip_past_char(file_str, index, ':') == FALSE) {
                gahoodson_delete_json_str(key); break;
            }
            while(file_str[*index] == ' ') (*index)++;
            if(file_str[*index] == '{') { gahoodson_get_next_object(key, file_str, index); }
            else if(file_str[*index] == '[') { gahoodson_get_next_list(key, file_str, index); }
            else { gahoodson_get_next_pair(key, file_str, index); }
            if(skip_past_char(file_str, index, ',') == FALSE) {
                gahoodson_delete_json_str(key); break;
            }
            key = NULL;
        }
    }
    return obj;
}

json_object * gahoodson_get_next_object(json_string *key, char *, int *) {
    json_object *json_obj = (json_object *) malloc(sizeof(json_obj));
    json_obj->key = key; 
    json_obj->num_of_subobjects = 0; json_obj->sub_objects = NULL;
    json_obj->num_of_lists = 0; json_obj->json_lists = NULL;
    json_obj->num_of_pairs = 0; json_obj->pairs = NULL;
    
    return json_obj;
}
 
json_list * gahoodson_get_next_list(json_string *key, char *, int *) {
    json_list *list = (json_list *) malloc(sizeof(json_list));
    list->key = key;
    list->num_of_elements = 0; list->elements = NULL;

    return list;
}

json_list_element * gahoodson_get_next_list_element(char *, int *) {
    json_list_element *element = (json_list_element *) malloc(sizeof(json_list_element));
    element->num_of_objects = 0; element->json_objects = NULL;
    element->num_of_pairs = 0; element->json_pairs = NULL;

    return element;
}

json_pair * gahoodson_get_next_pair(json_string *key, char *file_str, int *index) {
    json_pair *pair = (json_pair *) malloc(sizeof(json_pair));
    pair->key = key;
    pair->str_val = NULL;
    pair->int_val = NULL;
    pair->bool_val = NULL;

    if(file_str[*index] == '"') { 
        /* string val */
        (*index)++;
        pair->str_val = create_string(file_str, index);
        (*index)++;
    }
    else if(file_str[*index] - '0' < 10 && file_str[*index] - '0' >= 0) { 
        /* int val */
        int value = file_str[*index] - '0';
        (*index)++;
        while(file_str[*index] - '0' < 10 && file_str[*index] - '0' >= 0) {
            value *= 10;
            value += file_str[*index] - '0';
            (*index)++;
        }
        pair->int_val = create_int(value);
    }
    else {
        /* bool val */
        if(file_str[*index] == 't') {
            if(equals_string(file_str, index, "true") == TRUE) {
                printf("key1: %s\n", pair->key->val);
                pair->bool_val = create_bool(TRUE);
                printf("key2: %s\n", pair->key->val);
            }
            else {
                gahoodson_delete_json_pair(pair);
                return NULL;
            }
        }
        else if(file_str[*index] == 'f') {
            if(equals_string(file_str, index, "false") == TRUE) {
                pair->bool_val = create_bool(FALSE);
            }
            else {
                gahoodson_delete_json_pair(pair);
                return NULL;
            }
        }
        else {
            gahoodson_delete_json_pair(pair);
            return NULL;
        }
    }

    if(pair->bool_val != NULL) {
        printf("Created a pair = %s : %d\n", pair->key->val, pair->bool_val->val);
    }
    else if(pair->int_val != NULL) {
        printf("Created a pair = %s : %d\n", pair->key->val, pair->int_val->val);

    }
    else if(pair->str_val != NULL) {
        printf("Created a pair = %s : %s\n", pair->key->val, pair->str_val->val);
    }

    return pair;
}
