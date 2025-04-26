/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:52:46 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:02:45 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static unsigned int	ft_count_digits(int n)
{
	unsigned int	c;

	c = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		c += 1;
	while (n != 0)
	{
		n = n / 10;
		c++;
	}
	return (c);
}
/**@brief Integer to ascii
 * @param param n Integer 
 * @return The number in ascii
*/

char	*ft_itoa(int n)
{
	unsigned int		i;
	char				*str;
	unsigned int		n_digits;

	n_digits = ft_count_digits(n);
	str = (char *)malloc((n_digits + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		i = -n;
	}
	else
		i = n;
	if (i == 0)
		str[0] = '0';
	str[n_digits] = 0;
	while (i != 0)
	{
		str[n_digits - 1] = (i % 10) + '0';
		i = i / 10;
		n_digits--;
	}
	return (str);
}
/*int main()
{
	int test_cases[] = {0, 123, -456, 7890, -12345};
	int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

	printf("Testing ft_itoa function:\n");
	int	i;
	
	i = 0;
	while (i < num_cases)
	{
		int num = test_cases[i];
		char *result = ft_itoa(num);
		if (result == NULL) 
		{
			printf("Memory allocation failed for test case %d\n", num);
			continue;
		}
		printf("Number: %d, Result: %s\n", num, result);
		free(result);
		i++;
	}

	return (0);
}*/