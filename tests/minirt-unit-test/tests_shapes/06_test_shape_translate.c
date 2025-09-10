/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_test_shape_translate.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:35:47 by hallison          #+#    #+#             */
/*   Updated: 2025/09/10 02:27:20 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes_tests.h"

int test_shape_translate(void)
{
	t_object		s;
	t_ray			r;
	t_intersection	*xs;

	s = create_test_shape();
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	set_transform(&s, translation(5, 0, 0));
	xs = intersect(&s, r);
	if (fisequal(s.saved_ray.origin.x, -5)
			&& fisequal(s.saved_ray.origin.y, 0)
			&& fisequal(s.saved_ray.origin.z, -5))
		if (fisequal(s.saved_ray.direction.x, 0)
				&& fisequal(s.saved_ray.direction.y, 0)
				&& fisequal(s.saved_ray.direction.z, 1))
			return (0);
	return (-1);
}
