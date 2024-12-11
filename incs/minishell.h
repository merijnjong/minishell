/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:33:23 by dkros             #+#    #+#             */
/*   Updated: 2024/12/11 17:30:59 by mjong            ###   ########.fr       */
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

# define NO_REDIR 0
# define REDIR_IN 1
# define REDIR_OUT 2
# define REDIR_APPEND 3
# define REDIR_HEREDOC 4

extern char	**environ;

typedef struct s_cmdlist
{
	struct s_node	*head;
}	t_cmdlist;

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
	char		*filename;
	char		**args;
	t_redirect	*redirect;
}	t_cmd;

typedef struct s_node
{
	t_cmd			*cmd;
	struct s_node	*next;
}	t_node;

// /srcs/builtins
int			builtin_check(t_minishell *minishell, t_cmdlist *cmdlist);
int			cd(t_minishell *envlist, char **args);
int			echo(t_minishell *minishell, char **args);
int			env(t_minishell *envlist);
int			export(t_minishell *envlist, char **args);
int			pwd(char **args);
int			unset(t_minishell *envlist, char **args);

// /srcs/builtins/buitins_utils.c
char		*get_var_name(char *cmd, int *i);
char		*get_var_value(char *cmd, int i);
int			print_sorted_envlist(t_minishell *minishell);
void		print_envlist(t_minishell *minishell);

// /srcs/execution
int			ft_execute(t_cmd *cmd, char **envp);
int			handle_redirects(t_cmd *cmd);
int			execute_pipeline(t_cmdlist *cmdlist, char **envp);

// /srcs/execution/processes.c
int			process(t_minishell *minishell, t_cmdlist *cmdlist, char **envp);
int			run_child_process(t_cmd *cmd, char **envp, int input_fd,
				int output_fd);
int			run_parent_process(pid_t pid, int output_fd, int input_fd);
void		child_process_setup(int input_fd, int output_fd);
void		parent_process_cleanup(int *pipe_fd, int *input_fd);

// /srcs/execution/redirects.c
int			handle_redirects(t_cmd *cmd);

// /srcs/execution/signals.c
void		setup_signals(void);
// void		reset_signals_to_default(void);
void		sigint_handler(int signum);
void		sigquit_handler(int signum);

// /srcs/parsing/envlist.c
void		free_envlist(t_minishell *head);
int			start_envlist(t_minishell *envlist, char **envp, int i);

// /srcs/parsing/init.c
t_redirect	*init_redirect(void);
int			init_cmd_struct(t_cmd **cmd);
void		init_cmdlist(t_cmdlist *list);
void		init_minishell(t_minishell *minishell, char **envp);

// /srcs/parsing/parsing_arrays.c
char		**ft_split_skip_quotes(char *s, char c);

// /srcs/parsing/parsing_cmdlist.c
t_cmdlist	put_in_cmdlist(char **command_array);
void		print_commands(t_cmdlist *list);
void		free_commands(t_cmdlist *list);
void		add_command(t_cmdlist *list, t_cmd *cmd);

// /srcs/parsing/parsing_command.c
void		free_command(t_cmd *cmd);
t_node		*create_node(t_cmd *cmd);
void		print_command(t_cmd *cmd);
char		**get_command_array(char *str);
t_cmd		*get_command(char **arg_array);

// /srcs/parsing/parsing_convert.c
char		*convert_string(char *str);
void		add_spaces(char *new_str, char *str, int *i, int *j);
int			new_strlen(char *str);
int			get_meta_len(char *str, int i);

// /srcs/parsing/parsing_errors.c
int			check_for_errors(char *str);
int			check_for_uneven_quotes(char *str);
char		get_first_metachar(char *str);
int			is_valid_double(char *str, int i);
int			is_metachar(char c);

// /srcs/parsing/parsing_quotes.c
int			is_in_quoted_section(char *str, int i);
int			count_wordlen(char *str, int i);
int			ft_count_commands(char *str, char c);
int			count_between_quotes(char *str, int i);

// /srcs/parsing/parsing_redirects.c
char		**remove_redirections(char **args, t_redirect *redirect);
char		**create_new_args(char **args, t_redirect *redirect, int new_size);
int			handle_redirect(char **args, int *i, t_redirect *redirect);
int			count_new_size(char **args);
int			get_redirection_type(char *str);

// /srcs/parsing/parsing_utils.c
void		free_array(char **array);

// /srcs/parsing/parsing.c
t_cmdlist	ft_parsing(char *argv);
void		ft_print_array(char **array);
char		**fill_array(char **array, char *str, int wordcount);
void		clean_array(char **array, int i);

// minishell.c
void		ft_input(char **argv, char **envp);

// utils.c
void		ft_error(const char *msg);
int			ft_isdigit_str(const char *str);
void		ft_exit(char **args);
void		ft_free_dbl(char **ptr);
void		print_dbl_ptr(char **ptr);

#endif