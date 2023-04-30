/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:00:26 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/30 20:29:05 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_redirect_input(t_com *command)
{
	int	fd;

	fd = 0;
	if (command->cmd_input_mode == CMD_HERE_DOC)
	{
		command->infile = ft_strdup(".here_doc.tmp");
	}
	fd = open(command->infile, O_RDONLY, 0644);
	if (fd == -1)
	{
		global.exit_code = 1;
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		write(2, command->infile, ft_strlen(command->infile));
		write(2, "\n", 1);
		return (-1);
	}
	else
		dup2(fd, 0);
	close(fd);
	return (0);
}

int	ft_redirect_output(t_com *command)
{
	int	fd;

	if (command->cmd_output_mode == CMD_APPEND)
		fd = open(command->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(command->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		global.exit_code = 1;
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		write(2, command->outfile, ft_strlen(command->outfile));
		write(2, "\n", 1);
		return (-1);
	}
	else
		dup2(fd, 1);
	close(fd);
	return (0);
}

int	ft_redirect_io(t_com *command)
{
	int	returnval;

	returnval = 0;
	if (command->cmd_input_mode != CMD_STDIN)
		returnval = -ft_redirect_input(command);
	if (command->cmd_output_mode != CMD_STDOUT)
		returnval = -ft_redirect_output(command);
	return (returnval);
}