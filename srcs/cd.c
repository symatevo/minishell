/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihovhann <ihovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:18:21 by ihovhann          #+#    #+#             */
/*   Updated: 2022/07/22 13:18:22 by ihovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_home(t_var **env_lst, char **path)
{
	t_var	*tmp;

	tmp = *env_lst;
	while (tmp != 0)
	{
		if (ft_strncmp(tmp->name, "HOME", 5) == 0)
		{
			*path = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp == 0)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		change_status(env_lst, 1);
		return (-1);
	}
	return (0);
}

int	cd(t_command *command, t_var **env_lst)
{
	char	*path;
	int		res;

	res = 0;
	if (command->args[1] == 0)
		res = find_home(env_lst, &path);
	else
		path = ft_strdup(command->args[1]);
	if (res == 0)
		res = change_dir(path, env_lst);
	return (res);
}
