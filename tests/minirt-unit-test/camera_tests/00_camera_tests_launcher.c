/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_camera_tests_launcher.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 14:38:10 by smargine          #+#    #+#             */
/*   Updated: 2025/09/08 12:20:37 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_tests.h"
#include "libunit.h"

int	camera_tests_launcher(void)
{
	t_unit_test	testlist[2];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "CAMERA: create camera", &camera);
	ret = launch_tests(testlist);
	return (ret);
}
