/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_test_pattern_lighting.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:45:38 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/13 18:09:27 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"

int test_pattern_lighting(void)
{
	t_rgb		c1;
	t_rgb		c2;
	t_largs		largs;
	t_shape		s;

	s = sphere();
	largs.shape = &s;
	largs.eyev = vector(0, 0, -1);
	largs.normalv = vector(0, 0, -1);
	largs.light = point_light(point(0, 0, -10), color(255, 255, 255));
	largs.material.pattern = stripe_pattern(color(255, 255, 255), color(0, 0, 0));
	largs.material.ambient = 1;
	largs.material.diffuse = 0;
	largs.material.specular = 0;
	largs.in_shadow = false;
	largs.point = point(0.9, 0, 0);
	c1 = lighting(&largs);
	largs.point = point(1.1, 0, 0);
	c2 = lighting(&largs);
	free_matrices_and_ret(largs.shape, 0);
	if (c1.r != 1 || c1.g != 1 || c1.b != 1)
		return (-1);
	if (c2.r != 0 || c2.g != 0 || c2.b != 0)
		return (-1);
	return (0);
}
