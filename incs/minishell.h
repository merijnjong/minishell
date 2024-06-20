
#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_cmdlist
{
	struct s_node	*head;
} t_cmdlist;

typedef struct s_node
{
	struct s_node	*prev;
	struct t_cmd	*cmd;
	struct s_node	*next;
} t_node;

typedef struct s_cmd
{
	char	*input;
	char	*output;
	char	*executable;
} t_cmd;

// parsing.c //
void	ft_parser(char *input);

#endif
