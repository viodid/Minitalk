/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 22:12:33 by dyunta            #+#    #+#             */
/*   Updated: 2023/12/09 17:44:59 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minitalk.h"

int	main(int argc, char **argv)
{
	if (sanitized_input(argc, argv))
	{
		ft_putendl_fd("usage: ./client [PID] [message]", 2);
		return (1);
	}
	pid_t pid = getpid();
	ft_putendl_fd(ft_strjoin("Client PID: ", ft_itoa(pid)), 1);

	pid_t pid_server = ft_atoi(argv[1]);
	kill(pid_server, SIGUSR1);
	return (0);
}
