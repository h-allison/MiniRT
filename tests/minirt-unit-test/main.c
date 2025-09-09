/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:57:05 by smargine          #+#    #+#             */
/*   Updated: 2025/09/09 11:01:56 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_tests.h"
#include "shadow_tests.h"

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
	int	err;

	print_banner();
	err = 0;
	err += camera_tests_launcher();
	err += shadow_tests_launcher();
	if (!err)
		write(1, GREEN "All tests passed!\n\n" RESET, 28);
	return (0);
}
