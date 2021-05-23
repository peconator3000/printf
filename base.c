#include "printf.h"

static int		base_num(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static void	wr_num(int nbr, char *base, int n)
{
    char mid;
	if ((nbr / n) >= n)
	{
		wr_num(nbr / n, base, n);
		write(1, &base[nbr % n], 1);
	}
	else
	{
		write(1, &base[nbr / n], 1);
		write(1, &base[nbr % n], 1);
	}
}

void	ft_putnbr_base(int nbr, char *base)
{
	int n;

	n = base_num(base);
	wr_num(nbr, base, n);
}
