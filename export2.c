/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/07 19:30:47 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_varmod(char *cmd)
{
	char	*env_var;
	int		len;

	len = strintchr(cmd, '=');
	env_var = ft_substr(cmd, 0, len + 1);
	if (getenv(env_var))
		ft_strlcpy(getenv(env_var), cmd + len, ft_strlen(cmd + len) + 1);
	else
		len = 0;
	free (env_var);
	return (len);
}

int	export_check_args(int f, char **cmd)
{
	int	u;

	u = f;
	while (cmd[++u])
	{
		if (ft_strncmp(cmd[f], cmd[u], strintchr(cmd[u], '=') - 1) == 0 \
		&& ft_strncmp(cmd[f], cmd[u], strintchr(cmd[f], '=') - 1) == 0)
			return (0);
	}
	return (1);
}

int	export_check_equal(char *cmd)
{
	int	f;

	f = -1;
	while (cmd[++f])
	{
		if ((cmd[f] >= 65 && cmd[f] <= 90) || \
	(cmd[f] >= 97 && cmd[f] <= 122) || cmd[f] == 95)
			if (cmd[f + 1] == '=')
				return (1);
	}
	return (0);
}

void	export_print_error(char *str)
{
	int	f;

	f = 1;
	printf("export: `%s': not a valid identifier\n", str);
	g_glob.exit_status = 1;
}

void	very_trash(char	*str, int flag, int to_add)
{
	int	f;

	f = -1;
	if (ft_strncmp(str, "_=", 2) == 0)
		return ;
	printf("declare -x ");
	while (str[++f])
	{
		printf("%c", str[f]);
		if (str[f] == flag)
			printf("%c", to_add);
	}
	printf("%c\n", to_add);
}
