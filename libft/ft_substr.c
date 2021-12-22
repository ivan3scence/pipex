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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	int		i;

	if (!s)
		return (0);
	i = -1;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	subs = (char *) malloc((len + 1) * sizeof(char));
	if (!subs)
		return (0);
	while (len-- && start < (unsigned int) ft_strlen(s))
		subs[++i] = s[start++];
	subs[++i] = '\0';
	return (subs);
}
