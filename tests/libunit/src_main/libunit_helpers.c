/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:18:03 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/09 17:17:29 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

static void	write_nbr(int n, int fd);
static void	ft_putnbr_fd(int n, int fd);

int	print_status(int status)
{
	if (WIFSIGNALED(status))
		print_signals(status);
	else
	{
		if (WEXITSTATUS(status) == 0)
		{
			write(1, GREEN" [OK]\n"RESET, 15);
			return (0);
		}
		if (WEXITSTATUS(status) == 124)
			write(1, YELLOW" [TIMEOUT]\n"RESET, 20);
		else
			write(1, RED" [KO]\n"RESET, 15);
	}
	return (1);
}

void	print_result(int passed, int total)
{
	write(1, "passed ", 7);
	ft_putnbr_fd(passed, 1);
	write(1, "/", 1);
	ft_putnbr_fd(total, 1);
	if (passed == total)
		write(1, GREEN" [OK]\n"RESET, 15);
	else
		write(1, RED" [KO]\n"RESET, 15);
	write (1, "\n", 1);
}

void	print_signals(int status)
{
	if (WTERMSIG(status) == SIGSEGV)
		write(1, MAGENTA" [SEGV] >>> Segfault\n"RESET, 30);
	if (WTERMSIG(status) == SIGBUS)
		write(1, MAGENTA" [BUS] >>> Bus error\n"RESET, 30);
	if (WTERMSIG(status) == SIGABRT)
		write(1, MAGENTA" [ABRT] >>> Abort signal\n"RESET, 34);
	if (WTERMSIG(status) == SIGFPE)
		write(1, MAGENTA" [FPE] >>> Arithmetic error\n"RESET, 37);
	if (WTERMSIG(status) == SIGPIPE)
		write(1, MAGENTA" [PIPE] >>> Pipe error\n"RESET, 32);
	if (WTERMSIG(status) == SIGILL)
		write(1, MAGENTA" [ILL] >>>  Illegal operation\n"RESET, 39);
}

static void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write (fd, "-", 1);
		n = -n;
	}
	write_nbr(n, fd);
	return ;
}

static void	write_nbr(int n, int fd)
{
	if (n > 9)
		write_nbr(n / 10, fd);
	write(fd, &"0123456789"[n % 10], 1);
	return ;
}
