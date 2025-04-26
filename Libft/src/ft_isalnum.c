/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:35:45 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:02:24 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Variable is alpha or numeric
 * @param i Ascii representation
 * @return 1 if is alphanumeric or 0 if not
*/
int	ft_isalnum(int i)
{
	if (((i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z'))
		|| (i >= '0' && i <= '9'))
		return (1);
	return (0);
}
/*int	main()
{
	char i = '1';
	printf("%d\n", ft_isalnum(i));
	return(0);
}*/