/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:55:49 by joaoleote         #+#    #+#             */
/*   Updated: 2025/04/27 14:14:58 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
				file[j - 1] = ft_strdup("./\x12/\x12");
		}
	}
	file[j] = NULL;
	if (j == 0)
		return (free_double_array(file), NULL);
	return (file);
}

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
		if (ft_strcmp(str[i], GREAT_MARKER) == 0 || ft_strcmp(str[i], GREATER_MARKER) == 0)
		{
			file[j] = ft_strdup(str[i + 1]);
			if (!file[j++])
				file[j - 1] = ft_strdup("./\x12/\x12");
		}
	}
	file[j] = NULL;
	if (j == 0)
		return (free_double_array(file), NULL);
	return (file);
}
