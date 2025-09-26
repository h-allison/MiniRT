/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_schlick_total.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:26:50 by hallison          #+#    #+#             */
/*   Updated: 2025/09/26 16:40:23 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "refraction_tests.h"

int test_refract_schlick_total(void)
{
	t_ray			r;
	t_intersection	*xs;
	t_comps			comps;
	t_shape			*s;
	float			reflectance;

	s = glass_sphere();
	r = ray(point(0, 0, sqrtf(2)/2), vector(0, 1, 0));
	xs = intersections(intersection(-sqrtf(2)/2, s),
			intersection(sqrtf(2)/2, s));
	comps = prepare_computations(&xs[1], &r, xs);
	xs[0].object = NULL;
	reflectance = schlick(&comps);
	free_shape(s);
	if (reflectance != 1)
		return (-1);
	return (0);
}
