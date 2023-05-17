/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:51:48 by flauer            #+#    #+#             */
/*   Updated: 2023/05/17 14:59:49 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"

int	main(int argc, char *argv[], char *env[])
{
	ft_printf("argv:\n");
	for (int i = 0; argv[i]; ++i)
	{
		ft_printf("%s\n", argv[i]);
	}
	ft_printf("env:\n");
	for (int i = 0; env[i]; ++i)
	{
		ft_printf("%s\n", env[i]);
	}
	return (0);
}