#ifndef __CREGEX_PARSE_H__
#define __CREGEX_PARSE_H__

#include <stdbool.h>
#include "../cregex.h"


typedef struct{
    cregex_element_t* elems;
    size_t   elems_i;
    size_t   elems_size;

    const char* regex;
    size_t   regex_i;

    size_t   _elem_str_i;
}cregex_parse_str_section_args_t;


cregex_parse_str_section_args_t*  cregex_parse_str_section_arg_init(cregex_parse_str_section_args_t* args,const char* regex,cregex_element_t* elems,size_t elems_size);
cregex_parse_result_status_t   cregex_parse_str_section(cregex_parse_str_section_args_t* args,char termchr);
#endif
