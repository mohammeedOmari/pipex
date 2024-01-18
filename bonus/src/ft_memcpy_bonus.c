/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momari <momari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:05:29 by momari            #+#    #+#             */
/*   Updated: 2024/01/12 22:26:57 by momari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == src)
		return (dst);
	i = 0;
	while (n--)
	{
		*((unsigned char *)(dst + i)) = *((unsigned char *)(src + i));
		i++;
	}
	return (dst);
}
