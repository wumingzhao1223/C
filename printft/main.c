#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define TYPENAME(T) _Generic((T),                               \
    int:"int",                                                  \
    char:"char",                                                \
    char*:"char*",                                              \
    const char*:"const char*",                                  \
    default:"?"                                                 \
)

#define TYPE_INT                    1
#define TYPE_CHAR                   2
#define TYPE_CHAR_PTR               3
#define TYPE_CONST_CHAR_PTR         4
#define TYPE_DEFAULT                5

#define TYPECODE(T) _Generic((T),                               \
    int:TYPE_INT,                                               \
    char:TYPE_CHAR,                                             \
    char*:TYPE_CHAR_PTR,                                        \
    const char*:TYPE_CONST_CHAR_PTR,                            \
    default:TYPE_DEFAULT                                        \
)

#define PRINT_BUF_SIZE 1024

#define NUMBER_BUF_SIZE 32

#define P(arg) TYPECODE(arg), (arg)

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

int snfmtv(char* s, int n, const char* fmt, va_list v)
{
    memset(s, 0, n);
    int fmtlen = strlen(fmt);
    int bufIndex = 0;
    for (int i = 0; i < fmtlen; i++)
    {
        if (fmt[i] != '{')
        {
            s[bufIndex++] = fmt[i];
        }
        else
        {
            for (int j = i + 1; j < fmtlen; j++)
            {
                if (fmt[j] == '}')
                {
                    int typecode = va_arg(v, int);
                    if (typecode == TYPE_INT)
                    {
                        int intval = va_arg(v, int);
                        char intstr[NUMBER_BUF_SIZE];
                        int intstr_len = snprintf(intstr, NUMBER_BUF_SIZE, "%d", intval);
                        memcpy(s + bufIndex, intstr, intstr_len);
                        bufIndex += intstr_len;
                    }
                    if (typecode == TYPE_CHAR)
                    {
                        char charval = va_arg(v, char);
                        char charstr[NUMBER_BUF_SIZE];
                        int charstr_len = snprintf(charstr, NUMBER_BUF_SIZE, "%c", charval);
                        memcpy(s + bufIndex, charstr, charstr_len);
                        bufIndex += charstr_len;
                    }
                    if (typecode == TYPE_CHAR_PTR || typecode == TYPE_CONST_CHAR_PTR)
                    {
                        char* str = va_arg(v, char*);
                        int str_len = strlen(str);
                        memcpy(s + bufIndex, str, str_len);
                        bufIndex += str_len;
                    }
                    i = j;
                    break;
                }
            }
        }
    }
    return 0;
}

int snfmt(char* s, int n, const char* fmt, ...)
{
    va_list v;
    va_start(v, fmt);
    int c = snfmtv(s, n, fmt, v);
    va_end(v);
    return c;
}

int printftv(const char* format, va_list args)
{
    char buf[PRINT_BUF_SIZE];
    int c = snfmtv(buf, PRINT_BUF_SIZE, format, args);
    printf(buf);
    return 0;
}

int printft(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    int c = printftv(format, args);
    va_end(args);
    return c;
}

int main(void)
{
    const char* name = "Bob";
    int age = 31;
    //output: Hi, Bob. I'm 31 years old.
    printft("I'm {}, I'm {} years old.\n", P(name), P(age));
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
