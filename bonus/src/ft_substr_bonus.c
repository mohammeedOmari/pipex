/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momari <momari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:40:33 by momari            #+#    #+#             */
/*   Updated: 2024/01/12 22:27:49 by momari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static char	*ft_sstrcpy(char *dst, char const *src, size_t len)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*n_str;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start > len)
		n_str = (char *)malloc(len + 1);
	else
		n_str = (char *)malloc((s_len - start) + 1);
	if (n_str == NULL)
		return (NULL);
	ft_sstrcpy(n_str, s + start, len);
	return ((char *)n_str);
}
