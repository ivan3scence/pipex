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

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	j = (unsigned int)len;
	i = -1;
	if (!*needle)
		return ((char *) haystack);
	while (len-- && haystack[++i])
	{
		if (haystack[i] == needle[0])
		{
			if (!ft_strncmp(&haystack[i], needle, ft_strlen(needle))
				&& i + (unsigned int)ft_strlen(needle) <= j)
				return ((char *)&haystack[i]);
		}
	}
	return (0);
}
