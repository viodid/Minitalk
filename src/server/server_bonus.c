/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:40:48 by dyunta            #+#    #+#             */
/*   Updated: 2024/01/07 19:02:34 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

static void	signal_handler(int signum, siginfo_t *info, void *context);

int	main(void)
{
	pid_t				pid;
	char				*pid_str;
	char				*output_str;
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	pid = getpid();
	pid_str = ft_itoa(pid);
	output_str = ft_strjoin("Server PID: ", pid_str);
	ft_putendl_fd(output_str, 1);
	free(pid_str);
	free(output_str);
	while (1)
	{
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
		pause();
	}
	return (0);
}

/*
 * This function is called when the server receives a signal.
 * It is called once for each bit of the character.
 * When the character is complete, it is printed.
 * It also acknowledges the received signal.
 */
static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	cycle = 7;
	static int	letter = 0x00;

	(void) context;
	if (signum == SIGUSR1)
		letter |= 0x01 << cycle;
	if (cycle == 0)
	{
		if (letter == 255)
		{
			ft_putchar_fd('\n', 1);
			kill(info->si_pid, SIGUSR1);
		}
		else
			ft_putchar_fd((char) letter, 1);
		cycle = 7;
		letter = 0;
	}
	else
		cycle--;
}
