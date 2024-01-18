/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momari <momari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 22:14:59 by momari            #+#    #+#             */
/*   Updated: 2024/01/12 22:03:40 by momari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*ft_strcpy(char *dst, char const *src, size_t len)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*n_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	n_str = (char *)malloc(s1_len + s2_len + 1);
	if (n_str == NULL)
		return (NULL);
	ft_strcpy(n_str, s1, s1_len);
	ft_strcpy(n_str + s1_len, s2, s2_len);
	return (n_str);
}
