/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:51:41 by jmanet            #+#    #+#             */
/*   Updated: 2022/03/27 11:09:06 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbcount(int n)
{
	size_t	i;

	i = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i += 1;
		n = -n;
	}
	while (n / 10 >= 1)
	{
		i += 1;
		n = n / 10;
	}
	return (i);
}

int	ft_nextnb(int	*n)
{
	int	res;

	res = 0;
	if (*n > 9)
	{
		res = *n % 10;
		*n = *n / 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		*ptrn;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_nbcount(n);
	ptrn = &n;
	str = malloc(sizeof(*str) * size + 1);
	if (n == -2147483648)
	{
		str[i++] = '-';
		str[i++] = '2';
		n = 147483648;
	}
	if (n < 0)
	{
		str[i++] = '-';
		n = -n;
	}
	str[size] = '\0';
	while (n > 9)
		str[(size--) - 1] = (ft_nextnb(ptrn) + '0');
	str[i++] = n + '0';
	return (str);
}
