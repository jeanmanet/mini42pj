/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 09:17:31 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/09 19:15:14 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_import_envp(char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		ft_exit_error("Memory allocation error");
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

char	*ft_getenv(char *name, t_data *data)
{
	int		i;
	char	*ret;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], name, ft_strlen(name)))
		{
			ret = ft_strdup(&data->envp[i][ft_strlen(name)]);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

int	ft_addtoenv(char *value, t_data *data)
{
	char	**newenv;
	int		i;

	i = 0;
	while (data->envp[i])
		i++;
	newenv = malloc(sizeof(char *) * (i + 2));
	if (!newenv)
		return (0);
	i = 0;
	while (data->envp[i])
	{
		newenv[i] = ft_strdup(data->envp[i]);
		i++;
	}
	newenv[i] = ft_strdup(value);
	i++;
	newenv[i] = NULL;
	i = -1;
	while (data->envp[++i])
		free(data->envp[i]);
	free(data->envp);
	data->envp = newenv;
	return (1);
}

int	ft_setenv_add(int i, char *name, char *value, t_data *data)
{
	char	*new_value;
	char	*old_value;
	char	*value_if_flag;

	new_value = ft_substr(value, ft_strlen(name) + 1,
			ft_strlen(value) - ft_strlen(name) - 1);
	old_value = ft_strdup(data->envp[i]);
	value_if_flag = ft_strjoin(old_value, new_value);
	free(data->envp[i]);
	data->envp[i] = ft_strdup(value_if_flag);
	free(value_if_flag);
	free(old_value);
	free(new_value);
	return (0);
}

int	ft_setenv(char *name, char *value, t_flag *setenv_flag, t_data *data)
{
	int	i;

	i = 0;
	if (ft_ischarset(name, '='))
		return (EINVAL);
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], name, ft_strlen(name)))
		{
			if (setenv_flag->overwrite == 1)
			{
				if (setenv_flag->flag_plus)
					return (ft_setenv_add(i, name, value, data));
				free(data->envp[i]);
				data->envp[i] = ft_strdup(value);
				return (0);
			}
			return (0);
		}
		i++;
	}
	if (ft_addtoenv(value, data))
		return (0);
	return (-1);
}
