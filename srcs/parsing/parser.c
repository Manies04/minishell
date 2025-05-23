/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:06:52 by joaoleote         #+#    #+#             */
/*   Updated: 2025/05/21 01:52:58 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief Create and allocate the command data.
 * @param command the user command splitted.
 * @return new command struct node.
 */
static t_commands	*new_command(char *command)
{
	char		**splitted;
	t_commands	*new;

	new = malloc(sizeof(t_commands));
	if (!new)
		return ((void *)0);
	splitted = ft_split(command, '\2');
	splitted = expander(splitted);
	new->output = get_great(splitted);
	new->input = get_less(splitted);
	new->outfiles = get_output_files(splitted);
	new->infiles = get_input_files(splitted, "\7");
	new->heredocs = get_input_files(splitted, "\7\7");
	new->command = get_command(splitted);
	new->next = (void *)0;
	free_double_array(splitted);
	return (new);
}

/**@brief Adds the command node to the linked list.
 * @param lst First element of the list.
 * @param command the command to stract the data.
 */
static void	add_next_command(t_commands **lst, char *command)
{
	t_commands	*current;

	if (!(*(lst)))
	{
		*(lst) = new_command(command);
		return ;
	}
	current = *(lst);
	while (current->next)
		current = current->next;
	current->next = new_command(command);
}

void	parser(char *input)
{
	char	**splitted;
	int		i;

	i = 0;
	if (!ft_strchr(input, '\3'))
		add_next_command(&msh_inf()->commands, input);
	else
	{
		splitted = ft_split(input, '\3');
		while (splitted[i])
			add_next_command(&msh_inf()->commands, splitted[i++]);
		free_double_array(splitted);
	}
	if (i == 0)
		i = 1;
	msh_inf()->num_of_commands = i;
}
