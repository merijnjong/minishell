/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:33 by mjong             #+#    #+#             */
/*   Updated: 2024/12/04 17:42:36 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echo_env(t_minishell *envlist, const char *command)
{
    t_minishell *current = envlist;
    char *env = NULL;
    char *env_name = NULL;
    int i;

    command++;
    while (current) {
        i = 0;
        env_name = get_var_name(current->env, &i);
        if (env_name && ft_strcmp(env_name, command) == 0) {
            env = current->env + i;
            free(env_name);
            break;
        }
        free(env_name);
        current = current->next_env;
    }

    if (env)
        ft_printf("%s", env);
}


int echo(t_minishell *minishell, char **args)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    if (!args[1])
    {
        ft_printf("\n");
        return (0);
    }
    if (ft_strcmp(args[1], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (args[i])
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
    if (newline)
        ft_printf("\n");
    return (0);
}

