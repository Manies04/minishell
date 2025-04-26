/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:06:52 by joaoleote         #+#    #+#             */
/*   Updated: 2025/04/25 16:01:16 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	splitted = ft_split(command, SPACE_MARKER);
	splitted = expander(splitted);
	new->greater_than = get_great(splitted);
	new->less_than = get_less(splitted);
	new->gt_files = get_output_files(splitted);
	new->lt_files = get_input_files(splitted, LESS_MARKER);
	new->heredocs = get_input_files(splitted, LESSER_MARKER);
	new->command = get_commmand(splitted);
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
	if (!ft_strchr(input, PIPE_MARKER))
		add_next_command(&msh_inf()->commands, input);
	else
	{
		splitted = ft_split(input, PIPE_MARKER);
		while (splitted[i])
			add_next_command(&msh_inf()->commands, splitted[i++]);
		free_double_array(splitted);
	}
	if (i == 0)
		i = 1;
	msh_inf()->num_of_commands = i;
}
