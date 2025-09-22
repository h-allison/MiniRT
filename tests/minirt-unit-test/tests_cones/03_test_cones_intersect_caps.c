/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_test_cones_intersect_caps.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/22 15:55:46 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cones_tests.h"

int test_cones_intersect_caps(void)
{
	t_shape			c;
	t_ray			r;
	t_intersection	*xs;
	int				i;

	c = cone();
	c.minimum = -0.5;
	c.maximum = 0.5;
	c.closed = true;
	
	r = ray(point(0, 0, -5), tnorm(vector(0, 1, 0)));
	xs = local_intersect_cone(&c, r);
	if (xs[0].t || xs[0].object)
		return (-1);
	xs[0].object = NULL;

	r = ray(point(0, 0, -0.25), tnorm(vector(0, 1, 1)));
	xs = local_intersect_cone(&c, r);
	i = 0;
	while (xs[i].object)
		i++;
	if (i != 2)
		return (-1);
	xs[0].object = NULL;

	r = ray(point(0, 0, -0.25), tnorm(vector(0, 1, 0)));
	xs = local_intersect_cone(&c, r);
	i = 0;
	while (xs[i].object)
		i++;
	if (i != 4)
		return (-1);

	xs[0].object = NULL;
	free_shape(&c);
	return (0);
}
