/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_refract_launcher.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:46:21 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/16 17:19:12 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refraction_tests.h"
#include "libunit.h"

int	refract_tests_launcher(void)
{
	t_unit_test	testlist[100];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "REFRACTION: Basic test", &test_refract_and_transp);
	load_test(testlist, "REFRACTION: Create glass_sphere()", &test_refract_glass_sphere);
	load_test(testlist, "REFRACTION: Find n1, n2", &test_refract_find_n1_n2);
	load_test(testlist, "REFRACTION: Calculate under_point", &test_refract_under_point);
	load_test(testlist, "REFRACTION: Refracted color opaque", &test_refract_under_point);
	load_test(testlist, "REFRACTION: Max recursion", &test_refract_max_recursion);
	load_test(testlist, "REFRACTION: Total internal reflection", &test_refract_total);
	load_test(testlist, "REFRACTION: Refracted color", &test_refract_color);
	load_test(testlist, "REFRACTION: Shade_hit() with transparency", &test_refract_shade_hit);
	load_test(testlist, "REFRACTION: Schlick total reflection", &test_refract_schlick_total);
	load_test(testlist, "REFRACTION: Schlick perpendicular ray", &test_refract_schlick_perpendicular);
	load_test(testlist, "REFRACTION: Schlick small angle (n2 > n1)", &test_schlick_n2_bigger_n1);
	load_test(testlist, "REFRACTION: shade_hit() with reflective, transparent material", &test_shadehit_reflective_and_transparent);
	ret = launch_tests(testlist);
	return (ret);
}
