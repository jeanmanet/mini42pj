/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:46:07 by ory               #+#    #+#             */
/*   Updated: 2023/05/07 13:26:57 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_env_export(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		printf("declare -x %s\n", data->envp[i]);
		i++;
	}
}
