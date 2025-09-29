/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_shadehit_reflective_and_transparent.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:06:34 by hallison          #+#    #+#             */
/*   Updated: 2025/09/26 16:40:56 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refraction_tests.h"

int test_shadehit_reflective_and_transparent(void)
{
	t_world			w;
	t_ray			r;
	t_shape			*floor;
	t_shape			*ball;

	t_intersection	*xs;
	t_comps			comps;
	t_rgb			col;

	w = default_world();
	r = ray(point(0, 0, -3), vector(0, -sqrtf(2)/2, sqrtf(2)/2));

	floor = plane();
	set_transform(floor, translation(0, -1, 0));
	floor->m->reflective = 0.5;
	floor->m->transparency = 0.5;
	floor->m->refractive_index = 1.5;

	ball = sphere();
	ball->m->color = color(255, 0, 0);
	ball->m->ambient = 0.5;
	set_transform(ball, translation(0, -3.5, -0.5));

	w.s[2] = floor;
	w.s[3] = ball;
	w.s[4] = NULL;

	xs = intersections(intersection(sqrtf(2), floor),
			intersection(sqrtf(2), floor));
	comps = prepare_computations(&xs[0], &r, xs);
	xs[0].object = NULL;
	
	col = shade_hit(&w, &comps, 5);
	xs[0].object = NULL;
	free_world(&w);
	if (!fisequal(col.r, 0.933891))
		return (-1);
	if (!fisequal(col.g, 0.696412))
		return (-1);
	if (!fisequal(col.b, 0.692405))
		return (-1);
	return (0);
}
