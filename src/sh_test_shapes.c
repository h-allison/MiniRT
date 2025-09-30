/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_test_shapes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:39 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/30 17:56:13 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* TEST FUNCTIONS, PROTOTYPES */

t_tuple	local_normal_at(t_shape *s, t_tuple local_point)
{
	t_tuple	local_normal;

	(void)s;
	local_normal = tsub(local_point, point(0, 0, 0));
	return (local_normal);
}

t_shape	*create_test_shape(void)
{
	t_shape	*s;

	s = malloc(sizeof(t_shape));
	s->parent = NULL;
	s->group = NULL;
	s->triangle = NULL;
	s->transform = create_id_matrix();
	s->invtrans = minvert(s->transform, 4);
	s->local_normal_at = local_normal_at;
	s->local_intersect = local_intersect;
	s->m = material();
	return (s);
}

t_shape	*glass_sphere(void)
{
	t_shape	*s;

	s = malloc(sizeof(t_shape));
	s->parent = NULL;
	s->group = NULL;
	s->triangle = NULL;
	s->transform = create_id_matrix();
	s->invtrans = minvert(s->transform, 4);
	s->local_normal_at = local_normal_at_sphere;
	s->local_intersect = local_intersect_sphere;
	s->m = material();
	s->m->transparency = 1.0;
	s->m->refractive_index = 1.5;
	return (s);
}
