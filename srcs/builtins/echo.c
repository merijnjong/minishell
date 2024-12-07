/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:33 by mjong             #+#    #+#             */
/*   Updated: 2024/12/07 16:21:14 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    echo_env(t_minishell *envlist, const char *command)
{
    t_minishell *current;
    char        *env;
    char        *env_name;
    int         i;

    current = envlist;
    env = NULL;
    env_name = NULL;
    command++;
    while (current != NULL)
    {
        i = 0;
        env_name = get_var_name(current->env, &i);
        if (env_name && ft_strcmp(env_name, command) == 0)
        {
            env = current->env + i;
            free(env_name);
            break;
        }
        free(env_name);
        current = current->next_env;
    }
    if (env != NULL)
        ft_printf("%s", env);
}

int echo(t_minishell *minishell, char **args)
{
    int	newline;
    int	i;

    newline = 1;
    i = 1;
    if (args[1] == NULL)
    {
        ft_printf("\n");
        return (0);
    }
    if (ft_strcmp(args[1], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (args[i] != NULL)
    {
        if (ft_strcmp(args[i], "$?") == 0)
            ft_printf("%d", minishell->status);
        else if (ft_strncmp(args[i], "$", 1) == 0)
            echo_env(minishell, args[i]);
        else
            ft_printf("%s", args[i]);

        if (args[i + 1])
            ft_printf(" ");
        i++;
    }
    if (newline != 0)
        ft_printf("\n");
    return (0);
}

