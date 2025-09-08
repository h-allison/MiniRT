/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_camera_launcher.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 14:38:10 by smargine          #+#    #+#             */
/*   Updated: 2025/09/08 15:27:16 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_tests.h"
#include "libunit.h"

int	camera_tests_launcher(void)
{
	t_unit_test	testlist[7];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "CREATE_CAMERA: test floats", &test_camera_floats);
	load_test(testlist, "CREATE_CAMERA: test id-matrix", &test_camera_idm);
	load_test(testlist, "CREATE_CAMERA: test pixel-size", &test_camera_pixel);
	load_test(testlist, "CREATE_CAMERA: test rayforpixel_1",
			&test_camera_rayforpixel_1);
	load_test(testlist, "CREATE_CAMERA: test rayforpixel_2",
			&test_camera_rayforpixel_2);
	load_test(testlist, "CREATE_CAMERA: test rayforpixel_3",
			&test_camera_rayforpixel_3);
	ret = launch_tests(testlist);
	return (ret);
}
