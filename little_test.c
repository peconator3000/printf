#include <stdlib.h>
#include <stdio.h>
#include "printf.h"

void ft_ad(long long unsigned num, char *hex_set)
{
    int i;
    long long unsigned mid;

    if (!num)
    {
        write(1, "(null)", 6);
        return ;
    }
    i = 15;
    write(1, "0x", 2);
    if (num == 0)
        write(1, "0", 1);
    while (i >= 0)
    {
        mid = num >> (i-- * 4);
        if (mid != 0 && num<<(15*4))
            write(1, &hex_set[mid & 15], 1);
    }
}

void ft_hex(unsigned num, char *hex_set)
{
    int i;
    unsigned mid;

    if (!num)
    {
        write(1, "(null)", 6);
        return ;
    }
    i = 7;
    write(1, "0x", 2);
    if (num == 0)
        write(1, "0", 1);
    while (i >= 0)
    {
        mid = num >> (i-- * 4);
        write(1, &hex_set[mid & 15], 1);
    }
}

int main(void)
{
    // int n1 = 9087;
    // char n2 = 'a';
    
    // printf("chislo sym v %d = %lu", n1, ft_howlen_num(&n1, sizeof(n1)));
	char str[] = "nol";
	char sym = 'a';
	int y = 10980;
	ft_ad(y, "0123456789abcdef");
	printf("\n%p\n", y);
}