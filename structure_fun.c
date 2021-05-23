#include "printf.h"

s_elem *ft_newel(void)
{
    s_elem *res;

    res = (s_elem *)malloc(sizeof(*res));
    if (!res)
        return (NULL);
    res->width = 0;
    res->flag = 'n';//net flaga
    res->type = 'n';
    res->accur = 0;
    return (res);
}

int convertion_type(char c, va_list param)
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

int convertion_flag(char flag)
{
    if (flag == '0')
}

void ft_show_struct(s_elem *elem)
{
    

}