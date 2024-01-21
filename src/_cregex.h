#ifndef ___CREGEX_H__
#define ___CREGEX_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define CREGEX_ELEMENT_REPEAT_INFINTE 0

typedef enum{
    CREGEX_ELEMENT_TYPE_NONE,
    CREGEX_ELEMENT_TYPE_RANGE,
    CREGEX_ELEMENT_TYPE_STR,
    CREGEX_ELEMENT_TYPE_GROUP
}cregex_element_type_t;

typedef struct{
    cregex_element_type_t _type;
    union{
        struct{
            const char*     value;
            size_t          size;
        }str;
        struct{
            char        begin,end;
        }range;
        struct{
            size_t size;
        }group;
    }_data;
    struct{
        size_t min;
        size_t max;
    }_repeat;

    size_t   _or_next;
    /*TODO ANCHOR*/
}cregex_element_t;

cregex_element_t* cregex_element_init_range(cregex_element_t* obj,char begin,char end);
cregex_element_t* cregex_element_init_str(cregex_element_t* obj,const char* str, size_t strsize);
void              cregex_element_set_next_or_pos(cregex_element_t* obj,size_t pos);

cregex_element_t* cregex_element_set_repeat(cregex_element_t* obj,size_t min,size_t max);
/*only valid if cregex_element_is_repeat_max_infinite(obj)==false*/
size_t            cregex_element_get_repeat_max(cregex_element_t *obj);
size_t            cregex_element_get_repeat_min(cregex_element_t *obj);
bool              cregex_element_is_repeat(cregex_element_t *obj,size_t min,size_t max);


typedef struct{
    cregex_element_t* _parse_buffer;
    size_t            _parse_buffer_size_total;
    size_t            _parse_buffer_size_used;
}cregex_t;

typedef struct{
    char*             _read_buffer;
    size_t            _read_buffer_size;
    const cregex_t*   _parsed_regex;
    FILE*             _file;
    size_t            _read_limit;
}cregex_reader_file_t;



#endif
