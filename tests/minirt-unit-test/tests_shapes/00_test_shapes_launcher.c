/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_shapes_launcher.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:56:59 by hallison          #+#    #+#             */
/*   Updated: 2025/09/12 11:16:37 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes_tests.h"
#include "libunit.h"

int	shapes_tests_launcher(void)
{
	t_unit_test	testlist[10];
	int			ret;

	testlist[0].test = NULL;
//	load_test(testlist, "SHAPES: test shape", &test_shape_basic);
//	load_test(testlist, "SHAPES: test transform", &test_shape_transform);
//	load_test(testlist, "SHAPES: test material", &test_shape_material);
//	load_test(testlist, "SHAPES: assign material", &test_shape_ass_material);
//	load_test(testlist, "SHAPES: intersecting scaled shape", &test_shape_intersect);
//	load_test(testlist, "SHAPES: intersecting translated shape", &test_shape_translate);
//	load_test(testlist, "SHAPES: normal of translated shape", &test_shape_normal_translate);
	load_test(testlist, "SHAPES: normal of transformed shape", &test_shape_normal_transform);
	ret = launch_tests(testlist);
	return (ret);
}
