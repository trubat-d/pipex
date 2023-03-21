/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trubat-d <trubat-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:51:43 by lord              #+#    #+#             */
/*   Updated: 2022/11/04 16:19:51 by trubat-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_substr(const char *s, unsigned int st, size_t len)
{
	char	*res;
	size_t	i;
	size_t	size;

	size = (size_t)ft_strlen((char *)s);
	if (st >= (size))
	{
		res = malloc(1 * sizeof(char));
		if (!res)
			return (0);
		res[0] = '\0';
		return (res);
	}
	len = (size - st) * (len > (size - st)) + (len <= (size - st)) * len;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return ((void *)0);
	i = 0;
	while (i < len && s[i])
	{
		res[i] = s[st + i];
		i++;
	}
	res[len] = '\0';
	return (res);
}
