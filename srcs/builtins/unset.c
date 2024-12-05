/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:41 by mjong             #+#    #+#             */
/*   Updated: 2024/12/04 18:06:53 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int remove_current_node(t_minishell **envlist, t_minishell *current, t_minishell *prev)
{
    if (prev != NULL)
        prev->next_env = current->next_env;
    else
        *envlist = current->next_env;
    free(current->env);
    free(current);
    return (0);
}

int unset(t_minishell *envlist, char **args)
{
    t_minishell *current;
    t_minishell *prev;
    char *current_var_name;
    int i;

    prev = NULL;

    // Process each variable name in args[1..n]
    for (int j = 1; args[j]; j++) {
        current = envlist;
        while (current) {
            i = 0;
            current_var_name = get_var_name(current->env, &i);
            if (current_var_name && ft_strcmp(current_var_name, args[j]) == 0) {
                free(current_var_name);
                remove_current_node(&envlist, current, prev);
                break;
            }
            free(current_var_name);
            prev = current;
            current = current->next_env;
        }
    }
    return 0;
}


