/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:33:23 by dkros             #+#    #+#             */
/*   Updated: 2024/12/04 18:29:43 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
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

#define NO_REDIR 0
#define REDIR_IN 1
#define REDIR_OUT 2
#define REDIR_APPEND 3
#define REDIR_HEREDOC 4

extern char **environ;

typedef struct s_cmdlist
{
	struct s_node	*head;
} t_cmdlist;

typedef struct s_minishell
{
	char				*env;
	struct s_minishell	*next_env;
	int					status;

	t_cmdlist			*cmdlist;
}	t_minishell;

typedef struct s_redirect
{
	int		type;
	char	*filename;
}	t_redirect;

typedef struct s_cmd
{
	char	*filename;
	char	**args;
	t_redirect	*redirect;
} t_cmd;

typedef struct s_node
{
	t_cmd 			*cmd;
	struct s_node	*next;
} t_node;


// /srcs/builtins
// int			builtin_check(t_minishell *minishell, char **command);
int			builtin_check(t_minishell *minishell, t_cmdlist *cmdlist);
int			cd(t_minishell *envlist, char **args);          // Updated to take char **args
int			echo(t_minishell *minishell, char **args);      // Updated to take char **args
int			env(t_minishell *minishell);
int			export(t_minishell *envlist, char **args);      // Updated to take char **args
int			pwd(char **args);                               // Updated to take char **args
int			unset(t_minishell *envlist, char **args);       // Updated to take char **args

// /srcs/builtins/buitins_utils.c
char		*get_var_name(char *cmd, int *i);
char		*get_var_value(char *cmd, int i);
int			print_sorted_envlist(t_minishell *minishell);
void		print_envlist(t_minishell *minishell);

// /srcs/execution
void		ft_execute(t_cmd *cmd, char **envp);
int			ft_isdigit_str(const char *str);
int			ft_call_pipe(t_minishell *minishell, char *argv, char **envp);
int			handle_redirects(char **cmd);
int			process(t_minishell *minishell, t_cmdlist *cmdlist, char **envp); // Updated to remove argv
// int parent_process(t_minishell status, t_minishell *minishell, char *argv, char **envp);

// /parsing/cmdlist.c
t_cmd *get_command(char **arg_array);
void add_command(t_cmdlist *list, t_cmd *cmd);
t_cmdlist	put_in_cmdlist(char **command_array);
char **remove_redirections(char **args, t_redirect *redirect);


// /parsing/get_command.c
char		**get_command_array(char *str);

// /parsing/parsing_utils.c
int			count_between_quotes(char *str, int i);
void		free_array(char **array);
void		print_commands(t_cmdlist *list);
void		free_commands(t_cmdlist *list);

// /parsing/parsing.c
t_cmdlist	ft_parsing(char *argv);
t_redirect *init_redirect(void);
int init_cmd_struct(t_cmd **cmd);



// /parsing/new_dev.c
char		*convert_string(char *str);
char		check_for_errors(char *str);

// minishell.c
void		ft_input(char **argv, char **envp);

// utils.c
void		ft_error(const char *msg);
void		ft_exit(char **args);                            // Updated to take char **args
void		ft_free_dbl(char **ptr);
void		print_dbl_ptr(char **ptr);


#endif