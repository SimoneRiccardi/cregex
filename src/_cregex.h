#ifndef ___CREGEX_H__
#define ___CREGEX_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct{
    
}cregex_element_t;

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
