sourcefiles = 	ft_atoi.c ft_atol.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
				ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
				ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
				ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
				ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line.c \
				get_next_line_utils.c ft_printc.c ft_printd.c ft_printf.c ft_printp.c ft_prints.c \
				ft_printu.c ft_printx_lo.c ft_printx_up.c

objects =		$(sourcefiles:.c=.o)

NAME =			libft.a

all:			$(NAME)

$(NAME):		$(objects)
	@ar rcs libft.a $(objects)

%.o: %.c
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	@rm -f $(objects)

fclean:
	@rm -f $(objects) $(NAME)

re: 			fclean all