/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:46:45 by tiade-al          #+#    #+#             */
/*   Updated: 2025/04/19 12:36:38 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief This function checks if the string contains a "$" followed by a 
 * non-space character.
 * @param str The string to check
 * @return true if the string contains a "$" followed by a non-space character
 */
static int	is_expansion_needed(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '$')//if the str has a $ and there is another char and the next char is not a space or another $.
			return (1);//normal case
		else if (str[i] == '$' && str[i + 1] && str[i + 1] == '$')//if the str has a $ and there is another char and the next char is a $.
			return (2);//"$$" case, we need to check if the next char is a space or another $. in the next function we check the amount of "$" and if there are odd or even to print the right amount of pid.
		else if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')//if the str has a $ and there is another char and the next char is a ? (exit status).
			return (3);//"$?" case.
	}
	return (0);
}

/**@brief Handles special expansions $? and $$.
 * @param str Variable name ("?" or "$...")
 * @return Expanded value as a new string
 */
static char *expand_special(char *str)
{
	int		pid;
	int		count;
	char	*pid_str;
	char	*result;
	char	*temp;

	if (str[0] == '?')
		return (ft_itoa(msh_inf()->exit_status));//exit status returned for "$?"
	if (str[0] != '$')
		return (ft_strdup(""));//if here by mistake
	count = 0;
	while (str[count] == '$')//"$$"
		count++;
	count = (count + 1) / 2;//adds one cause we started in str+1, then divides cause we need them to be in pairs of 2
	pid = getpid();
	pid_str = ft_itoa(pid);
	result = ft_strdup("");
	while (count-- > 0)//while we have pairs
	{
		temp = result;
		result = ft_strjoin(temp, pid_str, 0);//join the pids
		free(temp);
	}
	free(pid_str);
	return (result);
}

/**@brief Expands a variable name (after $) into its value.
 * @param str Variable name (e.g., "HOME", "?", "$")
 * @return Expanded value as a new string, or "" if not found
 */
static char	*expand_var(char *str)
{
	char	**env;
	char	*value;
	int		i;

	if (str[0] == '?' || str[0] == '$')
		return (expand_special(str));//expecial type
	env = msh_inf()->env;
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], str, ft_strchr(env[i], '=') - env[i]) == 0
			&& ft_strlen(str) == (size_t)(ft_strchr(env[i], '=') - env[i]))//Compares str with the key portion of env[i] (up to the =) and ensures str’s length exactly matches the key’s length.
		{
			value = ft_strdup(ft_strchr(env[i], '=') + 1);//copies the value part skipping "="
			return (value);
		}
	}
	return (ft_strdup(""));
}

/**@brief Expands environment variables in a string.
 * @param str The string to expand
 * @return Expanded string
 */
char *expand_env_vars(const char *str)
{
	int		type;//what type of expansion (0 = none, 1 = normal, 2 = $$, 3 = $?)
	char	*var_value;//Value of the var
	char	*result;//final str
	char	*temp;

	type = is_expansion_needed(str);//checks what type of expansion is needed
	if (type == 0)
		return (ft_strdup(str));//return as is
	var_value = expand_var((char *)str + 1);//gets the var value, sending str + 1 so it skips the "$" at 1st position
	if (ft_strlen(str) == ft_strlen(str + 1) + 1)
		return (var_value);
	temp = ft_substr(str, 0, ft_strchr(str, '$') - str);//extracts the prefix of the str (whats before the "$")
	result = ft_strjoin(temp, var_value, 0);//Combines the prefix and the expanded variable value. 
	free(temp);
	temp = result;
	result = ft_strjoin(temp, str + ft_strlen(str + 1) + 1, 0);
	free(temp);
	free(var_value);
	return (result);
}

