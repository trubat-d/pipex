/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trubat-d <trubat-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:18:53 by trubat-d          #+#    #+#             */
/*   Updated: 2022/11/04 16:18:54 by trubat-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(int **pipes, int pipe_acc[5])
{
	int	i;
	int	j;
	int	check;

	i = 0;
	while (pipes[i])
	{
		check = 0;
		j = 0;
		while (pipe_acc[j] != -1)
		{
			if (i == pipe_acc[j])
			{
				close(pipes[i][1 - pipe_acc[j + 1]]);
				check = 1;
				break ;
			}
			j += 2;
		}
		if (!check && !close(pipes[i][0]) && !close(pipes[i][1]))
			check = check + 0;
		i++;
	}
}

void	let_open_close(int **pipes, int i_o[2], \
int pipe_acc[5], const int io_acc[2])
{
	close_pipes(pipes, pipe_acc);
	if (!io_acc[0])
		close(i_o[0]);
	if (!io_acc[1])
		close(i_o[1]);
}

int	close_wait(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmds + data->is_heredoc)
		wait(&(data->forks[i++]));
	return (0);
}

void	free_tab(void **tab)
{
	int		i;
	char	**tabs;

	tabs = (char **)tab;
	i = 0;
	while (tabs[i])
	{
		free(tabs[i]);
		i++;
	}
	free(tabs);
}
