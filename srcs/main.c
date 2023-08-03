/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihovhann <ihovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:19:21 by ihovhann          #+#    #+#             */
/*   Updated: 2022/07/22 14:19:57 by ihovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_status(t_var *env_lst, int *status)
{
	while (env_lst->meaning != '?')
		env_lst = env_lst->next;
	if (env_lst->value != 0)
	{
		if (ft_strncmp(env_lst->value, "exit", 5) == 0)
		{
			*status = env_lst->status;
			return (1);
		}
	}
	return (0);
}

static int	start(int argc, char **argv, char **envp, t_var **env_lst)
{
	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("The program no needs any argument\n", 2);
		return (1);
	}
	signals_init();
	env_to_list(envp, env_lst);
	shlvl(env_lst);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_var			*env_lst;
	t_token			*tokens;
	int				status;

	if (start(argc, argv, envp, &env_lst) == 1)
		return (0);
	while (1)
	{
		line = readline("\033[0;35mMinishell$ \033[0m");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			return (EXIT_SUCCESS);
		}
		if (ft_strncmp(line, "", ft_strlen(line)) != 0)
			add_history(line);
		parsing_line(line, &tokens, &env_lst);
		free(line);
		if (check_status(env_lst, &status) == 1)
			break ;
	}
	lst_clear(&env_lst, &free);
	return (status);
}
