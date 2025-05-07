/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:08:46 by joaoleote         #+#    #+#             */
/*   Updated: 2025/04/30 17:27:35 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief Makes the program know easily where are the strings between quotes
 * @param input String with the input
 * @return Nothing
*/
static void	mark_quotes(char *input)
{
	int		i;
	char	flag;//to use if we are inside a quote and if is a single or a double

	i = 0;
	flag = 0;
	while (input[i])
	{
		if ((input[i] == '"' || input[i] == '\'') && flag == 0) //if the current character is a single or a double quote and flag is 0 it means that we enconter the begining of a str between quotes
		{
			flag = input[i]; //keeps the quote that was found on flag
			if (input[i] == '"') //if flag is " puts DQUOTES and if not puts SQUOTES
				input[i] = '\4';
			else
				input[i] = '\5';
		}
		else if (input[i] == flag) //if we are between quotes and the character we are is the sames as flag, we found the closing of the quotes
		{
			flag = 0;
			if (input[i] == '"')
				input[i] = '\4';
			else
				input[i] = '\5'; //replaces the quote of closing for DQUOTE or SQUOTE
		}
		i++;
	}
}

/**@brief Changes all special case for more secure substitutes to change the string more safely
 * @param input String with the input
 * @return Nothing
*/
static void	change_characters(char *input)
{
	int		i;
	char	quote_flag; //to know is we are inside quotes and what type

	i = -1;
	quote_flag = 0;
	while (input[++i])
	{
		if ((input[i] == '\4' || input[i] == '\5')) //if the current character is one of these we are in a starting point of a str between quotes
		{
			quote_flag = input[i]; //keeps in quote_flag what type of quotes opened
			i++;
			while (input[i] && input[i] != quote_flag)
				i++;
		}
		if (!input[i]) //if there isnt any input we break
			break ;
		if (input[i] == ' ') //if the current character is a space we trade for SPACE MARKER
			input[i] = '\2';
		else if (input[i] == '|') //if the current character is a pipe we trade for PIPE MARKER
			input[i] = '\3';
		else if (input[i] == '>') //if the current character is a > we trade for GREAT MARKER
			input[i] = '\6';
		else if (input[i] == '<') //if the current character is a < we trade for LESS MARKER
			input[i] = '\7';
	}
}

/**@brief Adds SPACE_MARKERS (ARTIFICIAL SPACES) after  to ease the making of tokens.
 * @param input String with the input
 * @return Nothing
*/
static void	change_spaces(char *str)
{
	int		i;
	char	quote;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\4' || str[i] == '\5') //If it is a quote, of a str between quotes
		{
			quote = str[i++]; //keeps what type of quote was found
			while (str[i] && str[i] != quote) //we keep going till we find either the finalle of the str or the closing of the quotes
				i++;
		}
		if (is_whitespace(str[i]) && str[i] != ' ') //if it is a whitespace
			str[i] = ' '; //we normalize the space
	}
}

/**@brief Changes all special case for more secure substitutes to change the string more safely
 * @param input String with the input
 * @return Nothing
*/
static char	*add_redirect_spaces(char *input)
{
	size_t	len; //to str lenght
	char	*new; //to keep the new array
	int		i; //index to run through input
	int		j; //index to new

	len = ft_strlen(input); //uses ft_strlen to see the size of len
	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (len * 3)); // Alocates 3times the amount of memory needed to addthe spaces beteween characters
	if (!new)
		return (NULL); //Checkup to see if there arent any malloc failuers
	while (input[i])
	{
		new[j++] = input[i]; //Copies the current character to new
		if ((input[i] == '\6' || input[i] == '\7')
			&& input[i + 1] != input[i]) //if the current character is a redirection and the next one isn't
			new[j++] = '\2'; //puts a space after
		else if ((input[i + 1] == '\6' || input[i + 1] == '\7')
			&& input[i] != input[i + 1]) //if the next character is a redirection and the current is different
			new[j++] = '\2'; //puts a space after
		i++;
	}
	new[j] = '\0'; //puts it to \0 to finish the new str correctly
	return (new);
}

char	*lexer(char *input)
{
	char	*new;

	mark_quotes(input); //Substitutes single and double quotes to protect the content between quotes
	change_spaces(input); //Converts wierd spaces like \t, \n, etc for simple spaces
	change_characters(input); //Substitutes special characters for markers
	new = add_redirect_spaces(input); //Creates a new str based in input adding spaces arround redirections
	if (!new) //verification
		return (NULL);
	if (find_errors(new)) //if theres any error he frees the allocated memory and return NULL
		return (free(new), NULL);
	return (new);
}
