/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:47:39 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/18 20:51:31 by ory              ###   ########.fr       */
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

char	*var_name(char *str, int flag)
{
	char	*varname;

	if (unexpected_char_in_name(str))
	{
		if (flag == 1)
		{
			printf("export: `%s': not a valid identifier\n", str);
			return (NULL);
		}
		if (flag == 0)
		{
			printf("unset: `%s': not a valid identifier\n", str);
			return (NULL);
		}
	}
	varname = extract_name_in_assignment(str);
	return (varname);
}

int	ft_export(t_com *command, t_data *data)
{
	char	*name = NULL;
	char	*value;
	int		i;
	char	*tmp_value;
	int j = 0;
	int flag_plus = 0;

	i = 1;
	while (command->args[i])
	{
		name = var_name(command->args[i], 1);
		if (name && !ft_ischarset(command->args[i], '=') && (value = var_exist_outside_env(data, command->args[i])))
		{
			tmp_value = ft_strjoin("=", value);
			free(value);
			value = ft_strjoin(name, tmp_value);
			free(tmp_value);
			ft_setenv(name, value, 0, data, 0);
			delete_var_in_lst(&data->var_list, name);
			free(value);
		}
		else if (name && ft_ischarset(command->args[i], '='))
		{
			while(command->args[i][j])
			{
				if (command->args[i][j] == '=' && command->args[i][j - 1] == '+')
					flag_plus = 2;
				j++;
			}
			value = extract_value_in_assignment(command->args[i]);
			tmp_value = ft_strjoin("=", value);
			free(value);
			value = ft_strjoin(name, tmp_value);
			free(tmp_value);
			ft_setenv(name, value, 1, data, flag_plus);
			free(value);
		}
		else if (name)
			lst_add_var(data, name, NULL, 1);
		i++;
		free(name);
	}
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
	{
		free_mem(data);
		exit (0);
	}
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

int	ft_unset(t_com *command, t_data *data)
{
	
	int	i;
	char	*name;
	char	*value;

	i = 1;
	while(command->args[i])
	{
		if (ft_ischarset(command->args[i], '='))
			printf("unset: `%s': not a valid identifier\n", command->args[i]);
		name = var_name(command->args[i], 0);
		if (name && (ft_ischarset(name, '+')))
			printf("unset: `%s': not a valid identifier\n", command->args[i]);
		if ((value = var_exist_outside_env(data, name)))
			delete_var_in_lst(&data->var_list, name);
		if (var_is_in_env(name, data))
			delete_var_in_env(name, data);
		if (value)
			free(value);
		free(name);
		i++;
	}
	return (0);
}

void	delete_var_in_env(char *name, t_data *data)
{
	char	*name_with_equal;
	int	i;
	char	**new_envp;
	int	j;

	j = 0;
	i = 0;
	name_with_equal = ft_strjoin(name, "=");
	while(data->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		ft_exit_error("Memory allocation error");
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], name_with_equal, ft_strlen(name_with_equal)))
		{
			new_envp[j] = ft_strdup(data->envp[i]);
			j++;
		}
		i++;
	}
	i--;
	new_envp[i] = NULL;
	i = -1;
	while (data->envp[++i])
		free(data->envp[i]);
	free(data->envp);
	free(name_with_equal);
	data->envp = new_envp;
}