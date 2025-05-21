/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:46:45 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 02:01:36 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_expansion(char *result, char *temp, char *add, int size)
{
	int	i;
	int	j;
	int	k;

	init_vars(&i, &j, &k);
	while (temp[k] && temp[k] != '$')
		result[i++] = temp[k++];
	if (temp[k] == '$')
	{
		k++;
		if (temp[k] && ((temp[k] >= '0' && temp[k] <= '9') || temp[k] == '?' \
			|| temp[k] == '$'))
			k++;
		else
			k += size;
	}
	while (add[j])
		result[i++] = add[j++];
	while (temp[k])
		result[i++] = temp[k++];
	result[i] = '\0';
}

/**@brief Handles special expansions $? and $$.
 * @param str Variable name ("?" or "$...")
 * @return Expanded value as a new string
 */
static char	*expand_special(char *str)
{
	if (str[0] == '?')
		return (ft_itoa(msh_inf()->exit_status));
	if (str[0] == '$')
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
	if (ft_strcmp(str, "0") == 0)
		return (ft_strdup("minishell"));
	if (str[0] == '?' || str[0] == '$')
		return (expand_special(str));
	while (env[++i])
	{
		key = get_env_key(env[i]);
		if (ft_strcmp(key, str) == 0)
		{
			free(key);
			return (ft_strdup(ft_strchr(env[i], '=') + 1));
		}
		free(key);
	}
	return (ft_strdup(""));
}

/**@brief Copies text before '$' and updates the result string.
 * @param result The result string
 * @param temp Input string
 * @param i Index of '$' or end of string
 * @return Updated result string
 */
char	*copy_before_dollar(char *result, char *temp, int i)
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
char	*expand_variable(char *result, char *temp, int *i)
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
