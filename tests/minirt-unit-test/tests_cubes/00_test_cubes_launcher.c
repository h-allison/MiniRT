/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_cubes_launcher.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:46:21 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/16 23:35:08 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubes_tests.h"
#include "libunit.h"

int	cubes_tests_launcher(void)
{
	t_unit_test	testlist[100];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "CUBE: Intersect", &test_cubes_intersect);
	load_test(testlist, "CUBE: Ray misses", &test_cubes_ray_misses);
	load_test(testlist, "CUBE: Normal at", &test_cubes_normal_at);

	ret = launch_tests(testlist);
	return (ret);
}
