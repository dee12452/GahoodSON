#include "parse.h"
#include "stdio.h"

int main() {
    json *obj = gahoodson_create("test.json");
    printf("num objs = %d, num pairs = %d, num lists = %d\n",
            obj->num_of_objects,
            obj->num_of_pairs,
            obj->num_of_lists);
    gahoodson_delete(obj);
    return 0;
}
