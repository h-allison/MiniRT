/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_shadow_launcher.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 14:38:10 by smargine          #+#    #+#             */
/*   Updated: 2025/09/09 13:44:02 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow_tests.h"
#include "libunit.h"

int	shadow_tests_launcher(void)
{
	t_unit_test	testlist[7];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "SHADOWS: test new flag `in_shadow`", &test_shadow_in);
	load_test(testlist, "SHADOWS: test is_shadowed(); : nothing collinear", &test_is_shad_1);
	load_test(testlist, "SHADOWS: test is_shadowed(); : object in between", &test_is_shad_2);
	load_test(testlist, "SHADOWS: test is_shadowed(); : object behind light", &test_is_shad_3);
	load_test(testlist, "SHADOWS: test is_shadowed(); : point in between", &test_is_shad_4);
	load_test(testlist, "SHADOWS: test comps.over_point", &test_over_point);
	ret = launch_tests(testlist);
	return (ret);
}
