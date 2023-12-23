/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 22:19:13 by dyunta            #+#    #+#             */
/*   Updated: 2023/12/17 19:27:12 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	sanitized_input(int argc, char **argv)
{
	int	i;

	if (argc != 3)
		return (1);
	i = 0;
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i++]))
			return (1);
	}
	i = 0;
	while (argv[2][i])
	{
		if (!ft_isprint(argv[2][i++]))
			return (1);
	}
	return (0);
}
