/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:08:46 by joaoleote         #+#    #+#             */
/*   Updated: 2025/05/21 01:52:43 by tiade-al         ###   ########.fr       */
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
	char	flag;

	i = 0;
	flag = 0;
	while (input[i])
	{
		if ((input[i] == '"' || input[i] == '\'') && flag == 0)
		{
			flag = input[i];
			if (input[i] == '"')
				input[i] = '\4';
			else
				input[i] = '\5';
		}
		else if (input[i] == flag)
		{
			flag = 0;
			if (input[i] == '"')
				input[i] = '\4';
			else
				input[i] = '\5';
		}
		i++;
	}
}

/**@brief Changes all special case for more secure substitutes to change the 
 * string more safely
 * @param input String with the input
 * @return Nothing
*/
static void	change_characters(char *input)
{
	int		i;
	char	quote_flag;

	i = -1;
	quote_flag = 0;
	while (input[++i])
	{
		if ((input[i] == '\4' || input[i] == '\5'))
		{
			quote_flag = input[i];
			i++;
			while (input[i] && input[i] != quote_flag)
				i++;
		}
		if (!input[i])
			break ;
		if (input[i] == ' ')
			input[i] = '\2';
		else if (input[i] == '|')
			input[i] = '\3';
		else if (input[i] == '>')
			input[i] = '\6';
		else if (input[i] == '<')
			input[i] = '\7';
	}
}

/**@brief Adds SPACE_MARKERS (ARTIFICIAL SPACES) after  to ease the making of 
 * tokens.
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
		if (str[i] == '\4' || str[i] == '\5')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
		}
		if (is_whitespace(str[i]) && str[i] != ' ')
			str[i] = ' ';
	}
}

/**@brief Changes all special case for more secure substitutes to change the 
 * string more safely
 * @param input String with the input
 * @return Nothing
*/
static char	*add_redirect_spaces(char *input)
{
	size_t	len;
	char	*new;
	int		i;
	int		j;

	len = ft_strlen(input);
	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (len * 3));
	if (!new)
		return (NULL);
	while (input[i])
	{
		new[j++] = input[i];
		if ((input[i] == '\6' || input[i] == '\7')
			&& input[i + 1] != input[i])
			new[j++] = '\2';
		else if ((input[i + 1] == '\6' || input[i + 1] == '\7')
			&& input[i] != input[i + 1])
			new[j++] = '\2';
		i++;
	}
	new[j] = '\0';
	return (new);
}

char	*lexer(char *input)
{
	char	*new;

	mark_quotes(input);
	change_spaces(input);
	change_characters(input);
	new = add_redirect_spaces(input);
	if (!new)
		return (NULL);
	if (find_errors(new))
		return (free(new), NULL);
	return (new);
}
