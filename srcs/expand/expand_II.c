/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_II.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:34:20 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 02:18:02 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief This function marks the $ in single quotes to skip expansion, leaving
 *  it untouched in double quotes.
 * @param str The string to handle
 * @return 0 on success
 */
void	handle_quoted_expansion(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\5')
		{
			i++;
			while (str[i] && str[i] != '\5')
			{
				if (str[i] == '$')
					str[i] = '\1';
				i++;
			}
		}
		else if (str[i] == '\4')
		{
			i++;
			while (str[i] && str[i] != '\4')
				i++;
		}
		i++;
	}
}

/**@brief This function copies an array of strings to a new array.
 * @param strs The array of strings to copy
 * @return The new array of strings
 */
char	**ft_cp_double_str(char **strs)
{
	char	**cp;
	int		i;

	cp = (char **)malloc(sizeof(char *) * (count_strs(strs) + 1));
	if (!cp)
		return (NULL);
	i = 0;
	while (strs[i])
	{
		cp[i] = strs[i];
		strs[i] = NULL;
		i++;
	}
	cp[i] = NULL;
	return (cp);
}

/**@brief This function removes all \4 and \5 from the string and replaces \1 
 * with $.
 * @param dst The destination string
 * @param src The source string
 * @return Void.
 */
static void	markers_handler(char *dst, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[j])
	{
		if (src[j] == '\4' || src[j] == '\5')
			j++;
		else
		{
			if (src[j] == '\1')
				dst[i++] = '$';
			else
				dst[i++] = src[j];
			j++;
		}
	}
	dst[i] = '\0';
}

/**@brief This function removes all \4 and \5 from the string and replaces \1 
 * with $.
 * @param str The string to edit
 * @return Void.
 */
void	edit_str(char **str)
{
	char	*temp;

	temp = ft_strdup(*str);
	free(*str);
	*str = malloc(sizeof(char) * (ft_strlen(temp) + 1));
	if (!*str)
	{
		free(temp);
		return ;
	}
	markers_handler(*str, temp);
	free(temp);
}

/**@brief Core of the variable expansion process. 
 * Finds strings needing expansion, performs the expansion,
 * replaces them in the array, removes empty entries and quotes,
 * and returns the final cleaned-up array.
 * @param str The array of strings to expand
 * @return The expanded array of strings
 */
char	**expander(char **str)
{
	int	f;

	str = expand_variables(str, &f);
	if (f > 0)
		str = rm_empty_str(str);
	return (rm_quotes(str));
}
