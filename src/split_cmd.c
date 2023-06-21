/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:30:47 by flauer            #+#    #+#             */
/*   Updated: 2023/06/21 09:47:09 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_strlen_delimiter(char const *s, char *quotes)
{
	size_t	ret;

	ret = 0;
	while (!*quotes && s[ret] && s[ret] != ' ')
		ret++;
	while (*quotes && s[ret] && s[ret] != *quotes)
		ret++;
	return (ret);
}

static const char	*ft_find_next_substr(const char *s, char *quotes)
{
	int	i;

	i = 0;
	if (*quotes && s[i] == *quotes)
		i++;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '\'' || s[i] == '\"')
	{
		*quotes = s[i];
		i++;
	}
	return (&s[i]);
}

static size_t	ft_num_substr(char const *s)
{
	size_t	num_substr;
	size_t	i;
	char	quotes;

	i = 0;
	num_substr = 0;
	quotes = 0;
	if (s[i] && s[i] != ' ')
	{
		num_substr++;
		if (s[i] == '\'' || s[i] == '\"')
			quotes = s[i];
		i++;
	}
	while (s[i])
	{
		if (!quotes && s[i] == ' ' && s[i +1] && s[i +1] != ' ')
			num_substr++;
		if (quotes && quotes == s[i])
			quotes = 0;
		else if (!quotes && (s[i] == '\'' || s[i] == '\"'))
			quotes = s[i];
		i++;
	}
	return (num_substr);
}

char	**split_cmd(const char *s)
{
	char	**ret;
	size_t	i;
	char	*curr_start;
	size_t	curr_len;
	char	quotes;

	i = -1;
	quotes = 0;
	curr_start = (char *) ft_find_next_substr(s, &quotes);
	ret = ft_calloc(ft_num_substr(s) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (++i < ft_num_substr(s))
	{
		curr_len = ft_strlen_delimiter(curr_start, &quotes);
		ret[i] = ft_substr(curr_start, 0, curr_len);
		if (!ret[i])
		{
			free_splits(ret);
			return (NULL);
		}
		curr_start = (char *) ft_find_next_substr(curr_start + curr_len, &quotes);
	}
	return (ret);
}

// int	main(int argc, char *argv[])
// {
// 	int		i;
// 	int		j;
// 	char	**splits;

// 	i = 0;
// 	while (i < argc)
// 	{
// 		splits = split_cmd(argv[i]);
// 		j = 0;
// 		while (splits[j])
// 		{
// 			ft_printf("%s, ", splits[j]);
// 			++j;
// 		}
// 		ft_printf("\n");
// 		free_splits(splits);
// 		++i;
// 	}
// 	return (0);
// }
