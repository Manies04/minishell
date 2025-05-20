/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_II.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:34:20 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/20 19:30:59 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief This function marks the $ in single quotes to skip expansion, leaving
 *  it untouched in double quotes.
 * @param str The string to handle
 * @return 0 on success
 */
static void	handle_quoted_expansion(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\5') // Single quote
		{
			i++;//skip the single quote
			while (str[i] && str[i] != '\5')//while the other squote isnt reached
			{
				if (str[i] == '$')
					str[i] = '\1'; // Mark $ in single quotes for no expansion
				i++;
			}
		}
		else if (str[i] == '\4') // Double quote
		{
			i++;//skip the double quote
			while (str[i] && str[i] != '\4')//while the other double quote isnt reached
				i++; // Leave $ untouched in double quotes
		}
		i++;
	}
}

/**@brief This function finds the first string needing expansion.
 * @param strs The array of strings to check
 * @return The index of the first string needing expansion, or -1 if none found
 */
int	need_expansion(char **strs)
{
	int	i;
	int	j;

	i = 0;
	while (strs[i])
	{
		handle_quoted_expansion(strs[i]);//mark the $ in single quotes
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == '\5')//if single quote is found
			{
				j++;//skip the opening single quote
				while (strs[i][j] && strs[i][j] != '\5')
					j++;//skips the content until the closing single quote
			}
			else if (strs[i][j] == '$' && strs[i][j + 1] && \
			strs[i][j + 1] != '\4' && strs[i][j + 1] != ' ')//if it finds a $ and there's a next char that's not a double quote or space
				return (i);//returns the position of a $ needing expansion
			j++;
		}
		i++;//next string
	}
	return (-1);//if no $ needing expansion is found
}

/**@brief This function checks if the string contains a space.
 * @param str The string to check
 * @return 1 if the string contains a space, 0 otherwise
 */
int	str_w_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 32)//if a space is found
			return (1);
		i++;
	}
	return (0);
}

/**@brief This function counts the number of strs in the array.
 * @param strs The array of strings to count
 * @return The number of strings in the array
 */
int	count_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

/**@brief This function copies an array of strings to a new array.
 * @param strs The array of strings to copy
 * @return The new array of strings
 */
static char	**ft_cp_double_str(char **strs)
{
	char	**cp;//new array that will hold the copied strings
	int		i;

	cp = (char **)malloc(sizeof(char *) * (count_strs(strs) + 1));//allocates memory for the new array
	if (!cp)//allocation failed
		return (NULL);
	i = 0;
	while (strs[i])
	{
		cp[i] = strs[i];//copies the string
		strs[i] = NULL;//sets the original string to NULL
		i++;
	}
	cp[i] = NULL;//ends the new array with NULL
	return (cp);
}

/**@brief This function replaces a string at a given index in a string array 
 * with the result of splitting that string by spaces, while preserving the 
 * rest of the array.
 * @param strs The array of strings to manipulate
 * @param start The index of the string to manipulate
 * @return The manipulated array of strings
 */
char	**split_by_spaces(char **strs, int index)
{
	char	**tmp;//temporary array to hold the copied strings
	char	**add;//array to hold the split string by spaces
	int		c;
	int		j;
	int		k;

	init_vars(&c, &j, &k);//initialize the variables
	tmp = ft_cp_double_str(strs);//copies the original array to tmp
	add = ft_split(tmp[index], ' ');//splits the string at the index by spaces
	free(strs);
	strs = malloc(sizeof(char *) * (count_strs(tmp) + count_strs(add) + 1));//allocates memory for the new array(original number of strings (aux) + number of new parts inserted (add))
	if (!strs)//if allocation fails
		return (NULL);
	while (c != index)
		strs[k++] = tmp[c++];//copies the strings until the index
	free(tmp[c]);
	while (add[j])
		strs[k++] = add[j++];//copies the new strings
	c++;//skips the original string that was split
	while (tmp[c])
		strs[k++] = tmp[c++];//copy the remaining strings from tmp into strs
	strs[k] = NULL;
	free(tmp);
	free(add);
	return (strs);//returns the new manipulated array
}

/**@brief This function removes empty strings("") from an array of strings.
 * @param strs The array of strings to edit
 * @return The edited array, without empty strings
 */
char	**rm_empty_str(char **strs)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = ft_cp_double_str(strs);//copies the original array to temp
	free(strs);
	strs = (char **)malloc(sizeof(char *) * (count_strs(temp) + 1));//allocates memory for the new array, the "" will be removed when giving NULL to the last element
	if (!strs)
		return (NULL);
	while (temp[i])
	{
		if (ft_strcmp(temp[i], "") != 0)//if the string is not empty
			strs[j++] = temp[i++];//copies it to the new array
		else
			free(temp[i++]);//if the string is empty, free it
	}
	strs[j] = NULL;
	free(temp);
	return (strs);
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
static void	edit_str(char **str)
{
	char	*temp;

	temp = ft_strdup(*str);
	free(*str);
	*str = malloc(sizeof(char) * (ft_strlen(temp) + 1));
	if (!*str)
	{
		free(temp);
		return;
	}
	markers_handler(*str, temp);
	free(temp);
}

/**@brief This function removes all quotes and replaces \1 with $ for every str 
 * in the array.
 * @param strs The array of strings to edit
 * @return The edited array of strings
 */
char	**rm_quotes(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		edit_str(&strs[i]);
		i++;
	}
	return (strs);
}

/**@brief Core of the variable expansion process. 
 * Finds strings needing expansion, performs the expansion,
 * replaces them in the array, removes empty entries and quotes,
 * and returns the final cleaned-up array.
 * @param str The array of strings to expand
 * @return The expanded array of strings
 */
char **expander(char **str)
{
	int		i;
	int		f;//counter for the number of expansions
	char	*sendable;//string to be expanded
	char	*add;//result of the expansion
	char	*expanded;//string with the expansion applied

	f = 0;
	while ((i = need_expansion(str)) != -1)//loops trough the strs and finds the ones needing expansion
	{
		if (i != 0 && ft_strcmp(str[i - 1], "\7\7") == 0)//if the previous string is a heredoc
			break;
		sendable = get_var_name(str[i]);//gets the portion of the string to be expanded
		add = expand_var(sendable);//expands the variable
		expanded = add_expansion(&str[i], add, ft_strlen(sendable));//adds the expansion to the string
		str[i] = expanded;//updates the string in the array
		free(sendable);
		free(add);
		if (str_w_space(str[i]))//"hey there" -> "hey" "there"
			str = split_by_spaces(str, i);
		f++;//increments the number of expansions
	}
	if (f > 0)//if any expansions were made
		str = rm_empty_str(str);//clean up the array by removing empty strings
	return (rm_quotes(str));////removes quotes and replaces \1 with $
}
