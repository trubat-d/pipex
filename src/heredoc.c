/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trubat-d <trubat-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:23:54 by trubat-d          #+#    #+#             */
/*   Updated: 2022/11/02 23:00:38 by trubat-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_heredoc(int fd[2], char *limiter, const int lim_size)
{
	char	*buffer;
	char	*tmp;
	int		read_b;

	buffer = ft_calloc(sizeof(char), 1);
	tmp = malloc((lim_size + 2) * sizeof(char));
	tmp[0] = 0;
	while (!ft_strcmp(tmp, limiter, lim_size))
	{
		tmp[0] = 0;
		write(1, "HereDoc>", 9);
		while (ft_strchr(tmp, '\n') == 0)
		{
			read_b = (int)read(0, tmp, lim_size + 1);
			tmp[read_b] = 0;
			if (read_b < 0)
				return ;
			buffer = ft_strjoin(buffer, tmp);
		}
	}
	free(tmp);
	ft_putstr_fd(ft_substr(buffer, 0, \
	ft_strlen(buffer) - (lim_size + 1)), fd[1]);
	free(buffer);
}

void	process_heredoc(t_data *data, char **av, int ac)
{
	data->forks[0] = fork();
	if (!data->forks[0])
	{
		if (ac == 4)
		{
			let_open_close(data->pipes, data->i_o, \
			(int [5]){-1, -1, -1, -1, -1}, (int [2]){0, 1});
			write_heredoc(data->i_o, av[2], (const int)ft_strlen(av[2]));
		}
		else if (ac > 4)
		{
			let_open_close(data->pipes, data->i_o, \
			(int [5]){0, 1, -1, -1, -1}, (int [2]){0, 0});
			write_heredoc(data->pipes[0], av[2], (const int)ft_strlen(av[2]));
		}
		exit(0);
	}
	if (data->wait_heredoc)
		wait(&(data->forks[0]));
}

int	is_heredoc(int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (i != 1 && !ft_strncmp(av[i], "here_doc", 8))
		{
			exit(0 * (int)write(2, \
			"HereDocError: here_doc must be second argument\n", 47));
		}
		i++;
	}
	if (!ft_strncmp(av[1], "here_doc", 8) && ac >= 4)
		return (1);
	else if (!ft_strncmp(av[1], "here_doc", 8) && ac < 4)
		return (0 * (int)write(1, "HereDocError: no out or no limiter\n", 38));
	return (0);
}
