/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ch_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:52:39 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/09 19:13:18 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_pwd(char *pwd, char *arg, t_flag *setenv_flag, t_data *data)
{
	ft_setenv("OLDPWD", ft_strjoin("OLDPWD=",
			getcwd(pwd, 256)), setenv_flag, data);
	chdir(arg);
	ft_setenv("PWD", ft_strjoin("PWD=", getcwd(pwd, 256)), setenv_flag, data);
}

int	update_directory(char *arg, t_data *data, t_flag *setenv_flag)
{
	char		pwd[256];
	struct stat	sb;

	if (stat(arg, &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
		{
			update_pwd(pwd, arg, setenv_flag, data);
			return (0);
		}
		else
		{
			printf("cd: %s: Not a directory\n", arg);
			g_global.code_error = 1;
			return (1);
		}
	}
	else
	{
		printf("cd: %s: %s\n", arg, strerror(errno));
		return (1);
	}
}

int	ft_change_directory(t_com *command, t_data *data)
{
	t_flag		setenv_flag;

	setenv_flag.overwrite = 1;
	setenv_flag.flag_plus = 0;
	if (command->args[1] == NULL)
		return (0);
	return (update_directory(command->args[1], data, &setenv_flag));
}
