/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:46:45 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/20 19:30:16 by tiade-al         ###   ########.fr       */
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

static void	fill_expansion(char *result, char *temp, char *add, int size)
{
	int	i;
	int	j;
	int	k;

	init_vars(&i, &j, &k);//initialize i, j and k to 0
	while (temp[k] && temp[k] != '$')//copy chars until the first $
		result[i++] = temp[k++];
	if (temp[k] == '$')//'$' is found
	{
		k++;// Skip the '$'
		if (temp[k] && ((temp[k] >= '0' && temp[k] <= '9') || temp[k] == '?' || temp[k] == '$'))//if the next char is a special case
			k++;// Skip the special case
		else
			k += size;// Skip variable name
	}
	while (add[j])
		result[i++] = add[j++];//copy the expanded value into result
	while (temp[k])
		result[i++] = temp[k++];//copy the rest of the str(temp), after the variable already in result
	result[i] = '\0';
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
	result = malloc(sizeof(char) * (ft_strlen(temp) + ft_strlen(add) + 1));// allocate memory for the new string
	if (!result)//allocation failed
		return (NULL);
	fill_expansion(result, temp, add, size);//fill the result string with the expanded value
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
		return (ft_itoa(msh_inf()->exit_status));
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

/**@brief Copies text before '$' and updates the result string.
 * @param result The result string
 * @param temp Input string
 * @param i Index of '$' or end of string
 * @return Updated result string
 */
static char	*copy_before_dollar(char *result, char *temp, int i)
{
	char	*before;
	char	*new_result;

	before = ft_strndup(temp, i);
	new_result = ft_strjoin(result, before, 0);
	free(result);
	free(before);
	return (new_result);
}

/**@brief Handles variable expansion and updates result string.
 * @param result Current result string
 * @param temp Input string
 * @param i Index after '$'
 * @return Updated result string
 */
static char	*expand_variable(char *result, char *temp, int *i)
{
	char	*var_name;
	char	*var_value;
	char	*new_result;

	var_name = get_var_name(temp + *i);
	if (!var_name || var_name[0] == '\0')
	{
		free(var_name);
		new_result = ft_strjoin(result, "$", 0);
		*i += 1;
	}
	else
	{
		var_value = expand_var(var_name);
		new_result = ft_strjoin(result, var_value, 0);
		*i += 1 + ft_strlen(var_name);
		free(var_value);
		free(var_name);
	}
	free(result);
	return (new_result);
}

/**@brief Appends remaining text after last variable to result.
 * @param result Current result string
 * @param temp Input string
 * @return Updated result string
 */
static char	*append_remaining(char *result, char *temp)
{
	char	*remaining;
	char	*new_result;

	remaining = ft_strdup(temp);
	new_result = ft_strjoin(result, remaining, 0);
	free(result);
	free(remaining);
	return (new_result);
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
