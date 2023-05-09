/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_extract_and_replace.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:39:42 by ory               #+#    #+#             */
/*   Updated: 2023/05/09 19:07:28 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_var_value(char *str, int i, t_data *data)
{
	int		len_var;
	char	*var;
	char	*value;
	char	*result;

	len_var = variable_length(str, i);
	var = ft_substr(str, i + 1, len_var);
	value = replace_var(var, data);
	if (value == NULL)
			value = ft_strdup("");
	result = append_string(NULL, value);
	free(var);
	free(value);
	return (result);
}

char	*extract_vars(char *str, t_data *data)
{
	int		i;
	char	*result;
	char	*tmp;

	i = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != '$')
			get_var(str, &i, &result, data);
		else
		{
			tmp = ft_substr(str, i, 1);
			result = append_string(result, tmp);
			free(tmp);
		}
		i++;
	}
	return (result);
}

void	get_var(char *str, int *i, char **result, t_data *data)
{
	int		var_lenght;
	char	*var_value;

	var_lenght = 0;
	var_value = NULL;
	if (str[*i + 1] && str[*i + 1] == '?')
	{
			var_value = ft_itoa(g_global.exit_code);
			var_lenght = 1;
	}
	else
			var_value = extract_var_value(str, *i, data);
	*result = append_string(*result, var_value);
	free(var_value);
	if (var_lenght == 1)
			*i = *i + 1;
	else
			*i = *i + variable_length(str, *i);
	if (str[*i] == '=')
	{
		*result = append_string(*result, "=");
		(*i)++;
	}
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
	t_token_node	*tmp;
	char			*tmp_str;
	char			*new_str;

	tmp = data->token_list;
	while (tmp)
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
		tmp = tmp->next;
	}
	return (1);
}
