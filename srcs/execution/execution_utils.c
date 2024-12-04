#include "minishell.h"

char *expand_variable(char *cmd)
{
    int		i;
    int		len;
	int		var_name_len;
    char	*var_name;
    char	*var_value;
    char	*new_cmd;

	i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '$')
        {
            var_name = get_var_name(cmd, &i);
            if (var_name == NULL)
                return (cmd);
            var_value = getenv(var_name);
            var_name_len = ft_strlen(var_name);
            free(var_name);
            if (var_value == NULL)
                var_value = "";
            len = ft_strlen(cmd) - var_name_len + ft_strlen(var_value);
            new_cmd = malloc(len + 1);
            if (new_cmd == NULL)
                return (cmd);
            ft_strncpy(new_cmd, cmd, i);
            new_cmd[i] = '\0';
            strcat(new_cmd, var_value);
            strcat(new_cmd, cmd + i);
            free(cmd);
            return (new_cmd);
        }
        i++;
    }
    return (cmd);
}
