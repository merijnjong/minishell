/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:33:23 by dkros             #+#    #+#             */
/*   Updated: 2025/01/09 11:30:06 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../incs/libft.h"
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
# include <sys/stat.h>

# define NO_REDIR 0
# define REDIR_IN 1
# define REDIR_OUT 2
# define REDIR_APPEND 3
# define REDIR_HEREDOC 4
# define SINGLE_QUOTE 11
# define DOUBLE_QUOTE 12
# define TMP_HEREDOC_FILE "/tmp/.heredoc_tmp"

typedef struct s_cmdlist
{
	struct s_node	*head;
}	t_cmdlist;

typedef struct s_minishell
{
	char				*env;
	struct s_minishell	*next_env;
	int					status;

	t_cmdlist			cmdlist;
}	t_minishell;

typedef struct s_redirect
{
	int					type;
	char				*filename;
	struct s_redirect	*next;
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

extern int	g_in_child;

// srcs/builtins
int			builtin_check(t_minishell *minishell, t_cmdlist *cmdlist);
int			cd(t_minishell *envlist, char **args);
int			echo(t_cmd *command);
int			env(t_minishell *envlist, t_cmd *command);
int			ft_exit(char **args, t_minishell *minishell);
int			export(t_minishell *envlist, char **args);
int			pwd(t_cmd *command);
int			unset(t_minishell *envlist, char **args);

// srcs/builtins/buitins_utils.c
char		*get_var_name(char *cmd, int *i);
char		*get_var_value(char *cmd, int i);
int			print_sorted_envlist(t_minishell *minishell);
void		print_envlist(t_minishell *minishell);

// srcs/builtins/export.c
void		ft_setenv(t_minishell *envlist, char *var_name, char *var_value);

// srcs/execution
int			ft_execute(t_minishell *minishell, t_cmd *cmd);
int			handle_redirects(t_cmd *cmd);
int			execute_pipeline(t_minishell *minishell, t_cmdlist *cmdlist);
int			write_to_heredoc_file(t_redirect *redirect, int fd);

// srcs/execution/processes.c
int			process(t_minishell *minishell);
void		parent_process_cleanup(int *pipe_fd, int *input_fd);
int			handle_child_process(t_minishell *minishell, t_node *current,
				int input_fd, int *pipe_fd);
int			wait_for_all_processes(void);

// srcs/execution/signals.c
void		setup_signals(void);
// void		reset_signals_to_default(void);
void		sigint_handler(int signum);
void		sigquit_handler(int signum);
void		reset_signals_to_default(void);

// srcs/parsing/arrays.c
char		**ft_split_skip_quotes(char *s, char c);

// srcs/parsing/envlist.c
void		free_envlist(t_minishell *head);

// srcs/parsing/cmdlist.c
t_cmdlist	put_in_cmdlist(char **command_array);
void		free_commands(t_cmdlist *list);
void		add_command(t_cmdlist *list, t_cmd *cmd);
int			process_command(t_cmdlist *command_list, char *command_str);

// srcs/parsing/command.c
t_node		*create_node(t_cmd *cmd);
char		**get_command_array(char *str);
t_cmd		*get_command(char **arg_array);
void		free_command(t_cmd *cmd);

// srcs/parsing/convert.c
char		*convert_string(char *str);
void		add_spaces(char *new_str, char *str, int *i, int *j);
int			new_strlen(char *str);
int			get_meta_len(char *str, int i);

// srcs/parsing/errors.c
int			check_for_errors(char *str);
int			check_for_uneven_quotes(char *str);
char		get_first_metachar(char *str);
int			is_valid_double(char *str, int i);
int			is_metachar(char c);

// srcs/parsing/init.c
t_redirect	*init_redirect(void);
int			init_cmd_struct(t_cmd **cmd);
void		init_cmdlist(t_cmdlist *list);
void		init_minishell(t_minishell *minishell, char **envp);

// srcs/parsing/parsing_utils.c
void		free_array(char **array);
void		cleanup_minishell(t_minishell *minishell);
char		*extract_var_name(char **src);
char		*handle_var(char **src, char *dst, t_minishell *minishell);
char		*get_environ_value(char *var_name, t_minishell *minishell);

// srcs/parsing/parsing.c
t_cmdlist	ft_parsing(char *argv, t_minishell *minishell);
void		ft_print_array(char **array);
char		**fill_array(char **array, char *str, int wordcount);
void		clean_array(char **array, int i);
char		*replace_vars(t_minishell *minishell, char *str);

// srcs/parsing/quotes.c
int			is_in_quoted_section(char *str, int i);
int			count_wordlen(char *str, int i);
int			ft_count_commands(char *str, char c);
int			count_between_quotes(char *str, int i);
char		*process_src(t_minishell *minishell, char *src, char *str,
				char *result);

// srcs/parsing/parsing_redirects.c
char		**remove_redirections(char **args, t_redirect *redirect);
char		**create_new_args(char **args, t_redirect *redirect, int new_size);
int			handle_redirect(char **args, int *i, t_redirect *redirect);
int			count_new_size(char **args);
int			get_redirection_type(char *str);

// minishell.c
void		ft_input(char **argv, char **envp);

// utils.c
void		ft_error(const char *msg);
int			ft_isdigit_str(const char *str);
void		ft_free_dbl(char **ptr);
void		print_dbl_ptr(char **ptr);
int			is_whitespace_only(const char *str);

// update_env.c
int			update_env(t_minishell *env, char *var_to_change, char *value);
char		*get_new_env_str(char *var_to_change, char *new_value);
int			is_matching_var(char *varname, char *to_compare);
int			update_shlvl(t_minishell *env);
int			get_shlvl(char *str);

#endif