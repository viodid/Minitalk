/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 22:12:33 by dyunta            #+#    #+#             */
/*   Updated: 2023/12/14 20:52:05 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// change path at the end
# include "../../include/minitalk.h"

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

	// TODO: SERVER RECIEVES ONE MORE SIGUSR1 signal at the end of the binary than expected
	int i = 0;
	int j = 7;
	char letter = argv[2][i];
	while (letter)
	{
		while (j >= 0)
		{
			ft_putnbr_fd(letter >> j, 1);
			if (letter >> j)
			{
				kill(pid_server, SIGUSR1);
				letter -= 0x01 << j;
			}
			else
				kill(pid_server, SIGUSR2);
			usleep(5000);
			j--;
		}
		j = 7;
		i++;
		letter = argv[2][i];
		ft_putchar_fd('\n', 1);
	}
	kill(pid_server, SIGUSR1);
	return (0);
}
