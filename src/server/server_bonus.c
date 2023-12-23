/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:40:48 by dyunta            #+#    #+#             */
/*   Updated: 2023/12/17 20:02:54 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

static void	signal_handler(int signum);

int	main(void)
{
	const pid_t	pid = getpid();

	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	ft_putendl_fd("\033[0;35m", 1);
	ft_putendl_fd("\033[0;36m", 1);
	ft_putendl_fd(ft_strjoin("Server PID: ", ft_itoa(pid)), 1);
	while (1)
	{
		pause();
	}
	return (0);
}

/*
 * This function is called when the server receives a signal.
 * It is called once for each bit of the character.
 * When the character is complete, it is printed.
 */
static void	signal_handler(int signum)
{
	static int	cycle = 7;
	static int	letter = 0x00;

	if (signum == SIGUSR1)
		letter |= 0x01 << cycle;
	if (cycle == 0)
	{
		ft_putchar_fd((char)letter, 1);
		cycle = 7;
		letter = 0;
	}
	else
		cycle--;
}
