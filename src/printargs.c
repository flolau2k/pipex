/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:26:48 by flauer            #+#    #+#             */
/*   Updated: 2023/06/18 14:26:51 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../libft/include/libft.h"

int main(int argc, char **argv)
{
	int i = 0;

	while (i < argc)
	{
		ft_printf("%s\n", argv[i]);
		++i;
	}
	return (0);
}