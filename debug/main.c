#include "../cregex.h"

int cregex_parse_debug(){
    cregex_t re;
    cregex_element_t   pbuf[1000];
    
    cregex_parse_str(  cregex_init(&re,pbuf,1000) , "c{1,5}fghijk{6,}zzz{1,:}");
    return 0;
}

int main(){
    int r;
    r = cregex_parse_debug();
    if(r!=0)return r;
    
    return 0;
}
