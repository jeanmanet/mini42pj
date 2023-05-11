/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_extract_and_replace_utils.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:50:44 by ory               #+#    #+#             */
/*   Updated: 2023/05/11 16:50:17 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_value_in_assignment(char *str)
{
	char	*value;
	int		i;
	int		index;
	int		flag_plus;

	value = NULL;
	flag_plus = 0;
	i = -1;
	index = 0;
	while (str[++i])
	{
		if (str[i] == '=' || str[i] == '+')
		{
			if (str[i] == '+' && str[i + 1] == '=')
				flag_plus = 2;
			index = i + 1;
			break ;
		}
	}
	if (flag_plus)
		index++;
	while(str[index] && str[index] == ' ')
		index++;
	value = ft_substr(str, index, i - index);
	return (value);
}

char	*extract_name_in_assignment(char *str)
{
	char	*name;
	int		i;

	name = NULL;
	i = 0;
	if (!ft_ischarset(str, '='))
		return (ft_strdup(str));
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i] == '=' && str[i - 1] == '+')
				i = i - 1;
			name = ft_substr(str, 0, i);
			break ;
		}
		i++;
	}
	return (name);
}

int	variable_length(char *str, int start)
{
	int	len_var;
	int	j;

	len_var = 0;
	j = start + 1;
	while (str[j])
	{
		if (str[j] == '$' || str[j] == '=' || str[j] == ':' || str[j] == '\'' || str[j] == '/')
			break ;
		len_var++;
		j++;
	}
	return (len_var);
}

char	*append_string(char *str1, char *str2)
{
	char	*result;
	char	*tmp;

	if (str1)
	{
		tmp = ft_strdup(str1);
		free(str1);
	}
	else
		tmp = ft_strdup("");
	result = ft_strjoin(tmp, str2);
	free(tmp);
	return (result);
}
