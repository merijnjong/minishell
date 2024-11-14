/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:33:23 by dkros             #+#    #+#             */
/*   Updated: 2024/11/14 14:45:36 by mjong            ###   ########.fr       */
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

extern char **environ;

typedef struct s_cmd
{
	char	*filename;	// Command:
	char	**args;		// Arguments:
	char	**envp;
} t_cmd;

typedef struct s_node
{
	t_cmd 			*cmd;
	struct s_node	*next;
} t_node;

typedef struct s_cmdlist
{
	struct s_node	*head;
} t_cmdlist;

typedef struct s_status
{
	int	last;
}	t_status;

typedef struct s_envlist
{
	char				*env;
	struct s_envlist	*next;
}	t_envlist;

// /srcs/builtins
int			builtin_check(t_status status, t_envlist *envlist, char *input);
int			cd(t_envlist *envlist, char *cd_cmd);
int			echo(t_status status, t_envlist *envlist, char *input);
int			env(t_envlist *envlist);
int			export(t_envlist *envlist, char *cmd);
int			pwd(char *command);
int			unset(t_envlist *envlist, char *var_name);

// /srcs/builtins/buitins_utils.c
char		*get_var_name(char *cmd, int *i);
char		*get_var_value(char *cmd, int i);
int			print_sorted_envlist(t_envlist *envlist);
void		print_envlist(t_envlist *envlist);

// /srs/execution
void		ft_execute(char *argv, char **envp);
int			ft_call_pipe(t_status status, char *argv, char **envp);
int			handle_redirects(char **cmd);
int			process(t_status status, t_envlist *envlist, char *argv, char **envp);
// int parent_process(t_status status, t_envlist *envlist, char *argv, char **envp);

// /parsing/cmdlist.c
t_cmd		*get_command(char **arg_array);
void		add_command(t_cmdlist *list, t_cmd *cmd);
t_cmdlist	put_in_cmdlist(char **command_array);

// /parsing/get_command.c
char		**get_command_array(char *str);

// /parsing/parsing_utils.c
int			count_between_quotes(char *str, int i);
void		free_array(char **array);
void		print_commands(t_cmdlist *list);
void		free_commands(t_cmdlist *list);

// /parsing/parsing.c
void		ft_parsing(char **argv);

// minishell.c
void		ft_input(char **argv, char **envp);


// utils.c
void		ft_error(const char *msg);
void		ft_exit(char *argv);
void		ft_free_dbl(char **ptr);
void		print_dbl_ptr(char **ptr);

#endif