SRCS =  ft_printf.c strings.c address.c put.c
		
OBJ = $(SRCS:.c=.o)
REM = rm -rf
NAME = libftprintf.a


$(NAME): $(OBJ)
	ar rcs $(NAME) $?

all: $(NAME)

.c.o:
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	$(REM) $(OBJ)

fclean:	clean
	$(REM)

re:	fclean all

.PHONY: all clean fclean
