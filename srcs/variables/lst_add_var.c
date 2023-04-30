/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:44:07 by ory               #+#    #+#             */
/*   Updated: 2023/04/30 20:44:25 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    lst_add_var(t_data *data, char *name, char *value, int flag)
{
	t_lst_var       *new_var;
        char            *old_value;
        char            *new_value;

        if (flag == 2)
        {
                old_value = replace_var(name, data);
                new_value = ft_strjoin(old_value, value);
                free(old_value);
        }
        else
                new_value = ft_strdup(value);
        if (flag == 2)
                flag = 0;
        new_var = ft_var_lstnew(name, new_value, flag);
        ft_var_lstadd_back(&data->var_list, new_var);
        free(new_value);
}

t_lst_var       *ft_var_lstnew(char *name, char *value, int flag_env)
{
        t_lst_var       *new_element;

        new_element = malloc(sizeof(*new_element));
	if (!new_element)
		return (NULL);
        new_element->name = ft_strdup(name);
        new_element->value = ft_strdup(value);
        new_element->flag_var_for_env = flag_env;
        new_element->previous = NULL;
        new_element->next = NULL;
        return(new_element);
}

void	ft_var_lstadd_back(t_lst_var **lst, t_lst_var *new)
{
	t_lst_var	*tmp;

        tmp = *lst;
        while(tmp)
        {
                if (ft_strcmp(tmp->name, new->name) == 0)
                        delete_var_lst(lst, tmp);
                tmp = tmp->next;
        }
	if (*lst)
	{
		tmp = ft_var_lstlast(*lst);
		tmp->next = new;
                new->previous = tmp;
	}
	else
		(*lst) = new;
}

t_lst_var	*ft_var_lstlast(t_lst_var *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}