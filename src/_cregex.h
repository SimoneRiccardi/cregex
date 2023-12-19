#ifndef ___CREGEX_H__
#define ___CREGEX_H__

#include <stdlib.h>

typedef struct{
    
}cregex_element_t;

typedef struct{
    cregex_element_t* _parse_buffer;
    size_t            _parse_buffer_size_total;
    size_t            _parse_buffer_size_used;    
    char*             _read_buffer;
    size_t            _read_buffer_size;
}cregex_t;

#endif
