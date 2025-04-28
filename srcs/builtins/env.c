/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:17:30 by tiade-al          #+#    #+#             */
/*   Updated: 2025/04/27 14:21:28 by tiade-al         ###   ########.fr       */
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
	msh_inf()->exit_status = 127;//If a command is not found, the child process created to execute it returns a status of 127
}

/**@brief This function prints out the environment variable.
 * @param str The string to print.
 * @return Void.
 */
static void	print_env(char *str)
{
	write(1, str, ft_strlen(str)); // Print the full string (e.g., "batata=" or "batata")
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
	if (!env) // If env is empty
	{
		msh_inf()->exit_status = 1;
		return;
	}
	if (arg[1]) // It's not supposed to be more than "env"
	{
		arg_handle(arg, fd);//error handling
		return;
	}
	while (*env) // Print all env vars
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
/*
env is a builtin command that prints the current environment variables and
only takes one argument, which is the name of the variable to print. If no
arguments are given, it prints all environment variables. If an invalid 
argument is given, it prints an error message and sets the exit status to 127.
*/