/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:57:05 by smargine          #+#    #+#             */
/*   Updated: 2025/09/26 17:45:15 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_tests.h"
#include "shadow_tests.h"
#include "shapes_tests.h"
#include "planes_tests.h"
#include "patterns_tests.h"
#include "reflection_tests.h"
#include "refraction_tests.h"
#include "cub_cyl_tests.h"
#include "cones_tests.h"
#include "groups_tests.h"
#include "textures_tests.h"

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
	err += shapes_tests_launcher();
	err += planes_tests_launcher();
	err += patterns_tests_launcher();
	err += reflect_tests_launcher();
	err += refract_tests_launcher();
	err += cubes_tests_launcher();
	err += cones_tests_launcher();
	err += groups_tests_launcher();
	err += textures_tests_launcher();
	if (!err)
		write(1, GREEN "All tests passed!\n\n" RESET, 28);
	return (0);
}
