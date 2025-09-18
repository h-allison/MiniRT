/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_cones_launcher.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:46:21 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/18 11:30:03 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cones_tests.h"
#include "libunit.h"

int	cones_tests_launcher(void)
{
	t_unit_test	testlist[100];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "CONES: Intersect", &test_cones_intersect);
	load_test(testlist, "CONES: Intersect parallel", &test_cones_intersect_parallel);
	load_test(testlist, "CONES: Intersect end caps", &test_cones_intersect_caps);
	ret = launch_tests(testlist);
	return (ret);
}
