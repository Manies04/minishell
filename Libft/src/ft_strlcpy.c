/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:31:24 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:05:15 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Copy the src to dest with size being controled
 * @param *dest Destanation of the copy
 * @param *src Source of the copy
 * @param n Size where it finishes coping
 * @return The result of copy
*/
size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	j;
	size_t	i;

	i = ft_strlen(src);
	j = 0;
	if (n != 0)
	{
		while (src[j] != '\0' && j < n - 1)
		{
			dest[j] = src[j];
			j++;
		}
		dest[j] = '\0';
	}
	return (i);
}
/*#include <stdio.h>
int	main()
{
	char	src[] = "Ola amigos";
	char	dest[] = "muito bem";
	printf("%d\n%s\n", ft_strlcpy(dest, src, 8), dest);
}*/
