/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 10:26:17 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/23 15:06:23 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab_str_cmd(char **str)
{
	int	i;

	i = 0;
	if (!str[0] && str[1])
		i++;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (NULL);
}

char	*ft_absolute_path(char *cmd, const char *PATH)
{
	char	**paths;
	char	*tmp;
	char	*current_path;
	int		i;

	i = 0;
	paths = ft_split(PATH, ':');
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		current_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(current_path, X_OK) == 0)
		{
			free_tab_str_cmd(paths);
			return (current_path);
		}
		free(current_path);
		i++;
	}
	free_tab_str_cmd(paths);
	return (NULL);
}

char	*get_absolute_command(char	*arg, char **envp)
{
	char	*cmd;
	char	*path;
	char	*cmd_name;

	cmd = arg;
	cmd_name = arg;
	if (!access(cmd, X_OK))
		return (cmd);
	if (cmd[0] == '.' || cmd[0] == '/')
	{
		if (!access(cmd, X_OK))
			return (cmd);
		else
			exit_cmd_strerror(cmd_name);
	}
	path = path_env(envp);
	cmd = ft_absolute_path(cmd, path);
	if (!cmd)
		cmd_not_found(cmd_name);
	free(path);
	return (cmd);
}
