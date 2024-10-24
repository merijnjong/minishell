/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:33:23 by dkros             #+#    #+#             */
/*   Updated: 2024/10/24 16:59:39 by mjong            ###   ########.fr       */
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

typedef struct s_status
{
	int	last;
}	t_status;

typedef struct s_envlist
{
	char				*env;
	struct s_envlist	*next;
}	t_envlist;

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

// /srcs/builtins
int			builtin_check(char *input, t_status status, t_envlist *envlist);
int			cd(const char *cd_cmd);
int			echo(char *msg, t_status status);
int			env(t_envlist *envlist);
int			export(char *cmd, t_envlist *envlist);
void		print_sorted_envlist(t_envlist *envlist);
char		*get_var_name(char *cmd, int *i);
char		*get_var_value(char *cmd, int i);
int			pwd(char *command);
int			unset(char *msg);

// command_list.c
t_cmdlist	*create_list(void);
t_cmd		*add_command(char *input, char *output, char *executable);
void		free_cmdlist(t_cmdlist *list);
void		free_cmdlist_recursive(t_node *node);
void		free_command(t_cmd *cmd);
void		add_node(t_node **head, char *input, int begin, int end);

// execution.c
void		ft_execute(char *argv, char **envp);

// minishell.c
void		ft_input(char **argv, char **envp);

// parsing.c
int			ft_parser(char *argv, char **envp, t_status status, t_envlist *envlist);

// tokenization.c
t_tokenlist	*ft_tokenize(char *str);

// utils.c
void		ft_error(const char *msg);
void		ft_exit(char *argv);
void		ft_free_dbl(char **ptr);
void		print_dbl_ptr(char **ptr);
void		print_envlist(t_envlist *envlist);

#endif