/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:05:19 by joaoleote         #+#    #+#             */
/*   Updated: 2025/05/21 01:53:26 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief Verify Pipes
 * @param new String with the input
 * @return An integer
*/
static int	verify_pipes(char *new)
{
	char	**splitted;
	int		i;
	int		j;
	int		result;

	i = -1;
	result = 1;
	splitted = ft_split(new, '\2');
	while (splitted[++i])
	{
		j = -1;
		while (splitted[i][++j])
		{
			if (splitted[i][j] == '\3')
			{
				if (j == 0 && i == 0)
					result = 0;
				if (!splitted[i][j + 1] && !splitted[i + 1])
					result = 0;
				if (splitted[i][j + 1] == '\3')
					result = 0;
			}
		}
	}
	return (free_double_array(splitted), result);
}

/**@brief Sees if theres any quotes that are open
 * @param new a string
 * @return An integer
*/
static int	open_quotes(char *new)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (new[i])
	{
		if (new[i] == '\4')
			count++;
		i++;
	}
	if (count % 2 != 0)
		return (1);
	i = 0;
	count = 0;
	while (new[i])
	{
		if (new[i] == '\5')
			count++;
		i++;
	}
	if (count % 2 != 0)
		return (1);
	return (0);
}

/**@brief check whether the redirections are well done
 * @param new String
 * @return an integer
*/
static int	verify_redirections(char *new)
{
	char	**splitted;
	int		i;

	i = 0;
	splitted = ft_split(new, '\2');
	while (splitted[i])
	{
		if ((is_redirection(splitted[i]) && !splitted[i + 1]) || \
			(is_redirection(splitted[i]) && is_redirection(splitted[i + 1])))
			return (free_double_array(splitted), 0);
		i++;
	}
	return (free_double_array(splitted), 1);
}

int	find_errors(char *new)
{
	if (open_quotes(new))
		return (printf("There are open quotes.\n"));
	if (!verify_pipes(new))
		return (printf("Syntax error with Pipe.\n"));
	if (!verify_redirections(new))
		return (printf("Syntax error with Redirection.\n"));
	return (0);
}
