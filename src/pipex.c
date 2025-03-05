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
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
}

int	do_pipe(char **env, char **argv)
{
	t_pipe_data	data;

	if (pipe(data.p_fd) == -1)
		exit(1);
	data.pid = fork();
	if (data.pid == -1)
		exit(-1);
	if (!data.pid)
	{
		data.fd_in = open_file(argv[1], 0);
		dup2(data.fd_in, 0);
		dup2(data.p_fd[1], 1);
		close(data.p_fd[0]);
		exec(argv[2], env);
	}
	else
	{
		data.fd_out = open_file(argv[4], 1);
		dup2(data.fd_out, 1);
		dup2(data.p_fd[0], 0);
		close(data.p_fd[1]);
		exec(argv[3], env);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipe_data	data;

	if (argc != 5)
		exit_handler(1);
	else
		data.i = 2;
	while (data.i++ < 4)
		data.j = do_pipe(env, argv);
	while (data.j++ < data.i)
		wait(&data.status);
	/*while(waitpid(-1, &data.status, WUNTRACED) != -1)
		continue;*/
}
