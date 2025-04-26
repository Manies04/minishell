/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:23:35 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:05:43 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Takes a specific part of the string and returns that as a new string
 * @param *s The string which to create the substring
 * @param start The start index of the substring in the string 's'
 * @param len The maximum lenght of the substring
 * @return The new string
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*tab;

	if (!s || (unsigned int)ft_strlen(s) <= start || !len)
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	tab = malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	size = 0;
	while (size < len)
	{
		tab[size] = s[start + size];
		size++;
	}
	tab[size] = '\0';
	return (tab);
}
/*int main()
{
	const char	*string_original = "OlA o MEU nome e Joao";
	unsigned int	inicio = 8;
	size_t	comprimento = 6;
	char	*substring = ft_substr(string_original, inicio, comprimento);
	
	printf("%s\n", substring);
	free(substring);
	return (0);
}*/
