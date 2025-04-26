/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:58:48 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:04:18 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief 
 * @param *str Pointer to the memory that will be filled with a specific value
 * @param c Value that will be set to every byte
 * @param n Number of bytes that will be set
 * @return A pointer to a memory area of the string
*/
void	*ft_memset(void *str, int c, size_t n)
{
	char	*a;
	size_t	i;

	a = str;
	i = 0;
	while (i < n)
	{
		a[i] = c;
		i++;
	}
	return (str);
}
/*int main()
{
	char str[20];
	int c = 'o';
	size_t n = 10;

	ft_memset(str, c, n);

	printf("Resultado: \"%s\"\n", str);
	return 0;
}*/