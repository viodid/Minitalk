/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 22:12:33 by dyunta            #+#    #+#             */
/*   Updated: 2024/01/02 21:26:03 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// change path at the end
#include "../../include/minitalk.h"

static void	send_signals(char **argv, pid_t pid_server);
static void	signal_handler(int signum);
static void	send_newline(pid_t pid);

/*
* The following logic operates as follows:
* When sending an integer's bits in decimal format through signals,
* the code iteratively shifts from the 7th bit to the 0th bit, capturing
* the most significant bit in each iteration.
* For instance, when transmitting the decimal number 42 over signals,
* the code iterates through the 42, right-shifting 1 bit per iteration.
* Whenever a one is encountered during the iteration, it is signaled
 * (also the zero but with a differentiator).
* The server is responsible for deciphering the signal (or 1) location
* within the bit sequence.
*/
// 0 0 1 0 1 0 1 0 - 42
// 0 0 0 0 1 0 1 0 - 42 - 32 = 10
// 0 0 0 0 0 0 1 0 - 10 - 8 = 2
// 0 0 0 0 0 0 0 0 - 2 - 2 = 0
int	main(int argc, char **argv)
{
	pid_t	pid_server;

	signal(SIGUSR1, signal_handler);
	if (sanitized_input(argc, argv))
	{
		ft_putendl_fd("usage: ./client [PID] [message]", 2);
		return (1);
	}
	pid_server = ft_atoi(argv[1]);
	send_signals(argv, pid_server);
	return (0);
}

static void	send_signals(char **argv, pid_t pid_server)
{
	int	i;
	int	j;
	int	letter;

	i = 0;
	letter = (int) argv[2][i];
	while (letter)
	{
		j = 7;
		while (j >= 0)
		{
			if (letter >> j)
			{
				kill(pid_server, SIGUSR1);
				letter -= 0x01 << j;
			}
			else
				kill(pid_server, SIGUSR2);
			usleep(50);
			j--;
		}
		i++;
		letter = (int) argv[2][i];
	}
	send_newline(pid_server);
}

static void	send_newline(pid_t pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(50);
	}
}


static void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		ft_putendl_fd("Message received by the server.", 1);
}
