/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trubat-d <trubat-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:55:25 by trubat-d          #+#    #+#             */
/*   Updated: 2022/11/02 22:50:08 by trubat-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	int		**pipes;
	pid_t	*forks;
	int		*i_o;
	char	**access;
	int		is_heredoc;
	int		cmds;
	char	**cmd_tab;
	int		wait_heredoc;
}			t_data;

char	**ft_split(const char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strcmp(const char *a, const char *b, int n);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(const char *s, unsigned int st, size_t len);
void	write_heredoc(int fd[2], char *limiter, const int lim_size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
void	let_open_close(int **pipes, int i_o[2], int pipe_acc[5], \
const int io_acc[2]);
void	process_forks(t_data *data, int i);
void	process_heredoc(t_data *data, char **av, int ac);
void	init_heredoc(t_data *data, int i, int ac, char **av);
int		is_heredoc(int ac, char **av);
int		close_wait(t_data *data);
void	free_tab(void **tab);
void	init_no_heredoc(t_data *data, int i, int ac, char **av);
void	init_data(t_data *data, int ac, char **av, char **env);
void	get_access(char **tab, char *cmd, char **env, int j);

#endif