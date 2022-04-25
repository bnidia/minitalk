/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/03/31 22:25:08 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "minitalk.h"

static void	handler(int signo, siginfo_t *siginfo, void *unused);
static void	send_char(int pid, int character, size_t *str_len);

volatile sig_atomic_t	g_response = 0;

int	sigaction_setup(struct sigaction *act, siginfo_t *siginfo, char *pid)
{
	act->sa_flags = SA_SIGINFO;
	act->sa_sigaction = &handler;
	sigemptyset(&act->sa_mask);
	sigaction(SIGUSR1, act, NULL);
	siginfo->si_pid = ft_atoi(pid);
	if (siginfo->si_pid == 0 || \
		(kill(siginfo->si_pid, 0) && (errno == EPERM || errno == ESRCH)))
	{
		ft_printf("PID error\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	struct sigaction	act;
	siginfo_t			siginfo;
	int					i;
	size_t				str_len;

	if (3 != argc)
	{
		ft_printf("2 arguments must be passed: PID and message\n");
		return (0);
	}
	if (sigaction_setup(&act, &siginfo, argv[1]) != 0)
		return (0);
	ft_printf("client PID: %d\n", getpid());
	i = 0;
	str_len = 0;
	while (argv[2][i] != '\0')
		send_char(siginfo.si_pid, argv[2][i++], &str_len);
	send_char(siginfo.si_pid, argv[2][i], &str_len);
	ft_printf("Server received %ubit, %ubytes\n", str_len, str_len / 8);
	return (0);
}

static void	handler(int signo, siginfo_t *siginfo, void *unused)
{
	(void)unused;
	(void)siginfo;
	(void)signo;
	g_response = 1;
}

static void	send_char(int pid, int character, size_t *str_len)
{
	int	counter;
	int	err;

	counter = 0;
	while (counter <= 7)
	{
		if ((character >> counter) & 1)
			err = kill(pid, SIGUSR1);
		else
			err = kill(pid, SIGUSR2);
		if (-1 == err)
		{
			ft_printf("Error signal\n");
			exit(EXIT_FAILURE);
		}
		counter++;
		while (g_response != 1)
			;
		g_response = 0;
		(*str_len)++;
	}
}
