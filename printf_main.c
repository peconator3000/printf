#include "printf.h"

// int ft_printf(const char * param, ...)
// {
// }

int convertion(char c, va_list *str)
{
    if (c == 'c')
        write(1, str, 1);
    else if (c == 's')
        write(1, str, ft_strlen(str));
    else if (c == 'p')
        ft_address((unsigned int)&str[0], "0123456789abcdef");
    else
    {
        write(1, &c, 1);
        return(0);
    }
    return (1);
}

int parcing(char *str, char **set)
{
    if (!str)
        return 0;
    while(*str && *set)
    {
        if(*str == '%')
        {   
            if(convertion(*(str + 1), *set))
            {
                set++;
                str += 2;
            }
        }
        else
            write(1, str++, 1);
    }
    while(*str)
        write(1, str++, 1);
    return (1);
}

// int parcing(char *str, ...)
// {
//     va_list argptr;

//     if (!str)
//         return 0;
//     va_start(argptr);
//     while(*str)
//     {
//         if(*str == '%')
//         {   
//             if(convertion(*(str + 1), *set))
//             {
//                 set++;
//                 str += 2;
//             }
//         }
//         else
//             write(1, str++, 1);
//     }
//     while(*str)
//         write(1, str++, 1);
//     return (1);
// }

int sum(int n, ...)
{
    int res = 0;
    int *ptr;
    va_list argptr;

    va_start(argptr, n);
    while(n>0)
    {
        res += va_arg(argptr, int);
        n--;
    }
    return (res);
}

int main(void)
{   
    // printf("%d \n", sum(4, 1, 2, 3, 4));
    // printf("%d \n", sum(5, 12, 21, 13, 4, 5));
    char **set;
    // char mstr[] = "sym = %p and stroka2 = %s\n";

    set = malloc(sizeof(char *) * 3);
    set[0] = ft_strdup("hey1");
    set[1] = ft_strdup("hey2");
    set[2] = NULL;
    // parcing(mstr, set);
    printf("sym = %*.10p and stroka2 = %s\n", set[0], set[1]);
    return 0;
}