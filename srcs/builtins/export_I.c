/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_I.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:11:22 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/14 13:11:29 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//there is no "" after =

/**@brief This function uses Bubble sort implementation for sorting the cpy of env array
 * @param env The copy of env.
 * @param size The end of the list.
 * @return Void.
 */
static void	sort_env(char **env, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

/**@brief This function prints all the exported variables in "declare -x" 
 * format and sorted.
 * @param env The stored exported variables.
 * @param fd The fd to write to.
 * @return Void.
 */
static void	print_export(char **env, int fd)
{
	int count;//keeps track of how many variables there are
	char **env_copy;//a to be copy of the variables

	count = 0;
	while (env[count])
		count++;
	env_copy = ft_calloc(sizeof(char *), count + 1);//allocating memory
	if (!env_copy)
		return;
	copy_env_array(env, env_copy, count);//creates a dup of the list
	sort_env(env_copy, count);//Bubble sort the cpy
	print_sorted_env(env_copy, fd);// prints 
	free_array(env_copy);
}

// Find index of an environment variable by key
static int env_find(char *key, char **env)
{
	int i = 0;
	int len = ft_strlen(key);

	while (env[i])
	{
		// Match key up to its length, followed by '=' or end of string
		if (ft_strncmp(env[i], key, len) == 0 && (env[i][len] == '=' || env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

/* Sets key and new_var based on arg */
static int	init_env_var(char *arg, char **key, char **new_var, char **equal_sign)
{
	*equal_sign = ft_strchr(arg, '=');
	if (*equal_sign)
	{
		*key = ft_substr(arg, 0, *equal_sign - arg);
		if (!*key)
			return (-1);
		*new_var = ft_strdup(arg);
	}
	else
	{
		*key = ft_strdup(arg);
		if (!*key)
			return (-1);
		*new_var = ft_strdup(arg);
	}
	if (!*new_var)
	{
		free(*key);
		return (-1);
	}
	return (0);
}

/* Updates export array with downgrade protection */
static void	update_export(char *key, char *new_var, char *equal_sign)
{
	int	index;

	index = env_find(key, msh_inf()->export);
	if (index >= 0)
	{
		if (ft_strchr(msh_inf()->export[index], '=') && !equal_sign)
			return ;
		free(msh_inf()->export[index]);
		msh_inf()->export[index] = ft_strdup(new_var);
	}
	else
		add_new_env_var(new_var, &msh_inf()->export);
}

/* Updates env array if '=' is present */
static void	update_env(char *key, char *new_var, char *equal_sign)
{
	int	index;

	if (!equal_sign)
		return ;
	index = env_find(key, msh_inf()->env);
	if (index >= 0)
	{
		free(msh_inf()->env[index]);
		msh_inf()->env[index] = ft_strdup(new_var);
	}
	else
		add_new_env_var(new_var, &msh_inf()->env);
}

static int set_env_var(char *arg, int fd)//begins here 1st
{
	char	*equal_sign;
	char	*key;
	char	*new_var;

	if (init_env_var(arg, &key, &new_var, &equal_sign) < 0)
		return (1);
	if (!is_valid_identifier(key))
	{
		free(key);
		free(new_var);
		return (handle_invalid_identifier(arg, fd, equal_sign));
	}
	update_export(key, new_var, equal_sign);
	update_env(key, new_var, equal_sign);
	free(key);
	free(new_var);
	return (0);
}

/**@brief This is the main func to the buil-in export, if it has args it adds them to exported vars, if just "export" prints them all..
 * @param arg An array of strings with the variables to add.
 * @param fd The fd to write to.
 * @return Void.
 */
void ft_export(char **arg, int fd)
{
	int	i;

	msh_inf()->exit_status = 0;

	if (!arg[1]) // No arguments: print all export vars sorted
	{
		print_export(msh_inf()->export, fd); // Use export instead of env
		return;
	}
	i = 1;
	while (arg[i]) // If "export +arg" creates new export
	{
		if (set_env_var(arg[i], fd) != 0)
			msh_inf()->exit_status = 1; // Error occurred, continue processing
		i++;
	}
}
