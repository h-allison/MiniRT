/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_test_refract_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:02:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/21 05:24:22 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refraction_tests.h"

int test_refract_color(void)
{
	t_world			w;
	t_ray			r;
	t_intersection	*xs;
	t_comps			comps;
	t_rgb			col;

	w = default_world();
	w.s[0].m.ambient = 1.0;
	free_matrix(w.s[0].m.pattern.transform, 4);
	free_matrix(w.s[0].m.pattern.invtrans, 4);
	w.s[0].m.pattern = create_test_pattern();
	w.s[1].m.transparency = 1.0;
	w.s[1].m.refractive_index = 1.5;
	r = ray(point(0, 0, 0.1), vector(0, 1, 0));
	xs = intersections(intersection(-0.9899, &w.s[0]),
			intersection(-0.4899, &w.s[1]));
	xs = intersections(intersection(0.4899, &w.s[1]),
			intersection(0.9899, &w.s[0]));
	comps = prepare_computations(&xs[2], &r, xs);
	xs[0].object = NULL;
	col = refracted_color(&w, &comps, 5);
	if (!fisequal(col.r, 0) || !fisequal(col.g, 0.997872) || !fisequal(col.b, 0.047472))
		return (-1);
	free_world(&w);
	return (0);
}
