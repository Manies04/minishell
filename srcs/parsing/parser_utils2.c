/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:55:49 by joaoleote         #+#    #+#             */
/*   Updated: 2025/05/21 01:51:40 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief The last input redirection is saved in less
 * @param str array of str with an command divided in tokens
 * @param c string with the redirection to look for (< or <<)
 * @return an array of str with the correspondent files to that operator
*/
char	**get_input_files(char **str, char *c)
{
	int		i;
	int		j;
	char	**file;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	file = (char **)malloc(sizeof(char *) * i);
	i = -1;
	if (!file)
		return (NULL);
	while (str[++i])
	{
		if (ft_strcmp(str[i], c) == 0)
		{
			file[j] = ft_strdup(str[i + 1]);
			if (!file[j++])
				file[j - 1] = ft_strdup("./\2/\2");
		}
	}
	file[j] = NULL;
	if (j == 0)
		return (free_double_array(file), NULL);
	return (file);
}

/**@brief Extract from an tokenized command all file names that appeared after
 *  output redirections
 * @param str array of str with a command divided by tokens
 * @return an array with file names that appear after the output redirections 
 * (> or >>)
*/
char	**get_output_files(char **str)
{
	char	**file;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	file = (char **)malloc(sizeof(char *) * i);
	i = -1;
	if (!file)
		return (NULL);
	while (str[++i])
	{
		if (ft_strcmp(str[i], "\6") == 0 || ft_strcmp(str[i], "\6\6") == 0)
		{
			file[j] = ft_strdup(str[i + 1]);
			if (!file[j++])
				file[j - 1] = ft_strdup("./\2/\2");
		}
	}
	file[j] = NULL;
	if (j == 0)
		return (free_double_array(file), NULL);
	return (file);
}
