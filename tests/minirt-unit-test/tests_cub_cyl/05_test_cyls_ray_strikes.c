/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_test_cyls_ray_strikes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/17 11:31:33 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_cyl_tests.h"

int test_cyls_ray_strikes(void)
{
	t_shape			c;
	t_intersection	*xs;

	c = cylinder();
	c.saved_ray = ray(point(1, 0, -5), tnorm(vector(0, 0, 1)));
	xs = local_intersect_cyl(&c);
	if (!fisequal(xs[0].t, 5) || !fisequal(xs[1].t, 0))
		return (-1);
	xs[0].object = NULL;
	c.saved_ray = ray(point(0, 0, -5), tnorm(vector(0, 0, 1)));
	xs = local_intersect_cyl(&c);
	if (xs[0].t != 4 || xs[1].t != 6)
		return (-1);
	xs[0].object = NULL;
	c.saved_ray = ray(point(0.5, 0, -5), tnorm(vector(0.1, 1, 1)));
	xs = local_intersect_cyl(&c);
	if (!fisequal(xs[0].t, 6.80798) || !fisequal(xs[1].t, 7.08872))
		return (-1);
	xs[0].object = NULL;
	return (0);
}
