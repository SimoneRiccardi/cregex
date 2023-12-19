#include "./cregex_parse.h"

cregex_section_t   cregex_section_add(cregex_section_t elem,cregex_section_t start){ return start|elem;  }
bool               cregex_section_is(cregex_section_t elem,cregex_section_t toeval){return (elem&&toeval)!=0; }

cregex_parse_result_t   cregex_parse_str_section(cregex_t* obj,const char* regex,cregex_section_t type){
    size_t  i;
    
    for(i=0;;i++){
        switch(regex[i]){
            case '[':
            case '-':                
            case ']':
            case '(':
            case ')':
            case '*':
            case '+':
            case '?':
            case '{':
            case '}':
            case '^':
            case '$':
            case '|':
            default:
        }
    }
}
