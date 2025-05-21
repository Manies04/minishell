/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:46:22 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 02:03:44 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief This function handles the exit code and frees arrays/command.
 * @param exit_code The exit code to use.
 * @return Void.
 */
static void	exitwcode(int exit_code)
{
	if (msh_inf()->env)
	{
		free_array(msh_inf()->env);
		msh_inf()->env = NULL;
	}
	if (msh_inf()->export)
	{
		free_array(msh_inf()->export);
		msh_inf()->export = NULL;
	}
	if (msh_inf()->commands)
		free_commands(msh_inf()->commands);
	rl_clear_history();
	exit(exit_code);
}

/**@brief This function normalizes the exit code to be within the range
 *  of 0-255.
 * @param num The number to normalize.
 * @return The normalized exit code.
 */
static int	get_exit_code(long long num)
{
	int	code;

	code = (unsigned long long)num % 256;
	return (code);
}

/**@brief This function checks if a string is a valid numeric string within 
 * long long bounds.
 * @param str The string to check.
 * @return True if the string is a valid numeric string, false otherwise.
 */
static bool	inside_llong(char *str)
{
	long long	num;
	long long	limit;
	int			sign;

	num = 0;
	limit = LLONG_MAX / 10;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (num > limit || (num == limit && (*str - '0') > LLONG_MAX % 10 \
			+ (sign == -1)))
			return (false);
		num = num * 10 + (*str - '0');
		str++;
	}
	return (*str == '\0');
}

/**@brief Exits the shell with a specified or provided exit code, handling 
 * cleanup and validation.
 * @param command The arguments passed to the exit command (e.g., {"exit", 
 * "42", NULL}).
 * @param status A provided exit code to use when no arguments are given or
 *  as needed.
 * @return Void (exits) or returns on error (too many arguments).
 */
void	ft_exit(char **command, long status)
{
	long long	num;
	int			exit_code;

	printf("exit\n");
	if (!command || !command[1])
	{
		exit_code = get_exit_code(status);
		exitwcode(exit_code);
	}
	if (command[2] && ft_is_numeric(command[1]))
	{
		print_error("", "too many arguments\n");
		msh_inf()->exit_status = 1;
		return ;
	}
	if (!ft_is_numeric(command[1]) || !inside_llong(command[1]))
	{
		print_error(command[1], ": numeric argument required\n");
		exitwcode(2);
	}
	num = ft_atoll(command[1]);
	exit_code = get_exit_code(num);
	exitwcode(exit_code);
}

/**@brief This function is used to print the arguments passed to it.
 * @param cmd The list of commands.
 * @param fd The file descriptor to write to.
 * @return Void.
 */
void	ft_echo(char **cmd, int fd)
{
	int		i;
	bool	nflag;

	i = 1;
	nflag = false;
	if (cmd[1] && echonflag(cmd[1]))
	{
		nflag = true;
		i++;
	}
	while (cmd[i] && echonflag(cmd[i]))
		i++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		if (cmd[i + 1] != NULL)
			write(fd, " ", 1);
		i++;
	}
	if (!nflag)
		write(fd, "\n", 1);
	msh_inf()->exit_status = 0;
}
