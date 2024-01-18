/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momari <momari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:52:35 by momari            #+#    #+#             */
/*   Updated: 2024/01/15 21:31:07 by momari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*ft_createstr(char *src, char **string)
{
	int		i;
	char	*str;

	i = 0;
	if (string || *string)
		free(*string);
	if (!src || src[0] == '\0')
		return (NULL);
	while (src[i] && src[i] != '\n')
		i++;
	if (src[i] == '\n')
		i++;
	str = (char *)malloc(i + 1 * sizeof(char));
	if (!str)
		return (NULL);
	ft_strcpy(str, src, i);
	return (str);
}

static char	*ft_newbuffer(char *src)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (src[i] && src[i] != '\n')
		i++;
	if (src[i] == '\n')
		i++;
	while (src[i + j])
		j++;
	str = (char *)malloc(j + 1 * sizeof(char));
	if (!str)
		return (free(src), src = NULL, NULL);
	ft_strcpy(str, src + i, j + 1);
	free(src);
	src = NULL;
	return (str);
}

static int	ft_allocate(char **src)
{
	*src = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!*src)
		return (1);
	return (0);
}

static int	ft_check(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX || read(fd, 0, 0) == -1
		|| BUFFER_SIZE > INT_MAX)
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	int			re;
	static char	*buffer;
	char		*string;
	char		*return_str;

	if (ft_check(fd) == 1)
		return (free(buffer), buffer = NULL, NULL);
	if (ft_allocate(&string) == 1)
		return (free(buffer), buffer = NULL, NULL);
	re = 1;
	while (re)
	{
		re = read(fd, string, BUFFER_SIZE);
		if (re == -1)
			return (free(string), free(buffer), buffer = NULL, NULL);
		string[re] = '\0';
		buffer = ft_getjoin(buffer, string);
		if (!buffer || ft_search(string) != -1)
			break ;
	}
	return_str = ft_createstr(buffer, &string);
	if (!return_str)
		return (free(buffer), buffer = NULL, NULL);
	buffer = ft_newbuffer(buffer);
	return (return_str);
}
