/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:57:05 by smargine          #+#    #+#             */
/*   Updated: 2025/09/08 11:34:45 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_tests.h"

void	print_banner(void)
{
	const char	*banner;

	banner = "\n\n /$$       /$$ /$$       /$$   /$$	     /$$   /$$    \n"
		"| $$      |__/| $$      | $$  | $$          |__/  | $$    \n"
		"| $$       /$$| $$$$$$$ | $$  | $$ /$$$$$$$  /$$  / $$$$$$\n"
		"| $$      | $$| $$__  $$| $$  | $$| $$__  $$| $$|_  $$_/  \n"
		"| $$      | $$| $$  \\ $$| $$  | $$| $$  \\ $$| $$  | $$    \n"
		"| $$      | $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$ /$$\n"
		"| $$$$$$$$| $$| $$$$$$$/|  $$$$$$/| $$  | $$| $$  | $$$$/\n"
		"|________/|__/|_______/  \\______/ |__/  |__/|__/   \\___/  \n"
		"                                                          \n";
	write(1, banner, ft_strlen(banner));
	write(1, "\n", 1);
}

int	main(void)
{
	int	nbr_of_tests;
	int	passed;

	print_banner();
	passed = 0;
	nbr_of_tests = 1;
	passed += camera_tests_launcher();
	if (passed == nbr_of_tests)
		write(1, GREEN "All tests passed!\n\n" RESET, 28);
	return (0);
}
