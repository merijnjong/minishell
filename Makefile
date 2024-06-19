NAME	:= minishell
CFLAGS	:= -g -Wextra -Wall -Werror
LIBFT 	:= ./libft

INCS	:= -I./incs -I$(LIBFT)
LIBS	:= $(LIBFT)/libft.a
SRCS	:= $(wildcard srcs/*.c)
OBJS	:= ${SRCS:.c=.o}

all: libft $(NAME)

libft:
	@make -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(INCS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT)

re: clean all

.PHONY: all, clean, fclean, re, libft