/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:33:23 by dkros             #+#    #+#             */
/*   Updated: 2024/08/07 15:04:50 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define WORD 10
# define HEREDOC 11
// # define SPACE 12
# define PIPE 13
# define APPEND 14
# define INPUT 15
# define TRUNC 16
# define END 17

typedef struct s_cmd
{
	char	*filename;
	char	**args;
	char	**envp;
}	t_cmd;

typedef struct s_node
{
	int				type;
	t_cmd			*cmd;
	struct s_node	*next;
}	t_node;

typedef struct s_cmdlist
{
	struct s_node	*head;
}	t_cmdlist;

typedef struct s_token_node
{
	struct s_token_node	*prev;
	int					token;
	struct s_token_node	*next;
}	t_token_node;

typedef struct s_tokenlist
{
	struct s_node	*head;
}	t_tokenlist;

// minishell.c
void		ft_input(char *argv[], char *envp[]);

// parsing.c
int			ft_parser(char *input, char *envp[]);

// tokenization.c
t_tokenlist	*ft_tokenize(char *str);

// command_list.c
t_cmdlist	*create_list(void);
t_cmd		*add_command(char *input, char *output, char *executable);
void		free_cmdlist(t_cmdlist *list);
void		free_cmdlist_recursive(t_node *node);
void		free_command(t_cmd *cmd);
void		add_node(t_node **head, char *input, int begin, int end);

// execution.c
void		ft_execute(char *argv, char *envp[]);

// /srcs/builtins
int			builtincheck(char *input);
int			cd(const char *cd_cmd);
int			echo(char *msg);
int			env(void);
int			export(char *msg);
int			pwd(char *command);
int			unset(char *msg);

// utils.c
void		ft_error(const char *msg);

#endif
