/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_delete_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:42:27 by ory               #+#    #+#             */
/*   Updated: 2023/05/07 13:52:29 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_var_lst(t_lst_var **head, t_lst_var *to_delete)
{
	if (*head == NULL)
		return ;
	else if (*head == to_delete)
	{
		if ((*head)->next == NULL && (*head)->previous == NULL)
				*head = NULL;
		else
				*head = to_delete->next;
	}
	else if (to_delete->previous != NULL)
			to_delete->previous->next = to_delete->next;
	else if (to_delete->next != NULL)
			to_delete->next->previous = to_delete->previous;
	free(to_delete->name);
	free(to_delete->value);
	free(to_delete);
}

void	delete_var_in_lst(t_lst_var **head, char *name)
{
	t_lst_var	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			delete_var_lst(&(*head), tmp);
			return ;
		}
		tmp = tmp->next;
	}
	*head = NULL;
}
