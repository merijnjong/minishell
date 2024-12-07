#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>

# define NO_REDIR 0
# define REDIR_IN 1
# define REDIR_OUT 2
# define REDIR_APPEND 3
# define REDIR_HEREDOC 4

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

t_redirect *init_redirect(void)
{
    t_redirect *redirect;

    redirect = malloc(sizeof(t_redirect));
    if (!redirect)
        return (NULL);
    redirect->type = NO_REDIR;
    redirect->filename = NULL;
    return (redirect);
}

int get_redirection_type(char *str)
{
    if (!str)
        return (NO_REDIR);
    if (strcmp(str, "<<") == 0)
        return (REDIR_HEREDOC);
    if (strcmp(str, ">>") == 0)
        return (REDIR_APPEND);
    if (strcmp(str, "<") == 0)
        return (REDIR_IN);
    if (strcmp(str, ">") == 0)
        return (REDIR_OUT);
    return (NO_REDIR);
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

static int	count_new_size(char **args)
{
	int	i;
	int	new_size;

	i = 0;
	new_size = 0;
	while (args[i])
	{
		if (get_redirection_type(args[i]) != NO_REDIR)
		{
			if (args[i + 1])
				i += 2;
			continue ;
		}
		new_size++;
		i++;
	}
	return (new_size);
}

static int	handle_redirect(char **args, int *i, t_redirect *redirect)
{
	int	type;

	type = get_redirection_type(args[*i]);
	if (type != NO_REDIR && args[*i + 1])
	{
		redirect->type = type;
		free(redirect->filename);
		redirect->filename = ft_strdup(args[*i + 1]);
		*i += 2;
		return (1);
	}
	return (0);
}

static char	**create_new_args(char **args, t_redirect *redirect, int new_size)
{
	char	**new_args;
	int		i;
	int		j;

	new_args = malloc(sizeof(char *) * (new_size + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (handle_redirect(args, &i, redirect))
			continue ;
		if (get_redirection_type(args[i]) == NO_REDIR)
		{
			new_args[j] = ft_strdup(args[i]);
			if (!new_args[j])
				return (free_array(new_args), NULL);
			j++;
		}
		i++;
	}
	new_args[j] = NULL;
	return (new_args);
}

char	**remove_redirections(char **args, t_redirect *redirect)
{
	int		new_size;
	char	**new_args;

	new_size = count_new_size(args);
	new_args = create_new_args(args, redirect, new_size);
	return (new_args);
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
		{
			wordcount++;
			if (str[i + 1] != '\0' && str[i + 1] == c)
				return (-2);
		}
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

void clean_array(char **array, int i)
{
	while (i--)
		free(array[i]);
	free(array);
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
			return (clean_array(array, i), NULL);
		j += (wordlen + 1);
		i++;
	}
	array[wordcount] = NULL;
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

static int	init_cmd_struct(t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	if (!*cmd)
		return (0);
	(*cmd)->redirect = init_redirect();
	if (!(*cmd)->redirect)
	{
		free(*cmd);
		return (0);
	}
	return (1);
}

t_cmd	*get_command(char **arg_array)
{
	t_cmd	*cmd;
	char	**new_args;

	if (!init_cmd_struct(&cmd))
		return (NULL);
	new_args = remove_redirections(arg_array, cmd->redirect);
	if (!new_args)
	{
		free(cmd->redirect);
		free(cmd);
		return (NULL);
	}
	cmd->filename = ft_strdup(new_args[0]);
	if (!cmd->filename)
	{
		free_array(new_args);
		free(cmd->redirect);
		free(cmd);
		return (NULL);
	}
	cmd->args = new_args;
	return (cmd);
}

char **get_command_array(char *str)
{
	int wordcount;
	char **command_array;

	wordcount = ft_count_commands(str, '|');
	if (wordcount == -1)
		return (printf("Error: No ending quote\n"), NULL);
	if (wordcount == -2)
		return (printf("Error: Double pipes\n"), NULL);
	command_array = malloc((wordcount + 1) * sizeof(char *));
	if (!command_array)
		return (printf("Error: Malloc fail"), NULL);
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
		if (str[i])
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

void print_command(t_cmd *cmd)
{
    int i;

    if (!cmd)
        return;
    printf("Command: %s\n", cmd->filename);
    i = 0;
    if (cmd->args)
    {
        printf("Arguments: ");
        while (cmd->args[i])
            printf("(%s) ", cmd->args[i++]);
        printf("\n");
    }
    if (cmd->redirect)
    {
        printf("Redirection: ");
        if (cmd->redirect->type == REDIR_IN)
            printf("< %s\n", cmd->redirect->filename);
        else if (cmd->redirect->type == REDIR_OUT)
            printf("> %s\n", cmd->redirect->filename);
        else if (cmd->redirect->type == REDIR_APPEND)
            printf(">> %s\n", cmd->redirect->filename);
        else if (cmd->redirect->type == REDIR_HEREDOC)
            printf("<< %s\n", cmd->redirect->filename);
        else
            printf("none\n");
    }
    printf("\n");
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
    if (!cmd)
        return;
    if (cmd->filename)
        free(cmd->filename);
    if (cmd->args)
        free_array(cmd->args);
    if (cmd->redirect)
    {
        if (cmd->redirect->filename)
            free(cmd->redirect->filename);
        free(cmd->redirect);
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
        print_command(current->cmd);
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
		while (str[i] && is_space(str[i]))
			i++;
		while (str[i] && !is_space(str[i]))
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

static char	*get_env_value(const char *var_name)
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


void execute_command(t_cmd *cmd, char **envp, int input_fd, int output_fd) {
    // Handle redirections
    if (cmd->redirect && cmd->redirect->type != NO_REDIR) {
        int fd;
        if (cmd->redirect->type == REDIR_IN) {
            fd = open(cmd->redirect->filename, O_RDONLY);
        } else if (cmd->redirect->type == REDIR_OUT) {
            fd = open(cmd->redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        } else if (cmd->redirect->type == REDIR_APPEND) {
            fd = open(cmd->redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
        if (fd < 0) {
            perror("minishell");
            exit(1);
        }
        dup2(fd, (cmd->redirect->type == REDIR_IN) ? STDIN_FILENO : STDOUT_FILENO);
        close(fd);
    }

    // Handle input/output redirection from pipes
    if (input_fd != STDIN_FILENO) {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if (output_fd != STDOUT_FILENO) {
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
    }

    // Execute command
    if (execve(cmd->filename, cmd->args, envp) == -1) {
        perror(cmd->filename);
        exit(127);
    }
}

void execute_commands(t_cmdlist *cmdlist, char **envp) {
    t_node *current = cmdlist->head;
    int pipe_fd[2], input_fd = STDIN_FILENO;

    while (current) {
        if (current->next) {
            pipe(pipe_fd); // Create a pipe for the next command
        }

        pid_t pid = fork();
        if (pid == 0) { // Child process
            if (current->next) {
                close(pipe_fd[0]); // Close unused read end
                execute_command(current->cmd, envp, input_fd, pipe_fd[1]);
            } else {
                execute_command(current->cmd, envp, input_fd, STDOUT_FILENO);
            }
        } else if (pid > 0) { // Parent process
            waitpid(pid, NULL, 0); // Wait for child process
            close(pipe_fd[1]); // Close unused write end
            if (input_fd != STDIN_FILENO) {
                close(input_fd); // Close previous input_fd
            }
            input_fd = pipe_fd[0]; // Update input_fd for next command
        } else {
            perror("fork");
            exit(1);
        }
        current = current->next; // Move to next command
    }
}

void process_builtin_or_execute(t_cmdlist *cmdlist, char **envp) {
    execute_commands(cmdlist, envp);
}


int main(int argc, char **argv)
{
	t_cmdlist command_list;
	char	*converted_string;

	char **command_array;
	if (argc != 2 )
		return (printf("One argument only!\n"), 1);
	if (check_for_errors(argv[1]) != 0)
		return (1);
	converted_string = convert_string(argv[1]);
	if (!converted_string)
		return (1);
	converted_string = replace_vars(converted_string);
	if (!converted_string)
		return (1);
	command_array = get_command_array(converted_string);
	free(converted_string);
	if (!command_array)
		return (1);
	command_list = put_in_cmdlist(command_array);
	process_builtin_or_execute(&command_list, environ);
	free_commands(&command_list);
	free_array(command_array);
	return (0);
}

