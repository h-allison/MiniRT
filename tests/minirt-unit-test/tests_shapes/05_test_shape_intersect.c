/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_test_shape_intersect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:35:47 by hallison          #+#    #+#             */
/*   Updated: 2025/09/23 01:53:59 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes_tests.h"

static int	free_matrices_and_return(t_shape *p, int ret)
{
	if (p->transform)
		free_matrix(p->transform, 4);
	if (p->invtrans)
		free_matrix(p->invtrans, 4);
	if (p->m->pattern->transform)
		free_matrix(p->m->pattern->transform, 4);
	if (p->m->pattern->invtrans)
		free_matrix(p->m->pattern->invtrans, 4);
	return (ret);
}

int test_shape_intersect(void)
{
	t_shape	*s;
	t_ray	r;

	s = create_test_shape();
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	set_transform(s, scaling(2, 2, 2));
	intersect(s, r);
	if (fisequal(s->saved_ray.origin.x, 0)
			&& fisequal(s->saved_ray.origin.y, 0)
			&& fisequal(s->saved_ray.origin.z, -2.5))
		if (fisequal(s->saved_ray.direction.x, 0)
				&& fisequal(s->saved_ray.direction.y, 0)
				&& fisequal(s->saved_ray.direction.z, 0.5))
			return(free_matrices_and_return(s, 0));
	return(free_matrices_and_return(s, -1));
}
