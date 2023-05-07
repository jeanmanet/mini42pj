/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:09:54 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/07 14:02:27 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	size;

	i = 0;
	if	(start >= ft_strlen(s))
		return (NULL);
	size = ft_strlen(s) - start;
	if (len <= size)
		size = len;
	if (start <= ft_strlen(s))
		str = malloc(sizeof(*s) * (size + 1));
	else
	{
		str = malloc(sizeof(*s) * 1);
		ft_memset(str, 0, 1);
		return (str);
	}
	if (!str)
		return (NULL);
	while (i < len && s[i + start] != '\0')
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
