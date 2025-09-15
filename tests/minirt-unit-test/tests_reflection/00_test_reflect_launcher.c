/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_reflect_launcher.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:46:21 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/15 20:03:07 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection_tests.h"
#include "libunit.h"

int	reflect_tests_launcher(void)
{
	t_unit_test	testlist[8];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "REFLECTION: Basic test", &test_reflect_basic);
	load_test(testlist, "REFLECTION: Precompute comps.reflectv", &test_reflect_comps);
	load_test(testlist, "REFLECTION: Color non-reflective material", &test_reflect_col_nonreflect);
	load_test(testlist, "REFLECTION: Color reflective material", &test_reflect_col_reflective);
	load_test(testlist, "REFLECTION: shade_hit() reflective material", &test_reflect_shade_hit_reflective);
	load_test(testlist, "REFLECTION: mutually reflective surfaces", &test_reflect_mutually_reflective);
	load_test(testlist, "REFLECTION: Color at max recursion", &test_reflect_col_max_recursion);
	ret = launch_tests(testlist);
	return (ret);
}
