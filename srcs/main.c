/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:34:14 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/06 23:11:31 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;

	(void)av;
	minishell_init(envp);
	msh_inf()->pid = get_process();
	if (ac != 1 && ac != 3)
		return (write(1, "wrong arguments\n", 17));
	while (1)
	{
		signal(SIGINT, signal_handler_main);
		signal(SIGQUIT, SIG_IGN);
		msh_inf()->interactive = 1;
		input = readline("~minishell> ");
		msh_inf()->interactive = 0;
		if (!input)
			ft_exit(NULL, 0);
		if (*input)
			read_input(input);
	}
}

/* 
" > file " instead of creating a file with nothing on it, writes "exit"
 heredoc not working well, skips after 1st input from user
 */


//gcc -o minishell srcs/*.c srcs/builtins/*.c srcs/init/*.c srcs/utils/*.c srcs/expand/*.c srcs/execution/*.c srcs/parsing/*.c inc/Libft/libft.a -lreadline