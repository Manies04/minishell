/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:50:12 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:04:41 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	ft_count(const char *s, char c)
{
	size_t	i;
	int		b;

	i = 0;
	b = 0;
	if (!s[b])
		return (0);
	while (s[b])
	{
		while (s[b] == c)
			b++;
		if (s[b])
			i++;
		while (s[b] != c && s[b])
			b++;
	}
	return (i);
}
/**@brief returns an array of str by splitting 's' by the delimiter 'c'
 * @param *s The string to be split
 * @param c The delimiter Character
 * @return The array of new strings resulting from the split
*/

char	**ft_split(char const *s, char c)
{
	size_t	len;
	char	**split;
	int		i;

	i = 0;
	split = (char **)malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				len = ft_strlen(s);
			else
				len = ft_strchr(s, c) - s;
			split[i++] = ft_substr(s, 0, len);
			s = s + len;
		}
	}
	split[i] = NULL;
	return (split);
}

/*
int main(void)
{
	char const	*str = "Hello world this is a test";
	char	**result = ft_split(str, ' ');

	if (result)
	{
		int i = 0;
		while (result[i])
		{
			printf("%s\n", result[i]);
			free(result[i]);
			i++;
		}
		free(result);
	}
	return 0;
}
*/