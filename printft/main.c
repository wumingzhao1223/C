#include <stdio.h>

#define TYPENAME(T) _Generic((T),                               \
    int:"int",                                                  \
    char:"char",                                                \
    char*:"char*",                                              \
    const char*:"const char*",                                  \
    default:"?"                                                 \
)

int main(void)
{
    int i = 1;
    printf("%s\n", TYPENAME(i));
    printf("%s\n", TYPENAME(1));
    char c = 'a';
    printf("%s\n", TYPENAME(c));
    printf("%s\n", TYPENAME('a'));
    printf("%s\n", TYPENAME((char)97));
    char* s = "string";
    printf("%s\n", TYPENAME(s));
    printf("%s\n", TYPENAME("string"));
    const char* cs = "cstring";
    printf("%s\n", TYPENAME(cs));
    printf("%s\n", TYPENAME((const char*)"cstring"));
    return 0;
}
