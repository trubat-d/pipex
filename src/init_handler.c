/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trubat-d <trubat-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:20:00 by trubat-d          #+#    #+#             */
/*   Updated: 2022/11/04 16:20:01 by trubat-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_no_heredoc(t_data *data, int i, int ac, char **av)
{
	data->cmds = ac - 3;
	data->pipes = ft_calloc(sizeof(int *), (data->cmds + 1));
	while (i < data->cmds)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		pipe(data->pipes[i]);
		i++;
	}
	data->forks = malloc(sizeof(pid_t) * (data->cmds));
	data->cmd_tab = ft_calloc(sizeof(char *), (data->cmds + 1));
	i = 0;
	while (i < data->cmds)
	{
		data->cmd_tab[i] = ft_strdup(av[2 + i]);
		i++;
	}
}

void	check_access(t_data *data, int ac, char **av, char **env)
{
	int	i;

	i = 0;
	data->access = ft_calloc((data->cmds + 1), sizeof(char *));
	while (i < ac - 3 - data->is_heredoc)
	{
		get_access(data->access, av[i + 2 + data->is_heredoc], env, i);
		if (!data->access[i])
			exit(0 * (int)write(2, \
			"AccessError: command sent cannot be applied\n", 44));
		i++;
	}
}

void	init_data(t_data *data, int ac, char **av, char **env)
{
	int	i;

	i = 0;
	data->i_o = malloc(sizeof(int) * 2);
	if (!data->is_heredoc)
		data->i_o[0] = open(av[1], O_RDONLY);
	data->is_heredoc = is_heredoc(ac, av);
	data->i_o[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, \
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if ((data->i_o[0] < 0 && !data->is_heredoc) || data->i_o[1] < 0)
		exit(0 * write(2, "OpenFileError: couldn't open files correctly\n", 46));
	if (!data->is_heredoc)
		init_no_heredoc(data, i, ac, av);
	else
		init_heredoc(data, i, ac, av);
	check_access(data, ac, av, env);
}

void	init_heredoc(t_data *data, int i, int ac, char **av)
{
	data->cmds = ac - 4;
	data->pipes = ft_calloc(sizeof(int *), (data->cmds + 2));
	while (i < data->cmds + 1)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		pipe(data->pipes[i++]);
	}
	data->forks = malloc(sizeof(pid_t) * (data->cmds + 1));
	data->cmd_tab = ft_calloc(sizeof(char *), (data->cmds + 1));
	i = 0;
	while (i < data->cmds)
	{
		data->cmd_tab[i] = ft_strdup(av[3 + i]);
		i++;
	}
}
