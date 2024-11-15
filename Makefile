NAME = pipex
FLAGS = -Wall -Wextra -Werror

SOURCES = main.c

OBJS = $(SOURCES:.c=.o)

$(NAME): $(OBJS)
	cc $(FLAGS) -o $(NAME) $(OBJS) libft/libft.a

libft/libft.a:
	cd libft && make libft.a

%.o: %.c | libft/libft.a
	cc $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all