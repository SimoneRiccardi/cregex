#include "./cregex_parse.h"
#include <stdlib.h>

bool               cregex_parse_str_is_terminated(const char* str){
    /*TODO implement*/
    return *str=='\0';
}


cregex_parse_str_section_args_t*  cregex_parse_str_section_arg_init(cregex_parse_str_section_args_t* args,const char* regex,cregex_element_t* elems,size_t elems_size){
    args->elems = elems;
    args->elems_i = 0;
    args->elems_size = elems_size;
    args->regex = regex;
    args->regex_i = 0;
    args->_elem_str_i = 0;
    return args;
}

cregex_parse_result_status_t   cregex_parse_str_strbreak(cregex_parse_str_section_args_t* args){
    if(args->_elem_str_i>0){
        if(args->elems_i==args->elems_size){
            return CREGEX_PARSE_OUT_OF_MEMORY;
        }
        cregex_element_init_str(&args->elems[args->elems_i++],args->regex + args->regex_i - args->_elem_str_i,args->_elem_str_i);
        args->_elem_str_i=0;
    }
    return CREGEX_PARSE_SUCCESS;
}

cregex_parse_result_status_t  cregex_parse_str_range(cregex_parse_str_section_args_t* args){
    cregex_parse_result_status_t res;

    if(   args->regex_i==0 ||
          /*                      !cregex_section_in(args->type,CREGEX_SECTION_BRAKET) ||  TODO implement braket and uncomment this instruction*/
          cregex_parse_str_is_terminated(&args->regex[ args->regex_i + 1 ])
          ){
            return CREGEX_PARSE_SUCCESS;
    }
                
    
    --args->regex_i;
    --args->_elem_str_i;
    if((res = cregex_parse_str_strbreak(args)) != CREGEX_PARSE_SUCCESS) return res;

    if(args->elems_i==args->elems_size){
        return CREGEX_PARSE_OUT_OF_MEMORY;
    }
    cregex_element_init_range(&args->elems[args->elems_i++],args->regex[args->regex_i],args->regex[args->regex_i+2]);
    args->regex_i+=3;
    return CREGEX_PARSE_SUCCESS;
}

cregex_parse_result_status_t  cregex_parse_str_repeat(cregex_parse_str_section_args_t* args,size_t min,size_t max){
    if(args->elems_i==0 || cregex_element_is_repeat(&args->elems[args->elems_i-1],1,1)) return CREGEX_PARSE_SYNTAX_ERROR_INVALID_REPEAT_POSITION;

    cregex_element_set_repeat(&args->elems[args->elems_i-1],0,1);
    return CREGEX_PARSE_SUCCESS;
}

cregex_parse_result_status_t  cregex_parse_str_repeat_inf(cregex_parse_str_section_args_t* args,size_t min){
    if(args->elems_i==0 || cregex_element_is_repeat(&args->elems[args->elems_i-1],1,1)) return CREGEX_PARSE_SYNTAX_ERROR_INVALID_REPEAT_POSITION;    

    cregex_element_set_repeat_max_infinite(&args->elems[args->elems_i-1],min);
    return CREGEX_PARSE_SUCCESS;             
}

cregex_parse_result_status_t  cregex_parse_str_repeat_range(cregex_parse_str_section_args_t* args){
    /*TODO test*/
    size_t min,max,nsize;
    char* eptr;
    if(args->elems_i==0) return CREGEX_PARSE_SYNTAX_ERROR_INVALID_REPEAT_POSITION;
    ++args->regex_i;

    min = (size_t) strtoull(args->regex+args->regex_i,&eptr,0);
    nsize = ((args->regex+args->regex_i)-eptr);
    if(nsize==0){
        return CREGEX_PARSE_SYNTAX_ERROR_INVALID_CHARACTER;
    }
    args->regex_i = args->regex_i + nsize;

    if(args->regex[args->regex_i]=='}'){
        cregex_element_set_repeat(&args->elems[args->elems_i-1],min,min);        
        return CREGEX_PARSE_SUCCESS;
    }else if(args->regex[args->regex_i]!=','){
        return CREGEX_PARSE_SYNTAX_ERROR_INVALID_CHARACTER;
    }
    
    ++args->regex_i;    
    max = (size_t) strtoull(args->regex+args->regex_i,&eptr,0);
    nsize = ((args->regex+args->regex_i)-eptr);
    if(nsize==0){
        cregex_element_set_repeat_max_infinite(&args->elems[args->elems_i-1],min);
    }else{
        cregex_element_set_repeat(&args->elems[args->elems_i-1],min,max);
    }

    args->regex_i = args->regex_i + nsize;

    if(args->regex[args->regex_i]!='}'){
        return CREGEX_PARSE_SYNTAX_ERROR_INVALID_CHARACTER;
    }
    
    return CREGEX_PARSE_SUCCESS;
}

cregex_parse_result_status_t   cregex_parse_str_section(cregex_parse_str_section_args_t* args){
    cregex_parse_result_status_t res = CREGEX_PARSE_SUCCESS;
    /*    cregex_parse_str_result_t res;
    res.n_elements_used = 0;
    res.str_regex_i     = 0;
    size_t elem_str_i = 0;
    
    #define CREGEX_PARSE_STR_SECTION_ASSERT() {\
            if(res.n_elements_used==elems_n){               \
                res.status = CREGEX_PARSE_OUT_OF_MEMORY;    \
                return res;                                 \
            }                                               \
    }

    #define CREGEX_PARSE_STR_SECTION_BREAK() {                              \
            if(elem_str_i>0) {                                              \
                CREGEX_PARSE_STR_SECTION_MEMORY_ASSERT()                    \
                cregex_element_init_str(elems[res.n_elements_used++],regex+res.str_regex_i-elem_str_i,elem_str_i); \
                elem_str_i=0;                                               \
            }                                                               \
    }
    */
    for(;!cregex_parse_str_is_terminated(&args->regex[args->regex_i]);++args->regex_i){
        switch(args->regex[args->regex_i]){
            case '-':
                res = cregex_parse_str_range(args);
                break;
            case '*':
                if((res = cregex_parse_str_strbreak(args)) != CREGEX_PARSE_SUCCESS) break;
                res = cregex_parse_str_repeat_inf(args,0);
                break;
            case '+':
                if((res = cregex_parse_str_strbreak(args)) != CREGEX_PARSE_SUCCESS) break;                
                res = cregex_parse_str_repeat_inf(args,1);
                break;                
            case '?':
                if((res = cregex_parse_str_strbreak(args)) != CREGEX_PARSE_SUCCESS) break;                
                res = cregex_parse_str_repeat(args,0,1);
                break;
            case '{':
                if((res = cregex_parse_str_strbreak(args)) != CREGEX_PARSE_SUCCESS) break;                
                res = cregex_parse_str_repeat_range(args);
                break;
            case '[':
            case ']':
            case '(':
            case ')':
            case '^':
            case '$':
            case '|':
            case '\0':
            default:
                ++args->_elem_str_i;
                break;
        }

        if(res != CREGEX_PARSE_SUCCESS) return res;
    }

    return res;
}
