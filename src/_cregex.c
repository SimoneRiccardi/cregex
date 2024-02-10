#include "./_cregex.h"

cregex_element_t* cregex_element_init(cregex_element_t* obj){
    cregex_element_set_repeat(obj,1,1);
    return obj;
}

cregex_element_t* cregex_element_init_range(cregex_element_t* obj,char begin,char end){
    cregex_element_init(obj);
    obj->_type = CREGEX_ELEMENT_TYPE_RANGE;
    obj->_data.range.begin=begin;
    obj->_data.range.end=end;
    return obj;
}
cregex_element_t* cregex_element_init_array(cregex_element_t* obj,cregex_element_array_type_t type, size_t size){
    cregex_element_init(obj);
    obj->_type = CREGEX_ELEMENT_TYPE_ARRAY;
    obj->_data.array.type=type; 
    obj->_data.array.size=size;
    return obj;
}
cregex_element_t* cregex_element_init_str(cregex_element_t* obj,const char* str, size_t strsize){
    cregex_element_init(obj);
    obj->_type = CREGEX_ELEMENT_TYPE_STR;
    obj->_data.str.size=strsize;
    obj->_data.str.value=str;
    return obj;
}

size_t cregex_element_array_get_size(cregex_element_t *obj){
    return obj->_data.array.size;
}
void cregex_element_array_set_size(cregex_element_t *obj,size_t s){
    obj->_data.array.size=s;
}
void cregex_element_array_add_size(cregex_element_t *obj,int s){
    obj->_data.array.size+=s;
}

cregex_element_t* cregex_element_set_repeat(cregex_element_t* obj,size_t min,size_t max){
    obj->_repeat.min=min;
    obj->_repeat.max=max;
    return obj;
}

bool              cregex_element_is_repeat_max_infinite(cregex_element_t *obj){
    return   obj->_repeat.max==CREGEX_ELEMENT_REPEAT_INFINTE;
}
/*only valid if cregex_element_is_repeat_max_infinite(obj)==false*/
size_t            cregex_element_get_repeat_max(cregex_element_t *obj){
    return obj->_repeat.min;
}
size_t            cregex_element_get_repeat_min(cregex_element_t *obj){
    return obj->_repeat.max;
}

bool            cregex_element_is_repeat(cregex_element_t *obj,size_t min,size_t max){
    return obj->_repeat.min==min && obj->_repeat.max==max;
}
