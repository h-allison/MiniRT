/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_patterns_launcher.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:46:21 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/12 11:03:46 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"
#include "libunit.h"

int	patterns_tests_launcher(void)
{
	t_unit_test	testlist[9];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "PATTERNS: Basic test", &test_pattern_basic);
	load_test(testlist, "PATTERNS: Stripe is constant in y", &test_pattern_stripe_y);
	load_test(testlist, "PATTERNS: Stripe is constant in z", &test_pattern_stripe_z);
	load_test(testlist, "PATTERNS: Stripe alternates in x", &test_pattern_stripe_x);
	load_test(testlist, "PATTERNS: lighting with pattern applied", &test_pattern_lighting);
	load_test(testlist, "PATTERNS: Stripes with object transform", &test_stripes_obj_transform);
//	load_test(testlist, "PATTERNS: Stripes with object transform", &test_stripes_pat_transform);
//	load_test(testlist, "PATTERNS: Stripes with object transform", &test_stripes_all_transform);
	ret = launch_tests(testlist);
	return (ret);
}
