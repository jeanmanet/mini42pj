/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:00:26 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/14 23:40:47 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	make_here_doc(t_com *command)
{
	char	*line;
	char	*temp;

	line = NULL;
	temp = NULL;
	global.fd_here_doc = open(".here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (global.fd_here_doc == -1)
	{
		printf("Error, cannot create here_doc.tmp \n");
		return (-1);
	}
	while (1)
	{
		signal(SIGINT, ft_signal_handler_here_doc);
		signal(SIGQUIT, ft_signal_handler_here_doc);
		temp = readline("here_doc > ");
		if (!temp)
			break ;
		line = ft_strjoin(temp, "\n");
		free(temp);
		if (ft_strlen(line) == ft_strlen(command->here_doc_limiter) + 1)
			if (ft_strncmp(line, command->here_doc_limiter,
					ft_strlen(line) - 1) == 0)
				break ;
		ft_putstr_fd(line, global.fd_here_doc);
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	unlink(".here_doc.tmp");
	if (global.fd_here_doc)
		close(global.fd_here_doc);
	return (global.fd_here_doc);
}

int	ft_redirect_input(t_com *command)
{
	int	fd;

	fd = 0;
	if (command->cmd_input_mode == CMD_HERE_DOC)
	{
		command->here_doc_limiter = command->infile;
		command->infile = ft_strdup(".here_doc.tmp");
		fd = make_here_doc(command);
	}
	fd = open(command->infile, O_RDONLY, 0644);
	if (fd == -1)
	{
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
