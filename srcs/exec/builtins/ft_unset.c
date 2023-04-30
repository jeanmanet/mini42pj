/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:20:27 by ory               #+#    #+#             */
/*   Updated: 2023/04/30 20:24:46 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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