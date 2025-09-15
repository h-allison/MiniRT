/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_test_refract_color_opaque.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:02:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/16 00:24:25 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refraction_tests.h"

int test_refract_color_opaque(void)
{
	t_world			w;
	t_ray			r;
	t_intersection	*xs;
	t_comps			comps;
	t_rgb			col;

	w = default_world();
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	xs = intersections(intersection(4, &w.s[0]),
			intersection(6, &w.s[0]));
	comps = prepare_computations(&xs[0], &r, xs);
	col = refracted_color(&w, &comps, 5);
	if (col.r != 0 || col.g != 0 || col.b !=0)
		return (-1);
	return (0);
}
