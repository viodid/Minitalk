/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:40:48 by dyunta            #+#    #+#             */
/*   Updated: 2023/12/17 19:46:28 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

static void	signal_handler(int signum, siginfo_t *info, void *context);

int	main(void)
{
	const pid_t	pid = getpid();
	char		*pid_str;
	char		*output_str;

	// TODO: BONUS get sender PID https://stackoverflow.com/questions/48830222/get-pid-of-the-signal-sender-in-c
	struct sigaction act = {0};
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &signal_handler;

//	signal(SIGUSR1, signal_handler);
//	signal(SIGUSR2, signal_handler);
	ft_putendl_fd("\033[0;35m", 1);
	ft_putendl_fd("\033[0;36m", 1);
	// TODO: implement my printf
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
 */
static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	cycle = 7;
	static int	letter = 0x00;

	// Acknowledge received signal
	kill(info->si_pid, SIGUSR1);
	(void) context;
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
