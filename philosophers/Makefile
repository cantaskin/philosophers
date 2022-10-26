CC		=	gcc
NAME 	=	philo
SRC		=	./main.c ./life.c ./party_begin.c ./philo_init.c ./ultilits.c
OBJ		= 	$(SRC:%.c=%.o)
FLAGS	=	-Wall -Werror -Wextra
BLUE = \033[1;34m

all: $(NAME)
	@echo "$(BLUE)██████████████████████ Compiling is DONE ███████████████████████$(RESET)"

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o philo
clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(OBJ)
re: fclean all

.PHONY: clean fclean re all
