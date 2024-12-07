/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:05:48 by dkros             #+#    #+#             */
/*   Updated: 2024/12/07 17:29:52 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*init_redirect(void)
{
	t_redirect	*redirect;

	redirect = malloc(sizeof(t_redirect));
	if (redirect == NULL)
		return (NULL);
	redirect->type = NO_REDIR;
	redirect->filename = NULL;
	return (redirect);
}

int	get_redirection_type(char *str)
{
	if (str == NULL)
		return (NO_REDIR);
	if (ft_strcmp(str, "<<") == 0)
		return (REDIR_HEREDOC);
	if (ft_strcmp(str, ">>") == 0)
		return (REDIR_APPEND);
	if (ft_strcmp(str, "<") == 0)
		return (REDIR_IN);
	if (ft_strcmp(str, ">") == 0)
		return (REDIR_OUT);
	return (NO_REDIR);
}

int	count_new_size(char **args)
{
	int	new_size;
	int	i;

	new_size = 0;
	i = 0;
	while (args[i] != NULL)
	{
		if (get_redirection_type(args[i]) != NO_REDIR)
		{
			if (args[i + 1] != NULL)
				i += 2;
			continue ;
		}
		new_size++;
		i++;
	}
	return (new_size);
}

int	handle_redirect(char **args, int *i, t_redirect *redirect)
{
	int	type;

	type = get_redirection_type(args[*i]);
	if (type != NO_REDIR)
	{
		if (args[*i + 1] == NULL)
		{
			// needs to be changed to ft_printf or equavalent
			ft_printf("Error: Missing filename for redirection\n");
			return (-1);
		}
		redirect->type = type;

		free(redirect->filename);
		redirect->filename = ft_strdup(args[*i + 1]);
		if (redirect->filename == NULL)
			return (-1);

		*i += 2;
        return (1);
	}
	return (0);
}

char	**create_new_args(char **args, t_redirect *redirect, int new_size)
{
	char	**new_args;
	int		i;
	int		j;

	new_args = malloc(sizeof(char *) * (new_size + 1));
	if (new_args == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i] != NULL)
	{
		if (handle_redirect(args, &i, redirect))
			continue ;
		if (get_redirection_type(args[i]) == NO_REDIR)
		{
			new_args[j] = ft_strdup(args[i]);
			if (new_args[j] == NULL)
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

