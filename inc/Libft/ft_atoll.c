/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:21:03 by tiade-al          #+#    #+#             */
/*   Updated: 2025/02/19 15:22:58 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**@brief The ft_atoll() function converts the initial portion of the string 
 * pointed to by str to long long.
 *@param str: The string to convert to long long
 *@return The converted value
*/
long long	ft_atoll(const char *str)
{
	long long	num;
	int			minus;

	num = 0;
	minus = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	if (minus % 2 != 0)
		return (-num);
	return (num);
}
