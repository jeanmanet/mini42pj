/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_extract_and_replace.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:39:42 by ory               #+#    #+#             */
/*   Updated: 2023/04/28 12:44:53 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_value_in_assignment(char *str)
{
	char *value;
	int i;
	int index;
	int	flag_plus;
	
	value = NULL;
	flag_plus = 0;
	i = -1;
	index = 0;
	while(str[++i])
	{
	    if (str[i] == '=' || str[i] == '+')
	    {
		if (str[i] == '+' && str[i + 1] == '=')
			flag_plus = 2;
	        index = i + 1;
	        break;
	    }
	}
	if (flag_plus)
		index++;
	value = ft_substr(str, index, i - index);
	return (value);
}

char	*extract_name_in_assignment(char *str)
{
	char *name;
	int i;
	
	name = NULL;
	i = 0;
	if (!ft_ischarset(str, '='))
		return (ft_strdup(str));
	while(str[i])
	{
	    if (str[i] == '=')
	    {
		if (str[i] == '=' && str[i - 1] == '+')
			i = i - 1;
	        name = ft_substr(str, 0, i);
	        break;
	    }
	    i++;
	}
	return (name);
}

// char* extract_vars(char* str, t_data *data) 
// {
//     int i = 0;
//     int len_var = 0;
//     char* result = NULL;
//     char* tmp;
//     int j = 0;
//     int flag = 0;

//     char* tmp2;

//     while (str[i]) 
//     {
//         if (str[i] == '$') 
//         {
//             j = i + 1;
//             while(str[j])
//             {
//                 if (str[j] == '$' || str[j] == '=')
//                 {
//                         if (str[j] == '=')
//                                 flag = 1;
//                         break;
//                 }
//                 len_var++;
//                 j++;
//             }
//             char* var = ft_substr(str, i + 1, len_var);
//             char* value = replace_var(var, data);
// 	    if (result)
// 	    {
// 		tmp = ft_strdup(result);
// 		free(result);
// 	    }
// 	    else
// 		tmp = ft_strdup("");
// 	    if (value == NULL)
// 	    	value = ft_strdup("");
//             result = ft_strjoin(tmp, value);
//             free(tmp);
//             free(var);
//             free(value);
//             i = i + len_var;
//             len_var = 0;
//             if (flag == 1)
//             {
//                 tmp = ft_strdup(result);
//                 free(result);
//                 result = ft_strjoin(tmp, "=");
// 		free(tmp);
//                 i++;
//                 flag = 0;
//             }
//         }
//         else 
//         {
//             char* tmp = ft_substr(str, i, 1);
//             if (result)
//             {
//                 tmp2 = ft_strdup(result);
//                 free(result);
//             }
//             else
//                 tmp2 = ft_strdup("");
//             result = ft_strjoin(tmp2, tmp);
//             free(tmp);
//             free(tmp2);
//         }
//         i++;
//     }
//     return result;
// }

int variable_length(char* str, int start) 
{
    int len_var = 0;
    int j = start + 1;
    while(str[j])
    {
        if (str[j] == '$' || str[j] == '=' || str[j] == ':')
            break;
        len_var++;
        j++;
    }
    printf("len var = %d\n", len_var);
    return len_var;
}

char* append_string(char* str1, char* str2) 
{
    char        *result;
    char        *tmp;
    if (str1)
    {
        tmp = ft_strdup(str1);
        free(str1);
    }
    else
        tmp = ft_strdup("");
    result = ft_strjoin(tmp, str2);
    free(tmp);
    return result;
}

char* extract_var_value(char* str, int i, t_data* data) 
{
    int len_var = variable_length(str, i);
    char* var = ft_substr(str, i + 1, len_var);
    printf("var = %s\n", var);
    char* value = replace_var(var, data);
    printf("var value2 = %s\n", value);
    if (value == NULL) 
    {
        value = ft_strdup("");
    }
    char* result = append_string(NULL, value);
    free(var);
    free(value);
    return result;
}

char* extract_vars(char* str, t_data* data) 
{
    int i = 0;
    char* result = NULL;
    char* var_value = NULL;
    int         var_lenght;

    while (str[i]) 
    {
        var_lenght = 0;
        if (str[i] == '$' && str[i + 1] && str[i + 1] != '$') 
        {
                if (str[i + 1] && str[i + 1] == '?')//(str[i + 1] == '?' && str[i + 2] == '$') || ft_strcmp(str, "$?") == 0)
                {
                        printf("i1 = %d\n", i);
                        printf("str = %s\n", str);
                        var_value = ft_itoa(global.exit_code);
                        var_lenght = 1;
                }
                else
                        var_value = extract_var_value(str, i, data);
                printf("var value = %s\n", var_value);
                result = append_string(result, var_value);
                free(var_value);
                if (var_lenght == 1)
                        i = i + 1;
                else
                        i = i + variable_length(str, i);
                if (str[i] == '=') 
                {
                    result = append_string(result, "=");
                    i++;
                }
        } 
        else 
        {
            char *tmp = ft_substr(str, i, 1);
            result = append_string(result, tmp);
            free(tmp);
        }
        i++;
        printf("i = %d\n", i);
    }
    return result;
}



char	*replace_var(char *var, t_data *data)
{
	char	*value;

	value = get_env_variable_value(var, data);
	if (value == NULL)
        	value = var_exist_outside_env(data, var);
	return (value);
}

int	replace_var_by_value(t_data *data)
{
	t_token_node 	*tmp;
	char		*tmp_str;
	char		*new_str;
	//int		flag;
	//flag = 0;
	tmp = data->token_list;
	while(tmp)
	{
		// if (ft_strcmp(tmp->token, "$?") == 0)
		// {
		// 	free(tmp->token);
		// 	tmp->token = ft_itoa(global.exit_code);
		// 	//tmp = tmp->next;
		// }
		if (tmp->q_state > 0 && ft_ischarset(tmp->token, '$'))
		{
			// if (ft_ischarset(tmp->token, '=') && tmp->token[0] != '$' && (!tmp->prev || tmp->prev->type == 4))
			// 	return (0);
                        printf("aaaaaaaaaaaaaa\n");
			tmp_str = ft_strdup(tmp->token);
			new_str = extract_vars(tmp_str, data);
			free(tmp->token);
			tmp->token = ft_strdup(new_str);
			free(new_str);
			free(tmp_str);
			// if (flag == 1)
			// 	return (0);
		}
                 printf("token = %s type = %d  quote = %d  flag = %d\n", tmp->token, tmp->type, tmp->q_state, tmp->flag_for_join_with_prev_token);
		tmp = tmp->next;
	}
	return (1);
}