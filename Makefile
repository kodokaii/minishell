OBJECTS = \
		  minishell.o \

LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft
ifeq ($(DEBUG), 1)
CFLAGS += -g
endif

NAME = minishell

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug:
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
