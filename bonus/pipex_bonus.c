/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momari <momari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 21:08:17 by momari            #+#    #+#             */
/*   Updated: 2024/01/16 09:21:47 by momari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_command(char *av, char **env)
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
			ft_handle_error(-1, "command not found");
		if (execve(path, cmds, env) == -1)
		{
			ft_free(cmds);
			free(path);
			ft_handle_error(-1, "Execve failed");
		}
		free(path);
	}
	ft_free(cmds);
}

void	first_command(char **av, char **env, int n, int *fd_stdin)
{
	int	fd[2];
	int	pid1;

	ft_handle_error(pipe(fd), "Pipe creation failed");
	pid1 = fork();
	ft_handle_error(pid1, "Fork failed");
	if (pid1 == 0)
	{
		ft_handle_error(close(fd[0]), "Close failed");
		ft_handle_error(dup2(*fd_stdin, 0), "Dup2 failed ");
		ft_handle_error(dup2(fd[1], 1), "Dup2 failed");
		ft_close2file(fd[1], *fd_stdin);
		exec_command(av[n], env);
	}
	else
	{
		ft_close2file(fd[1], *fd_stdin);
		*fd_stdin = dup(fd[0]);
		close(fd[0]);
	}
}

void	last_command(char **av, char **env, int ac, int fd)
{
	int	fd1;
	int	pid1;

	fd1 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_handle_error(fd1, "Open file failed");
	pid1 = fork();
	ft_handle_error(pid1, "Fork failed");
	if (pid1 == 0)
	{
		ft_handle_error(dup2(fd, 0), "Dup2 failed");
		ft_handle_error(dup2(fd1, 1), "Dup2 failed");
		ft_close2file(fd1, fd);
		exec_command(av[ac - 2], env);
	}
	else
		ft_close2file(fd1, fd);
}

void	ft_fille_file(char **av, int fd)
{
	char	*str;
	int		len;

	ft_putstr_fd("here_doc> ", 0);
	str = get_next_line(0);
	len = ft_strlen(av[2]);
	while (str)
	{
		if (!ft_strncmp(av[2], str, len) && str[len] == '\n')
			break ;
		ft_putstr_fd(str, fd);
		free(str);
		ft_putstr_fd("here_doc> ", 0);
		str = get_next_line(0);
	}
	if (str != NULL)
		free(str);
}

int	main(int ac, char **av, char **env)
{
	int	fd1;
	int	i;

	if (!ft_strncmp(av[1], "here_doc", 8) && !av[1][8])
	{
		if (ac == 6)
			ft_her_doc(av, env);
		else
			ft_handle_error(-1, "incorerct number of argument for here_doc");
	}
	fd1 = open(av[1], O_RDONLY);
	ft_handle_error(fd1, "Open file failed ");
	if (ac >= 5)
	{
		i = 1;
		while (++i < ac - 2)
			first_command(av, env, i, &fd1);
		last_command(av, env, ac, fd1);
		while (wait(NULL) != -1)
			;
	}
	else
		ft_handle_error(-2, "Argument number incorrect");
}
