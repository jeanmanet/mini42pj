/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:47:39 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/30 20:24:39 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_echo(t_com *command)
{
	int	i;

	i = 0;
	if (!command->args[1])
	{
		printf("\n");
		return (0);
	}
	if (!ft_strncmp(command->args[1], "-n", 3))
		i = 2;
	else
		i = 1;
	while (command->args[i])
	{
		printf("%s", command->args[i]);
		i++;
		if (command->args[i])
			printf(" ");
	}
	if (ft_strncmp(command->args[1], "-n", 3))
		printf("\n");
	return (0);
}

int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while(data->envp[i])
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
	return (1);
}

int	cmd_is_builtin(t_com *command)
{
	if (!ft_strncmp(command->args[0], "exit", 5))
		return (1);
	if (!ft_strncmp(command->args[0], "cd", 3))
		return (1);
	if (!ft_strncmp(command->args[0], "pwd", 4))
		return (1);
	if (!ft_strncmp(command->args[0], "echo", 5))
		return (1);
	if (!ft_strncmp(command->args[0], "export", 7))
		return (1);
	if (!ft_strncmp(command->args[0], "env", 4))
		return (1);
	if (!ft_strncmp(command->args[0], "unset", 6))
		return (1);
	return (0);
}

int	cmd_is_builtin_2(char *command)
{
	if (ft_ischarset(command, '='))
		return (0);
	if (!ft_strncmp(command, "exit", 5))
		return (1);
	if (!ft_strncmp(command, "cd", 3))
		return (1);
	if (!ft_strncmp(command, "pwd", 4))
		return (1);
	if (!ft_strncmp(command, "echo", 5))
		return (1);
	if (!ft_strncmp(command, "export", 7))
		return (1);
	if (!ft_strncmp(command, "env", 4))
		return (1);
	if (!ft_strncmp(command, "unset", 6))
		return (1);
	return (0);
}

int	exec_builtin(t_com *command, t_data *data)
{
	if (!ft_strncmp(command->args[0], "exit", 5))
		return (ft_exit(command, data));
	if (!ft_strncmp(command->args[0], "cd", 3))
		return (ft_change_directory(command, data));
	if (!ft_strncmp(command->args[0], "pwd", 4))
		printf("%s\n", ft_getenv("PWD=", data));
	if (!ft_strncmp(command->args[0], "echo", 5))
		return (ft_echo(command));
	if (!ft_strncmp(command->args[0], "export", 7))
		return (ft_export(command, data));
	if (!ft_strncmp(command->args[0], "env", 4))
		return (ft_env(data));
	if (!ft_strncmp(command->args[0], "unset", 6))
		return (ft_unset(command, data));
	return (0);
}