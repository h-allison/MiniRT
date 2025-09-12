/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:57:05 by smargine          #+#    #+#             */
/*   Updated: 2025/09/12 11:13:49 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_tests.h"
#include "shadow_tests.h"
#include "shapes_tests.h"
#include "planes_tests.h"
#include "patterns_tests.h"

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
//	err += camera_tests_launcher();
//	err += shadow_tests_launcher();
	err += shapes_tests_launcher();
	err += planes_tests_launcher();
//	err += patterns_tests_launcher();
	if (!err)
		write(1, GREEN "All tests passed!\n\n" RESET, 28);
	return (0);
}
