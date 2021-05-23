#ifndef PRINTF_H
# define PRINTF_H

# include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

// typedef struct  elem
// {
//     char type;
//     int width;
//     int accur;
//     char flag;
// }               s_elem;

void	ft_putstrr(char *s);
void	ft_putnbr(int n);
ssize_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void	ft_putnbr_base(int nbr, char *base);
char	*ft_itoa(int n);
// void ft_address(unsigned int num, char *hex_set);
void ft_address(unsigned long num, char *hex_set, char system);
int	ft_isalpha(int ch);
int	ft_specificator(int c);
void ft_hex(unsigned num, char *hex_set);
ssize_t ft_howhex_num(unsigned long num, char system);
int ft_printf(char *str, ...);


#endif