#include "printf.h"

typedef struct elem
{
    int minus;
    int accur;
    int zero;
    int width;
    int type;
    int is_valid;
    char *data_char;
    size_t data_int;
}              t_elem; 

t_elem ft_newel(void)
{
    t_elem el;

    el.zero = 0;
    el.minus = 0;
    el.is_valid = 1;
    el.type = 0;
    el.width = 0;
    el.accur = 0;
    el.data_int = 0;
    el.data_char = NULL;
    return (el);
}


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
        return (0);
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
    if (ft_specificator(s))
    {
        (elem)->type = s;
        if (s == 'd' || s == 'i' || s == 'x' || s == 'X' || s == 'p')
            elem->data_int = (va_arg(param, size_t));
        else if (s == 's')
            elem->data_char = (va_arg(param, char*));
        else if (s == 'c')
            elem->data_int = (va_arg(param, size_t));
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

size_t ft_howdec_num(size_t num)
{
    size_t res;

    res = 0;
    if (num == 0)
        return (res);
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

    i = 0;
    if (elem->type == 'c' || elem->type == 's' || elem->type == 'p')
        elem->accur = 0;
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
    char tmp;

    if (elem->type == 'c')
    {
        tmp = elem->data_int;
        write(1, &(elem->data_int), 1);
    }
    else if (elem->type == 's')
        write(1, elem->data_char, ft_strlen(elem->data_char));
    else if (elem->type == 'p' || elem->type == 'x')
        ft_address(elem->data_int, "0123456789abcdef");
    else if(elem ->type == 'd' || elem->data_int == 'i')
        ft_putnbr(elem->data_int);//va_arg(param, int));
    else if (elem->type == 'X')
        ft_address(elem->data_int, "0123456789ABCDEF");
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
        return (ft_howdec_num(elem->data_int));//ft_howhex_num(elem->data_int));
    else if (c == 'p')
        return (ft_howdec_num(elem->data_int));//return (ft_address_num(elem->data_int));
    else if (c == 's')
        return (ft_strlen(elem->data_char));
    else if (c == 'c')
        return (1);
    else
        return (0);
}

size_t ft_add(t_elem *elem)
{
    char c;
    long int add_ac;
    long int add_w;

    // printf("shirina %d\n", elem->width);
    c = elem->type;
    if (c == 'c' || c == 's')
        add_ac = 0;
    else
        add_ac = elem->accur - ft_how_symbols(elem);
    if (add_ac < 0)
        add_w = elem->width - ft_how_symbols(elem);
    else
        add_w = elem->width - (ft_how_symbols(elem) + add_ac);
    // printf("add_w %ld\n", add_w);
    if (add_w <= 0)
            return (0);
    return (add_w);
}

int ft_show(t_elem *elem)
{
    long int i;
    long int tmp;
    char add;

    i = 0;
    add = ' ';
    if (elem->minus)
    {
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
        tmp = ft_add(elem);
        while(i++ < tmp)
            write(1, &add, 1);  
        ft_show_accur(elem);     
        ft_show_type(elem);
    }
    return (1);
}

int parcer(char *str, ...)
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

int main(void)
{   
    // printf("%d \n", sum(4, 1, 2, 3, 4));
    // printf("%d \n", sum(5, 12, 21, 13, 4, 5));
    char **set;
    char mstr[] = "sym = %*.3d and stroka2 = %8s and sym = '%c'\n";
    int nn = 9;
    char t = 'W';
    set = malloc(sizeof(char *) * 3);
    set[0] = ft_strdup("hey1");
    set[1] = ft_strdup("hey2");
    set[2] = NULL;
    parcer(mstr, -6, nn, set[1], t);
    printf("sym = %*.3d and stroka2 = %8s and sym = '%c'\n", -6, nn, set[1], t);
    return 0;
}