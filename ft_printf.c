#include "printf.h"

typedef struct elem
{
    int minus;
    int znak;
    int accur;
    int zero;
    int width;
    int type;
    int is_dot;
    char *data_char;
    long int data_int;
    unsigned long ul;
}              t_elem; 

t_elem ft_newel(void)
{
    t_elem el;

    el.zero = 0;
    el.znak = 0;
    el.minus = 0;
    el.type = 0;
    el.width = 0;
    el.accur = 0;
    el.data_int = 0;
    el.data_char = NULL;
    el.ul = 0;
    el.is_dot = 1;
    return (el);
}

size_t ft_how_symbols(t_elem *elem);

int	ft_isdigit(int ch)
{
	if (ch >= 48 && ch <= 57)
		return (1);
	else
		return (0);
}

ssize_t ft_flag_checker(t_elem *elem, const char *str)
{
    ssize_t i;

    i = 0;
    while (str[i] == '0' || str[i] == '-')
    {
        if (str[i] == '0')
            (elem)->zero = 1;
        if (str[i] == '-')
            (elem)->minus = 1;
        i++;
    }
    if ((elem)->minus)
        (elem)->zero = 0;
    return (i);
}

ssize_t ft_width_checker(t_elem *elem, const char *str, va_list param)
{
    ssize_t i;
    ssize_t wdth;

    i = 0;
    if (str[i] == '*')
    {
        (elem)->width = va_arg(param, int);
        if (elem->width < 0)
        {
            elem->minus = 1;
            elem->zero = 0;
            elem->width *= -1;
        }
        return (1);
    }
    wdth = 0;
    while (ft_isdigit(str[i]))
    {
        wdth = wdth * 10 + str[i] - '0';
        i++;
    }
    (elem)->width = wdth;
    return (i);
}

ssize_t ft_accur_checker(t_elem *elem, const char *str, va_list param)
{
    ssize_t i;
    ssize_t accur;
    
    i = 0;
    if (str[i] != '.')
    {
        elem->is_dot = 0;
        return (0);
    }
    i++;
    if (str[i] == '*')
    {
        (elem)->accur = va_arg(param, int);
        return (2);
    }
    accur = 0;
    while (ft_isdigit(str[i]))
    {
        accur = accur * 10 + str[i] - '0';
        i++;
    }
    (elem)->accur = accur;
    return (i);
}

ssize_t ft_type_checker(t_elem *elem, char s, va_list param)
{
    int num;

    if (ft_specificator(s))
    {
        (elem)->type = s;
        if (s == 'x' || s == 'X' || s == 'p')
            elem->ul = (va_arg(param, long unsigned int));
        else if (s == 's')
            elem->data_char = (va_arg(param, char*));
        else if (s == 'c' || s == 'd' || s == 'i')
        {
            num = (va_arg(param, int));
            if (num < 0)
            {
                elem->znak = 1;
                num = -num;
            }
            elem->data_int = num;
            //printf("READ = %ld\ntype  = %c\n", elem->data_int, elem->type);
        }
        return (1);
    }
    return (0);
}

ssize_t ft_write(t_elem *elem, char *str, va_list param)
{
    ssize_t i;

    i = 0;
    i+=ft_flag_checker(elem, &str[i]);
    i+=ft_width_checker(elem, &str[i], param);
    i+=ft_accur_checker(elem, &str[i], param);
    i+=ft_type_checker(elem, str[i], param);
    return (i);            
}

size_t ft_howdec_num(long int num)
{
    size_t res;

    res = 0;
    if (num < 0)
    {
        res++;
        num *= -1;
    }
    if (num == 0)
        return (1);
    //printf("postupilo %ld\n", num);
    while (num)
    {
        res++;
        num = num/10;
    }
    return (res);
}

void ft_show_accur(t_elem *elem)
{
    ssize_t i;
    ssize_t cur_acc;
    char c;

    i = 0;
    c = elem->type;
    if (c == 'p' || c == '%')
    {
        elem->accur = 0;
    }
    else if ((c == 'c' || c == 's'))
    {

        if (c == 's' &&(!(elem->is_dot) ||  elem->accur > ft_strlen(elem->data_char)))
            elem->accur = ft_strlen(elem->data_char);
        else if ((c == 'c' && elem->accur > 1) || !(elem->is_dot))
            elem->accur = 1;
    }
    else
    {
        i = elem->accur;
        cur_acc = ft_howdec_num(elem->data_int);
        while(i-- > cur_acc)
            write(1, "0", 1);
    }
}

void ft_show_type(t_elem *elem)//обрабатывает и выводит уже элемент вывода
{
    if (elem->type == 'c')
        write(1, &(elem->data_int), 1);
    else if (elem->type == 's')
    {
        if (!elem->data_char)
            write(1, "(null)", elem->accur);
        else
            write(1, elem->data_char, elem->accur);//ft_strlen(elem->data_char));
    }
    else if (elem->type == 'p')
        ft_address(elem->ul, "0123456789abcdef", 'p');
    else if(elem ->type == 'd' || elem->type == 'i')
        ft_putnbr(elem->data_int);//va_arg(param, int));
    else if (elem->type == 'X')
        ft_address(elem->ul, "0123456789ABCDEF", 'X');
    else if (elem->type == 'x')
        ft_address(elem->ul, "0123456789abcdef", 'x');
    else if (elem->type == '%')
        write(1, "%", 1);
    else
        write(1, &(elem->type), 1);
}

// size_t ft_howhex_num()
// {

// }

size_t ft_how_symbols(t_elem *elem)
{
    char c;

    c = elem->type;
    if (c == 'd' || c == 'i')
        return (ft_howdec_num(elem->data_int));
    else if (c == 'x' || c == 'X')
        return (ft_howhex_num(elem->ul, c));
    else if (c == 'p')
        return (ft_howhex_num(elem->ul, c));
    else if (c == 's')
        return (ft_strlen(elem->data_char));
    else if (c == 'c' || c == '%')
        return (1);
    else
        return (0);
}

size_t ft_add(t_elem *elem)
{
    char c;
    long int add_ac;
    long int add_w;

    c = elem->type;
    //printf("width %ld\naccur %ld\nsymbols = %d\n", elem->width, elem->accur, ft_how_symbols(elem));
    add_ac = elem->accur - ft_how_symbols(elem);
    if (c == 's' || c == 'c')
        add_w = elem->width - elem->accur;
    else if (add_ac < 0)
        add_w = elem->width - ft_how_symbols(elem) - elem->znak;
    else
        add_w = elem->width - (ft_how_symbols(elem) + add_ac) - elem->znak;
    //printf("add_w %ld\n", add_w);
    if (add_w <= 0)
            return (0);
    return (add_w);
}

int ft_show(t_elem *elem)
{
    long int i;
    long int tmp;
    char add;
    char c;

    i = 0;
    add = ' ';
     c = elem->type;
    if (elem->minus)
    {
        if (elem->znak)
            write(1, "-", 1);
        ft_show_accur(elem);
        ft_show_type(elem);
        tmp = ft_add(elem);
        while(i++ < tmp)
            write(1, &add, 1);
    }
    else
    {
        if (elem->zero == 1)
            add = '0';
       
        if ((c == 'c' || c == 's'))
        {
            if (c == 's' &&(!(elem->is_dot) ||  elem->accur > ft_strlen(elem->data_char)))
                elem->accur = ft_strlen(elem->data_char);
            else if ((c == 'c' && elem->accur > 1) || !(elem->is_dot))
                elem->accur = 1;
        }
        tmp = ft_add(elem);
        if (elem->accur > 0)
            add = ' ';
        while(i++ < tmp)
            write(1, &add, 1);
        if (elem->znak)
            write(1, "-", 1);
        ft_show_accur(elem);     
        ft_show_type(elem);
    }
    return (1);
}

int ft_printf(char *str, ...)
{
    ssize_t i;
    t_elem newel;
    va_list param;

    if (!str)
        return (0);
    i = 0;
    va_start(param, str);
    while(str[i])
    {
        if (str[i] == '%')
        {
            newel = ft_newel();
            i+=ft_write(&newel, &str[i+1], param) + 1;
            ft_show(&newel);
        }
        else
            write(1, &str[i++], 1);
    }
    va_end(param);
    return (1);
}

// int main(void)
// {   
//     // printf("%d \n", sum(4, 1, 2, 3, 4));
//     // printf("%d \n", sum(5, 12, 21, 13, 4, 5));
//     char **set;
//     char mstr[] = "'7.5s'\n";
//     int nn = 100;
//     char t = 'W';
//     set = malloc(sizeof(char *) * 3);
//     set[0] = ft_strdup("hey1");
//     set[1] = ft_strdup("hey2");
//     set[2] = NULL;
//     ft_printf("'%7.9i'", 14);
//     printf("\n'%7.9i'\n", 14);
//     return 0;
// }