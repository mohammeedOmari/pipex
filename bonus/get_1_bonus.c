/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_1_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momari <momari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:17:31 by momari            #+#    #+#             */
/*   Updated: 2024/01/15 21:31:42 by momari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_search(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strcpy(char *dst, char const *src, size_t len)
{
	size_t	i;

	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_getjoin(char *s1, char *s2)
{
	char	*n_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1)
		return (free(s1), s1 = NULL, ft_strdup((const char *)s2));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	n_str = (char *)malloc(s1_len + s2_len + 1 * sizeof(char));
	if (n_str == NULL)
		return (free(s1), s1 = NULL, NULL);
	ft_strcpy(n_str, s1, s1_len);
	ft_strcpy(n_str + s1_len, s2, s2_len);
	free(s1);
	s1 = NULL;
	return (n_str);
}

void	ft_her_doc(char **av, char **env)
{
	int	fd1;

	fd1 = open("/tmp/.forStoring", O_CREAT | O_RDWR | O_TRUNC, 0664);
	ft_handle_error(fd1, "Open file failed ");
	ft_fille_file(av, fd1);
	ft_handle_error(close(fd1), "Closing file failed ");
	fd1 = open("/tmp/.forStoring", O_RDWR, 0664);
	ft_handle_error(fd1, "Open file failed ");
	first_command(av, env, 3, &fd1);
	last_command_here(av, env, 6, fd1);
	while (wait(NULL) != -1)
		;
	exit(0);
}

void	last_command_here(char **av, char **env, int ac, int fd)
{
	int	fd1;
	int	pid1;

	fd1 = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
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
