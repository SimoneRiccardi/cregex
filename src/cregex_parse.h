#ifndef __CREGEX_PARSE_H__
#define __CREGEX_PARSE_H__

#include <stdbool.h>
#include "../cregex.h"

typedef enum{
    CREGEX_SECTION_NONE = 0,
    CREGEX_SECTION_GROUPING = 1,
    CREGEX_SECTION_BRAKET= 2,
    CREGEX_SECTION_COLLATION = 4
} cregex_section_t;

cregex_parse_str_result_t   cregex_parse_str_section(cregex_t* obj,const char* regex,cregex_section_t type);

#endif
