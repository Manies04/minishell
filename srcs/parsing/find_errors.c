/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:05:19 by joaoleote         #+#    #+#             */
/*   Updated: 2025/04/30 17:25:04 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief Verify Pipes
 * @param new String with the input
 * @return An integer
*/
static int	verify_pipes(char *new)
{
	char	**splitted; //array of strings where which string will be a psrt of the original str
	int		i; //an int to run splitted
	int		j; //an int to run which str of splitted
	int		result; //a value to indicate if the verification passed

	i = -1; // initializes i with -1
	result = 1; //initializes with 1, assuming that the result is correct
	splitted = ft_split(new, '\2'); // Uses ft_split to divide the str new throughout Spaces
	while (splitted[++i]) //Starts running each str inside of splitted
	{
		j = -1;
		while (splitted[i][++j]) //increments j to start at splitted[i][0]
		{
			if (splitted[i][j] == '\3') //if the current character is a pipe
			{
				if (j == 0 && i == 0) //if he found a pipe in the start its invalid -> result = 0;
					result = 0;
				if (!splitted[i][j + 1] && !splitted[i + 1]) //if after the pipe there isnt anything ot there isnt any strings after its invalid -> result = 0;
					result = 0;
				if (splitted[i][j + 1] == '\3') //if theres another pipe after the first one its also invalid > result = 0;
					result = 0;
			}
		}
	}
	return (free_double_array(splitted), result); // Frees all the memory from splitted and return the result
}

/**@brief Sees if theres any quotes that are open
 * @param new a string
 * @return An integer
*/
static int	open_quotes(char *new)
{
	int	i; //starts in the first character in the str
	int	count; //to count the number of quotes that finds
	
	i = 0;
	count = 0;
	while (new[i])
	{
		if (new[i] == '\4') //if the character is a diuble quote we increment count
			count++;
		i++; //advances to the next character
	}	
	if (count % 2 != 0) //After going through the str if count is odd it means that there are unclosed quotes and return 1 to show an error
		return (1);
	i = 0;
	count = 0;
	while (new[i])
	{
		if (new[i] == '\5') //Does the same to Single quotes
			count++;
		i++;
	}
	if (count % 2 != 0) //After going through the str if count is odd it means that there are unclosed quotes and return 1 to show an error
		return (1);
	return (0);
}

/**@brief check whether the redirections are well done
 * @param new String
 * @return an integer
*/
static int	verify_redirections(char *new)
{
	char	**splitted; //an array of strings where which string will be a psrt of the original str
	int		i; //an index to run though the array splitted
	
	i = 0;
	splitted = ft_split(new, '\2'); //Uses ft_split to split the new str using Spaces as delimiter
	while (splitted[i]) //while splitted exists
	{
		if (is_redirection(splitted[i]) && \
				!splitted[i + 1] || \
				(is_redirection(splitted[i]) && \
				is_redirection(splitted[i + 1]))) //if theres any redirection and there isnt a next argument is error, and if theres two redirections in a row
			return (free_double_array(splitted), 0); //returns 0 to show error and frees the memory
		i++;
	}
	return (free_double_array(splitted), 1); //if everything is correct it frees the memory and returns 1
}

int	find_errors(char *new)
{
	if (open_quotes(new)) //if it returns 1 theres an error so returns an error message
		return (printf("There are open quotes.\n"));
	if (!verify_pipes(new)) //if it returns 0 theres an error so returns an error message
		return (printf("Syntax error with Pipe.\n"));
	if (!verify_redirections(new)) //if it returns 0 theres an error so returns an error message
		return (printf("Syntax error with Redirection.\n"));
	return (0); //if there arent any errors returns 0 indicating that everything is ok
}
