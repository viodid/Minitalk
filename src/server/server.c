/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:40:48 by dyunta            #+#    #+#             */
/*   Updated: 2023/12/09 21:44:49 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minitalk.h"

void	signal_handler(int signum)
{
	ft_putendl_fd(ft_itoa(signum), 1);
	ft_putendl_fd("This is great", 1);
}

int	main(int argc, char **argv)
{
	struct sigaction sa;

	(void)argv;
	sa.sa_handler = signal_handler;
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &sa, NULL);

	pid_t pid = getpid();
	ft_putendl_fd(ft_strjoin("Server PID: ", ft_itoa(pid)), 1);

	while (argc == 1)
	{
		pause();
	}

	return (0);
}
