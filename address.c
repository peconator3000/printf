#include "printf.h"

// void ft_address(size_t num, char *hex_set)
// {
//     ssize_t i;
//     size_t mid;

//     if (!num)
//     {
//         write(1, "(null)", 6);
//         return ;
//     }
//     i = 7;
//     write(1, "0x", 2);
//     if (num == 0)
//         write(1, "0", 1);
//     while (i >= 0)
//     {
//         mid = num >> (i-- * 4);
//         write(1, &hex_set[mid & 15], 1);
        
//     }
// }

void ft_address(unsigned long num, char *hex_set, char system)
{
    int i;
    long long unsigned mid;

    if (!num)
    {
        write(1, "0x0", 3);
        return ;
    }
    i = 15;
    if (system == 'p')
        write(1, "0x", 2);
    if (num == 0)
        write(1, "0", 1);
    while (i >= 0)
    {
        mid = num >> (i * 4);
        if (mid != 0 && num>>(i * 4))
            write(1, &hex_set[mid & 15], 1);
        i--;
    }
}

ssize_t ft_howhex_num(unsigned long num, char system)
{
    int i;
    long unsigned mid;
    ssize_t res;

    if (!num)
        return (3);
    i = 15;
    res = 0;
    if (system == 'p')
        res = 2;
    if (num == 0)
        return (res + 1);
    while (i >= 0)
    {
        mid = num >> (i * 4);
        if (mid != 0 && num>>(i * 4))
            res++;
        i--;
    }
    return (res);
}