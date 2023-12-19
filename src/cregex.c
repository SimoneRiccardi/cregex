#include "../cregex.h"


cregex_t*  cregex_create(cregex_t* obj,cregex_element_t* parse_buffer,size_t parse_buffer_size,char* read_buffer,size_t read_buffer_size){
    obj->_parse_buffer = parse_buffer;
    obj->_parse_buffer_size_total = parse_buffer_size;
    obj->_read_buffer = read_buffer;
    obj->_read_buffer_size = read_buffer_size;
    return obj;
}

cregex_parse_result_t   cregex_parse_str(cregex_t* obj,const char* regex){

}

cregex_read_result_t  cregex_read(cregex_t* obj,FILE* file,size_t read_limit){
    
}
