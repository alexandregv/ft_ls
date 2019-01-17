NAME			= ft_ls
INCLUDES	= ./includes
CFLAGS 		+= -Wall -Wextra -Werror
SRC 			= 
OBJ				= $(SRC:.c=.o)

all: $(NAME)

%.c:%.o
	gcc $(CFLAGS) -I $(INCLUDES) -c $(SRC)

$(NAME): $(OBJS)
	gcc -I $(INCLUDES) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
