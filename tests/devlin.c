/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:32:31 by mjong             #+#    #+#             */
/*   Updated: 2024/11/13 16:32:33 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct s_cmd
{
	char	*filename;
	char	**args;
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

extern char **environ;

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

int count_between_quotes(char *str, int i)
{
	int j;
	char temp;

	j = 1;
	temp = str[i];
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

int ft_count_commands(char *str, char c)
{
	int i;
	int wordcount;

	i = 0;
	wordcount = 1;
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

int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\v' || c == '\r')
		return (1);
	return (0);
}

int count_wordlen(char *str, int i)
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

char **fill_array(char **array, char *str, int wordcount)
{
	int i;
	int j;
	int wordlen;

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

void ft_print_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
	return ;
}

void free_array(char **array)
{
	int i;

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

t_cmd *get_command(char **arg_array)
{
	t_cmd *a;

	a = malloc(sizeof(t_cmd));
	a->filename = ft_strdup(arg_array[0]);
	if (!a->filename)
		return (free(a), NULL);
	a->args = array_dup(arg_array);
	if (!a->args)
	{
		free(a->filename);
		return (free(a), NULL);
	}
	a->envp = array_dup(environ);
	if (!a->envp)
	{
		free(a->filename);
		free_array(a->args);
		return (free(a), NULL);
	}
	return (a);
}

char **get_command_array(char *str)
{
	int wordcount;
	char **command_array;

	wordcount = ft_count_commands(str, '|');
	if (wordcount < 0)
		return (printf("No ending quote"), NULL);
	command_array = malloc((wordcount + 1) * sizeof(char *));
	if (!command_array)
		return (printf("Malloc fail"), NULL);
	command_array[wordcount] = NULL;
	fill_array(command_array, str, wordcount);
	return (command_array);
}

int ft_count_words(char *str, char c)
{
	int i;
	int wordcount;

	i = 0;
	wordcount = 0;
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

int	ft_word_length(char *s, char c, int i)
{
	int	j;
	int temp;

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

char	**ft_split_skip_quotes(char*s, char c)
{
	int		i;
	int		j;
	char	**array;

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
		return ;
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

void init_cmdlist(t_cmdlist *list)
{
    list->head = NULL;
}

t_node *create_node(t_cmd *cmd)
{
	t_node *new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return NULL;
    new_node->cmd = cmd;
    new_node->next = NULL;
    return (new_node);
}

void add_command(t_cmdlist *list, t_cmd *cmd)
{
	t_node *new_node;
	t_node *temp;
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

void free_command(t_cmd *cmd) {
    if (cmd->filename) free(cmd->filename);
    if (cmd->args) {
        for (char **arg = cmd->args; *arg != NULL; arg++) {
            free(*arg);
        }
        free(cmd->args);
    }
    if (cmd->envp) {
        for (char **env = cmd->envp; *env != NULL; env++) {
            free(*env);
        }
        free(cmd->envp);
    }
    free(cmd);
}

void free_commands(t_cmdlist *list) {
    t_node *current = list->head;
    t_node *next;
    while (current != NULL) {
        next = current->next;
        free_command(current->cmd);
        free(current);
        current = next;
    }
    list->head = NULL;
}

void print_commands(t_cmdlist *list) {
	t_node *current;
	char **arg;

	current = list->head;
	while (current != NULL)
	{
        printf("Command: %s\n", current->cmd->filename);
        if (current->cmd->args)
		{
			arg = current->cmd->args;
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

t_cmdlist put_in_cmdlist(char **command_array)
{
	int i;
	char **temp;
	t_cmd *command;
	t_cmdlist command_list;


	i = 0;
	init_cmdlist(&command_list);
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

int main(int argc, char **argv)
{
	t_cmdlist command_list;

	char **command_array;
	if (argc != 2 ) 
		return (printf("One argument only!"), 1);
	command_array = get_command_array(argv[1]);
	if (!command_array)
		return (1);
	command_list = put_in_cmdlist(command_array);
	print_commands(&command_list);
	free_commands(&command_list);
	free_array(command_array);
	return (0);
}