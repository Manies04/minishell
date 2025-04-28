/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:08:46 by joaoleote         #+#    #+#             */
/*   Updated: 2025/04/26 23:10:05 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief Changes quotes for more secure substitutes to change the string more safely
 * @param input String with the input
 * @return Nothing
*/
static void	mark_quotes(char *input)
{
	int		i = 0;
	char	flag = 0;

	while (input[i])
	{
		if ((input[i] == '"' || input[i] == '\'') && flag == 0)
		{
			flag = input[i];
			input[i] = (flag == '"') ? DQUOTE : SQUOTE;
		}
		else if ((input[i] == flag) && flag != 0)
		{
			input[i] = (flag == '"') ? DQUOTE : SQUOTE;
			flag = 0;
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
	int		i = 0;
	char	quote_flag = 0;

	while (input[i])
	{
		if ((input[i] == DQUOTE || input[i] == SQUOTE))
		{
			quote_flag = input[i];
			i++;
			while (input[i] && input[i] != quote_flag)
				i++;
		}
		if (!input[i])
			break ;
		if (input[i] == ' ')
			input[i] = SPACE_MARKER;
		else if (input[i] == '|')
			input[i] = PIPE_MARKER;
		else if (input[i] == '>')
			input[i] = GREAT_MARKER;
		else if (input[i] == '<')
			input[i] = LESS_MARKER;
		i++;
	}
}

/**@brief Adds SPACE_MARKERS (ARTIFICIAL SPACES) after  to ease the making of tokens.
 * @param input String with the input
 * @return Nothing
*/
static void	change_spaces(char *str)
{
	int	i = 0;

	while (str[i])
	{
		if (str[i] == SQUOTE || str[i] == DQUOTE)
		{
			char	quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
		}
		if (is_whitespace(str[i]) && str[i] != ' ')
			str[i] = ' ';
		i++;
	}
}

/**@brief Changes all special case for more secure substitutes to change the string more safely
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
		if ((input[i] == GREAT_MARKER || input[i] == LESS_MARKER)
			&& input[i + 1] != input[i])
			new[j++] = SPACE_MARKER;
		else if ((input[i + 1] == GREAT_MARKER || input[i + 1] == LESS_MARKER)
			&& input[i] != input[i + 1])
			new[j++] = SPACE_MARKER;

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
