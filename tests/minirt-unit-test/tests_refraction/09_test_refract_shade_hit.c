/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_test_refract_shade_hit.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:08:03 by hallison          #+#    #+#             */
/*   Updated: 2025/09/30 16:06:20 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refraction_tests.h"

int test_refract_shade_hit(void)
{
	t_world			*w;
	t_shape			*floor;
	t_shape			*ball;
	t_ray			r;
	t_intersection	*xs;
	t_comps			comps;
	t_rgb			col;

	w = default_world();
	floor = plane();
	set_transform(floor, translation(0, -1, 0));
	floor->m->transparency = 0.5;
	floor->m->refractive_index = 1.5;

	ball = sphere();
	ball->m->color = color(255, 0, 0);
	ball->m->ambient = 0.5;
	set_transform(ball, translation(0, -3.5, -0.5));

	w->s[2] = floor;
	w->s[3] = ball;
	w->s[4] = NULL;

	r = ray(point(0, 0, -3), vector(0, -sqrtf(2)/2, sqrtf(2)/2));
	xs = intersections(intersection(sqrtf(2), w->s[2]),
			intersection(sqrtf(2), w->s[2]));
	comps = prepare_computations(&xs[0], &r, xs);
	xs[0].object = NULL;
	col = shade_hit(w, &comps, 5);
	if (!fisequal(col.r, 0.93642) || !fisequal(col.g, 0.68642) || !fisequal(col.b, 0.68642))
		return (-1);
	free_world(w);
	return (0);
}
