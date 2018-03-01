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

#include "parse.h"

#ifdef __cplusplus
}
#endif

#endif
