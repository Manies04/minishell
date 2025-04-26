/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:31:17 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:05:33 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Find in a string what i'm searching for
 * @param *str String were it will be search the "to_find"
 * @param *to_find What will be search in the string
 * @param n Size of bytes that will be tracked 
 * @return The string from the byte that i'm looking for till the '\0'
*/
char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	a;
	size_t	b;

	a = 0;
	if (to_find[0] == '\0' || to_find == NULL)
		return ((char *)str);
	while (str[a] != '\0' && a < n)
	{
		b = 0;
		if (str[a] == to_find[b])
		{
			while (str[a + b] == to_find[b] && a + b < n)
			{
				if (to_find[b + 1] == '\0')
					return ((char *)str + a);
				b++;
			}
		}
		a++;
	}
	return (NULL);
}
/*#include <stdio.h>
int	main()
{
	const char	*str = "os dentes caem quando o paulinho marca";
	const char	*find = "caem";
    size_t  n = 13;
    char    *result= ft_strnstr(str, find, n);

	printf("%s\n", result);
    return (0);
}*/
