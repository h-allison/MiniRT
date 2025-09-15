/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_refract_launcher.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:46:21 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/16 00:34:21 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refraction_tests.h"
#include "libunit.h"

int	refract_tests_launcher(void)
{
	t_unit_test	testlist[7];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "REFRACTION: Basic test", &test_refract_and_transp);
	load_test(testlist, "REFRACTION: Create glass_sphere()", &test_refract_glass_sphere);
	load_test(testlist, "REFRACTION: Find n1, n2", &test_refract_find_n1_n2);
	load_test(testlist, "REFRACTION: Calculate under_point", &test_refract_under_point);
	load_test(testlist, "REFRACTION: Refracted color opaque", &test_refract_under_point);
	load_test(testlist, "REFRACTION: Max recursion", &test_refract_max_recursion);
	ret = launch_tests(testlist);
	return (ret);
}
