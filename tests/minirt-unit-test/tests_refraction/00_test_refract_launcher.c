/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_refract_launcher.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:46:21 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/14 19:27:21 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refraction_tests.h"
#include "libunit.h"

int	refract_tests_launcher(void)
{
	t_unit_test	testlist[8];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "REFRACTION: Basic test", &test_refract_and_transp);
	load_test(testlist, "REFRACTION: Create glass_sphere()", &test_refract_glass_sphere);
	ret = launch_tests(testlist);
	return (ret);
}
