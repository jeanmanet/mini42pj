/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:58:40 by ory               #+#    #+#             */
/*   Updated: 2023/04/28 15:48:11 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*var_exist_outside_env(t_data *data, char *var_name)
{
	t_lst_var	*tmp;

	tmp = data->var_list;
	if (!var_name)
		return (NULL);
	while(tmp)
	{
		if (ft_strcmp(var_name, tmp->name) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

char *get_env_variable_value(char *var_name, t_data *data)
{
	char	*var_with_equal;
	char	*tmp_value;
	char	*value;

	value = NULL;
	tmp_value = NULL;
	if (!var_name)
		return (NULL);
	var_with_equal = ft_strjoin(var_name, "=");
	tmp_value = ft_getenv(var_with_equal, data);
	free(var_with_equal);
	if (tmp_value == NULL)
		return (NULL);
	else if (tmp_value != NULL)
	{
		value = ft_strdup(tmp_value);
		free(tmp_value);
	}
	return (value);
}

void	add_var_in_list(t_data *data, char *str)
{
	char	*name;
	char	*value;
	int	index;
	int	i;
	int	flag_plus;
	
	name = NULL;
	value = NULL;
	index = get_name_and_index(str, &name, &flag_plus, &i);
	value = ft_substr(str, index, i - index);
	if (check_if_var_is_for_env(name, value, data, flag_plus) == 0)
		lst_add_var(data, name, value, flag_plus); // flag toujour 0 ou 2
	free(name);
	free(value);
}

int get_name_and_index(char *str, char **name, int *flag_plus, int *i)
{
	int	index;
	
	*i = 0;
	*flag_plus = 0;
	index = 0;
	while(str[*i])
	{
	    if (str[*i] == '=' || str[*i] == '+')
	    {
			if (str[*i] == '+' && str[*i + 1] == '=')
				*flag_plus = 2;
	        *name = ft_substr(str, 0, *i);
	        index = *i + 1;
	        break;
	    }
	    (*i)++;
	}
	return index;
}

int	check_if_var_is_for_env(char *name, char *value, t_data *data, int flag_plus)
{
	t_lst_var	*tmp;
	char		*tmp_str;
	char		*str;

	tmp = data->var_list;
	while(tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0 && tmp->flag_var_for_env == 1)
		{
			delete_var_in_lst(&data->var_list, name);
			tmp_str = ft_strjoin(name, "=");
			str = ft_strjoin(tmp_str, value);
			ft_setenv(name, str, 1, data, 0);
			free(tmp_str);
			free(str);
			return (1);
		}
		tmp = tmp->next;
	}
	if (var_is_in_env(name, data))
	{
		set_env_var(name, value, data, flag_plus);
		return (1);
	}
	return (0);
}

void	set_env_var(char *name, char *value, t_data *data, int flag_plus)
{
    	char	*tmp_str;
    	char	*str;

    	tmp_str = ft_strjoin(name, "=");
    	str = ft_strjoin(tmp_str, value);
    	ft_setenv(name, str, 1, data, flag_plus);
    	free(tmp_str);
    	free(str);
}

int	var_is_in_env(char *name, t_data *data)
{
	int	i;
	char	*name_with_equal;
	char	*new_name;

	i = 0;
	if (!ft_ischarset(name, '='))
	{
		name_with_equal = ft_strjoin(name, "=");
		new_name = ft_strdup(name_with_equal);
		free(name_with_equal);
	}
	else
		new_name = ft_strdup(name);
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], new_name, ft_strlen(new_name)))
		{
			free(new_name);
			return (1);
		}
		i++;
	}
	free(new_name);
	return (0);
}