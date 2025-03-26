/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:26:01 by hdescamp          #+#    #+#             */
/*   Updated: 2025/02/24 10:26:03 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		ft_putstr_fd("pipex : command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
}

pid_t	do_pipe2(char **env, char **argv, int *p_fd)
{
	t_pipe_data	data;

	data.pid2 = fork();
	if (data.pid2 == -1)
		exit(-1);
	if (data.pid2 == 0)
	{
		data.fd_out = open_file(argv[4], 1);
		dup2(data.fd_out, 1);
		dup2(p_fd[0], 0);
		close(p_fd[1]);
		exec(argv[3], env);
	}
	return (data.pid2);
}

void	do_pipe(char **env, char **argv)
{
	t_pipe_data	data;

	if (pipe(data.p_fd) == -1)
		exit(1);
	data.pid1 = fork();
	if (data.pid1 == -1)
		exit(-1);
	if (data.pid1 == 0)
	{
		data.fd_in = open_file(argv[1], 0);
		dup2(data.fd_in, 0);
		dup2(data.p_fd[1], 1);
		close(data.p_fd[0]);
		exec(argv[2], env);
	}
	data.pid2 = do_pipe2(env, argv, data.p_fd);
	close(data.p_fd[0]);
	close(data.p_fd[1]);
	waitpid(data.pid1, &data.status, 0);
	if (WIFEXITED(data.status))
		data.exit_status = WEXITSTATUS(data.status);
	waitpid(data.pid2, &data.status, 0);
	if (WIFEXITED(data.status))
		data.exit_status = WEXITSTATUS(data.status);
	exit(data.exit_status);
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
		exit_handler(1);
	do_pipe(env, argv);
}
