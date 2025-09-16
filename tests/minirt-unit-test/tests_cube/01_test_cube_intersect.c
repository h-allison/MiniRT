/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_cube_intersect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/16 17:50:33 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_tests.h"


int test_cube_intersect(void)
{
	t_shape			c;
	t_ray			r;
	t_intersection	xs;

	c = cube();
	r = ray(point(5, 0.5, 0), vector(-1, 0, 0));
	xs = local_intersect(c, r);
	printf("xs: %f, %f", xs[0].t, xs[1].t);
}
