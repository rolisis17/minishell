SRC = minishell.c cmds.c parse.c signals.c parse_2.c splitting.c tools.c parse_3.c \
storage.c freedom.c cd.c echo.c env.c exit.c export.c export2.c pwd.c unset.c redirect.c \
here_doc.c tools_2.c cmd_tools.c history.c
BIN = bin
VAL = suppress
OBJ = $(SRC:%.c=${BIN}/%.o)
NAME = minishell
HEADERS = minishell.h
FLAGS = -Wall -Werror -Wextra -g -fPIE
FSAN = -fsanitize=address
LIBFT = ./libft/libft.a
LIBCOM = -C ./libft --no-print-directory
RM = rm -rf
CC = cc

#Colors
GREEN=\033[0;32m
RED=\033[0;31m
END=\033[0m

all : $(NAME)

$(NAME) : $(BIN) $(OBJ) | $(LIBFT)
	@$(CC) $(OBJ) $(FLAGS) -Llibft -lft -lreadline -fPIE -o $(NAME)
	@echo "$(GREEN)>>>> Compiled <<<<$(END)"

$(LIBFT) :
	@make $(LIBCOM)
	@make clean $(LIBCOM)

$(BIN) :
	@mkdir -p $(BIN)

$(BIN)/%.o : %.c
	@$(CC) $(FLAGS) -c $< -o $@

valgrind :  $(NAME) $(VAL)
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=suppress ./$(NAME)
	@rm $(VAL)

$(VAL) : 
	@echo '{' > suppress
	@echo '	ignore_readline_conditional_jump_errors' >> suppress
	@echo '	Memcheck:Leak' >> suppress
	@echo '	...' >> suppress
	@echo '	obj:/usr/lib/x86_64-linux-gnu/libreadline.so.*' >> suppress
	@echo '}' >> suppress


clean :
	@$(RM) $(BIN)
	@if test -f $(VAL); then rm suppress; fi
	@echo "$(RED)>>>> Cleaned <<<<$(END)"

fclean : clean
	@$(RM) $(NAME)
	@echo "$(RED)>>>> All <<<<$(END)"

libclean : 
	@make fclean $(LIBCOM)

re : fclean all

.PHONY : all clean fclean re libclean
