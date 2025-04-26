/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:30:57 by joaoleote         #+#    #+#             */
/*   Updated: 2025/04/26 11:49:26 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_msh	*msh_inf(void)
{
	static t_msh	msh;

	return (&msh);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;

	(void)av;
	msh_inf()->pid = get_process;
	if (ac != 1 && ac != 3)
		return (write(1, "wrong arguments\n", 17));
	get_env(envp);
	while (1)
	{
		signal(SIGINT, signal_handler_main);
		signal(SIGQUIT, SIG_IGN);
		msh_inf()->interactive = 1;
		input = readline("minishell>");
		msh_inf()->interactive = 0;
		if (!input)
			ft_exit(NULL, 0);
		if (*input)
			read_input(input);
	}
}
