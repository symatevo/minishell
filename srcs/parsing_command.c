/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihovhann <ihovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:19:31 by ihovhann          #+#    #+#             */
/*   Updated: 2022/07/22 13:26:45 by ihovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parsing_final(t_token **tokens, t_var *env_lst)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *tokens;
	tmp2 = tmp;
	while (tmp != 0 && tmp->type != 'p')
	{
		if (tmp2 != tmp && tmp2->type == 'r' && \
				ft_strncmp(tmp2->value, "<<", 3) == 0)
			tmp->type = 'h';
		quote_counting(tmp);
		if (tmp->type != 'h')
			p_expansion(tmp, env_lst);
		tmp2 = tmp;
		tmp = tmp->next;
	}
	word_splitting(tokens, env_lst);
	tmp = *tokens;
	while (tmp != 0 && tmp->type != 'p')
	{
		if (tmp->type != 'r')
			quote_removal(tmp);
		tmp = tmp->next;
	}
}

int	parsing_command(t_token **tokens, t_command *command, t_var **env_lst)
{
	int	i;

	parsing_final(tokens, *env_lst);
	arg_count(tokens, command);
	i = parsing_opers(tokens, command, env_lst);
	if (i == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command->oper_value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		change_status(env_lst, 1);
	}
	if (i == -2)
	{
		change_status(env_lst, 258);
		return (-1);
	}
	if (i == -3)
		change_status(env_lst, 1);
	if (i < 0)
		return (-1);
	return (0);
}
