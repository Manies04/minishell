/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:54:50 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/20 22:05:57 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/**@brief This function
 * @param fd A pointer to the file descriptors to be initialized.
 * @param current A pointer to the current command.
 * @param exec A pointer to the execution structure.
 * @return Void.
 */
static int	do_multable_builtin(t_commands *current, t_exec *exec)
{
	if (!current->command)
		return (0);//export batata stays only in 1 command so the next command is NULL, for it to have 2 commands it would have to have pipes (|), redirections (>).
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

static int	check_errors(t_exec *exec, int i)
{
	if (msh_inf()->quit)
		return (exit_executor(exec, -1), 1);
	exec->pids[i] = fork();
	if (exec->pids[i] < 0)
		exit_executor(exec, 1);
	return (0);
}

static void	redirect_io(int file, int std)
{
	if (file != -1)
	{
		dup2(file, std);
		close(file);
	}
}

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

/**@brief This is the main function to execute the commands.
 * @param commands A pointer to the commands to be executed.
 * @return Void.
 */
void	executor(t_commands **commands)
{
	t_commands	*current;
	t_exec		exec;

	current = *commands;
	if (do_multable_builtin(current, &exec))
		return;
	exec.pids = malloc(sizeof(int) * msh_inf()->num_of_commands);
	if (!exec.pids)
		return;
	init_fds(&exec.fd, &exec.files);
	exec.next_fd[0] = -1;
	exec.next_fd[1] = -1;
	if (!do_commands(current, &exec))
	{
		free(exec.pids);
		return;
	}
	wait_for_children(&exec, msh_inf()->num_of_commands);
	free(exec.pids);
}