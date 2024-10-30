/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:33 by mjong             #+#    #+#             */
/*   Updated: 2024/10/30 17:19:08 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_env(t_envlist *envlist, char *input)
{
	char		*env;
	char		*env_name;
	t_envlist	*current;
	int			i;

	input++;
	env = NULL;
	current = envlist;
	while (current != NULL)
	{
		i = 0;
		env_name = get_var_name(current->env, &i);
		if (strcmp(env_name, input) == 0 && env_name != NULL)
		{
			env = current->env + i;
			free(env_name);
			break ;
		}
		free(env_name);
		current = current->next;
	}
	if (env == NULL)
		ft_printf("\n");
	else
		ft_printf("%s\n", env);
}

int	echo(t_status status, t_envlist *envlist, char *input)
{
	while (*input == ' ')
		input++;
	if (ft_strncmp(input, "-n", 2) == 0)
		ft_printf("%s", input + 3);
	else if (ft_strncmp(input, "$?", 2) == 0)
		ft_printf("%d\n", status.last);
	else if (ft_strncmp(input, "$", 1) == 0)
		echo_env(envlist, input);
	else
		ft_printf("%s\n", input);
	return (0);
}

// int	echo(char *input, t_status status)
// {
// 	int	print_newline;

// 	print_newline = 1;
// 	while (*input == ' ')
// 		input++;
// 	if (strncmp(input, "-n", 2) == 0 && (input[2] == ' ' || input[2] == '\0'))
// 	{
// 		print_newline = 0;
// 		input += 2;
// 		while (*input == ' ')
// 			input++;
// 	}
// 	if (strncmp(input, "$?", 2) == 0 && (input[2] == ' ' || input[2] == '\0'))
//         printf("%d", status.last);
//     else
//         printf("%s", input);
//     if (print_newline)
//         printf("\n");
//     return (0);
// }