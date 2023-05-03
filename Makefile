SRC = minishell.c cmds.c parse.c signals.c builtins.c parse_2.c splitting.c tools.c parse_3.c
BIN = bin
OBJ = ${SRC:%c=${BIN}/%o}
NAME = minishell
HEADERS = minishell.h
FLAGS = -Wall -Werror -Wextra -g
FSAN = -fsanitize=address
LIBFT = libft
RM = rm -rf
CC = cc

#Colors
GREEN=\033[0;32m
RED=\033[0;31m
END=\033[0m

all : ${NAME}

${NAME} : ${BIN} ${OBJ} ${HEADERS} | ${LIBFT}
	@${CC} ${OBJ} ${FSAN} -Llibft -lft -lreadline -o ${NAME}
	@echo "$(GREEN)>>>> Compiled <<<<$(END)"

${BIN}/%o : %c
	@${CC} ${FLAGS} -c $< -o $@

${BIN} :
	@mkdir -p ${BIN}

clean :
	@${RM} ${BIN}
	@echo "$(RED)>>>> Cleaned <<<<$(END)"

fclean : clean
	@${RM} ${NAME}
	@echo "$(RED)>>>> All <<<<$(END)"

libclean : 
	@make fclean -C ${LIBFT} --no-print-directory

${LIBFT} :
	@make -C ${LIBFT} --no-print-directory

re : fclean all

.PHONY : all clean fclean ${LIBFT} re libclean