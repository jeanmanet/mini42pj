/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:09:15 by jmanet            #+#    #+#             */
/*   Updated: 2022/04/01 09:45:31 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_freemem(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static size_t	ft_strcount(char const *s, char c)
{
	size_t	i;
	size_t	strs;

	i = 0;
	strs = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			strs++;
			while (s[i] != c && s[i])
			{
				i++;
			}
		}
	}
	return (strs);
}

static void	ft_writecurrentstr(char *dest, const char *src, char c)
{
	int	i;

	i = 0;
	while (src[i] != c && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static char	**ft_writestrs(char **strs, size_t nbstr, const char *s, char c)
{
	size_t	idx;
	int		i;
	int		j;

	idx = 0;
	i = 0;
	while (idx < nbstr)
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (s[i + j] != c && s[i + j])
				j++;
			strs[idx] = malloc(sizeof(char) * (j + 1));
			if (!strs[idx])
				return (ft_freemem(strs));
			ft_writecurrentstr(strs[idx], s + i, c);
			idx++;
			i = i + j;
		}
	}
	strs[idx] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	size_t	nbstr;	
	char	**strs;

	if (!s)
		return (NULL);
	nbstr = ft_strcount(s, c);
	strs = malloc(sizeof(char *) * (nbstr + 1));
	if (!strs)
		return (NULL);
	strs = ft_writestrs(strs, nbstr, s, c);
	return (strs);
}
