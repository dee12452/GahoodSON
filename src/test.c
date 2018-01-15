#include "parse.h"

int main() {
    json_object *obj = gahoodson_create("test.json");
    gahoodson_delete(obj);
    return 0;
}
