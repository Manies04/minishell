/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:34:14 by tiade-al          #+#    #+#             */
/*   Updated: 2025/04/27 15:58:20 by tiade-al         ###   ########.fr       */
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
		input = readline("~minishell>");
		msh_inf()->interactive = 0;
		if (!input)
			ft_exit(NULL, 0);
		if (*input)
			read_input(input);
	}
}




























/* int main(int argc, char **argv, char **envp)
{
	minishell_init(envp);


	
	while (1)
	{
		msh_inf()->input = readline("~minishell>");//prints "~minishell" and gets outputs what is after it to input
		printf("input: '%s'\n", msh_inf()->input);
		if (!msh_inf()->input)//if NULL
		{
			ft_putstr_fd("exit\n", 2);//EXIT
			break ;
		}
		if (msh_inf()->input && *msh_inf()->input)//this checks if its not null and after it Dereferences the input to check if the insides isnt just a \0 by the user having pressed enter.
		{
			msh_inf()->line_nbr++;//why?
			add_history(msh_inf()->input);//for user to recall comands with the arrow keys
			char **args = ft_split(msh_inf()->input, ' '); // Split input into tokens
			
			
			if (strcmp(args[0], "exit") == 0)
			{
				free(msh_inf()->input);
				break;
			}

			//////////////////////////////////////////////////////dps de parser feito ver se o comando "batata=yes" sozinho da update a batata ja estando no export ou env
			else if (ft_strcmp(args[0], "export") == 0)//Se export, apenas print. Se com mais args adiciona no **export
			{
				printf("\nTesting export\n");
				ft_export(args, 1);  // Pass args directly to ft_export
			}

			
			else if (ft_strcmp(args[0], "env") == 0)
			{
				printf("\n\nENV:\n\n");
				ft_env(args, 1);  // Passing NULL as arg to just print env
			}
			
			
			else if (ft_strcmp(args[0], "unset") == 0 && args[1])
			{
				printf("\n\nUnset: %s\n\n", args[1]);
				ft_unset(args);
			}


			else if (ft_strcmp(args[0], "pwd") == 0)
			{
				printf("\nTesting pwd\n");
				ft_pwd(1);
			}


			else if (ft_strcmp(args[0], "echo") == 0)
			{
				if (args[1] && args[1][0] == '$')
				{
					args[1] = expand_env_vars(args[1]);
					printf("\nTesting echo with expansion\n");
					ft_echo(args, 1);
				}
				else if (args[1] && ft_strcmp(args[1], "-n") == 0 && args[2] && args[2][0] == '$')
				{
					args[2] = expand_env_vars(args[2]);
					printf("\nTesting echo with expansion\n");
					ft_echo(args, 1);
				}
				else
				{
					printf("\nTesting echo\n");
					ft_echo(args, 1);
				}
			}
			else if (ft_strcmp(args[0], "cd") == 0)
			{
				if (args[1] && args[1][0] == '$')
				{
					args[1] = expand_env_vars(args[1]);
					printf("\nTesting cd with expansion\n");
					ft_cd(args, 1);
				}
				else
				{
					printf("\nTesting cd\n");
					ft_cd(args, 1);
				}
			}
			else if (args[0][0] == '$')
				printf("\nTesting expansion\n\n'%s' = '%s'\n", args[0], expand_env_vars(args[0]));
		}
	}
	clean_all();
} */


//gcc -o minishell srcs/*.c srcs/builtins/*.c srcs/init/*.c srcs/utils/*.c srcs/expand/*.c inc/Libft/libft.a -lreadline