/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:14:35 by hdescamp          #+#    #+#             */
/*   Updated: 2025/02/13 09:21:40 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

//includes

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include "./libft/ft_printf.h"
# include "./libft/get_next_line.h"

//Function

void	exit_handler(int n_exit);
int		open_file(char *file, int in_or_out);
void	ft_free_tab(char **tab);
char	*get_path(char *cmd, char **env);

//struct

typedef struct s_vars
{
	int		i;
	int		fd_in;
	int		fd_out;
	int		status;
	int		j;
	int		p_fd[2];
	pid_t	pid;
}		t_pipe_data;

#endif
