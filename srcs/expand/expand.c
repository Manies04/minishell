/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:46:45 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/07 01:45:10 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief This function extracts the key (name part) from a variable string.
 * @param variable The variable string (e.g., "PATH=/usr/bin")
 * @return The key part of the variable (e.g., "PATH")
 */
char	*get_env_key(char *variable)
{
	char	*env_key;
	if (ft_strchr(variable, '='))// if the variable has an equal sign
		env_key = ft_strndup(variable, ft_strchr(variable, '=') - variable);//get the part before the equal sign ("PATH=/usr/bin" -> "PATH")
	else
		env_key = ft_strndup(variable, ft_strlen(variable));//duplicate the whole variable
	return (env_key);
}

/**@brief This function extracts the variable name (after '$').
 * @param str The string to extract from the variable name from
 * @return The variable name (e.g., "PATH", "HOME", etc.)
 */
char	*get_var_name(char *str)
{
	char	*sendable;//string to hold the variable name
	int		i;
	int		j;

	i = 0;
	j = 0;
	sendable = malloc(sizeof(char) * (ft_strlen(str) + 1));//allocate memory for the variable name
	if (!sendable)//allocation failed
		return (NULL);
	while (str[i] && str[i] != '$')//skip to the first $
		i++;
	if (str[i] == '$')//move past the $
		i++;
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_' || ft_isdigit(str[i])))//copies chars that are valid into sendable(letter, digit or "_")
		sendable[j++] = str[i++];
	if (j == 0 && str[i] && (str[i] == '?' || str[i] == '$' || str[i] == '0'))// if no char was copied and the next char is a special case, copy it
		sendable[j++] = str[i++]; // Handles $?, $$, $0 cases
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
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	temp = *str;
	if (!temp || !add)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(temp) + ft_strlen(add) + 1));// allocate memory for the new string
	if (!result)//allocation failed
		return (NULL);
	while (temp[k] && temp[k] != '$')//copy chars until the first $
		result[i++] = temp[k++];
	if (temp[k] == '$')//'$' is found
	{
		k++; // Skip the '$'
		if (temp[k] && ((temp[k] >= '0' && temp[k] <= '9') || temp[k] == '?' || temp[k] == '$'))//if the next char is a special case
			k++; // Skip the special case
		else
			k += size; // Skip variable name
	}
	while (add[j])
		result[i++] = add[j++];//copy the expanded value into result
	while (temp[k])
		result[i++] = temp[k++];//copy the rest of the str(temp), after the variable already in result
	result[i] = '\0';
	free(temp);
	*str = result;//update the pointer
	return (result);
}

/**@brief Handles special expansions $? and $$.
 * @param str Variable name ("?" or "$...")
 * @return Expanded value as a new string
 */
static char	*expand_special(char *str)
{
	if (str[0] == '?')//$?
		return (ft_itoa(msh_inf()->exit_status / 256));
	if (str[0] == '$')//$$
		return (ft_itoa(msh_inf()->pid));
	return (ft_strdup(""));
}

/**@brief Expands a variable name (after $) into its value.
 * @param str Variable name (e.g., "HOME", "?", "$")
 * @return Expanded value as a new string, or "" if not found
 */
char	*expand_var(char *str)
{
	char	**env;
	char	*key;
	int		i;

	i = -1;
	env = msh_inf()->env;
	if (ft_strcmp(str, "0") == 0)//$0 case
		return (ft_strdup("minishell"));
	if (str[0] == '?' || str[0] == '$')//$? $$ cases
		return (expand_special(str));
	while (env[++i])
	{
		key = get_env_key(env[i]);//get the key from the env variable
		if (ft_strcmp(key, str) == 0)//compares it with variable name
		{
			free(key);
			return (ft_strdup(ft_strchr(env[i], '=') + 1));//returns the value of the variable if found
		}
		free(key);
	}
	return (ft_strdup(""));//if not found, return empty string
}

/**@brief This function replaces all \10 with $ in the string.
 * @param str The string to manipulate
 * @return Void
 */
void	marker_to_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\10')
			str[i] = '$';
		i++;
	}
}

/**@brief This function expands the heredoc string by replacing all variables with their values and the reverts the marker \10 to $.
 * @param str The string to manipulate
 * @return Void
 */
void	expand_heredoc(char **str)
{
	char	*expanded;

	expanded = expand_env_vars(*str);//expand the string
	marker_to_dollar(expanded);//replace \10 with $
	free(*str);
	*str = expanded;
}

/**@brief Expands environment variables in a string, skipping single-quoted 
 * sections.
 * @param str The string to expand
 * @return Expanded string
 */
char	*expand_env_vars(const char *str)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	char	*temp;
	int		i;

	i = 0;
	result = ft_strdup(str);
	while (result[i])//loop through the string
	{
		if (result[i++] == '\5') // Skip single-quoted sections
			while (result[i] && result[i] != '\5')
				i++;
		else if (result[i] == '$' && result[i + 1] && !is_whitespace(result[i + 1]))//if a $ is found and the next char is not a white space
		{
			var_name = get_var_name(result + i); // Extract variable name
			var_value = expand_var(var_name); // Get value
			temp = result;
			result = add_expansion(&temp, var_value, ft_strlen(var_name)); // Replace variable with value
			free(temp);
			free(var_name);
			free(var_value);
			i = 0; // Restart to check for more expansions
		}
		else
			i++;//move to the next char
	}
	return (result);
}
