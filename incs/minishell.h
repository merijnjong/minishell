/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:33:23 by dkros             #+#    #+#             */
/*   Updated: 2024/12/07 14:52:57 by marvin           ###   ########.fr       */
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
int			env(t_minishell *envlist);
int			export(t_minishell *envlist, char **args);      // Updated to take char **args
int			pwd(char **args);                               // Updated to take char **args
int			unset(t_minishell *envlist, char **args);       // Updated to take char **args

// /srcs/builtins/buitins_utils.c
char		*get_var_name(char *cmd, int *i);
char		*get_var_value(char *cmd, int i);
int			print_sorted_envlist(t_minishell *minishell);
void		print_envlist(t_minishell *minishell);

// /srcs/execution
int			ft_execute(t_cmd *cmd, char **envp);
int			ft_isdigit_str(const char *str);
int			handle_redirects(t_cmd *cmd);
int			execute_pipeline(t_cmdlist *cmdlist, char **envp);

// /srcs/execution/processes.c
int			process(t_minishell *minishell, t_cmdlist *cmdlist, char **envp);
int			run_child_process(t_cmd *cmd, char **envp, int input_fd, int output_fd);
int			run_parent_process(pid_t pid, int output_fd, int input_fd);
void		child_process_setup(int input_fd, int output_fd);
void		parent_process_cleanup(int *pipe_fd, int *input_fd);

// /srcs/execution/signals.c
void		setup_signals(void);
void		reset_signals_to_default(void);
void		sigint_handler(int signum);
void		sigquit_handler(int signum);

int         ft_strlen(const char *str);
char        *ft_strdup(const char *s);
void        free_array(char **array);
void        ft_print_array(char **array);
int         ft_count_words(char *str, char c);
int         ft_word_length(char *s, char c, int i);
char        **ft_split_skip_quotes(char *s, char c);
char        *ft_substr(const char *s, unsigned int start, size_t len);
char        *convert_string(char *str);
char        *replace_vars(const char *str);
int         count_between_quotes(char *str, int i);
void        free_command(t_cmd *cmd);
void        free_commands(t_cmdlist *list);

// Parsing Functions
t_cmdlist   ft_parsing(char *argv);
int         check_for_errors(char *str);
int         check_for_uneven_quotes(char *str);
int         is_metachar(char c);
int         is_valid_double(char *str, int i);
char        get_first_metachar(char *str);
int         new_strlen(char *str);
int         get_redirection_type(char *str);
char        **get_command_array(char *str);
t_cmd       *get_command(char **arg_array);
t_cmdlist   put_in_cmdlist(char **command_array);

// Command List Functions
void        init_cmdlist(t_cmdlist *list);
void        add_command(t_cmdlist *list, t_cmd *cmd);
void        print_command(t_cmd *cmd);
void        print_commands(t_cmdlist *list);
t_node      *create_node(t_cmd *cmd);
void		free_envlist(t_minishell *head);
int			start_envlist(t_minishell *envlist, char **envp, int i);
void		init(t_minishell *minishell, char **envp);

// Redirection Handling
t_redirect  *init_redirect(void);
char        **remove_redirections(char **args, t_redirect *redirect);
int         handle_redirect(char **args, int *i, t_redirect *redirect);

// Environment Variable Functions
char        *get_environ_value(const char *var_name);

// Other Helpers
int         get_meta_len(char *str, int i);
int         is_in_quoted_section(char *str, int i);
void        add_spaces(char *new_str, char *str, int *i, int *j);

// minishell.c
void		ft_input(char **argv, char **envp);

// utils.c
void		ft_error(const char *msg);
void		ft_exit(char **args);                            // Updated to take char **args
void		ft_free_dbl(char **ptr);
void		print_dbl_ptr(char **ptr);

#endif