/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihovhann <ihovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:18:27 by ihovhann          #+#    #+#             */
/*   Updated: 2022/07/22 13:18:29 by ihovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *str)
{
	char	*tmp;
	char	*err;

	tmp = ft_strjoin(str, "': not a valid identifier\n");
	err = ft_strjoin("Minishell: '", tmp);
	free(tmp);
	ft_putstr_fd(err, 2);
	free(err);
}

int	check_var_name(char *str, int *res, t_var **env_lst)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (i == 0 && ((str[0] == '_') || (str[0] >= 'a' && str[0] <= 'z') || \
				(str[0] >= 'A' && str[0] <= 'Z')))
			continue ;
		else if (i != 0 && ((str[i] >= 48 && str[i] <= 57) || \
				(str[i] >= 'a' && str[i] <= 'z') || \
				(str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_')))
			continue ;
		else
		{
			print_error(str);
			change_status(env_lst, 1);
			*res = 1;
			return (1);
		}
	}
	return (0);
}
