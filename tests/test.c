/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:33:23 by dkros             #+#    #+#             */
/*   Updated: 2024/11/27 17:00:32 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/incs/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
// # include <linux/limits.h>
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
#include <ctype.h>


extern char **environ;

typedef struct s_minishell
{
	char				*env;
	struct s_minishell	*next_env;
	int					status;

	char				**envp;
	t_cmdlist			*cmdlist;
}	t_minishell;

typedef struct s_redirect
{
	int		type;
	char	*output_file;
} t_redirect;

typedef struct s_cmd
{
	char	*command;
	char	**arguments;
	t_redirect	*redirect;
}	t_cmd;

typedef struct s_node
{
	t_cmd		*cmd;
	struct s_node	*next;
} t_node;

typedef struct s_cmdlist
{
	struct s_node	*head;
} t_cmdlist;

// /srcs/builtins
int			builtin_check(t_minishell *minishell, t_cmdlist *cmdlist);
int			cd(t_minishell *envlist, char *command);
int			echo(t_minishell *minishell, char *command);
int			env(t_minishell *minishell);
int			export(t_minishell *envlist, char *command);
int			pwd(char *command);
int			unset(t_minishell *minishell, char *var_name);

// /srcs/builtins/buitins_utils.c
char		*get_var_name(char *cmd, int *i);
char		*get_var_value(char *cmd, int i);
int			print_sorted_envlist(t_minishell *minishell);
void		print_envlist(t_minishell *minishell);

// /srs/execution
void		ft_execute(char *argv, char **envp);
int			ft_call_pipe(t_minishell *minishell, char *argv, char **envp);
int			handle_redirects(char **cmd);
int			process(t_minishell *minishell, t_cmdlist *cmdlist, char *argv, char **envp);
// int parent_process(t_minishell status, t_minishell *minishell, char *argv, char **envp);

// /parsing/cmdlist.c
t_minishell	*get_command(char **arg_array);
void		add_command(t_cmdlist *list, t_minishell *cmd);
t_cmdlist	put_in_cmdlist(char **command_array);

// /parsing/get_command.c
char		**get_command_array(char *str);

// /parsing/parsing_utils.c
int			count_between_quotes(char *str, int i);
void		free_array(char **array);
void		print_commands(t_cmdlist *list);
void		free_commands(t_cmdlist *list);

// /parsing/parsing.c
t_cmdlist	ft_parsing(char *argv);

// /parsing/new_dev.c
char		*convert_string(char *str);
char		check_for_errors(char *str);

// minishell.c
void		ft_input(char **argv, char **envp);

// utils.c
void		ft_error(const char *msg);
void		ft_exit(char *argv);
void		ft_free_dbl(char **ptr);
void		print_dbl_ptr(char **ptr);

#endif

int	ft_word_length(char *s, char c, int i)
{
	int	temp;
	int	j;

	j = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		if (s[i] == 34 || s[i] == 39)
			{
				temp = count_between_quotes(s, i);
				if (temp < 0)
					return (-1);
				i += temp;
				j += temp;
			}
		i++;
		j++;
	}
	return (j);
}

int	ft_count_words(char *str, char c)
{
	int	wordcount;
	int	i;

	wordcount = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			while (str[i] && str[i + 1] && str[i] != c)
			{
				if (str[i] == 34 || str[i] == 39)
				{
					if (count_between_quotes(str, i) < 0)
						return (-1);
					i += count_between_quotes(str, i);
				}
				i++;
			}
			wordcount++;
		}
		i++;
	}
	return (wordcount);
}

char	**ft_split_skip_quotes(char *s, char c)
{
	char	**array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	array = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!array || !s)
		return (NULL);
	while (i < ft_count_words(s, c))
	{
		while (s[j] == c)
			j++;
		array[i] = ft_substr(s, j, ft_word_length(s, c, j));
		if (array[i] == NULL)
		{
			free_array(array);
			return (NULL);
		}
		j += ft_word_length(s, c, j);
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	init_cmdlist(t_cmdlist *list)
{
    list->head = NULL;
}

t_cmdlist	put_in_cmdlist(char **command_array)
{
	t_cmdlist	command_list;
	t_minishell	*command;
	char		**temp;
	int			i;

	init_cmdlist(&command_list);
	i = 0;
	while (command_array[i])
	{
		temp = ft_split_skip_quotes(command_array[i], ' ');
		if (!temp)
			free_array(command_array);
		command = get_command(temp);
		if (!command)
			free_array(command_array);
		add_command(&command_list, command);
		free_array(temp);
		i++;
	}
	return (command_list);
}

t_node	*create_node(t_minishell *cmd)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return NULL;
    new_node->cmd = cmd;
    new_node->next = NULL;
    return (new_node);
}

void	add_command(t_cmdlist *list, t_minishell *cmd)
{
	t_node	*new_node;
	t_node	*temp;

	new_node = create_node(cmd);
	if (!new_node)
		return;
    if (!list->head)
        list->head = new_node;
    else
	{
        temp = list->head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

char	**array_dup(char **array)
{
	int		i;
	char	**duplicate_array;

	i = 0;
	while (array[i] != NULL)
		i++;
	duplicate_array = (char **)malloc((i + 1) * sizeof(char *));
	if (!duplicate_array)
		return (NULL);
	duplicate_array[i] = NULL;
	i--;
	while (i >= 0)
	{
		duplicate_array[i] = ft_strdup(array[i]);
		if (!duplicate_array[i])
		{
			while (duplicate_array[++i])
				free(duplicate_array[i]);
			free(duplicate_array);
			return (NULL);
		}
		i--;
	}
	return (duplicate_array);
}

t_minishell	*get_command(char **arg_array)
{
	t_minishell	*a;

	a = malloc(sizeof(t_minishell));
	a->command = ft_strdup(arg_array[0]);
	if (!a->command)
		return (free(a), NULL);
	a->arguments = array_dup(arg_array);
	if (!a->arguments)
	{
		free(a->command);
		return (free(a), NULL);
	}
	a->envp = array_dup(environ);
	if (!a->envp)
	{
		free(a->arguments);
		free_array(a->arguments);
		return (free(a), NULL);
	}
	return (a);
}

int	count_wordlen(char *str, int i)
{
	int len;
	int temp;

	len = 0;
	while (str[i] && str[i] != '|')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			temp = count_between_quotes(str, i);
			if (temp < 0)
				return (-1);
			i += temp;
			len += temp;
		}
		len++;
		i++;
	}
	return (len);
}

char	**fill_array(char **array, char *str, int wordcount)
{
	int wordlen;
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < wordcount && str[j])
	{
		wordlen = count_wordlen(str, j);
		array[i] = ft_substr(str, j, wordlen);
		if (!array[i])
		{
			while (i--)
				free(array[i]);
			return (free(array), NULL);
		}
		j += (wordlen + 1);
		i++;
	}
	return (array);
}

int	ft_count_commands(char *str, char c)
{
	int wordcount;
	int i;

	wordcount = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			wordcount++;
		if (str[i] == 34 || str[i] == 39)
		{
			if (count_between_quotes(str, i) < 0)
				return (-1);
			i += count_between_quotes(str, i);
		}
		i++;
	}
	return (wordcount);
}

char	**get_command_array(char *str)
{
	char	**command_array;
	int		wordcount;

	wordcount = ft_count_commands(str, '|');
	if (wordcount < 0)
		return (ft_printf("No ending quote"), NULL);
	command_array = malloc((wordcount + 1) * sizeof(char *));
	if (!command_array)
		return (ft_printf("Malloc fail"), NULL);
	command_array[wordcount] = NULL;
	fill_array(command_array, str, wordcount);
	return (command_array);
}

int is_metachar(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int is_valid_double(char *str, int i)
{
	if (str[i] && (str[i] == '<' || str[i] == '>'))
	{
		if (str[i - 1] && str[i - 1] == str[i] && str[i - 2]
			&& !is_metachar(str[i - 2]))
			return (1);
	}
	return (0);
}

char get_first_metachar(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (is_metachar(str[i]))
			return (str[i]);
		i++;
	}
	return (0);
}

int check_for_uneven_quotes(char *str)
{
	int i;
	int single_count;
	int double_count;

	i = 0;
	single_count = 0;
	double_count = 0;
	while (str[i])
	{
		if (str[i] == 34)
			double_count++;
		if (str[i] == 39)
			single_count++;
		i++;
	}
	if (single_count % 2 == 1)
		return (printf("syntax error near unexpected token '\''\n"), 1);
	if (double_count % 2 == 1)
		return (printf("syntax error near unexpected token '\"'\n"), 1);
	return (0);
}

char check_for_errors(char *str)
{
	int		i;
	char	last_char;

	i = 0;
	if (!str[i])
		return (1);
	last_char = get_first_metachar(str);
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		while (str[i] && !ft_isspace(str[i]))
		{
			if ((is_metachar(str[i]) && is_metachar(last_char)) && !is_valid_double(str, i))
				return (printf("syntax error near unexpected token '%c'\n", last_char), last_char);
			last_char = str[i];
			i++;
		}
	}
	if (last_char == 0 || check_for_uneven_quotes(str) == 1)
		return (1);
	if (is_metachar(last_char))
		return (printf("syntax error near unexpected token '%c'\n", last_char), last_char);
	return (0);
}

int	get_meta_len(char *str, int i)
{
	if (str[i + 1] && str[i + 1] == str[i])
		return (2);
	return (1);
}

int	new_strlen(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] && is_metachar(str[i]))
		{
			i += get_meta_len(str, i);
			count += 2;
		}
		else
			i++;
		count++;
	}
	return (count);
}

int is_in_quoted_section(char *str, int i)
{
	int temp;
	int count;

	temp = i;
	count = 0;
	while (str[temp--])
	{
		if (str[temp] == 34 || str[temp] == 39)
			count++;
	}
	if (count % 2 == 1)
		return (1);
	return (0);
}

void	add_spaces(char *new_str, char *str, int *i, int *j)
{
	int	k;
	int	meta_len;

	k = 0;
	if (*j > 0 && new_str[*j - 1] != ' ' && !is_in_quoted_section(str, *i))
		new_str[(*j)++] = ' ';
	meta_len = get_meta_len(str, *i);
	while (k < meta_len)
	{
		new_str[(*j)++] = str[(*i)++];
		k++;
	}
	if (str[*i] && str[*i] != ' '  && !is_in_quoted_section(str, *i))
		new_str[(*j)++] = ' ';
}

char	*convert_string(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = new_strlen(str);
	if (len < 0)
		return (NULL);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] && is_metachar(str[i]))
			add_spaces(new_str, str, &i, &j);
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

void	print_commands(t_cmdlist *list)
{
	t_node	*current;
	char	**arg;

	current = list->head;
	while (current != NULL)
	{
        printf("Command: %s\n", current->cmd->command);
        if (current->cmd->arguments)
		{
			arg = current->cmd->arguments;
            printf("Arguments: ");
            while (*arg != NULL)
			{
				printf("(%s) ", *arg);
				arg++;
			}
            printf("\n\n");
        }
        current = current->next;
    }
}

void	free_command(t_minishell *cmd)
{
	char	**arg;
	char	**env;

	arg = cmd->arguments;
	env = cmd->envp;
	if (cmd->command) free(cmd->command);
    if (cmd->arguments)
	{
        while (*arg != NULL)
		{
            free(*arg);
			arg++;
        }
        free(cmd->arguments);
    }
    if (cmd->envp)
	{
        while (*env != NULL)
		{
            free(*env);
			env++;
        }
        free(cmd->envp);
    }
    free(cmd);
}

void	free_commands(t_cmdlist *list)
{
    t_node	*current;
    t_node	*next;

	current = list->head;
    while (current != NULL)
	{
        next = current->next;
        free_command(current->cmd);
        free(current);
        current = next;
    }
    list->head = NULL;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
	return ;
}

int	count_between_quotes(char *str, int i)
{
	char	temp;
	int		j;

	temp = str[i];
	j = 1;
	i++;
	while (str[i] && str[i] != temp)
	{
		j++;
		i++;
	}
	if (!str[i])
		return (-1);
	return (j);
}

void	print_command(t_minishell *a)
{
	int	i;

	i = 0;
	if (a && a->command)
		printf("filename: %s\n\n", a->command);
	else
		return ;
	if (!a->arguments)
	{
		printf("\n");
		return ;
	}
	while (a->arguments[i])
	{
		printf("arg %i: %s\n", (i + 1), a->arguments[i]);
		i++;
	}
	ft_printf("\n");
	ft_printf("\n");
	return ;
}

void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
	return ;
}

static char	*get_env_value(char *var_name)
{
	int		i;
	size_t	len;

	i = 0;
	len = strlen(var_name);
	while (environ[i])
	{
		if (strncmp(environ[i], var_name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*handle_var(char **src, char *dst)
{
	char	*start;
	char	*var_name;
	char	*value;
	size_t	var_len;

	(*src)++;
	start = *src;
	while (isalnum(**src) || **src == '_')
		(*src)++;
	var_len = *src - start;
	var_name = strndup(start, var_len);
	value = get_env_value(var_name);
	free(var_name);
	if (value)
	{
		strcpy(dst, value);
		dst += strlen(value);
	}
	return (dst);
}

char	*replace_vars(char *str)
{
	char		*result;
	char	*src;
	char		*dst;

	result = malloc(strlen(str) + 1);
	if (!result)
		return (NULL);
	src = str;
	dst = result;
	while (*src)
	{
		if (*src == '$' && *(src + 1) != '\0'
			&& (isalpha(*(src + 1)) || *(src + 1) == '_'))
			dst = handle_var(&src, dst);
		else
			*dst++ = *src++;
	}
	*dst = '\0';
	free(str);
	return (result);
}

t_cmdlist	ft_parsing(char *argv)
{
	t_cmdlist	command_list;
	char		**command_array;
	char		*converted_string;
	
	if (check_for_errors(argv) != 0)
        return (command_list.head = NULL, command_list);
    converted_string = convert_string(argv);
    if (!converted_string)
        return (command_list.head = NULL, command_list);
	converted_string = replace_vars(converted_string);
	if (!converted_string)
		return (command_list.head = NULL, command_list);
    command_array = get_command_array(converted_string);
    free(converted_string);
	command_list = put_in_cmdlist(command_array);
	print_commands(&command_list);
	return (command_list);
	// free_commands(&command_list);
	// free_array(command_array);
}
extern char **environ;

char	*get_env_value(const char *var_name)
{
	int		i;
	size_t	len;

	i = 0;
	len = strlen(var_name);
	while (environ[i])
	{
		if (strncmp(environ[i], var_name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*handle_var(const char **src, char *dst)
{
	const char	*start;
	char		*var_name;
	char		*value;
	size_t		var_len;

	(*src)++;
	start = *src;
	while (isalnum(**src) || **src == '_')
		(*src)++;
	var_len = *src - start;
	var_name = strndup(start, var_len);
	value = get_env_value(var_name);
	free(var_name);
	if (value)
	{
		strcpy(dst, value);
		dst += strlen(value);
	}
	return (dst);
}

char	*replace_vars(const char *str)
{
	char		*result;
	const char	*src;
	char		*dst;

	result = malloc(strlen(str) + 1);
	if (!result)
		return (NULL);
	src = str;
	dst = result;
	while (*src)
	{
		if (*src == '$' && *(src + 1) != '\0'
			&& (isalpha(*(src + 1)) || *(src + 1) == '_'))
			dst = handle_var(&src, dst);
		else
			*dst++ = *src++;
	}
	*dst = '\0';
	return (result);
}

int	main(int argc, char *argv[])
{
	char	*output;

	if (argc != 2)
		return (1);
	ft_parsing(argv[1]);
	if (output)
	{
		printf("%s\n", output);
		free(output);
	}
	return (0);
}
