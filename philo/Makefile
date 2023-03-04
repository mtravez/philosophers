NAME = philo

SRC = philo.c utils.c init_functions.c

#BONUS = checker

#BONUS_SRC = bonus/instructions.c bonus/checker.c bonus/double_function.c

FLAGS = -Wall -Wextra -Werror -pthread

OBJ = $(SRC:%.c=%.o)

#OBJ_BONUS = $(BONUS_SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@cc  $(FLAGS) $(SRC) -lpthread -o $(NAME) 
clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME) $(BONUS)

re: fclean all 

.PHONY: all clean fclean re