/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:32:31 by mjong             #+#    #+#             */
/*   Updated: 2024/12/05 12:35:02 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void print_command(t_node *node)
{
    t_cmd *cmd;
    int i;

    // Ensure the node and its command are valid
    if (!node || !(cmd = node->cmd))
        return;

    // Print the command name (filename)
    if (cmd->filename)
        printf("filename: %s\n\n", cmd->filename);

    // Print the arguments if available
    if (!cmd->args)
    {
        printf("\n");
        return;
    }

    i = 0;
    while (cmd->args[i])
    {
        printf("arg %i: %s\n", (i + 1), cmd->args[i]);
        i++;
    }
    printf("\n\n");
}

int init_cmd_struct(t_cmd **cmd)
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
