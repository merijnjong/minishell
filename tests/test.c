/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:47:25 by mjong             #+#    #+#             */
/*   Updated: 2024/07/31 14:48:29 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

#define WORD 10
#define HEREDOC 11
#define SPACE 12
#define PIPE 13
#define APPEND 14
#define INPUT 15
#define TRUNC 16
#define END 17
#define NEWLINE 18
#define GREAT 19
#define AMPERSAND 20
#define LESS 21
#define GREATGREAT 22
#define QUOTE 23
#define DOUBLEQUOTE 24
#define ENVAR 25

typedef struct s_cmd
{
	char	*input;
	char	*output;
	char	*executable;
}	t_cmd;

typedef struct s_node
{
	struct s_node	*prev;
	t_cmd			*cmd;
	struct s_node	*next;
}	t_node;

typedef struct s_cmdlist
{
	struct s_node	*head;
}	t_cmdlist;

typedef struct s_token_node
{
	struct s_token_node	*prev;
	int					token;
	struct s_token_node	*next;
}	t_token_node;

typedef struct s_tokenlist
{
	struct s_toke_node	*head;
}	t_tokenlist;

t_tokenlist		*ft_tokenize(char *str);
void			add_token(t_tokenlist *tokenlist, int data);
t_token_node	*create_token_node(int data);
int				ft_isword(char *str);
char			*ft_strchr(const char *s, int c);
int				ft_isalpha(int c);

int	ft_get_token(char *str, int i)
{
	if (str[i] == '|' && str[i + 1] && str[i + 1] == ' ')
		return (PIPE);
	if (str[i] == '<' && str[i + 1] && str[i + 1] == ' ')
		return (LESS);
	if (str[i] == '>' && str[i + 1]
		&& str[i + 1] == '>' && str[i + 2] && str[i + 2] == ' ')
		return (GREATGREAT);
	if (str[i] == '>' && str[i + 1] && str[i + 1] == ' ')
		return (GREAT);
	if (str[i] == '$')
		return (ENVAR);
	if (str[i] == 39)
		return (QUOTE);
	if (str[i] == 34)
		return (DOUBLEQUOTE);
	if (str[i] == '&')
		return (AMPERSAND);
	return (0);
}

t_tokenlist	*ft_tokenize(char *str)
{
	int			i;
	int			temp;
	bool		word;
	char		*delimiters;
	char		*tokenchars;
	t_tokenlist	*tokenlist;

	i = 0;
	tokenlist = (t_tokenlist *)malloc(sizeof(t_token_node));
	delimiters = " \n\t";
	tokenchars = "|><$&'";
	while (str[i] != '\0')
	{
		word = false;
		while (ft_strchr(delimiters, str[i]) != NULL)
			i++;
		if (ft_strchr(tokenchars, str[i]) != NULL)
		{
			temp = ft_get_token(str, i);
			if (temp != 0)
				add_token(tokenlist, temp);
			i++;
		}
		while (ft_isalpha(str[i]) || str[i] == '-')
		{
			word = true;
			i++;
		}
		if (word == true)
			add_token(tokenlist, WORD);
	}
	return (tokenlist);
}

t_token_node	*create_token_node(int data)
{
	t_token_node	*new_node;

	new_node = (t_token_node *)malloc(sizeof(t_token_node));
	if (!new_node)
		return (NULL);
	new_node->token = data;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

int	ft_isword(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
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

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}

void	print_tokenlist(t_tokenlist *tokenlist)
{
	t_token_node	*temp;

	if (tokenlist->head == NULL)
	{
		printf("Tokenlist is empty\n");
		return ;
	}
	temp = tokenlist->head;
	printf("Tokenlist: ");
	while (temp != NULL)
	{
		printf("%d ", temp->token);
		temp = temp->next;
	}
	printf("\n");
}

int	main(void)
{
	char		*test;
	t_tokenlist	*tokenlist;

	test = "this is a test | for > tokens";
	tokenlist = ft_tokenize(test);
	print_tokenlist(tokenlist);
	return (0);
}

// int	ft_isalnum(int c)
// {
// 	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
// 	{
// 		return (1);
// 	}
// 	return (0);
// }int	ft_check_num_operators(char *str)
// {
// 	int		i;
// 	int		count;
// 	char	*operators;
// 	char	*delimiters;	i = 0;
// 	count = 0;
// 	delimiters = " \t\n";
// 	operators = "><|";
// 	while (str[i])
// 	{
// 		if ((str[i] && str[i - 1] && str[i + 1])
// 			&& strchr(operators, str[i]) && strchr(delimiters, str[i - 1])
// 				&& strchr(delimiters,(str[i + 1])))
// 			count ++;
// 		i++;
// 	}
// 	return (count);
// }int	get_token_count(char *input)
// {
// 	int		i;
// 	int		count;
// 	char	*delimiters;
// 	char	*operators;	count = 1;
// 	delimiters = " \t\n";
// 	operators = "><|";
// 	while (strchr(delimiters, input[i]) && input[i])
// 		i++;
// 	while (input[i] != '\0')
// 	{
// 		if (strchr(delimiters, input[i]))
// 		{
// 			while (strchr(delimiters, input[i]) && input[i])
// 				i++;
// 			if (input[i] && input[i + 1])
// 				count++;
// 		}
// 		if (strchr(operators, input[i]))
// 			count++;
// 		i++;
// 	}
// 	count -= ft_check_num_operators(input);
// 	return (count);
// }int main(int argc, char *argv[])
// {
// 	if (argc != 2)
// 		return (printf("Please give one argument"), 1);
// 	return (printf("Number of tokens: %d\n\n", get_token_count(argv[1])), 0);
// }
