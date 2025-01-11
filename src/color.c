#include "color.h"

const char* color_start(enum color_t c) {
    char* str[] = {"\33[38:5:0m", "\33[38:5:15m", "\33[38:5:208m", "\33[38:5:13m", "\33[38:5:135m", "\33[38:5:11m", "\33[38:5:12m", "\33[38:5:1m", "\33[38:5:10m", "\33[38:5:9m", "\33[38:5:0m"};
    return str[c];
}


const char* color_to_string(enum color_t c){
    char* str[] = {"black", "white", "orange", "pink", "violet", "yellow", "blue", "brown", "green", "red", "shiny", "max colors"};
    return str[c];
}

const char* color_stop() {
    return "\33[00m";
}
