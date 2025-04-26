/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:05:19 by joaoleote         #+#    #+#             */
/*   Updated: 2025/04/24 16:26:48 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**@brief Changes all special case for more secure substitutes to change the string more safely
 * @param input String with the input
 * @return Nothing
*/
static int	verify_pipes(char *new)
{
	char	**splited;
	int		i;
	int		j;
	int		result;

	i = -1;
	result = 1;
	splited = ft_split(new, SPACE_MARKER);
	while (splited[++i])
	{
		j = -1;
		while (splited[i][j++])
		{
			if (splited[i][j] == PIPE_MARKER)
			{
				if (j == 0 && i == 0)
					result = 0;
				if (!splited[i][j + 1] && !splited[i + 1])
					result = 0;
				if (splited[i][j + 1] == PIPE_MARKER)
					result = 0;
			}
		}
	}
	return (free_double_array(splited), result);
}

/**@brief Changes all special case for more secure substitutes to change the string more safely
 * @param input String with the input
 * @return Nothing
*/
static int	open_quotes(char *new)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while (new[i])
	{
		if (new[i] == DQUOTE)
			count++;
		i++;
	}	
	if (count % 2 != 0)
		return (1);
	i = 0;
	count = 0;
	while (new[i])
	{
		if (new[i] == SQUOTE)
			count++;
		i++;
	}
	if (count % 2 != 0)
		return (1);
	return (0);
}

/**@brief Changes all special case for more secure substitutes to change the string more safely
 * @param input String with the input
 * @return Nothing
*/
static int	verify_redirections(char *new)
{
	char	**splitted;
	int		i;
	
	i = 0;
	splitted = ft_split(new, SPACE_MARKER);
	while (splitted[i])
	{
		if (is_redirection(splitted[i]) && !splitted[i + 1] || \
			(is_redirection(splitted[i]) && \
			is_redirection(splitted[i + 1])))
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
