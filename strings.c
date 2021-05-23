#include "printf.h"

ssize_t	ft_strlen(const char *str)
{
	ssize_t	i;

	if (!str)
        return (6);
    i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	n;
	char	*res;

	n = ft_strlen(s1);
	res = malloc(sizeof(char) * (n + 1));
	if (!res)
		return (0);
	res[n] = '\0';
	while (n-- > 0)
		res[n] = s1[n];
	return (res);
}

int	ft_specificator(int c)
{
	if (c == 'c' || c == 's' || c == 'd' || c == 'i')
		return (1);
	else if (c == 'x' || c == 'X' || c == 'p' || c == '%')
		return (1);
	else
		return (0);
}