/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trubat-d <trubat-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:18:59 by trubat-d          #+#    #+#             */
/*   Updated: 2022/11/04 16:19:00 by trubat-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	middle_fork(t_data *data, int i)
{
	let_open_close(data->pipes, data->i_o, (int [5]) \
		{i - 1, 0, i, 1, -1}, (int [2]) \
		{0, 0});
	dup2(data->pipes[i -1][0], 0);
	dup2(data->pipes[i][1], 1);
}

void	start_fork(t_data *data, int i)
{
	let_open_close(data->pipes, data->i_o, (int [5]) \
		{i, 1, -1, -1, -1}, (int [2]) \
		{1, 0});
	dup2(data->i_o[0], 0);
	dup2(data->pipes[i][1], 1);
}

void	end_fork(t_data *data, int i)
{
	let_open_close(data->pipes, data->i_o, (int [5]) \
		{i -1, 0, -1, -1, -1}, (int [2]) \
		{0, 1});
	dup2(data->i_o[1], 1);
	dup2(data->pipes[i -1][0], 0);
}

void	heredoc_fork(t_data *data)
{
	let_open_close(data->pipes, data->i_o, (int [5]) \
		{-1, -1, -1, -1, -1}, (int [2]){1, 1});
	dup2(data->i_o[1], 1);
	dup2(data->i_o[0], 0);
}

void	process_forks(t_data *data, int i)
{
	if (i != 0 && i != data->cmds - 1 + data->is_heredoc)
		middle_fork(data, i);
	else if (!i && i != data->cmds - 1 + data->is_heredoc)
		start_fork(data, i);
	else if (i == data->cmds - 1 + data->is_heredoc && i)
		end_fork(data, i);
	else if (i == data->cmds - 1 + data->is_heredoc && !i)
		heredoc_fork(data);
}
