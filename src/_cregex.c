#include "./_cregex.h"

cregex_element_t* cregex_element_init(cregex_element_t* obj){
    cregex_element_set_repeat(obj,1,1);
    obj->_or_next = 0;
    return obj;
}

cregex_element_t* cregex_element_init_range(cregex_element_t* obj,char begin,char end){
    cregex_element_init(obj);
    obj->_type = CREGEX_ELEMENT_TYPE_RANGE;
    obj->_data.range.begin=begin;
    obj->_data.range.end=end;
    return obj;
}
cregex_element_t* cregex_element_init_str(cregex_element_t* obj,const char* str, size_t strsize){
    cregex_element_init(obj);
    obj->_type = CREGEX_ELEMENT_TYPE_STR;
    obj->_data.str.size=strsize;
    obj->_data.str.value=str;
    return obj;
}
cregex_element_t* cregex_element_set_repeat(cregex_element_t* obj,size_t min,size_t max){
    obj->_repeat.min=min;
    obj->_repeat.max=max;
    return obj;
}
void cregex_element_set_next_or_pos(cregex_element_t* obj,size_t pos){
    obj->_or_next = pos;
}

cregex_element_t* cregex_element_set_repeat_max_infinite(cregex_element_t* obj,size_t min){
    obj->_repeat.min=min;
    obj->_repeat.max=0;
    return obj;    
}
bool              cregex_element_is_repeat_max_infinite(cregex_element_t *obj){
    return   obj->_repeat.max==0;
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
