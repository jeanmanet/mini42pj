/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:09:54 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/08 10:49:00 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	size;

	if (start >= ft_strlen(s))
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
	ft_strlcpy(str, s + start, size + 1);
	return (str);
}
