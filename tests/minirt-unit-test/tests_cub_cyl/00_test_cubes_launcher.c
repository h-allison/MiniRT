/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_cubes_launcher.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:46:21 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/17 11:10:45 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_cyl_tests.h"
#include "libunit.h"

int	cubes_tests_launcher(void)
{
	t_unit_test	testlist[100];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "CUBE: Intersect", &test_cubes_intersect);
	load_test(testlist, "CUBE: Ray misses", &test_cubes_ray_misses);
	load_test(testlist, "CUBE: Normal at", &test_cubes_normal_at);
	load_test(testlist, "CYLINDER: Ray misses", &test_cyls_ray_misses);
	load_test(testlist, "CYLINDER: Ray strikes", &test_cyls_ray_strikes);

	ret = launch_tests(testlist);
	return (ret);
}
