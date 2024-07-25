/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokanization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:25 by mjong             #+#    #+#             */
/*   Updated: 2024/07/25 18:05:52 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// int *ft_get_token(char *str, int i)
// {
// 	str = NULL;
// 	i = 0;
// 	return (0);
// }

// t_tokenlist	*ft_tokenize(char *str)
// {
// 	int		i;
// 	char	*delimiters;

// 	i = 0;
// 	delimiters = " \n\t";
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '|' || str[i] == '>' ||str[i] == '<'
// 			|| str[i] == '"' || str[i] == 39 || str[i] == '$')
// 			ft_get_token(str, i);
// 	}
// }

char *get_filename(char *str)
{
	int i;
	char *command;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	command = malloc((i + 1) * sizeof(char));
	if (!command)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		command[i] = str[i];
		i++;
	}
	command[i] = '\0';
	return (command);
}

t_cmd *get_command(char *str, int end)
{
	int i;
	char *temp;
	t_cmd *command;

	i = 0;
	temp = get_filename(str);
	command->filename = ft_strjoin("/usr/bin/", temp);
	free(temp);
	if (!command->filename)
		return (NULL);
	while (str[i] && str[i] != ' ' && i != end)
		i++;
	command->args = ft_split(*(str + i), ' ');
	if (!command->args)
		return (free(command->filename), NULL);
	command->envp = __environ;
	if (!command->envp)
	{
		free(command->filename);
		return (ft_free(command->args), NULL);
	}
	return (command);
}

int ft_divider(char *str)
{
	int i;
	t_cmd *command;

	i = 0;
	command = malloc(sizeof(command));
	if (!ft_token_in_string(str))
		get_command(str, command);
}

int ft_token_in_string(char *str)
{
	int i;
	char *tokens;

	i = 0;
	tokens = "<>|$";
	while (str[i])
	{
		if (ft_strchr(tokens, str[i]) || str[i] == 34 || str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

// ls -a | grep hello
// zoeken naar literals ("")
// zoeken in string naar pipes en redirects
// cmdlist of cmd, red, cm, red, cmd length.
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 

t_cmdlist *get_substrings(char *str)
{
	t_cmdlist	*list;
	t_cmd		*temp;

	list = malloc(sizeof(t_cmdlist));
	if (!list)
		return (NULL);
	list->head = add_command
	
}
