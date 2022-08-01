# GahoodSON

GahoodSON is a very minimal JSON parser written in C. It is intended to be a fast cross-platform solution to parsing JSON files for any given application.

# Install

On a Unix-based environment, just use cmake and make to create the library binary.
```
$ cmake . && make
```
This will produce the libGahoodSON.a binary that you can now include in your project. Make sure to grab `src/\*.h` and throw them into your include folders.

On windows, you will follow the same step, but the output will be a different file. 


## How to use GahoodSON

 - To Create a json object that contains all of the data, call the following:<br>
 `
       json * <variable_name_here> = gahoodson_create_from_file(<file_path_here>);
 `
 <br> or <br>
 `
       json * <variable_name_here> = gahoodson_create_from_string(<passed_json_string>);
 `

  - ALWAYS call the following when you are FINISHED using the parsed data object:
       `
       gahoodson_delete(<json_object_you_made>);
       `
 
  - The "json" struct stores all the objects, pairs, and lists in the json file.
  - Pairs are just pairs and their values. 
  - Objects have a key id and then carry other objects, lists or pairs.
  - Lists have list elements and nothing else. Those list elements have no key id but will carry objects, lists, or pairs just like objects
 
  - json_string data type contains a null-terminated string as "key" and the size of the string
  - json_int carries just a 32-bit integer value.
  - json_bool carries an 8-bit value that SHOULD be only 1 or 0. 1 means TRUE, 0 means FALSE. 
 
  - You can traverse the json by using the num_of_<type> int stored in each json list, list element, or object. It is recommended to make a wrapper around this library, but that's up to you.
