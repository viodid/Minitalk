/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:40:48 by dyunta            #+#    #+#             */
/*   Updated: 2023/12/09 20:49:28 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minitalk.h"

void	signal_handler(int signum)
{
	ft_putendl_fd(ft_itoa(signum), 1);
	ft_putendl_fd("This is great", 1);
}

int	main(void)
{
	struct sigaction sa;
	sa.sa_handler = signal_handler;
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &sa, NULL);

	pid_t pid = getpid();
	ft_putendl_fd(ft_strjoin("Server PID: ", ft_itoa(pid)), 1);

	while (1)
	{
		sleep(42);
	}

	return (0);
}
