typedef unsigned char bool;
#define false 0
#define true 1

/*
Macro that converts args (...) into (numArgs, ...) meaning number of args does not have to be declared when calling a function
*/
#define NUMARGS(type, ...) (sizeof((type[]){0, ##__VA_ARGS__}) / sizeof(type) - 1)