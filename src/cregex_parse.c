#include "./cregex_parse.h"
#include <stdlib.h>

cregex_parse_str_section_args_t*  cregex_parse_str_section_arg_init(cregex_parse_str_section_args_t* args,const char* regex,cregex_element_t* elems,size_t elems_size){
    args->elems = elems;
    args->elems_i = 0;
    args->elems_size = elems_size;
    args->regex = regex;
    args->regex_i = 0;
    args->_elem_str_i = 0;
    args->_elem_allocated  = NULL;
    return args;
}

cregex_element_t*  cregex_parse_str_element_get_allocated(cregex_parse_str_section_args_t* args){
    return args->_elem_allocated;
}

size_t  cregex_parse_str_element_get_allocated_size(cregex_parse_str_section_args_t* args){
    return (args->elems+args->elems_i)-args->_elem_allocated;
}

size_t cregex_parse_str_element_alloc(cregex_parse_str_section_args_t* args,size_t n){
    if(args->elems_i+n > args->elems_size){
        return args->elems_size-args->elems_i;
    }
    args->_elem_allocated = args->elems;
    args->elems_i = args->elems_i+n;
    return n;
}

cregex_parse_result_status_t   cregex_parse_str_strbreak(cregex_parse_str_section_args_t* args){
    if(args->_elem_str_i>0){
        /*if(args->elems_i==args->elems_size){ return CREGEX_PARSE_OUT_OF_MEMORY; }
        cregex_element_init_str(&args->elems[args->elems_i++],args->regex + args->regex_i - args->_elem_str_i,args->_elem_str_i);
         */
        if(!cregex_parse_str_element_alloc(args,1)){
            return CREGEX_PARSE_OUT_OF_MEMORY;
        }
        cregex_element_init_str(cregex_parse_str_element_get_allocated(args),args->regex + args->regex_i - args->_elem_str_i,args->_elem_str_i);
        args->_elem_str_i=0;
    }
    return CREGEX_PARSE_SUCCESS;
}

cregex_parse_result_status_t   cregex_parse_str_repeat_strbreak(cregex_parse_str_section_args_t* args){
    if(args->_elem_str_i>1){
        cregex_parse_result_status_t res;
        --args->regex_i;
        --args->_elem_str_i;
        res = cregex_parse_str_strbreak(args);
        ++args->regex_i;
        ++args->_elem_str_i;        

        if(res != CREGEX_PARSE_SUCCESS) return res;
    }
    return cregex_parse_str_strbreak(args);
}



cregex_parse_result_status_t  cregex_parse_str_repeat(cregex_parse_str_section_args_t* args,size_t min,size_t max){
    /*if(!cregex_parse_str_element_get_allocated(args) || !cregex_element_is_repeat(&args->elems[args->elems_i-1],1,1)) return CREGEX_PARSE_SYNTAX_ERROR_INVALID_REPEAT_POSITION;*/
    if(!cregex_parse_str_element_get_allocated(args) || !cregex_element_is_repeat(cregex_parse_str_element_get_allocated(args),1,1)) return CREGEX_PARSE_SYNTAX_ERROR_INVALID_REPEAT_POSITION;
 
    cregex_element_set_repeat(cregex_parse_str_element_get_allocated(args),min,max);
    return CREGEX_PARSE_SUCCESS;
}

cregex_parse_result_status_t  cregex_parse_str_repeat_range(cregex_parse_str_section_args_t* args){
    size_t min,max,nsize;
    char* eptr;
    if(args->elems_i==0) return CREGEX_PARSE_SYNTAX_ERROR_INVALID_REPEAT_POSITION;
    ++args->regex_i;

    min = (size_t) strtoul(args->regex+args->regex_i,&eptr,0);
    nsize = (eptr-(args->regex+args->regex_i));
    if(nsize==0){
        return CREGEX_PARSE_SYNTAX_ERROR_INVALID_CHARACTER;
    }
    args->regex_i = args->regex_i + nsize;
    
    if(args->regex[args->regex_i]=='}'){
        cregex_element_set_repeat(cregex_parse_str_element_get_allocated(args),min,min);
        return CREGEX_PARSE_SUCCESS;
    }else if(args->regex[args->regex_i]!=','){
        return CREGEX_PARSE_SYNTAX_ERROR_INVALID_CHARACTER;
    }
    
    ++args->regex_i;    
    max = (size_t) strtoul(args->regex+args->regex_i,&eptr,0);
    nsize = (eptr-(args->regex+args->regex_i));
    if(nsize==0){
        cregex_element_set_repeat(cregex_parse_str_element_get_allocated(args),min,CREGEX_ELEMENT_REPEAT_INFINTE);
    }else{
        cregex_element_set_repeat(cregex_parse_str_element_get_allocated(args),min,max);
    }

    args->regex_i = args->regex_i + nsize;

    if(args->regex[args->regex_i]!='}'){
        return CREGEX_PARSE_SYNTAX_ERROR_INVALID_CHARACTER;
    }
    
    return CREGEX_PARSE_SUCCESS;
}

cregex_parse_result_status_t  cregex_parse_str_range(cregex_parse_str_section_args_t* args){
    cregex_parse_result_status_t res;

    if(   args->regex_i==0 
          /*  || !cregex_section_in(args->type,CREGEX_SECTION_BRAKET) ||  TODO implement braket and uncomment this instruction*/
          /*  ||  cregex_parse_str_is_terminated(&args->regex[ args->regex_i + 1 ])*/
          ){
            return CREGEX_PARSE_SUCCESS;
    }
    
    --args->regex_i;
    --args->_elem_str_i;
    if((res = cregex_parse_str_strbreak(args)) != CREGEX_PARSE_SUCCESS) return res;
    /*
    if(args->elems_i==args->elems_size){
        return CREGEX_PARSE_OUT_OF_MEMORY;
    }
    cregex_element_init_range(&args->elems[args->elems_i++],args->regex[args->regex_i],args->regex[args->regex_i+2]);
    */
    if(cregex_parse_str_element_alloc(args,1)!=1){
        return CREGEX_PARSE_OUT_OF_MEMORY;
    }
    cregex_element_init_range(cregex_parse_str_element_get_allocated(args),args->regex[args->regex_i],args->regex[args->regex_i+2]); 
    args->regex_i+=3;
    return CREGEX_PARSE_SUCCESS;
}

cregex_parse_result_status_t  cregex_parse_str_braket(cregex_parse_str_section_args_t* args){

}


cregex_parse_result_status_t   cregex_parse_str_section(cregex_parse_str_section_args_t* args,char termchr){
    cregex_parse_result_status_t res = CREGEX_PARSE_SUCCESS;
/*
    cregex_parse_str_result_t res;
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
    for(;args->regex[args->regex_i]!=termchr;++args->regex_i){
        switch(args->regex[args->regex_i]){
            case '-':
                res = cregex_parse_str_range(args);
                break;
            case '*':
                if((res = cregex_parse_str_repeat_strbreak(args)) != CREGEX_PARSE_SUCCESS) return res;
                if((res = cregex_parse_str_repeat(args,0,CREGEX_ELEMENT_REPEAT_INFINTE)) != CREGEX_PARSE_SUCCESS) return res;
                break;
            case '+':
                if((res = cregex_parse_str_repeat_strbreak(args)) != CREGEX_PARSE_SUCCESS) return res;
                if((res = cregex_parse_str_repeat(args,1,CREGEX_ELEMENT_REPEAT_INFINTE)) != CREGEX_PARSE_SUCCESS) return res;
                break;                
            case '?':
                if((res = cregex_parse_str_repeat_strbreak(args)) != CREGEX_PARSE_SUCCESS) return res;
                if((res = cregex_parse_str_repeat(args,0,1)) != CREGEX_PARSE_SUCCESS) return res;
                break;
            case '{':                
                if((res = cregex_parse_str_repeat_strbreak(args)) != CREGEX_PARSE_SUCCESS) return res;
                if((res = cregex_parse_str_repeat_range(args)) != CREGEX_PARSE_SUCCESS) return res;
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
    }

    res = cregex_parse_str_strbreak(args);

    return res;
}
