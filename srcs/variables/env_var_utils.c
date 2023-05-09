/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:19:41 by ory               #+#    #+#             */
/*   Updated: 2023/05/09 15:20:11 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_var_is_for_env(char *name, char *value, 
	t_data *data, int flag_plus)
{
	t_flag		setenv_flag;

	setenv_flag.overwrite = 1;
	setenv_flag.flag_plus = flag_plus;

	if (update_var_for_env(name, value, data, &setenv_flag))
		return (1);
	return (0);
}