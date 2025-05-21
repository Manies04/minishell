/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:17:30 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 02:04:03 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief This function handles errors when there are too many arguments.
 * @param arg The arguments passed to the command.
 * @param fd The file descriptor to write to.
 * @return Void.
 */
static void	arg_handle(char **arg, int fd)
{
	write(fd, "env: '", 6);
	write(fd, arg[1], ft_strlen(arg[1]));
	write(fd, "': No such file or directory\n", 30);
	msh_inf()->exit_status = 127;
}

/**@brief This function prints out the environment variable.
 * @param str The string to print.
 * @return Void.
 */
static void	print_env(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

/**@brief This function prints the environment variables.
 * @param arg The arguments passed to the command.
 * @param fd The file descriptor to write to.
 * @return Void.
 */
void	ft_env(char **arg, int fd)
{
	char	**env;

	env = msh_inf()->env;
	if (!env)
	{
		msh_inf()->exit_status = 1;
		return ;
	}
	if (arg[1])
	{
		arg_handle(arg, fd);
		return ;
	}
	while (*env)
		print_env(*env++);
	msh_inf()->exit_status = 0;
}

int	is_builtin(char **command)
{
	if (!ft_strcmp(command[0], "exit"))
		return (1);
	if (!ft_strcmp(command[0], "echo"))
		return (1);
	if (!ft_strcmp(command[0], "pwd"))
		return (1);
	if (!ft_strcmp(command[0], "unset"))
		return (1);
	if (!ft_strcmp(command[0], "export"))
		return (1);
	if (!ft_strcmp(command[0], "cd"))
		return (1);
	if (!ft_strcmp(command[0], "env"))
		return (1);
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
