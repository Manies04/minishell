/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:56:11 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:04:07 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Comparing blocks of memory unitl the byte n
 * @param *str1 Pointer to the first region being compared
 * @param *str2 Pointer to the second region being compared
 * @param n Number of bytes being compared
 * @return A pointer to the 
*/
int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t					a;
	const unsigned char		*s1;
	const unsigned char		*s2;

	s1 = (const unsigned char *)str1;
	s2 = (const unsigned char *)str2;
	a = 0;
	while (a < n)
	{
		if (s1[a] != s2[a])
			return (s1[a] - s2[a]);
		a++;
	}
	return (0);
}
/*#include <stdio.h>
int	main()
{
	printf("%d\n", ft_memcmp("hEllo", "hello", 2));
	return(0);
}*/
