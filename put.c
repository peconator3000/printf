#include "printf.h"

static void	put(char c, long int n)
{
	if (n)
	{
		put(c, n / 10);
		c = n % 10 + 48;
		write(1, &c, 1);
	}
}

void	ft_putnbr(int n)
{
	long int	num;
	char		c;

	num = n;
	c = 0;
	if (n < 0)
	{
		num *= -1;
		//write(1, "-", 1);
	}
	else if (n == 0)
		write(1, "0", 1);
	put(c, num);
}

// ssize_t ft_howlen_num(void *arg, int size)
// {
// 	size_t num;
// 	ssize_t res;

// 	num = arg;
// 	if (num == 0)
// 		return (1);
// 	res = 0;
// 	while(num)
// 	{
// 		num>>=size;
// 		res++;
// 	}
// 	return (res);
// }