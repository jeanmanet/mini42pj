/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:47:39 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/30 18:34:04 by ory              ###   ########.fr       */
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

	varname = NULL;
	if (unexpected_char_in_name(str))
	{
		if (flag == 1)
		{
			printf("export: `%s': not a valid identifier\n", str);
			global.exit_code = 1;
			return (NULL);
		}
		if (flag == 0)
		{
			printf("unset: `%s': not a valid identifier\n", str);
			global.exit_code = 1;
			return (NULL);
		}
	}
	varname = extract_name_in_assignment(str);
	return (varname);
}

// int	ft_export(t_com *command, t_data *data)
// {
// 	char	*name = NULL;
// 	char	*value;
// 	int		i;
// 	char	*tmp_value;
// 	int j = 0;
// 	int flag_plus = 0;

// 	i = 1;
// 	while (command->args[i])
// 	{
// 		name = var_name(command->args[i], 1);
// 		if (name && !ft_ischarset(command->args[i], '=') && (value = var_exist_outside_env(data, command->args[i])))
// 		{
// 			tmp_value = ft_strjoin("=", value);
// 			free(value);
// 			value = ft_strjoin(name, tmp_value);
// 			free(tmp_value);
// 			ft_setenv(name, value, 0, data, 0);
// 			delete_var_in_lst(&data->var_list, name);
// 			free(value);
// 		}
// 		else if (name && ft_ischarset(command->args[i], '='))
// 		{
// 			while(command->args[i][j])
// 			{
// 				if (command->args[i][j] == '=' && command->args[i][j - 1] == '+')
// 					flag_plus = 2;
// 				j++;
// 			}
// 			value = extract_value_in_assignment(command->args[i]);
// 			tmp_value = ft_strjoin("=", value);
// 			free(value);
// 			value = ft_strjoin(name, tmp_value);
// 			free(tmp_value);
// 			ft_setenv(name, value, 1, data, flag_plus);
// 			free(value);
// 		}
// 		else if (name)
// 			lst_add_var(data, name, NULL, 1);
// 		i++;
// 		free(name);
// 	}
// 	return (0);
// }

int	ft_export(t_com *command, t_data *data)
{
	int		i;
	
	i = 1;
	while (command->args[i])
	{
		export_var(command->args[i], data);
		i++;
	}
	return (0);
}

// void export_var(char *arg, t_data *data)
// {
// 	char	*name = NULL;
// 	char	*value;
// 	char	*tmp_value;
// 	int j = 0;
// 	int flag_plus = 0;

// 	name = var_name(arg, 1);
// 	if (name && !ft_ischarset(arg, '=') && (value = var_exist_outside_env(data, arg)))
// 	{
// 		tmp_value = ft_strjoin("=", value);
// 		free(value);
// 		value = ft_strjoin(name, tmp_value);
// 		free(tmp_value);
// 		ft_setenv(name, value, 0, data, 0);
// 		delete_var_in_lst(&data->var_list, name);
// 		free(value);
// 	}
// 	else if (name && ft_ischarset(arg, '='))
// 	{
// 		while(arg[j])
// 		{
// 			if (arg[j] == '=' && arg[j - 1] == '+')
// 				flag_plus = 2;
// 			j++;
// 		}
// 		value = extract_value_in_assignment(arg);
// 		tmp_value = ft_strjoin("=", value);
// 		free(value);
// 		value = ft_strjoin(name, tmp_value);
// 		free(tmp_value);
// 		ft_setenv(name, value, 1, data, flag_plus);
// 		free(value);
// 	}
// 	else if (name)
// 		lst_add_var(data, name, NULL, 1);
// 	free(name);
// }

void export_var(char *arg, t_data *data)
{
	char	*name;
	char	*value;

	name = NULL;
	name = var_name(arg, 1);
	if (name && !ft_ischarset(arg, '=') && (value = var_exist_outside_env(data, arg)))
	{
		var_already_outside_env(name, value, data);
		free(value);
	}
	else if (name && ft_ischarset(arg, '='))
		export_var_assignment(name, arg, data);
	else if (name)
		lst_add_var(data, name, NULL, 1);
	free(name);
}

void	export_var_assignment(char *name, char *arg, t_data *data)
{
	char	*value;
	char	*tmp_value;
	int	flag_plus;
	int	j;

	flag_plus = 0;
	j = 0;
	while(arg[j])
	{
		if (arg[j] == '=' && arg[j - 1] == '+')
			flag_plus = 2;
		j++;
	}
	value = extract_value_in_assignment(arg);
	tmp_value = ft_strjoin("=", value);
	free(value);
	value = ft_strjoin(name, tmp_value);
	free(tmp_value);
	ft_setenv(name, value, 1, data, flag_plus);
	free(value);
}

void	var_already_outside_env(char *name, char *value, t_data *data)
{
    	char	*new_value;
    	char	*tmp_value;

    	new_value = ft_strjoin(name, "=");
    	tmp_value = ft_strjoin(new_value, value);
    	free(new_value);
    	ft_setenv(name, tmp_value, 0, data, 0);
    	delete_var_in_lst(&data->var_list, name);
    	free(tmp_value);
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

int	ft_unset(t_com *command, t_data *data)
{
	int	i;
	char	*name;

	i = 1;
	while(command->args[i])
	{
		if (ft_ischarset(command->args[i], '='))
		{
			printf("unset: `%s': not a valid identifier\n", command->args[i]);
			global.exit_code = 1;
		}
		name = var_name(command->args[i], 0);
		if (name == NULL)
        	{
        	    i++;
        	    continue;
        	}
		if (name && (ft_ischarset(name, '+')))
		{
			printf("unset: `%s': not a valid identifier\n", command->args[i]);
			global.exit_code = 1;
		}
		// if (name && (value = var_exist_outside_env(data, name)))
		// 	delete_var_in_lst(&data->var_list, name);
		// if (name && var_is_in_env(name, data))
		// 	delete_var_in_env(name, data);
		// if (value)
		// 	free(value);
		// if (name)
		// 	free(name);
		unset_variable(name, data);
		i++;
	}
	return (0);
}

void	unset_variable(char *name, t_data *data)
{
	char	*value;

	value = NULL;
	if (name && (value = var_exist_outside_env(data, name)))
		delete_var_in_lst(&data->var_list, name);
	if (name && var_is_in_env(name, data))
		delete_var_in_env(name, data);
	if (value)
		free(value);
	if (name)
		free(name);
}


void	delete_var_in_env(char *name, t_data *data)
{
	char	*name_with_equal;
	int	i;
	char	**new_envp;

	i = 0;
	name_with_equal = ft_strjoin(name, "=");
	while(data->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		ft_exit_error("Memory allocation error");
	make_new_env(new_envp, data->envp, name_with_equal);
	i = -1;
	while (data->envp[++i])
		free(data->envp[i]);
	free(data->envp);
	free(name_with_equal);
	data->envp = new_envp;
}

void	make_new_env(char **new_envp, char **envp, char *name_with_equal)
{
    	int	i;
    	int	j;

    	i = 0,
    	j = 0;
    	while (envp[i])
    	{
    	    if (ft_strncmp(envp[i], name_with_equal, ft_strlen(name_with_equal)))
		{
    	        new_envp[j] = ft_strdup(envp[i]);
    	        j++;
    	    }
    	    i++;
    	}
    	new_envp[j] = NULL;
}

// int	ft_exit(t_com *command, t_data *data)
// {
// 	int	i;
// 	int	exit_code;
// 	char	*str;

// 	i = 1;
// 	if (command->args[i])
// 	{
// 		while(command->args[i])
// 			i++;
// 		i--;
// 		if(i > 1 && str_is_only_digit(command->args[1]))
// 		{
// 			printf("exit\nminishell: exit: too many arguments\n");
// 			global.exit_code = 1;
// 		}
// 		else if (!str_is_only_digit(command->args[1]))
// 		{
// 			printf("exit\nminishell: exit: %s: numeric argument required\n", command->args[1]);
// 			free_mem(data);
// 			exit(255);
// 		}
// 		else
// 		{
// 			printf("exit\n");
// 			str = ft_strdup(command->args[1]);
// 			exit_code = ft_atoi(str);
// 			free(str);
// 			free_mem(data);
// 			exit(exit_code);
// 		}
// 	}
// 	else
// 	{
// 		free_mem(data);
// 		exit (0);
// 	}
// 	return (0);
// }

void	check_exit_args(t_com *command, t_data *data)
{
	int	i;

	i = 1;
	while (command->args[i])
		i++;
	i--;
	if (i > 1 && str_is_only_digit(command->args[1]))
	{
		printf("exit\nminishell: exit: too many arguments\n");
		global.exit_code = 1;
	}
	else if (!str_is_only_digit(command->args[1]))
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n", command->args[1]);
		free_mem(data);
		exit(255);
	}
	else
	{
		printf("exit\n");
		exit(ft_atoi(command->args[1]));
	}
}

int	ft_exit(t_com *command, t_data *data)
{
	if (command->args[1])
		check_exit_args(command, data);
	else
	{
		free_mem(data);
		exit(0);
	}
	return (0);
}


int	str_is_only_digit(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}