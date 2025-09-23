/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_test_shape_normal_transform.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:35:47 by hallison          #+#    #+#             */
/*   Updated: 2025/09/23 01:58:56 by mmillhof         ###   ########.fr       */
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

int test_shape_normal_transform(void)
{
	t_shape	*s;
	float	**m;
	t_tuple	n;

	s = create_test_shape();
	m = mmultfree(scaling(1, 0.5, 1), rotation_z(M_PI / 5));
	set_transform(s, m);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
	n = normal_at(s, point(0, M_PI / 2, -M_PI / 2));
	if (fisequal(n.x, 0)
			&& fisequal(n.y, 0.97014)
			&& fisequal(n.z, -0.24254)
			&& fisequal(n.w, 0))
		return (free_matrices_and_return(s, 0));
	return (free_matrices_and_return(s, -1));
}
