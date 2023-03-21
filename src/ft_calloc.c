/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trubat-d <trubat-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 19:45:45 by theo              #+#    #+#             */
/*   Updated: 2022/11/02 00:28:49 by trubat-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*res;

	i = 0;
	res = malloc(nmemb * size);
	if (!res)
		return (0);
	while (i < (nmemb * size))
	{
		((unsigned char *)res)[i] = 0;
		i++;
	}
	return (res);
}
