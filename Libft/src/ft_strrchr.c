/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:53:17 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:05:36 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Searches for the last occurance of 'c' in "str"
 * @param *str The string were it will be search
 * @param c Character that is being search
 * @return The last occurence of 'c'
*/
char	*ft_strrchr(const char *str, int c)
{
	int		len;

	len = ft_strlen(str);
	while (len >= 0)
	{
		if (str[len] == (char)c)
			return ((char *)&str[len]);
		len--;
	}
	return (0);
}
/*
int	main()
{
	const char *str = "Hello, world!";
	int search_char = 'o';
	char *result = ft_strrchr(str, search_char);

	if (result != NULL)
	{
		printf("Última ocorrência de '%c' em '%s' encontrada em: %ld\n", 
		search_char, str, result - str);
	}
	else
	{
		printf("Caractere '%c' não encontrado em '%s'\n", search_char, str);
	}
	return (0);
}
*/