/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trubat-d <trubat-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:12:56 by lord              #+#    #+#             */
/*   Updated: 2022/10/31 21:52:12 by trubat-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_count(const char *str, char c)
{
	int	i;
	int	count;
	int	mode;

	mode = !(str[0] == c || str[0] == '\0');
	count = 0;
	if (mode == 1)
		count++;
	i = 0;
	while (str[i])
	{
		if (mode == 1 && (str[i] == c || str[i] == '\0'))
			mode = 0;
		else if (mode == 0 && str[i] != c && str[i])
		{
			mode = 1;
			count++;
		}
		i++;
	}
	return (count);
}

char	*ft_string(const char *str, char c)
{
	int		i;
	char	*result;
	int		size;

	size = 0;
	while (str[size] != c && str[size])
	{
		size++;
	}
	result = (char *)malloc(size * sizeof(char) + 1);
	i = 0;
	while (str[i] != c && str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[size] = 0;
	return (result);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	char	*string;
	int		cnt;
	int		i;

	string = (char *)s;
	cnt = 0;
	i = 0;
	result = (char **) malloc(sizeof(char *) * (ft_count(string, c) + 1));
	if (!result)
		return (0);
	if (string[0] != c && string[0])
		result[i++] = ft_string(string, c);
	if (ft_count(string, c) > 0)
	{
		while (string[cnt + 1])
		{
			if (string[cnt] == c && string[cnt + 1] != c)
				result[i++] = ft_string(string + cnt + 1, c);
			cnt++;
		}
	}
	result[ft_count(string, c)] = 0;
	return (result);
}
