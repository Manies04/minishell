/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:29:18 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/20 16:15:31 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_child(int sig)
{
	if (sig == SIGINT)
		msh_inf()->sig_int = 1;
	if (sig == SIGQUIT)
		msh_inf()->sig_quit = 1;
}

void	sig_for_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		close(0); // closes stdin to break any blocking input reads
		printf("\n"); // mimic shell behavior with a newline
		msh_inf()->quit = 1;
	}
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
