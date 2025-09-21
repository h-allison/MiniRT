/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_schlick_perpendicular.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:39:00 by hallison          #+#    #+#             */
/*   Updated: 2025/09/21 04:37:50 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "refraction_tests.h"

int test_refract_schlick_perpendicular(void)
{
	t_ray			r;
	t_intersection	*xs;
	t_comps			comps;
	t_shape			s;
	float			reflectance;

	s = glass_sphere();
	r = ray(point(0, 0, 0), vector(0, 1, 0));
	xs = intersections(intersection(-1, &s),
			intersection(1, &s));
	comps = prepare_computations(&xs[1], &r, xs);
	xs[0].object = NULL;
	reflectance = schlick(&comps);
	if (!fisequal(reflectance, 0.04))
		return (-1);
	free_shape(&s);
	return (0);
}
