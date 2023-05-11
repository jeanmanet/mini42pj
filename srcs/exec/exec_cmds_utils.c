/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 10:26:17 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/11 22:23:24 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab_str_cmd(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
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
	char	*result;
	int		i;

	i = 0;
	paths = ft_split(PATH, ':');
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		current_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(current_path, X_OK) == 0)
		{
			free_tab_str_cmd(paths);
			result = ft_strdup(current_path);
			free(current_path);
			return (result);
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
	struct stat	sb;

	cmd = arg;
	cmd_name = arg;
	if (!access(cmd, X_OK))
	{
		if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
			return (print_access_error("is a directory", cmd_name));
		return (ft_strdup(cmd));
	}
	if (errno == EACCES)
		return (print_access_error("Permission denied", cmd_name));
	if (!str_is_cmd(cmd, envp) && errno == ENOENT)
		return (print_access_error("No such file or directory", cmd_name));
	path = path_env(envp);
	cmd = ft_absolute_path(cmd, path);
	if (!cmd)
		cmd_not_found(cmd_name);
	free(path);
	return (cmd);
}

char	*str_is_cmd(char *arg, char **envp)
{
	char	*cmd;
	char	*path;

	if (ft_ischarset(arg, '='))
		return (NULL);
	if (!access(arg, X_OK))
		return (ft_strdup(arg));
	path = path_env(envp);
	cmd = ft_absolute_path(arg, path);
	free(path);
	return (cmd);
}
