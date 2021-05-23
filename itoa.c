#include "printf.h"

static int	how(int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*zapolnenie(long int n, int znak)
{
	char	*res;
	int		i;

	i = how(n) + znak;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (0);
	res[i--] = '\0';
	while (n)
	{
		res[i--] = n % 10 + 48;
		n = n / 10;
	}
	if (znak == 1)
		res[i] = '-';
	return (res);
}

char	*ft_itoa(int n)
{
	int			znak;
	long int	c;
	char		*res;

	znak = 0;
	c = (long int)n;
	if (n < 0)
	{
		znak = 1;
		c *= -1;
	}
	else if (n == 0)
	{
		res = malloc(sizeof(char) * 2);
		if (!res)
			return (0);
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	res = zapolnenie(c, znak);
	return (res);
}
