/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:28:44 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/12 16:47:29 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_command(t_com *command, t_data *data)
{
	int	returnval;
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	returnval = ft_redirect_io(command);
	if (!returnval && command->args[0] != NULL)
	{
		if (cmd_is_builtin(command))
			returnval = exec_builtin(command, data);
		else
			returnval = exec_processus(command, data);
	}
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	if (command->cmd_input_mode == CMD_HERE_DOC)
	{
		unlink(command->infile);
		free(command->infile);
	}
	return (returnval);
}

char	*resolve_absolute_path(char *cmd, char **envp, char *cmd_name)
{
	char	*path;
	char	*abs_cmd;

	path = path_env(envp);
	abs_cmd = ft_absolute_path(cmd, path);
	free(path);
	if (!abs_cmd)
		cmd_not_found(cmd_name);
	return (abs_cmd);
}

int	ft_perror(char *str)
{
	perror(str);
	return (-1);
}

char	*print_access_error(char *str, char *cmd_name)
{
	printf("%s: %s\n", cmd_name, str);
	return (NULL);
}

int	exec_processus(t_com *command, t_data *data)
{
	char	**cmd;
	char	*absolute_cmd;
	int		status;

	cmd = command->args;
	absolute_cmd = get_absolute_command(cmd[0], data->envp);
	if (absolute_cmd)
	{
		g_global.pid = fork();
		if (g_global.pid == -1)
			return (ft_perror("Fork"));
		if (g_global.pid == 0)
			execve(absolute_cmd, cmd, data->envp);
		else
		{
			while (waitpid(g_global.pid, &status, WNOHANG) == 0)
				;
			free(absolute_cmd);
			return (WEXITSTATUS(status));
		}
	}
	return (127);
}
