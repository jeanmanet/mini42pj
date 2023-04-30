/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 08:59:42 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/30 21:01:19 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit_error(char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
	exit (errno);
}

void	exit_cmd_strerror(char *cmd_name)
{
	global.exit_code = 127;
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, ": ", 2);
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, "\n", 1);
}

void	cmd_not_found(char *cmd_name)
{
	global.exit_code = 127;
	write(2, "command not found: ", 19);
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, "\n", 1);
}

void	print_error(char *str, int error)
{
	global.exit_code = error;
	printf("%s", str);
}
