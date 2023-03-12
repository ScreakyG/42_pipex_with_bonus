NAME = pipex
OUTFILE = outfile
FLAGS = -Wall -Werror -Wextra
CC = gcc

HEADERS_DIR = includes/
HEADERS_FILES = pipex.h
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_FILES))

SRCS_DIR = src/
SRCS_FILES = main.c error.c child.c utils.c free.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS = ${SRCS:.c=.o}

FUNC_DIR = fonctions/
FUNC_FILES = ft_split.c ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_substr.c
FUNC = $(addprefix $(FUNC_DIR), $(FUNC_FILES))
OBJS_F = $(FUNC:.c=.o)

#COMMANDES
%.o: %.c $(HEADERS) Makefile
								${CC} ${FLAGS} -c $< -o $@

$(NAME): $(OBJS_F) $(OBJS)
		$(CC) $(OBJS_F) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
		rm -f $(OBJS)
		rm -f $(OBJS_F)

fclean: clean
		rm -f $(NAME)
		rm -f $(OUTFILE)

re: fclean all

.PHONY: all clean fclean re
