/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_shapes_launcher.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:56:59 by hallison          #+#    #+#             */
/*   Updated: 2025/09/09 17:35:18 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shapes_tests.h"
#include "libunit.h"

int	shapes_tests_launcher(void)
{
	t_unit_test	testlist[2];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "SHAPES: test shape", &test_shape_basic);
//	load_test(testlist, "SHAPES: test shape", &test_shape_transform);
	ret = launch_tests(testlist);
	return (ret);
}
