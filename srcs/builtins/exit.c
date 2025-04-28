/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:46:22 by tiade-al          #+#    #+#             */
/*   Updated: 2025/04/27 23:20:57 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 
void	exitwcode(int exit_code)
{
	clean_all();//to be made!!!!!!!!!!!!!!!!!!!!
	exit(exit_code);//exits
}

int	get_exit_code(long long num)
{
	int	code;
	//unsigned is to take out the risk of when we get a negative number so we dont end up with a negative one after the operation bellow
	code = (unsigned long long)num % 256;//256 cause of 0 if code 255/255 = 0 so we need +1(256)
	return (code);
}
*/

/**@brief This function checks if the string is a valid numeric string.
 * @param str The string to check.
 * @return True if the string is numeric, false otherwise.
 */
/* 
bool	inside_llong(char *str)
{
	long long	num;
	long long	limit;
	int			sign;

	sign = 1;//positive num
	limit = LLONG_MAX / 10;  // Gives the Largest Safe nbr Before Multiplication (x10)
	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)// Skip whitespace
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;//turns negative
		str++;
	}
	while (*str >= '0' && *str <= '9')//while a num
	{
		if (num > limit || (num == limit && (*str - '0') > LLONG_MAX % 10 + (sign == -1)))//if num is greater than limit || num==limit and the next digit is bigger than the last number on llong_max or min, depending on the result of (sign == -1) 0 if positive, else == 1.
			return (false);  // Overflow check
		num = num * 10 + (*str - '0');//updates num
		str++;
	}
	return (true);
}
 */

/**@brief This function exits the shell program with a specified exit code.
 * @param args The arguments passed to the exit command.
 * @return Void.
 */
/* 
void	ft_exit(char **args)
{
	long long	num;
	int			exit_code;

	write(2, "exit\n", 5);
	if (!args[1])//if only "exit"
	{
		exitwcode(0);//clean everything, exit with 0
	}
	if (args[2] && ft_is_numeric(args[1]))//if after exit there is a number and there is text after
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	if (!ft_is_numeric(args[1]) || !inside_llong(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exitwcode(2);
	}
	num = ft_atoll(args[1]);//converts string to long long
	exit_code = get_exit_code(num);//function calculate code for exit(num)
	exitwcode(exit_code);
}
 */
/* exit_func is a function that handles the exit command in a shell program.
It takes an array of strings (args) as input, which represents the command and its arguments. The function performs the following tasks:
1. It prints "exit" to the standard error output.
2. If no arguments are provided, it calls the exitwcode function with an exit code of 0, indicating a successful exit.
3. If there are more than two arguments(exit 123 batata), it prints an error message indicating that there are too many arguments.
4. If the first argument is not a valid numeric string or if it exceeds the limits of a long long integer, it prints an error message indicating that a numeric argument is required and calls exitwcode with an exit code of 2.
5. If the first argument is a valid numeric string, it converts it to a long long integer using the ft_atoll function.
6. It calculates the exit code using the get_exit_code function, which ensures that the exit code is within the range of 0 to 255.
7. Finally, it calls the exitwcode function with the calculated exit code to terminate the program.

Use $? to get the exit code of the last command executed.
exit codes go from 0 to 255.
 */












static void	exitwcode(int exit_code)//FIXME is only this to free?
{
	free_structs(); // Free all allocated memory
/* 	free_env(msh_inf()->env); //TODO Free environment
	if (msh_inf()->commands)
		free_commands(msh_inf()->commands); // Free commands */
	rl_clear_history(); // Clear readline history
	exit(exit_code);
}

// Normalize exit code to 0–255
static int	get_exit_code(long long num)
{
	int	code;
	code = (unsigned long long)num % 256; // Normalize to 0–255
	return (code);
}

// Check if string is a valid numeric string within long long bounds
static bool	inside_llong(char *str)
{
	long long	num;
	long long	limit;
	int			sign;
	
	num = 0;
	limit = LLONG_MAX / 10;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32) // Skip whitespace
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (num > limit || (num == limit && (*str - '0') > LLONG_MAX % 10 + (sign == -1)))
			return (false); // Overflow check
		num = num * 10 + (*str - '0');
		str++;
	}
	return (*str == '\0'); // Ensure no trailing characters
}

/**
 * @brief Exits the shell with a specified or provided exit code, handling cleanup and validation.
 * @param command The arguments passed to the exit command (e.g., {"exit", "42", NULL}).
 * @param status A provided exit code to use when no arguments are given or as needed.
 * @return Void (exits) or returns on error (too many arguments).
 */
void	ft_exit(char **command, long status)
{
	long long	num;
	int			exit_code;

	printf("exit\n"); // Print "exit" to stdout, matching Bash
	if (!command || !command[1]) // No argument: exit with provided status (normalized)
	{
		exit_code = get_exit_code(status);
		exitwcode(exit_code);
	}
	if (command[2] && ft_is_numeric(command[1])) // Too many arguments with valid first arg
	{
		print_error("", "too many arguments\n");
		msh_inf()->exit_status = 1; // Set exit_status to 1 (Bash convention for errors)
		return;
	}
	if (!ft_is_numeric(command[1]) || !inside_llong(command[1])) // Invalid numeric argument
	{
		print_error(command[1], ": numeric argument required\n");
		exitwcode(2);
	}
	num = ft_atoll(command[1]); // Convert to long long
	exit_code = get_exit_code(num); // Normalize exit code
	exitwcode(exit_code);
}