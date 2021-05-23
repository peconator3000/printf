#include "printf.h"

int convertion(char c, va_list param)
{
    char *mid;

    if (c == 'c')
    {
        write(1, va_arg(param, char*), 1);
    }
    else if (c == 's')
    {
        mid = va_arg(param, char*);
        write(1, mid, ft_strlen(mid));
    }
    else if (c == 'p')
        ft_address(param, "0123456789abcdef");
    else
    {
        write(1, &c, 1);
        return(0);
    }
    return (1);
}

// int how(char *str)
// {
//     size_t i;

//     i = 0;
//     if (!str)
//         return (0);
//     while(*str)
//         if (*str++== '%')
//             i++;
//     return (i);
// }

// void mnogo(char *str, ...)
// {
//     va_list param;
//     size_t len;

//     //len = how(str);
//     va_start(param, str);
//     while (*str)
//     {
//         if(*str == '%')
//         {   
//             if(convertion(*(str + 1), param))
//                 str += 2;
//             else

//         }
//         else
//             write(1, str++, 1);
//     }
//     va_end(param);
// }

int main(void)
{
    // char **set;
    // char mstr[] = "sym = %p and stroka2 = %s\n";

    // set = malloc(sizeof(char *) * 3);
    // set[0] = ft_strdup("hey1");
    // set[1] = ft_strdup("hey2");
    // set[2] = NULL;
    // mnogo(mstr, 5, set[1]);
    printf("sym = %*7.b and stroka2 = %s\n",4, "hey");
    //printf("sym = %41s and stroka2\n", "hey");
    return 0;
}