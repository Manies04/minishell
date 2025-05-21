/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_III.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:21:57 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 02:00:51 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief This function replaces a string at a given index in a string array 
 * with the result of splitting that string by spaces, while preserving the 
 * rest of the array.
 * @param strs The array of strings to manipulate
 * @param start The index of the string to manipulate
 * @return The manipulated array of strings
 */
char	**split_by_spaces(char **strs, int index)
{
	char	**tmp;
	char	**add;
	int		c;
	int		j;
	int		k;

	init_vars(&c, &j, &k);
	tmp = ft_cp_double_str(strs);
	add = ft_split(tmp[index], ' ');
	free(strs);
	strs = malloc(sizeof(char *) * (count_strs(tmp) + count_strs(add) + 1));
	if (!strs)
		return (NULL);
	while (c != index)
		strs[k++] = tmp[c++];
	free(tmp[c]);
	while (add[j])
		strs[k++] = add[j++];
	c++;
	while (tmp[c])
		strs[k++] = tmp[c++];
	strs[k] = NULL;
	free(tmp);
	free(add);
	return (strs);
}

/**@brief Expands all variables (starting with $) in a heredoc input string.
 * @param str Pointer to the input string (will be modified)
 * @return Void
 */
void	expand_heredoc(char **str)
{
	char	*input;
	char	*result;
	char	*temp;
	int		i;

	input = *str;
	result = ft_strdup("");
	temp = input;
	i = -1;
	if (!input || !result)
		return ;
	while (temp[++i])
	{
		if (temp[i] == '$')
		{
			result = copy_before_dollar(result, temp, i);
			result = expand_variable(result, temp, &i);
			temp += i;
			i = 0;
		}
	}
	if (i > 0)
		result = append_remaining(result, temp);
	free(*str);
	*str = result;
}

/**@brief This function extracts the key (name part) from a variable string.
 * @param variable The variable string (e.g., "PATH=/usr/bin")
 * @return The key part of the variable (e.g., "PATH")
 */
char	*get_env_key(char *variable)
{
	char	*env_key;

	if (ft_strchr(variable, '='))
		env_key = ft_strndup(variable, ft_strchr(variable, '=') - variable);
	else
		env_key = ft_strndup(variable, ft_strlen(variable));
	return (env_key);
}

/**@brief This function extracts the variable name (after '$').
 * @param str The string to extract from the variable name from
 * @return The variable name (e.g., "PATH", "HOME", etc.)
 */
char	*get_var_name(char *str)
{
	char	*sendable;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sendable = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!sendable)
		return (NULL);
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$')
		i++;
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_' || \
		ft_isdigit(str[i])))
		sendable[j++] = str[i++];
	if (j == 0 && str[i] && (str[i] == '?' || str[i] == '$' || str[i] == '0'))
		sendable[j++] = str[i++];
	sendable[j] = '\0';
	return (sendable);
}

/**@brief This function replaces a variable (starting with $) in a string with 
 * its expanded value
 * @param str The string to manipulate
 * @param add The string to add(expansion)
 * @param size The size of the variable name
 * @return The string with the variable replaced with its value
 */
char	*add_expansion(char **str, char *add, int size)
{
	char	*temp;
	char	*result;

	temp = *str;
	if (!temp || !add)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(temp) + ft_strlen(add) + 1));
	if (!result)
		return (NULL);
	fill_expansion(result, temp, add, size);
	free(temp);
	*str = result;
	return (result);
}
