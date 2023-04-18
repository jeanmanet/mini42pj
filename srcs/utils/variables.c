/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:58:40 by ory               #+#    #+#             */
/*   Updated: 2023/04/18 20:49:52 by ory              ###   ########.fr       */
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

char* extract_vars(char* str, t_data *data) 
{
    int i = 0;
    int len_var = 0;
    char* result = NULL;
    char* tmp;
    int j = 0;
    int flag = 0;

    char* tmp2;

    while (str[i]) 
    {
        if (str[i] == '$') 
        {
            j = i + 1;
            while(str[j])
            {
                if (str[j] == '$' || str[j] == '=')
                {
                        if (str[j] == '=')
                                flag = 1;
                        break;
                }
                len_var++;
                j++;
            }
            char* var = ft_substr(str, i + 1, len_var);
            char* value = replace_var(var, data);
	    if (result)
	    {
		tmp = ft_strdup(result);
		free(result);
	    }
	    else
		tmp = ft_strdup("");
	    if (value == NULL)
	    	value = ft_strdup("");
            result = ft_strjoin(tmp, value);
            free(tmp);
            free(var);
            free(value);
            i = i + len_var;
            len_var = 0;
            if (flag == 1)
            {
                tmp = ft_strdup(result);
                free(result);
                result = ft_strjoin(tmp, "=");
		free(tmp);
                i++;
                flag = 0;
            }
        }
        else 
        {
            char* tmp = ft_substr(str, i, 1);
            if (result)
            {
                tmp2 = ft_strdup(result);
                free(result);
            }
            else
                tmp2 = ft_strdup("");
            result = ft_strjoin(tmp2, tmp);
            free(tmp);
            free(tmp2);
        }
        i++;
    }
    return result;
}

char	*replace_var(char *var, t_data *data)
{
	char	*value;

	value = get_env_variable_value(var, data);
	if (value == NULL)
        	value = var_exist_outside_env(data, var);
	return (value);
}

int	replace_var_by_value(t_data *data)
{
	t_token_node 	*tmp;
	char		*tmp_str;
	char		*new_str;
	int		flag;

	flag = 0;
	tmp = data->token_list;
	while(tmp)
	{
		if (ft_strcmp(tmp->token, "$?") == 0)
		{
			free(tmp->token);
			tmp->token = ft_itoa(global.exit_code);
			tmp = tmp->next;
		}
		if (tmp->q_state > 0 && ft_ischarset(tmp->token, '$'))
		{
			if (ft_ischarset(tmp->token, '=') && tmp->token[0] != '$' && (!tmp->prev || tmp->prev->type == 4))
				flag = 1;
			tmp_str = ft_strdup(tmp->token);
			new_str = extract_vars(tmp_str, data);
			free(tmp->token);
			tmp->token = ft_strdup(new_str);
			free(new_str);
			free(tmp_str);
			if (flag == 1)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	add_var_in_list(t_data *data, char *str)
{
	char *name;
	char *value;
	int i;
	int index;
	int	flag_plus;
	
	name = NULL;
	value = NULL;
	flag_plus = 0;
	i = 0;
	index = 0;
	while(str[i])
	{
	    if (str[i] == '=' || str[i] == '+')
	    {
		if (str[i] == '+' && str[i + 1] == '=')
			flag_plus = 2;
	        name = ft_substr(str, 0, i);
	        index = i + 1;
	        break;
	    }
	    i++;
	}
	if (flag_plus)
		index++;
	value = ft_substr(str, index, i - index);
	if (check_if_var_is_for_env(name, value, data, flag_plus) == 0)
		lst_add_var(data, name, value, flag_plus); // flag toujour 0 ou 2
	free(name);
	free(value);
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
		tmp_str = ft_strjoin(name, "=");
		str = ft_strjoin(tmp_str, value);
		ft_setenv(name, str, 1, data, flag_plus);
		free(tmp_str);
		free(str);
		return (1);
	}
	return (0);
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

char	*extract_value_in_assignment(char *str)
{
	char *value;
	int i;
	int index;
	int	flag_plus;
	
	value = NULL;
	flag_plus = 0;
	i = -1;
	index = 0;
	while(str[++i])
	{
	    if (str[i] == '=' || str[i] == '+')
	    {
		if (str[i] == '+' && str[i + 1] == '=')
			flag_plus = 2;
	        index = i + 1;
	        break;
	    }
	}
	if (flag_plus)
		index++;
	value = ft_substr(str, index, i - index);
	return (value);
}

char	*extract_name_in_assignment(char *str)
{
	char *name;
	int i;
	
	name = NULL;
	i = 0;
	if (!ft_ischarset(str, '='))
		return (ft_strdup(str));
	while(str[i])
	{
	    if (str[i] == '=')
	    {
		if (str[i] == '=' && str[i - 1] == '+')
			i = i - 1;
	        name = ft_substr(str, 0, i);
	        break;
	    }
	    i++;
	}
	return (name);
}
