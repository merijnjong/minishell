/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:45:45 by mjong             #+#    #+#             */
/*   Updated: 2024/10/09 13:34:54 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// TE LUI OM .H TE INCLUDEN

# define WORD 10
# define HEREDOC 11 // <<
// # define SPACE 12
# define PIPE 13 // |
# define REDIRECT 14 // >>
# define APPEND 15 // <
# define INPUT 16 // >
# define END 17

extern char **envliston;

typedef struct s_cmd
{
	char	*filename;
	char	**args;
	char	**envp;
} t_cmd;

typedef struct s_node
{
	int 			type;
	t_cmd 			*cmd;
	struct s_node	*next;
} t_node;

typedef struct s_cmdlist
{
	struct s_node	*head;
} t_cmdlist;



int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char) c == '\0')
		return ((char *)s + i);
	return (NULL);
}
static int	ft_stringcounter(char const *s, char c)
{
	int	strings;
	int	sign;

	strings = 0;
	sign = 0;
	while (*s != '\0')
	{
		if (*s != c && sign == 0)
		{
			strings++;
			sign = 1;
		}
		if (*s == c)
		{
			sign = 0;
		}
		s++;
	}
	return (strings);
}

static int	ft_length(const char *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		j++;
	}
	return (j);
}

void	ft_free(char **str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		free(str[j]);
		j++;
	}
	free(str);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	totlen;
	char	*str;

	i = 0;
	totlen = ft_strlen(s);
	str = (char *)malloc(totlen + 1);
	if (!str)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	substr_len;
	char	*str;

	i = 0;
	substr_len = len;
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (start + substr_len > (unsigned int)ft_strlen(s))
		substr_len = (unsigned int)ft_strlen(s) - start;
	str = (char *)malloc(substr_len + 1);
	if (!str)
		return (NULL);
	while (i < substr_len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;

	str = malloc((ft_stringcounter(s, c) + 1) * sizeof(char *));
	i = 0;
	j = 0;
	if (!str || !s)
		return (NULL);
	while (i < ft_stringcounter(s, c))
	{
		while (s[j] == c)
			j++;
		str[i] = ft_substr(s, j, ft_length(s, c, j));
		if (str[i] == NULL)
		{
			ft_free(str);
			return (NULL);
		}
		j += ft_length(s, c, j);
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	totlen;
	char	*str;

	i = 0;
	j = 0;
	totlen = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(totlen + 1);
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	**get_next_arg(char *str_ptr)
{
	int		i;
	char	*arg_string;
	char	**arg_array;
	char	*split_chars;

	i = 0;
	split_chars = "|<>";
	while (str_ptr[i] && !ft_strchr(split_chars, str_ptr[i]))
		i++;
	if (i == 0)
		return (NULL);
	arg_string = malloc(i * sizeof(char) + 1);
	if (!arg_string)
		return (printf("no arg string"), NULL);
	arg_string[i] = '\0';
	while (i--)
		arg_string[i] = str_ptr[i];
	arg_array = ft_split(arg_string, ' ');
	if (!arg_array)
	{
		printf("no arg array");
		return (free(arg_string), NULL);
	}
	free(arg_string);
	return (arg_array);
}

char	**array_dup(char **array)
{
	int		i;
	char	**duplicate_array;

	i = 0;
	while (array[i] != NULL)
		i++;
	duplicate_array = malloc((i + 1) * sizeof(char *));
	if (!duplicate_array)
		return (NULL);
	duplicate_array[i] = NULL;
	i = 0;
	while (duplicate_array[i] != NULL)
	{
		duplicate_array[i] = ft_strdup(array[i]);
		if (!duplicate_array[i])
		{
			while (--i)
				free(duplicate_array[i]);
			free(duplicate_array);
			return (NULL);
		}
		i++;
	}
	return (duplicate_array);
}

t_cmd *get_redirect_or_pipe(char c, int is_double) // DON'T FORGET TO ADD MALLOC PROTECTION!!
{
	t_cmd	*command;

	command = (t_cmd *)malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	if (c == '|')
		command->filename = ft_strdup("pipe");
	else if (c == '>')
	{
		if (is_double == 1)
			command->filename = ft_strdup("redirect");
		else
			command->filename = ft_strdup("input");
	}
	else if (c == '<')
	{
		if (is_double == 1)
			command->filename = ft_strdup("heredoc");
		else
			command->filename = ft_strdup("append");
	}
	command->args = NULL;
	command->envp = array_dup(envliston);
	return (command);
}

t_cmd *add_redirect_or_pipe(char *str_ptr, int *i)
{
	if (*str_ptr && *(str_ptr + 1))
	{
		if (*str_ptr == *(str_ptr + 1) && *str_ptr == '<' || *str_ptr == '>')
		{
			*i += 2;
			return (get_redirect_or_pipe(*str_ptr, 1));
		}
		else if (*str_ptr != *(str_ptr + 1))
		{
			*i += 1;
			return (get_redirect_or_pipe(*str_ptr, 0));
		}
		else
			return (NULL);
	}
	return (NULL);
}


int	print_array(char **arg_array) // -> print arg **
{
	int i;

	i = 0;
	if (arg_array == NULL)
		return (0);
	while (arg_array[i] != NULL)
	{
		printf("%s\n", arg_array[i]);
		i++;
	}
	return (i);
}

t_cmd	*cmd_dup(t_cmd *command)
{
	t_cmd *duplicate;

	duplicate = (t_cmd *)malloc(sizeof(t_cmd));
	if (!duplicate)
		return (NULL);
	duplicate->filename = ft_strdup(command->filename);
	if (duplicate->filename)
		return (free(duplicate), NULL);
	duplicate->args = array_dup(command->args);
	if (!duplicate->args)
	{
		free(duplicate->filename);
		return (free(duplicate), NULL);
	}
	duplicate->envp = array_dup(command->envp);
	if (!duplicate->envp)
	{
		free(duplicate->filename);
		free_array(duplicate->args);
		return (free(duplicate), NULL);
	}
	return (duplicate);
}

void    add_node(t_node **head, t_cmd *command)
{
    t_node  *new_node;
    t_node  *current_node;

    new_node = (t_node *)malloc(sizeof(t_node));
    if (!new_node)
        return ;
    new_node->next = NULL;
	new_node->cmd = cmd_dup(command);
	if (!new_node->cmd)
		return (free(new_node), NULL);
	current_node = NULL;
	if (!*head)
        *head = new_node;
    else
    {
        current_node = *head;
        while (current_node->next != NULL)
            current_node = current_node->next;
        current_node->next = new_node;
    }
}

void free_command(t_cmd **a)
{
	t_cmd *copy;

	copy = *a;
	if (!copy)
		return ;
	if (copy->filename)
		free(copy->filename);
	if (copy->args)
		free_array(copy->args);
	if (copy->envp)
		free_array(copy->envp);
	free(copy);
	return ;
}

void free_cmdlist_recursive(t_node *node)
{
    if (!node)
        return ;
    free_cmdlist_recursive(node->next);
    free_command(&node->cmd);
    free(node);
}

void free_cmdlist(t_cmdlist *list)
{
    if (!list)
        return ;
    free_cmdlist_recursive(list->head);
    free(list);
}

t_cmdlist   *create_list(void)
{
    t_cmdlist   *list;

    list = malloc(sizeof(t_cmdlist));
    if (!list)
        return (NULL);
    list->head = NULL;
    return (list);
}

void	free_array(char **array)
{
	int i;

	i = 0;
	if (array && array[i])
	{
		while (array[i] != NULL)
			free(array[i++]);
		free(array);
	}
	return ;
}


t_cmd *get_command(char **arg_array, t_cmd *a)
{
	a->filename = ft_strdup(arg_array[0]);
	if (!a->filename)
	{
		return (free(a), NULL);
	}
	a->args = array_dup(arg_array);
	if (!a->args)
		return (NULL);
	a->envp = array_dup(envliston);
	if (!a->envp)
		return (NULL);
	return (a);
}

void print_command(t_cmd *a)
{
	int	i;

	i = 0;
	if (a && a->filename)
		printf("filename: %s\n\n", a->filename);
	else
		return ;
	if (!a->args)
	{
		printf("\n");
		return;
	}
	while (a->args[i])
	{
		printf("arg %i: %s\n", (i + 1), a->args[i]);
		i++;
	}
	printf("\n");
	printf("\n");
	return ;
}


int	main(int argc, char *argv[])
{
	int			i;
	t_cmd		*a;
	t_cmdlist	*list;
	char		*split_chars;
	char		**arg_array;

	i = 0;
	split_chars = "|<>";
	if (argc != 2)
		return (1);
	list = create_list();
	while (argv[1][i])
	{
		arg_array = get_next_arg(argv[1] + i);
		while (argv[1][i] && !ft_strchr(split_chars, argv[1][i]))
			i++;
		a = (t_cmd *)malloc(sizeof(t_cmd));
		get_command(arg_array, a);
		add_node(&list, a);
		print_command(a);
		free_command(&a);
		free_array(arg_array);
		a = add_redirect_or_pipe((argv[1] + i), &i);
		print_command(a);
		free_command(&a);
		if (argv[1][i] && ft_strchr(split_chars, argv[1][i]))
			return (printf("Invalid redirect or pipe combination: %c (char %i)", argv[1][i], i), 1);
	}
	return (0);
}
