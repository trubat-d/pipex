/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trubat-d <trubat-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 20:36:59 by trubat-d          #+#    #+#             */
/*   Updated: 2022/11/02 22:57:10 by trubat-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*search_access(char **res, char **cmd_name, char **path, char *tmp)
{
	int	i;

	i = 0;
	while (path[i])
	{
		*res = ft_strjoin(path[i], "/");
		tmp = *res;
		*res = ft_strjoin(*res, cmd_name[0]);
		free(tmp);
		tmp = *res;
		if (access(*res, X_OK) == 0)
			return (*res);
		free(tmp);
		i++;
	}
	return (NULL);
}

void	get_access(char **tab, char *cmd, char **env, int j)
{
	char	**path;
	char	*res;
	char	**cmd_name;
	char	*tmp;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	path = ft_split(&(env[i][5]), ':');
	cmd_name = ft_split(cmd, ' ');
	tmp = NULL;
	res = search_access(&res, cmd_name, path, tmp);
	if (res == NULL)
		tab[j] = NULL;
	else
		tab[j] = res;
	free_tab((void **)path);
	free_tab((void **)cmd_name);
}

void	call_fork(t_data *data, int i, char **env)
{
	data->forks[i] = fork();
	if (!data->forks[i])
	{
		process_forks(data, i);
		execve(data->access[i - data->is_heredoc], \
					ft_split(data->cmd_tab[i - data->is_heredoc], ' '), env);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		i;

	if (ac <= 3)
		exit(0 * (int)write(1, "Wrong number of Arguments\n", 26));
	init_data(&data, ac, av, env);
	if ((data.i_o)[0] < 0 && data.is_heredoc == 0)
		return (0 * (int)write(1, \
		"Input file error: your input file cannot be accessed! \n", 55));
	i = 0;
	while (i < data.cmds + data.is_heredoc)
	{
		if (i == 0 && data.is_heredoc)
			process_heredoc(&data, av, ac);
		else
			call_fork(&data, i, env);
		i++;
	}
	let_open_close(data.pipes, data.i_o, (int [5]) \
	{-1, -1, -1, -1, -1}, (int [2]){0, 0});
	close_wait(&data);
	exit(0);
}
