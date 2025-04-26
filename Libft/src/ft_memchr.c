/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:23:40 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:04:03 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Finds the first time the character is on the string
 * @param *str Pointer to the memory 
 * @param c Character that is being searched
 * @param len Number of bytes that is being searched
 * @return A pointer to the byte where the character was found
*/
void	*ft_memchr(const void *str, int c, size_t len)
{
	size_t		i;
	const char	*s;

	i = 0;
	s = (const char *)str;
	while (i < len)
	{
		if (s[i] == (char)c)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
/*
int	main()
{
	const	char	str[] = "Hello, world!";
	int	c = 'o';
	size_t	len = ft_strlen(str);
	void	*result;

	result = ft_memchr(str, c, len);

	if (result != NULL)
	{
		printf("Caractere '%c' encontrado em '%s' na posição: %ld\n", 
		c, str, (char *)result - str);
	}
	else
	{
		printf("Caractere '%c' não encontrado em '%s'\n", c, str);
	}
	return (0);
}*/