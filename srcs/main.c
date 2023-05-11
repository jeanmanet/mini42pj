/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:03:37 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/11 18:14:49 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global	g_global;

void	prompt(t_data *data)
{
	ft_signal_handler();
	g_global.in_prompt = 1;
	data->command_line = readline("minishell > ");
	g_global.in_prompt = 0;
	add_history(data->command_line);
	if (data->command_line)
	{
		g_global.code_error = 0;
		ft_command_line(data);
		if (g_global.pid != 0)
		{
			kill(g_global.pid, SIGINT);
			g_global.pid = 0;
		}
	}
	else
		ft_exit_no_readline();
}

void	ft_command_line(t_data *data)
{
	if (!check_cmdline(data->command_line))
	{
		data->token_list = tokenizer(data->command_line);
		if (!unexpected_token_2(data))
		{
			replace_var_by_value(data);
			ft_add_var(data);
			parse_token_list(data);
			execute_ast(data);
		}
		free_mem(data);
	}
	else
		free(data->command_line);
}

t_data	*data_init(char **envp)
{
	t_data	*data;

	g_global.pid = 0;
	g_global.code_error = 0;
	data = malloc(sizeof(*data));
	if (!data)
		ft_exit_error("Memory allocation error \n");
	data->commands_tree = malloc(sizeof(t_ast));
	if (!data->commands_tree)
		ft_exit_error("Memory allocation error \n");
	data->commands_tree->root = NULL;
	data->envp = ft_import_envp(envp);
	data->pid = 0;
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	data = data_init(envp);
	if (argc > 1)
	{
		printf("Invalid argument(s), ");
		printf("this minishell doesn't execute scriptfiles !\n");
	}
	else
		while (1)
			prompt(data);
	return (0);
}
