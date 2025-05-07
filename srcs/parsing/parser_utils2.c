/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:55:49 by joaoleote         #+#    #+#             */
/*   Updated: 2025/04/30 17:31:06 by tiade-al         ###   ########.fr       */
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
	int		i; //index to run the original str
	int		j; //index to fill the array file
	char	**file; //array that will contain the name of the files

	i = 0;
	j = 0;
	while (str[i]) //counts how many elements has str
		i++;
	file = (char **)malloc(sizeof(char *) * i); //uses i to alocate the array file
	i = -1;
	if (!file) //if the malloc failes it returns NULL
		return (NULL);
	while (str[++i]) //runs through str
	{
		if (ft_strcmp(str[i], c) == 0) //if the current element is equal to the operator that was passed in c
		{
			file[j] = ft_strdup(str[i + 1]); //copys the next token
			if (!file[j++]) //if the copy fails, puts an invalid str to sinilize the error
				file[j - 1] = ft_strdup("./\2/\2");
		}
	}
	file[j] = NULL; //finishes the array 
	if (j == 0) //if not one file was found, frees file and returns NULL
		return (free_double_array(file), NULL);
	return (file);
}

/**@brief Extract from an tokenized command all file names that appeared after output redirections
 * @param str array of str with a command divided by tokens
 * @return an array with file names that appear after the output redirections (> or >>)
*/
char	**get_output_files(char **str)
{
	char	**file; //an array that will have the output name files
	int		i; //index to run str
	int		j; //index to fill file

	i = 0;
	j = 0;
	while (str[i]) //counts how many elements has str
		i++;
	file = (char **)malloc(sizeof(char *) * i); //uses i to alocate the array file
	i = -1;
	if (!file) // if the malloc failes it returns NULL
		return (NULL);
	while (str[++i])
	{
		if (ft_strcmp(str[i], "\6") == 0 || ft_strcmp(str[i], "\6\6") == 0) //verifies if the current token is an output redirection
		{
			file[j] = ft_strdup(str[i + 1]); //makes a copy of the next token, that is expected to be the file name
			if (!file[j++]) //if the dup fails, puts a value  invalid placeholder to signal 
				file[j - 1] = ft_strdup("./\2/\2");
		}
	}
	file[j] = NULL; //finishes the array correctly
	if (j == 0) //if not one file was found, frees file and returns NULL
		return (free_double_array(file), NULL);
	return (file);
}
