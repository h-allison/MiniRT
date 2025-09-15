/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_refract_launcher.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:46:21 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/15 19:39:17 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refraction_tests.h"
#include "libunit.h"

int	refract_tests_launcher(void)
{
	t_unit_test	testlist[5]; // TODO
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "REFRACTION: Basic test", &test_refract_and_transp);
	load_test(testlist, "REFRACTION: Create glass_sphere()", &test_refract_glass_sphere);
	load_test(testlist, "REFRACTION: Find n1, n2", &test_refract_find_n1_n2);
	ret = launch_tests(testlist);
	return (ret);
}
