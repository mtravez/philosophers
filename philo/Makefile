NAME = philo

SRC = philo.c utils.c init_functions.c activities.c parsing.c free_stuff.c perm_thread.c

FLAGS = -Wall -Wextra -Werror -pthread

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@cc  $(FLAGS) $(SRC) -lpthread -o $(NAME) 
clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME) $(BONUS)

re: fclean all 

.PHONY: all clean fclean re