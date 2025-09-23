/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_schlick_n2_bigger_n1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:41:33 by hallison          #+#    #+#             */
/*   Updated: 2025/09/23 03:23:29 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refraction_tests.h"

int test_schlick_n2_bigger_n1(void)
{
	t_ray			r;
	t_intersection	*xs;
	t_comps			comps;
	t_shape			*s;
	float			reflectance;

	s = glass_sphere();
	r = ray(point(0, 0.99, -2), vector(0, 0, 1));
	xs = intersections(intersection(1.8589, s),
			intersection(1.8589, s));
	comps = prepare_computations(&xs[0], &r, xs);
	xs[0].object = NULL;
	reflectance = schlick(&comps);
	if (!fisequal(reflectance, 0.48873))
		return (-1);
	free_shape(s);
	return (0);
}
