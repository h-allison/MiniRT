/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_groups_launcher.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:46:21 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/19 23:14:18 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "groups_tests.h"
#include "libunit.h"

int	groups_tests_launcher(void)
{
	t_unit_test	testlist[100];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "GROUPS: Basic test", &test_groups_basic);
	load_test(testlist, "GROUPS: Group has an empty parent", &test_groups_has_parent);
	load_test(testlist, "GROUPS: Add child to group", &test_groups_add_child);
	load_test(testlist, "GROUPS: Intersecting empty group", &test_groups_intersect_empty);
	load_test(testlist, "GROUPS: Intersecting nonempty group", &test_groups_intersect);
	load_test(testlist, "GROUPS: Intersecting transformed group", &test_groups_intersect_transformed);
	load_test(testlist, "GROUPS: Converting point from world to object space", &test_groups_point_convert_space);
	load_test(testlist, "GROUPS: Converting normal from object to world space", &test_groups_normal_convert_space);
	ret = launch_tests(testlist);
	return (ret);
}
