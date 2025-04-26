/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:08:40 by joaoleote         #+#    #+#             */
/*   Updated: 2025/04/25 18:32:50 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_handler_child(int sig)
{
	if (sig == SIGINT)
		msh_inf()->ctrl = 1;
	if (sig == SIGQUIT)
		msh_inf()->sig_quit = 1;
}

void	signal_handler_main(int sig)
{
	if (sig == SIGINT && msh_inf()->interactive)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		msh_inf()->exit_status = 256 * 130;
	}
}

void	signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		printf("\n");
		msh_inf()->quit = 1;
	}
}
