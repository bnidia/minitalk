/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/03/29 19:43:16 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int signum, siginfo_t *sig, void *context);

static volatile sig_atomic_t	g_response[2] = {};

int	main(void)
{
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	if (-1 == sigaction(SIGUSR1, &act, NULL)
		|| -1 == sigaction(SIGUSR2, &act, NULL))
	{
		ft_printf("Error setting the signal disposition\n");
		return (0);
	}
	ft_printf("Server started successfully and now waiting for client\n");
	ft_printf("PID is: %i\n", getpid());
	while (42)
	{
		while (g_response[0] != 1)
			;
		g_response[0] = 0;
		kill(g_response[1], SIGUSR1);
	}
}

static void	string_assembly(unsigned char c)
{
	static unsigned char	str[4096];
	static int				str_i;

	str[str_i++] = c;
	if (str_i == 4096)
	{
		write(1, &str, str_i);
		str_i = 0;
	}
	if (c == 0)
	{
		write(1, &str, str_i);
		write(1, "\n", 1);
		str_i = 0;
	}
}

static void	handler(int signum, siginfo_t *sig, void *context)
{
	static unsigned char	letter;
	static int				i;

	(void)context;
	if ((SIGUSR1 ^ signum) == 0)
		letter |= (1 << i);
	i++;
	if ((8 ^ i) == 0)
	{
		string_assembly(letter);
		letter = 0;
		i = 0;
	}
	g_response[0] = 1;
	g_response[1] = sig->si_pid;
}
