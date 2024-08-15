#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// TE LUI OM .H TE INCLUDEN

extern char **environ;

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

int	add_redirect_or_pipe(char *str_ptr)
{
	if (str_ptr && (str_ptr + 1))
	{
		if (*str_ptr == *(str_ptr + 1))
			return (printf("\ndouble: %c%c\n", *str_ptr, *(str_ptr + 1)), 2);
		else
			return (printf("\nsingle: %c\n", *str_ptr), 1);
	}
	return (0);
}

int	print_array(char **arg_array)
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

t_cmd    *add_command(char **args, int type)
{
 t_cmd   *command;

 command = (t_cmd *)malloc(sizeof(t_cmd *));
 if (!command)
     return (NULL);
 command->filename = ft_strjoin("/usr/bin/", args[0]);
 if (!command->filename)
     return (free(command), NULL);
 command->args = args;
 if (!command->args)
 {
     free(command->filename);
     return (free(command), NULL);
 }
 command->envp = environ;
 if (!command->envp)
 {
     free(command->filename);
     ft_free(command->args);
     return (free(command), NULL);
 }
 return (command);
}

void    add_node(t_node **head, char **args, int type)
{
    t_node  *new_node;
    t_node  *current_node;

    new_node = (t_node *)malloc(sizeof(t_node));
    if (!new_node)
        return ;
    new_node->next = NULL;
    new_node->cmd = add_command(args, type);
    if (!new_node->cmd)
    {
        free(new_node);
        return ;
    }
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


t_cmdlist   *create_list(void)
{
    t_cmdlist   *list;

    list = malloc(sizeof(t_cmdlist));
    if (!list)
        return (NULL);
    list->head = NULL;
    return (list);
}

int	main(int argc, char *argv[])
{
	int			i;
	t_cmdlist	*list;
	char		*test_string;
	char		*split_chars;
	char		**arg_array;

	i = 0;
	test_string = "this is a test || to see <<if it works";
	split_chars = "|<>";
	list = create_list();
	while (test_string[i])
	{
		arg_array = get_next_arg((test_string) + i);
		while (test_string[i] && !ft_strchr(split_chars, test_string[i]))
			i++;
		if (arg_array)
		{
			add_node(&list->head, arg_array, 5);
			printf("\n\nArray:\n");
			print_array(arg_array);
			ft_free(arg_array);
		}
		if (test_string[i])
			i += add_redirect_or_pipe(test_string + i);
		if (test_string[i] && ft_strchr(split_chars, test_string[i]))
			return (printf("Invalid redirect or pipe combination: %c (char %i)", test_string[i], i), 1);
	}
	printf("is het gelukt? head->filename: %s arg 1 & 2: %s & %s", list->head->cmd->filename, list->head->cmd->args[0], list->head->cmd->args[1]);
	return (0);
}