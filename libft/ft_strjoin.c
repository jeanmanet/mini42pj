/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:56:56 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/12 12:41:05 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{	
	size_t	size;
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if ((!s1 && !s2 ))
		return (NULL);
	if (!s1)
		return ft_strdup(s2);
	if (!s2)
		return ft_strdup(s1);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(*str) * (size + 1));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{	
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
