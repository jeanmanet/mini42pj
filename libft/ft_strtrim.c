/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:27:36 by jmanet            #+#    #+#             */
/*   Updated: 2022/04/19 12:00:25 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ischarset(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_startpoint(char const *s1, char const *set)
{	
	size_t	i;

	i = 0;
	while (s1[i])
	{
		while (ft_ischarset(set, s1[i]))
			i++;
		break ;
	}
	return (i);
}

size_t	ft_endpoint(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (!ft_ischarset(set, s1[len - i - 1]))
			break ;
		i++;
	}
	return (len - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	size;

	start = ft_startpoint(s1, set);
	end = ft_endpoint(s1, set);
	size = 0;
	if (!set)
		return (ft_strdup(s1));
	if (start < end)
		size = end - start + 1;
	str = malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	if (start >= end)
		str[0] = '\0';
	if (size > 1)
		ft_strlcpy(str, s1 + start, size);
	return (str);
}
