/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_test_cyls_ray_misses.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/22 15:46:54 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_cyl_tests.h"

int test_cyls_ray_misses(void)
{
	t_shape			c;
	t_ray			r;
	t_intersection	*xs;

	c = cylinder();
	r = ray(point(1, 0, 0), tnorm(vector(0, 1, 0)));
	xs = local_intersect_cyl(&c, r);
	if (xs[0].t != 0 && !xs[0].object)
		return (-1);
	xs[0].object = NULL;
	c.saved_ray = ray(point(0, 0, 0), tnorm(vector(0, 1, 0)));
	xs = local_intersect_cyl(&c, r);
	if (xs[0].t != 0 && !xs[0].object)
		return (-1);
	xs[0].object = NULL;
	c.saved_ray = ray(point(0, 0, -5), tnorm(vector(1, 1, 1)));
	xs = local_intersect_cyl(&c, r);
	if (xs[0].t != 0 && !xs[0].object)
		return (-1);
	xs[0].object = NULL;
	free_shape(&c);
	return (0);
}
