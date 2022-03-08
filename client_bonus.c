/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghelman <ghelman@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:30:15 by ghelman           #+#    #+#             */
/*   Updated: 2021/03/08 18:30:16 by ghelman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

static int	g_got_response;

static void	handler(int number, siginfo_t *info, void *context)
{
	(void)number;
	(void)info;
	(void)context;
	g_got_response = 1;
}

static size_t	str_to_nat(char *str)
{
	size_t	result;

	result = 0;
	while (*str)
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	return (result);
}

static size_t	str_len(char *str)
{
	size_t	result;

	result = 0;
	while (*str)
	{
		result++;
		str++;
	}
	return (result);
}

static void	send_message(char *message, size_t length, int pid)
{
	int		bit;
	int		signal;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < length)
	{
		j = 0;
		while (j < 8)
		{
			bit = message[i] >> j & 1;
			g_got_response = 0;
			if (bit % 2 == 0)
				signal = SIGUSR1;
			else
				signal = SIGUSR2;
			while (kill(pid, signal) != 0)
				;
			while (!g_got_response)
				;
			j++;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	int					server_pid;
	char				*message;

	if (argc != 3)
		return (1);
	server_pid = str_to_nat(argv[1]);
	message = argv[2];
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	while (sigemptyset(&sa.sa_mask) != 0)
		;
	while (sigaction(SIGUSR1, &sa, NULL))
		;
	send_message(message, str_len(message), server_pid);
}
