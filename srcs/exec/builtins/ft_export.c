/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:20:17 by ory               #+#    #+#             */
/*   Updated: 2023/05/02 13:47:34 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_export(t_com *command, t_data *data)
{
	int		i;
	
	i = 1;
	if (!command->args[1])
		ft_env_export(data);
	while (command->args[i])
	{
		export_var(command->args[i], data);
		i++;
	}
	return (0);
}

void    export_var(char *arg, t_data *data)
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