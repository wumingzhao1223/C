#include <stdio.h>

#define TYPENAME(T) _Generic((T),                               \
    int:"int",                                                  \
    char:"char",                                                \
    char*:"char*",                                              \
    const char*:"const char*",                                  \
    default:"?"                                                 \
)

#define print(T) _Generic((T),                                  \
    int:printf("%d", (T)),                                      \
    char:printf("%c", (T)),                                     \
    char*:printf("%s", (T)),                                    \
    const char*:printf("%s", (T)),                              \
    default:printf("?")                                         \
)

#define println(T) _Generic((T),                                  \
    int:printf("%d\n", (T)),                                      \
    char:printf("%c\n", (T)),                                     \
    char*:printf("%s\n", (T)),                                    \
    const char*:printf("%s\n", (T)),                              \
    default:printf("?\n")                                         \
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

    int i2 = 1;
    print(i2);
    print(1);
    char c2 = 'a';
    print(c2);
    print('a');
    print((char)97);
    char* s2 = "string";
    print(s2);
    print("string");
    const char* cs2 = "cstring";
    print(cs2);
    print((const char*)"cstring");

    return 0;
}
