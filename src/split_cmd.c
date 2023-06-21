/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:30:47 by flauer            #+#    #+#             */
/*   Updated: 2023/06/21 15:50:35 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_curr_start(const char *s)
{
	char	*ret;

	ret = s;
	while (ft_isspace(ret))
		++ret;
	return (ret);
}

static void	handle_strong_quotes(t_list **lst, char **pos)
{
	int	i;

	i = 0;
	++(*pos);
	while (*pos[i] && *pos[i] != '\'')
		++i;
	ft_lstadd_back(lst, ft_lstnew(ft_substr(*pos, 0, i)));
	*pos = *pos + i;
}

static void	handle_soft_quotes(t_list **lst, char **pos)
{
	int	i;

	i = 0;
	++(*pos);
	while (*pos[i] && *pos[i] != '\"')
	{
		if (!*pos[i])
			break;
		else if (*pos[i] != '\"')
			++i;
		else if (*pos[i] == '\"' && *pos[i - 1] && *pos[i - 1] == "\\")

	}
	*pos = *pos + i;
}

static void	handle_substr(t_list **lst, char **pos)
{
	int		i;

	i = 0;
	if (!pos || !*pos)
		return ;
	if (*pos[i] == '\'')
		handle_strong_quotes(lst, pos);
	else if (*pos[i] == '\"')
		handle_soft_quotes(lst, pos);
	while (*pos[i] && !ft_isspace(*pos[i]))
		++i;
	ft_lstadd_back(lst, ft_lstnew(ft_substr(*pos, 0, i)));
	*pos = *pos + i;
}

char	**split_cmd(const char *s)
{
	char	**ret;
	t_list	*args;
	char	*curr_pos;

	args = NULL;
	curr_pos = find_curr_start(s);
	while (curr_pos)
	{
		handle_substr(&args, &curr_pos);
		curr_pos = find_curr_start(curr_pos);
	}
	ret = list_to_arr(&args);
	return (ret);
}
