/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momari <momari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 21:08:12 by momari            #+#    #+#             */
/*   Updated: 2024/01/15 21:23:54 by momari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_checkpath(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp((const char *)env[i], "PATH", 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	while (i)
	{
		free(str[i]);
		i--;
	}
	str = NULL;
}

char	*get_path(char *av, char **env)
{
	int		i;
	int		index;
	char	*str;
	char	*str1;
	char	**paths;

	i = 0;
	index = ft_checkpath(env);
	if (index == -1)
		return (NULL);
	paths = ft_split((const char *)(env[index] + 5), ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		str1 = ft_strjoin(paths[i], "/");
		str = ft_strjoin(str1, av);
		if (access(str, X_OK) == 0)
			return (ft_free(paths), free(str1), str);
		free(str1);
		free(str);
		i++;
	}
	return (NULL);
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

void	ft_close2file(int fd1, int fd2)
{
	ft_handle_error(close(fd1), "Close failed");
	ft_handle_error(close(fd2), "Close failed");
}
