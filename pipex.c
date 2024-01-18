/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momari <momari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:25:51 by momari            #+#    #+#             */
/*   Updated: 2024/01/15 21:15:02 by momari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_command(char *av, char **env)
{
	char	**cmds;
	char	*path;

	cmds = ft_split(av, ' ');
	if (ft_strchr(av, '/') != NULL)
	{
		if (execve(cmds[0], cmds, env) == -1)
			ft_handle_error(-1, "Command not found");
	}
	else
	{
		path = get_path(cmds[0], env);
		if (!path)
			ft_handle_error(-1, "Command not found");
		if (execve(path, cmds, env) == -1)
		{
			free(cmds);
			free(path);
			ft_handle_error(-1, "Execve failed");
		}
		free(path);
	}
	ft_free(cmds);
}

static void	first_command(char **av, char **env, int *fd_stdin)
{
	int	fd1;
	int	pid1;
	int	fd[2];

	ft_handle_error(pipe(fd), "Pipe creation failed");
	fd1 = open(av[1], O_RDONLY);
	ft_handle_error(fd1, "Open file failed");
	pid1 = fork();
	ft_handle_error(pid1, "Fork failed");
	if (pid1 == 0)
	{
		ft_handle_error(close(fd[0]), "Close failed");
		ft_handle_error(dup2(fd1, 0), "Dup2 failed");
		ft_handle_error(dup2(fd[1], 1), "Dup2 failed");
		ft_close2file(fd1, fd[1]);
		exec_command(av[2], env);
	}
	else
	{
		ft_handle_error(close(fd[1]), "Close failed");
		*fd_stdin = dup(fd[0]);
		ft_handle_error(*fd_stdin, "Dup failed");
		ft_close2file(fd1, fd[0]);
	}
}

static void	last_command(char **av, char **env, int fd)
{
	int	pid1;
	int	fd1;

	fd1 = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_handle_error(fd1, "Open file failed");
	pid1 = fork();
	if (pid1 == 0)
	{
		ft_handle_error(dup2(fd, 0), "Dup2 failed");
		ft_handle_error(dup2(fd1, 1), "Dup2 failed");
		ft_close2file(fd1, fd);
		exec_command(av[3], env);
	}
	else
		ft_close2file(fd1, fd);
}

void	ft_handle_error(int n, char *str)
{
	if (n == -1)
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
	else if (n == -2)
	{
		ft_putstr_fd(str, 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **env)
{
	int	fd;

	if (ac == 5)
	{
		first_command(av, env, &fd);
		last_command(av, env, fd);
		while (wait(NULL) != -1)
			;
	}
	else
		ft_handle_error(-2, "Argument number incorrect");
	return (EXIT_SUCCESS);
}
