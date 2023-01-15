/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghelman <ghelman@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:32:15 by ghelman           #+#    #+#             */
/*   Updated: 2022/03/08 18:32:16 by ghelman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void	handler(int signal, siginfo_t *info, void *context)
{
	static int				i;
	static unsigned char	c;
	static int				pid;
	int						return_code;
	int						bit;

	(void)context;
	if (signal == SIGUSR1)
		bit = 0;
	else
		bit = 1;
	c = c | bit << i;
	if (i == 8 - 1)
	{
		return_code = 0;
		while (return_code < 1)
			return_code = write(1, &c, 1);
		c = 0;
	}
	i = (i + 1) % 8;
	if (info->si_pid != 0)
		pid = info->si_pid;
	return_code = -1;
	while (return_code != 0)
		return_code = kill(pid, SIGUSR1);
}

static size_t	dec_nat_len(size_t dec_nat)
{
	size_t	result;

	result = 1;
	while (dec_nat >= 10)
	{
		dec_nat /= 10;
		result++;
	}
	return (result);
}

char	*dec_nat_to_str(size_t dec_nat)
{
	char	*result;
	size_t	length;

	length = dec_nat_len(dec_nat);
	result = malloc(length + 1);
	if (result == NULL)
		return (NULL);
	result[length] = '\0';
	while (length)
	{
		result[length - 1] = dec_nat % 10 + '0';
		dec_nat /= 10;
		length--;
	}
	return (result);
}

void	print_dec_nat(size_t dec_nat)
{
	ssize_t	return_code;
	size_t	to_write;
	size_t	written;
	char	*str;

	written = 0;
	str = dec_nat_to_str(dec_nat);
	while (str == NULL)
		str = dec_nat_to_str(dec_nat);
	to_write = dec_nat_len(dec_nat);
	return_code = write(1, str + written, to_write);
	while (1)
	{
		if (return_code != -1)
		{
			to_write -= return_code;
			written += to_write;
			if (to_write == 0)
				break ;
		}
		return_code = write(1, str + written, to_write);
	}
	free(str);
}

int	main(void)
{
	struct sigaction	sa;
	ssize_t				return_code;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	return_code = -1;
	while (return_code != 0)
		return_code = sigemptyset(&sa.sa_mask);
	return_code = -1;
	while (return_code != 0)
		return_code = sigaction(SIGUSR1, &sa, NULL);
	return_code = -1;
	while (return_code != 0)
		return_code = sigaction(SIGUSR2, &sa, NULL);
	return_code = 0;
	print_dec_nat(getpid());
	while (write(1, "\n", 1) != 1)
		;
	while (1)
		pause();
}
