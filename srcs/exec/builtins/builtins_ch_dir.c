/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ch_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:52:39 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/12 17:26:04 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_pwd(char *pwd, char *arg, t_flag *setenv_flag, t_data *data)
{
	char	*oldpwd_str;
	char	*pwd_str;

	oldpwd_str = ft_strjoin("OLDPWD=", getcwd(pwd, 256));
	pwd_str = ft_strjoin("PWD=", getcwd(pwd, 256));
	ft_setenv("OLDPWD", oldpwd_str, setenv_flag, data);
	chdir(arg);
	ft_setenv("PWD", pwd_str, setenv_flag, data);
	free(oldpwd_str);
	free(pwd_str);
}

int	update_directory(char *arg, t_data *data, t_flag *setenv_flag)
{
	char		pwd[256];
	struct stat	sb;

	if (stat(arg, &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode) && !access(arg, R_OK))
		{
			update_pwd(pwd, arg, setenv_flag, data);
			return (0);
		}
		else
		{
			if (errno == EACCES)
				printf("cd: %s: Permission denied\n", arg);
			else
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
