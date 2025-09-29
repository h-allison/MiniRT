/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_triangles_launcher.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:46:21 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/27 20:56:08 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangles_tests.h"
#include "libunit.h"

int	triangles_tests_launcher(void)
{
	t_unit_test	testlist[100];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "TRIANGLES: Create triangle", &test_triangles_create);
	load_test(testlist, "TRIANGLES: Local normal at", &test_triangles_normal_at);
	load_test(testlist, "TRIANGLES: Ray parallel to the triangle", &test_triangles_ray_parallel);
	load_test(testlist, "TRIANGLES: Ray misses p1-p3 edge", &test_triangles_ray_misses_p1_p3);
	load_test(testlist, "TRIANGLES: Ray misses p1-p2 and p2-p3 edge", &test_triangles_ray_misses_p1_p2_p3);
	load_test(testlist, "TRIANGLES: Ray strikes a triangle", &test_triangles_ray_strikes);
	ret = launch_tests(testlist);
	return (ret);
}
