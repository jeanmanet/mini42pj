/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ch_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:52:39 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/30 17:23:46 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_change_directory(t_com *command, t_data *data)
{
	char		pwd[256];
	struct stat	sb;

	if (command->args[1] == NULL)
		return (0);
	if (stat(command->args[1], &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
		{
			ft_setenv("OLDPWD", ft_strjoin("OLDPWD=",
					getcwd(pwd, 256)), 1, data, 0);
			chdir(command->args[1]);
			ft_setenv("PWD", ft_strjoin("PWD=", getcwd(pwd, 256)), 1, data, 0);
			return (0);
		}
		else
		{
			printf("cd: %s: Not a directory\n", command->args[1]);
			global.exit_code = 1;
			return (1);
		}
	}
	else
		printf("cd: %s: %s\n", command->args[1], strerror(errno));
	return (1);
}
