#include "parse.h"
#include <stdlib.h>
#include <stdio.h>

static void gahoodson_delete_json_obj(json_object *);
static void gahoodson_delete_json_list(json_list *);

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
    free(obj);
}

void gahoodson_delete_json_list(json_list *list) {
    if(list == NULL) return;
    free(list);
}


