SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c \
ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
get_next_line.c ft_printf.c
BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
ft_lstclear.c ft_lstiter.c ft_lstmap.c
CC = cc
CFLAGS = -Wall -Werror -Wextra
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)
NAME = libft.a
LIBH = libft.h
LIBC = ar rc
RM = rm -f

#Colors
GREEN=\033[0;32m
RED=\033[0;31m
END=\033[0m

.c.o: 
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME) : $(OBJS)
	@$(LIBC) $(NAME) $(OBJS)
	@echo "$(GREEN)>>>> Libft made <<<<$(END)"

all : $(NAME)

bonus : $(BONUS_OBJS)

	@$(LIBC) $(NAME) $(BONUS_OBJS)
	@echo "$(GREEN)>>>> Bonus added <<<<$(END)"

clean : 
	@$(RM) $(OBJS) $(BONUS_OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY : fclean all bonus clean re 
