/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:54:50 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 01:50:53 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief Checks and executes specific built-in commands that can run without 
 * forking if there's no pipeline.
 * @param current Structure containing the command data, including the command 
 * array.
 * @param exec Structure with execution variables, including file descriptors
 *  for redirection.
 * @return 1 if a built-in command was executed, 0 otherwise.
 */
static int	do_multable_builtin(t_commands *current, t_exec *exec)
{
	if (!current->command)
		return (0);
	if (!current->next && \
		(!ft_strcmp(current->command[0], "exit") || \
		!ft_strcmp(current->command[0], "export") || \
		!ft_strcmp(current->command[0], "unset") || \
		!ft_strcmp(current->command[0], "cd")))
	{
		exec->files[0] = input_redirect(current, exec);
		exec->files[1] = output_redirect(current, exec);
		executor_router(current->command, exec);
		close_pipe_ends(exec->files);
		return (1);
	}
	else
		return (0);
}

/**@brief Executes a command in a child process, handling redirections and 
 * pipes.
 * @param current Structure containing the command data, including the command
 *  array.
 * @param exec Structure with execution variables, including file descriptors 
 * for pipes and redirections.
 * @return Void. Exits the child process with the global exit status or a 
 * specific error code.
 */
static void	child_routine(t_commands *current, t_exec *exec)
{
	if (exec->files[0] == -2 || exec->files[1] == -2)
		exit(1);
	if (exec->next_fd[1] != -1)
	{
		dup2(exec->next_fd[1], STDOUT_FILENO);
		close(exec->next_fd[1]);
	}
	redirect_io(exec->fd[0], STDIN_FILENO);
	redirect_io(exec->files[0], STDIN_FILENO);
	redirect_io(exec->files[1], STDOUT_FILENO);
	close_pipe_ends(exec->next_fd);
	close_pipe_ends(exec->fd);
	executor_router(current->command, exec);
	exit(msh_inf()->exit_status);
}

/**@brief Processes and forks commands, setting up pipes and redirections for 
 * execution.
 * @param current Structure containing the command data, including the command 
 * array.
 * @param exec Structure with execution variables, including process IDs and 
 * file descriptors.
 * @return 1 if commands are executed successfully, 0 if an error occurs (e.g.,
 *  pipe or fork failure).
 */
static int	do_commands(t_commands *current, t_exec *exec)
{
	int	i;

	i = 0;
	while (current)
	{
		signal(SIGINT, signal_handler_child);
		init_fds(&exec->next_fd, &exec->files);
		if (current->next)
			if (pipe(exec->next_fd) < 0)
				return (exit_executor(exec, 1), 0);
		exec->files[0] = input_redirect(current, exec);
		exec->files[1] = output_redirect(current, exec);
		if (check_errors(exec, i))
			return (0);
		if (exec->pids[i++] == 0)
			child_routine(current, exec);
		close_pipe_ends(exec->fd);
		close_pipe_ends(exec->files);
		exec->fd[0] = exec->next_fd[0];
		exec->fd[1] = exec->next_fd[1];
		current = current->next;
	}
	return (close_pipe_ends(exec->next_fd), 1);
}

/**@brief Waits for child processes to complete and updates the global exit 
 * status.
 * @param exec Structure with execution variables, including the array of 
 * process IDs.
 * @param num_commands The number of commands (and child processes) to wait
 *  for.
 * @return Void.
 */
static void	wait_for_children(t_exec *exec, int num_commands)
{
	int	i;
	int	status;

	i = 0;
	while (i < num_commands)
	{
		waitpid(exec->pids[i++], &status, 0);
		msh_inf()->exit_status = (status >> 8) & 0xFF;
		if (msh_inf()->sig_int)
			msh_inf()->exit_status = 130;
		else if (msh_inf()->sig_quit)
			msh_inf()->exit_status = 131;
		msh_inf()->sig_int = 0;
		msh_inf()->sig_quit = 0;
	}
}

/**@brief Main function to execute commands, handling built-ins and forking for
 *  external commands.
 * @param commands A pointer to the linked list of commands to be executed.
 * @return Void.
 */
void	executor(t_commands **commands)
{
	t_commands	*current;
	t_exec		exec;

	current = *commands;
	if (do_multable_builtin(current, &exec))
		return ;
	exec.pids = malloc(sizeof(int) * msh_inf()->num_of_commands);
	if (!exec.pids)
		return ;
	init_fds(&exec.fd, &exec.files);
	exec.next_fd[0] = -1;
	exec.next_fd[1] = -1;
	if (!do_commands(current, &exec))
	{
		free(exec.pids);
		return ;
	}
	wait_for_children(&exec, msh_inf()->num_of_commands);
	free(exec.pids);
}
