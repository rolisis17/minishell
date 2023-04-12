SRC = minishell.c cmds.c parse.c
OBJ = $(SRC:.c=.o)
NAME = minishell
FLAGS = -Wall -Werror -Wextra -g
LIBFT = -C ./libft --no-print-directory
RM = rm -f
CC = cc

#Colors
GREEN=\033[0;32m
RED=\033[0;31m
END=\033[0m

all : $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
# @make $(LIBFT)
	@$(CC) $(OBJ) -fsanitize=address -Llibft -lft -lreadline -g -o $(NAME)
	@echo "$(GREEN)>>>> Compiled <<<<$(END)"

clean :
	@$(RM) $(OBJ)
# @make clean $(LIBFT)
	@echo "$(RED)>>>> Cleaned <<<<$(END)"

fclean : clean 
	@$(RM) $(NAME)
# @make fclean $(LIBFT)
	@echo "$(RED)>>>> All <<<<$(END)"

re : fclean all

.PHONY : all fclean clean re make