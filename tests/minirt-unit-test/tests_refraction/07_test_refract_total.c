/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_test_refract_total.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:02:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/16 12:07:11 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refraction_tests.h"

int test_refract_total(void)
{
	t_world			w;
	t_ray			r;
	t_intersection	*xs;
	t_comps			comps;
	t_rgb			col;

	w = default_world();
	w.s[0].m.transparency = 1.0;
	w.s[0].m.refractive_index = 1.5;
	r = ray(point(0, 0, sqrtf(2)/2), vector(0, 1, 0));
	xs = intersections(intersection(-sqrtf(2)/2, &w.s[0]),
			intersection(sqrtf(2)/2, &w.s[0]));
	comps = prepare_computations(&xs[1], &r, xs);
	col = refracted_color(&w, &comps, 0);
	if (col.r != 0 || col.g != 0 || col.b !=0)
		return (-1);
	return (0);
}
