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

char	*ft_strrchr(const char *s, int c)
{
	const char	*cc;

	cc = 0;
	if (c == '\0')
		return ((char *)(&s[ft_strlen(s)]));
	c = c % 128;
	while (*s)
	{
		if (*s == c)
			cc = s;
		s++;
	}
	if (cc)
		return ((char *)cc);
	else
		return (0);
}
