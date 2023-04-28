/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_extract_and_replace.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:39:42 by ory               #+#    #+#             */
/*   Updated: 2023/04/28 15:47:33 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_value_in_assignment(char *str)
{
	char    *value;
	int     i;
	int     index;
	int     flag_plus;
	
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
	char    *name;
	int     i;
	
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

int variable_length(char* str, int start) 
{
        int len_var;
        int j;

        len_var = 0;
        j = start + 1;
        while(str[j])
        {
            if (str[j] == '$' || str[j] == '=' || str[j] == ':')
                break;
            len_var++;
            j++;
        }
        return len_var;
}

char* append_string(char* str1, char* str2) 
{
        char        *result;
        char        *tmp;

        if (str1)
        {
            tmp = ft_strdup(str1);
            free(str1);
        }
        else
            tmp = ft_strdup("");
        result = ft_strjoin(tmp, str2);
        free(tmp);
        return result;
}

char* extract_var_value(char* str, int i, t_data* data) 
{
        int     len_var;
        char    *var;
        char    *value;
        char    *result;

        len_var = variable_length(str, i);
        var = ft_substr(str, i + 1, len_var);
        value = replace_var(var, data);
        if (value == NULL) 
            value = ft_strdup("");
        result = append_string(NULL, value);
        free(var);
        free(value);
        return result;
}

char* extract_vars(char* str, t_data* data) 
{
        int     i;
        char    *result;
        char    *var_value;
        int     var_lenght;
        char    *tmp;

        i = 0;
        result = NULL;
        var_value = NULL;
        while (str[i]) 
        {
            var_lenght = 0;
            if (str[i] == '$' && str[i + 1] && str[i + 1] != '$') 
            {
                    if (str[i + 1] && str[i + 1] == '?')
                    {
                            var_value = ft_itoa(global.exit_code);
                            var_lenght = 1;
                    }
                    else
                            var_value = extract_var_value(str, i, data);
                    result = append_string(result, var_value);
                    free(var_value);
                    if (var_lenght == 1)
                            i = i + 1;
                    else
                            i = i + variable_length(str, i);
                    if (str[i] == '=') 
                    {
                        result = append_string(result, "=");
                        i++;
                    }
            } 
            else 
            {
                tmp = ft_substr(str, i, 1);
                result = append_string(result, tmp);
                free(tmp);
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

	tmp = data->token_list;
	while(tmp)
	{
		if (tmp->q_state > 0 && ft_ischarset(tmp->token, '$'))
		{
			tmp_str = ft_strdup(tmp->token);
			new_str = extract_vars(tmp_str, data);
			free(tmp->token);
			tmp->token = ft_strdup(new_str);
			free(new_str);
			free(tmp_str);
		}
                //printf("token = %s type = %d  quote = %d  flag = %d\n", tmp->token, tmp->type, tmp->q_state, tmp->flag_for_join_with_prev_token);
		tmp = tmp->next;
	}
	return (1);
}