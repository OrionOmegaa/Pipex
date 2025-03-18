/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:26:09 by hdescamp          #+#    #+#             */
/*   Updated: 2025/02/24 10:26:11 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	if (cmd[0] == '\0')
		exit_handler(1);
	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
}

void	here_doc_put_in(char **argv, int *p_fd)
{
	char	*ret;

	close(p_fd[0]);
	while (1)
	{
		ret = get_next_line(0);
		if (ft_strncmp(ret, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(ret);
			exit(0);
		}
		ft_putstr_fd(ret, p_fd[1]);
		free(ret);
	}
}

void	here_doc(char **argv)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		here_doc_put_in(argv, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		wait(NULL);
	}
}

int	do_pipe(char *cmd, char **env)
{
	t_pipe_data	data;

	if (pipe(data.p_fd) == -1)
		exit(1);
	data.pid = fork();
	if (data.pid == -1)
		exit(-1);
	if (data.pid == 0)
	{
		dup2(data.p_fd[1], 1);
		close(data.p_fd[0]);
		exec(cmd, env);
	}
	else
	{
		close(data.p_fd[1]);
		dup2(data.p_fd[0], 0);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipe_data	data;

	if (argc < 5)
		exit_handler(1);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (argc < 6)
			exit_handler(1);
		data.i = 3;
		data.fd_out = open_file(argv[argc - 1], 2);
		here_doc(argv);
	}
	else
	{
		data.i = 2;
		data.fd_in = open_file(argv[1], 0);
		data.fd_out = open_file(argv[argc - 1], 1);
		dup2(data.fd_in, 0);
	}
	while (data.i < argc - 1)
		data.j = do_pipe(argv[data.i++], env);
	dup2(data.fd_out, 1);
	while (data.j++ < data.i)
		wait(&data.status);
}
