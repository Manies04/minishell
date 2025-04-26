/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:13:57 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:04:10 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Copies a block of memorie from src to dest
 * @param dest The destination of the copy
 * @param src The source of the copy
 * @param n Size of the bytes needed
 * @return A pointer to dest location 
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest1;
	char	*src1;
	size_t	a;

	a = 0;
	dest1 = (char *)dest;
	src1 = (char *)src;
	while (a < n)
	{
		dest1[a] = src1[a];
		a++;
	}
	return (dest);
}
/*
#include <stdio.h>
int	main()
{
	char	src[] = "Hello World!";
	char	dest[150];
	size_t	n = sizeof(src);

	ft_memcpy(dest, src, n);
	printf("dest: %s\n", dest);
	return (0);
}*/
