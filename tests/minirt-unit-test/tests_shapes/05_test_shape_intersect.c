/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_test_shape_intersect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:35:47 by hallison          #+#    #+#             */
/*   Updated: 2025/09/25 01:37:46 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes_tests.h"

int test_shape_intersect(void)
{
	t_shape	*s;
	t_ray	r;

	s = create_test_shape();
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	set_transform(s, scaling(2, 2, 2));
	intersect(s, r);
	if (!fisequal(s->saved_ray.origin.x, 0)
			|| !fisequal(s->saved_ray.origin.y, 0)
			|| !fisequal(s->saved_ray.origin.z, -2.5)
			|| !fisequal(s->saved_ray.direction.x, 0)
			|| !fisequal(s->saved_ray.direction.y, 0)
			|| !fisequal(s->saved_ray.direction.z, 0.5))
		return(free_shape(s), -1);
	return(free_shape(s), 0);
}
