/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:19:04 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:05:40 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Removes whitespaces in the beginning and the end of the string
 * @param *s1 Pointer to the string were it will be trimmed
 * @param *set Pointer to the string with the whitespaces
 * @return The string trimmed
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	a;
	size_t	b;
	char	*str;

	str = NULL;
	a = 0;
	b = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (s1[a] && ft_strchr(set, s1[a]))
		a++;
	while (b > a && ft_strchr(set, s1[b - 1]))
		b--;
	str = malloc(sizeof(char) * (b - a + 1));
	ft_strlcpy(str, &s1[a], b - a + 1);
	return (str);
}
/*
int	main() 
{
	char *s1 = "   hello world   ";
	char *set = " ";
	char *trimmed_str = ft_strtrim(s1, set);

	printf("String original: \"%s\"\n", s1);
	printf("String após remoção de espaços em branco: \"%s\"\n", trimmed_str);
	free(trimmed_str);
	return (0);
}
*/