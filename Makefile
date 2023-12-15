SRC			= \
			parsing/fill_env.c \
			parsing/fill_glob.c \
			parsing/get_token.c \
			parsing/get_word.c \
			parsing/lexing.c \
			parsing/lexing_utils.c \
			parsing/token_error.c \
			parsing/parsing.c \
			parsing/parsing_utils.c \
			parsing/parsing_cleanup.c \
			parsing/str_quoted.c \
			parsing/str_quoted_utils.c \
			parsing/files.c \
			parsing/debug.c \
			minishell.c \
			builtins/handle.c \
			builtins/cd.c \
			builtins/pwd.c \
			builtins/exit.c \
			builtins/env.c \
			builtins/echo.c \
			builtins/unset.c \
			builtins/export.c \
			signals.c \
			glob.c \
			env.c

OBJ 		= $(SRC:.c=.o)

FT			= libft
LIBFT 		= $(FT)/libft.a

CC 			= cc
CLONE		= git clone --depth=1
CFLAGS 		= -Wall -Wextra -Werror -Ilibft -I.
LDFLAGS 	= -lreadline

ifeq ($(DEBUG), 1)
CFLAGS += -g
endif

NAME 		= minishell

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(LDFLAGS)

$(LIBFT): $(FT)
	$(MAKE) -C libft

$(FT):
	$(CLONE) https://github.com/kodokaii/libft_plus_plus.git $(FT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: fclean
	$(MAKE) DEBUG=1 all

clean: 
	if [ -d "$(FT)" ]; then $(MAKE) clean -C $(FT); fi
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

clear:
	$(RM) -r $(FT)

re: fclean all

-include myrules.mk

.PHONY: all debug clean fclean clear re
