/** @file cregex.h
    @brief cregex interface
 */

#ifndef __CREGEX_H__
#define __CREGEX_H__

#include "./src/_cregex.h"

#include <stdlib.h>
#include <stdio.h>

/**
   @param  obj the object to initialize
   @param  parse_buffer array of elements used for parsing the regex
   @param  parse_buffer_size  size of parse_buffer
   @param  read_buffer        character buffer that will be used for reading
   @param  read_buffer_size   size of read_buffer
   @return     initalized object
 */
cregex_t*  cregex_init(cregex_t* obj,cregex_element_t* parse_buffer,size_t parse_buffer_size,char* read_buffer,size_t read_buffer_size);


typedef enum{
    CREGEX_PARSE_SUCCESS,
    CREGEX_PARSE_OUT_OF_MEMORY    
}cregex_parse_result_status_t;


typedef struct{
    cregex_parse_result_status_t  status; /** parse result */
    size_t                        parsed; /** in case of error the character when the error occurred */
}cregex_parse_result_t;

/**
   
   @param obj the object where the parse result will be memorized
   @param regex the regular exp
   @return     initalized objectression
   @return parse result
   @see cregex_parse_result_t
 */
cregex_parse_result_t    cregex_parse_str(cregex_t* obj,const char* regex);


typedef enum{
    CREGEX_READ_EOF,
    CREGEX_READ_REACHED_LIMIT,   /** returned if the read_limit number of character is reached @see cregex_read */
    CREGEX_READ_MATCH            /** returned as soon there is a complete match*/
}cregex_read_result_status_t;

typedef struct{
    cregex_read_result_status_t  status;       /** read result */
    size_t                       readed_size;  /** number of character readed */
    size_t                       matched_size; /** number of character that matches the regex */
}cregex_read_result_t;

/**
   
   @param obj the object that contains the parse regex and read data
   @param file the file to 
   @param read_limit the maximun number of character that should be readed. After reading 'read_limit' characters the function returns  with status CREGEX_READ_REACHED_LIMIT. If no limit is needed set the variable to 0
   @return read result
   @see cregex_read_result_t
   @see cregex_read_result_status_t
 */
cregex_read_result_t  cregex_read(cregex_t* obj,FILE* file,size_t read_limit);

#endif
