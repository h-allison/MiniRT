/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_textures_launcher.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:46:21 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/26 17:26:59 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures_tests.h"
#include "libunit.h"

int	textures_tests_launcher(void)
{
	t_unit_test	testlist[100];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "TEXTURES: File open wrong header  ", &test_textures_wrong_header);
	load_test(testlist, "TEXTURES: PPM returns right size", &test_textures_size);
	load_test(testlist, "TEXTURES: Reading pixel data", &test_textures_read_pixel);
	load_test(testlist, "TEXTURES: Comments...", &test_textures_comments);
	load_test(testlist, "TEXTURES: RGB-triple spans lines", &test_textures_rgb_span);
	load_test(testlist, "TEXTURES: RGB scaling", &test_textures_rgb_scaling);
	load_test(testlist, "TEXTURES: 2D checkers", &test_textures_2D_checkers);
	ret = launch_tests(testlist);
	return (ret);
}
