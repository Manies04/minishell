/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:53:38 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:05:22 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Aply a function to each caracter of the string
 * @param *s Pointer to a string
 * @param *f Pointer to function to be aplied
 * @return The return value of the function aplied
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s)) + 1);
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
char	convert_to_uppercase(unsigned int index, char character)
{
	if (index % 2 == 1)
	{
		if (character >= 'a' && character <= 'z')
		{
			return (character - 32);
		}
	}
	return (character);
}
int	main()
{
	const char *original = "hello world";
	char *result;

	result = ft_strmapi(original, &convert_to_uppercase);

	if (result != NULL)
	{
		printf("String original: %s\n", original);
		printf("String resultante: %s\n", result);
		free(result);
	}
	else
	{
		printf("Erro: falha ao alocar memória.\n");
	}
	return 0;
}*/