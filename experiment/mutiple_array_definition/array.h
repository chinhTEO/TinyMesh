#define APPENDING_STR(...) char * const array[] = {__VA_ARGS__, NULL}

extern char * const array[];

void array_print(char * const array[]);