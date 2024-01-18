/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momari <momari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:24:18 by momari            #+#    #+#             */
/*   Updated: 2024/01/12 22:27:25 by momari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		s1_len;

	s1_len = ft_strlen(s1);
	ptr = (char *)malloc((s1_len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s1, s1_len);
	ptr[s1_len] = '\0';
	return (ptr);
}
