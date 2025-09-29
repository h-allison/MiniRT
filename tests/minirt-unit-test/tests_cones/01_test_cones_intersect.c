/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_cones_intersect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/27 16:35:46 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cones_tests.h"

int test_cones_intersect(void)
{
	t_shape			*c;
	t_ray			r;
	t_intersection	*xs;

	c = cone();
	
	r = ray(point(0, 0, -5), tnorm(vector(0, 0, 1)));
	xs = local_intersect_cone(c, r);
	if (!fisequal(xs[0].t, 5) || !fisequal(xs[1].t, 5))
		return (-1);
	xs[0].object = NULL;
	r = ray(point(0, 0, -5), tnorm(vector(1, 1, 1)));
	xs = local_intersect_cone(c, r);
	if (!fisequal(xs[0].t, 8.660254) || !fisequal(xs[1].t, 8.660254))
		return (-1);
	xs[0].object = NULL;
	r = ray(point(1, 1, -5), tnorm(vector(-0.5, -1, 1)));
	xs = local_intersect_cone(c, r);
	if (!fisequal(xs[0].t, 4.55006) || !fisequal(xs[1].t, 49.44994))
		return (-1);
	xs[0].object = NULL;
	free_shape(c);
	return (0);
}
