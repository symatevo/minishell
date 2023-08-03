/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihovhann <ihovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:19:58 by ihovhann          #+#    #+#             */
/*   Updated: 2022/07/22 13:19:59 by ihovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	single_quotes(char *line, int *i, int *count, char *metachars)
{
	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] != '\'' && line[*i] != '\0')
			(*i)++;
		if (line[*i] == '\0')
		{
			ft_putstr_fd("Error: found not closed quote\n", 2);
			(*count) = -300;
		}
		(*i)++;
		if (line[*i] == '\0' || ft_strchr(metachars, line[*i]) != 0)
			(*count)++;
	}
}

static void	double_quotes(char *line, int *i, int *count, char *metachars)
{
	if (line[*i] == '\"')
	{
		(*i)++;
		while (line[*i] != '\"' && line[*i] != '\0')
			(*i)++;
		if (line[*i] == '\0')
		{
			ft_putstr_fd("Error: found not closed quote\n", 2);
			(*count) = -300;
		}
		(*i)++;
		if (line[*i] == '\0' || ft_strchr(metachars, line[*i]) != 0)
			(*count)++;
	}
}

static void	words_and_ops(char *line, int *i, int *count, char *metachars)
{
	if (ft_strchr(metachars, line[*i]) != 0 && line[*i] != '\0')
	{	
		while (ft_strchr(metachars, line[*i]) != 0 && line[*i] != '\0')
			(*i)++;
		(*count)++;
	}
	else if (line[*i] != '\'' && line[*i] != '\"' && line[*i] != '\0')
	{
		while (ft_strchr(metachars, line[*i]) == 0 && \
				line[*i] != '\0' && line[*i] != '\'' && line[*i] != '\"')
			(*i)++;
		if ((line[*i] != '\'' && line[*i] != '\"') || line[*i] == '\0')
			(*count)++;
	}
}

int	tokens_count(char *line, char *metachars)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		single_quotes(line, &i, &count, metachars);
		double_quotes(line, &i, &count, metachars);
		words_and_ops(line, &i, &count, metachars);
	}
	return (count);
}
