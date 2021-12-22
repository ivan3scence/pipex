/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:37:50 by sdonny            #+#    #+#             */
/*   Updated: 2021/10/11 15:18:46 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digits(int n)
{
	int	count;

	count = 0;
	while (n)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	i;

	i = n;
	n = ft_digits(n);
	str = (char *) malloc(sizeof(char) * (n + 2));
	if (!str)
		return (0);
	if (i < 0)
	{
		str[0] = '-';
		n++;
		i = -i;
	}
	str[n] = '\0';
	if (i == 0)
		str[0] = '0';
	if (i == 0)
		str[1] = '\0';
	while (i)
	{
		str[--n] = i % 10 + '0';
		i = i / 10;
	}
	return (str);
}
