/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/16 09:31:12 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_varmod(char *cmd)
{
	char	*env_var;
	int		len;

	len = strintchr(cmd, '=');
	env_var = ft_substr(cmd, 0, len);
	if (getenv(env_var))
		ft_strlcpy(getenv(env_var), cmd + len + 1, ft_strlen(cmd + len));
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

	f = 0;
	while (cmd[f] && (cmd[f] != '='))
	{
		if (ft_isalnum(cmd[f]) || cmd[f] == 95)
			f++;
		else
			break ;
	}
	if (cmd[f] == '=')
		return (1);
	if (!cmd[f])
		return (-1);
	return (0);
}

void	export_print_error(char *str)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
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
