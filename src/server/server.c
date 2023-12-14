/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:40:48 by dyunta            #+#    #+#             */
/*   Updated: 2023/12/14 21:17:58 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minitalk.h"

s_list head = ft_lstnew("1");

void	signal_handler_usr1(int signum)
{

	ft_putendl_fd(ft_itoa(signum), 4);
	ft_putchar_fd('1', 1);
}

void	signal_handler_usr2(int signum)
{
	ft_putendl_fd(ft_itoa(signum), 4);
	ft_putchar_fd('0', 1);
}


int	main(int argc, char **argv)
{
	struct sigaction sa1;
	struct sigaction sa2;

	(void)argv;
	sa1.sa_handler = signal_handler_usr1;
	sa1.sa_flags = SA_SIGINFO;
	sa2.sa_handler = signal_handler_usr2;
	sa2.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa2, NULL);

	pid_t pid = getpid();
	ft_putendl_fd(ft_strjoin("Server PID: ", ft_itoa(pid)), 1);

	while (argc == 1)
	{
		pause();
	}

	return (0);
}
