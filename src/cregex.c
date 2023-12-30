#include "../cregex.h"
#include "./cregex_parse.h"

cregex_t*  cregex_create(cregex_t* obj,cregex_element_t* parse_buffer,size_t parse_buffer_size){
    obj->_parse_buffer = parse_buffer;
    obj->_parse_buffer_size_total = parse_buffer_size;
    return obj;
}

cregex_reader_file_t*  cregex_reader_file_init(cregex_reader_file_t* obj,const cregex_t* parsed_regex, FILE* file,size_t read_limit,char* read_buffer,size_t read_buffer_size){
    obj->_read_buffer = read_buffer;
    obj->_read_buffer_size = read_buffer_size;
    obj->_parsed_regex = parsed_regex;
    obj->_file = file;
    obj->_read_limit = read_limit;
    return obj;
}

cregex_parse_str_result_t   cregex_parse_str(cregex_t* obj,const char* regex){
    return cregex_parse_str_section(obj,regex,CREGEX_SECTION_NONE);
}

cregex_read_result_t  cregex_read_file(const cregex_reader_file_t* obj){
    
}
