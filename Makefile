NAME = pipex
FLAGS = -Wall -Wextra -Werror -g

SOURCES = main.c

OBJS = $(SOURCES:.c=.o)

$(NAME): libft/libft.a $(OBJS)
	cc $(FLAGS) -o $(NAME) $(OBJS) libft/libft.a

libft/libft.a:
	make -C libft libft.a

%.o: %.c
	cc $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all