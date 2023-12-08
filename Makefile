OBJECTS = \
		  minishell.o \
		  builtins/handle.o \
		  builtins/cd.o \
		  builtins/pwd.o \
		  builtins/exit.o \
		  builtins/env.o \
		  signals.o

LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft -I.
LDFLAGS = -lreadline
ifeq ($(DEBUG), 1)
CFLAGS += -g
endif

NAME = minishell

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: fclean
	$(MAKE) DEBUG=1 all

clean: 
	$(MAKE) -C libft $@
	$(RM) $(OBJECTS)

fclean: clean
	$(MAKE) -C libft $@
	$(RM) $(NAME)

re: fclean all

-include myrules.mk

.PHONY: all debug clean fclean re
