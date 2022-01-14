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

char	*ft_strjoin(char const *s1, char const	*s2)
{
	char	*joined;
	int		i;

	i = -1;
	joined = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
		return (0);
	while (*s1)
		joined[++i] = *s1++;
	while (*s2)
		joined[++i] = *s2++;
	joined[++i] = '\0';
	return (joined);
}
