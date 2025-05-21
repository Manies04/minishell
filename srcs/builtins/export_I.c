/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_I.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:11:22 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 01:59:06 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief This function prints all the exported variables in "declare -x" 
 * format and sorted.
 * @param env The stored exported variables.
 * @param fd The fd to write to.
 * @return Void.
 */
static void	print_export(char **env, int fd)
{
	int		count;
	char	**env_copy;

	count = 0;
	while (env[count])
		count++;
	env_copy = ft_calloc(sizeof(char *), count + 1);
	if (!env_copy)
		return ;
	copy_env_array(env, env_copy, count);
	sort_env(env_copy, count);
	print_sorted_env(env_copy, fd);
	free_array(env_copy);
}

/**@brief Updates the export array with a new variable, with downgrade 
 * protection.
 * @param key The variable key to update or add.
 * @param new_var The full variable string (key or key=value).
 * @param equal_sign Pointer to the '=' character in new_var, or NULL if absent.
 * @return Void.
 */
void	update_export(char *key, char *new_var, char *equal_sign)
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

/**@brief Main function for the built-in export command. Adds variables to the 
 * export array or prints all exported variables if no arguments are provided.
 * @param arg An array of strings with the variables to add (e.g., ["export", 
 * "KEY=value"]).
 * @param fd The file descriptor to write output or error messages to.
 * @return Void.
 */
void	ft_export(char **arg, int fd)
{
	int	i;

	msh_inf()->exit_status = 0;
	if (!arg[1])
	{
		print_export(msh_inf()->export, fd);
		return ;
	}
	i = 1;
	while (arg[i])
	{
		if (set_env_var(arg[i], fd) != 0)
			msh_inf()->exit_status = 1;
		i++;
	}
}

int	check_errors(t_exec *exec, int i)
{
	if (msh_inf()->quit)
		return (exit_executor(exec, -1), 1);
	exec->pids[i] = fork();
	if (exec->pids[i] < 0)
		exit_executor(exec, 1);
	return (0);
}

/**@brief This function redirects the input and output file descriptors.
 * @param file The file descriptor to redirect.
 * @param std The standard file descriptor to redirect to (STDIN or STDOUT).
 * @return Void.
 */
void	redirect_io(int file, int std)
{
	if (file != -1)
	{
		dup2(file, std);
		close(file);
	}
}
