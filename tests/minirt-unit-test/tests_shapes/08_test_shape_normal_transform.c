/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_test_shape_normal_transform.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:35:47 by hallison          #+#    #+#             */
/*   Updated: 2025/09/10 03:12:21 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes_tests.h"

int test_shape_normal_transform(void)
{
	t_shape	s;
	float	**m;
	t_tuple	n;

	s = create_test_shape();
	m = mmultfree(scaling(1, 0.5, 1), rotation_z(M_PI / 5));
	set_transform(&s, m);
	n = normal_at(&s, point(0, M_PI / 2, -M_PI / 2));
	free_matrix(s.transform, 4);
	if (fisequal(n.x, 0)
			&& fisequal(n.y, 0.97014)
			&& fisequal(n.z, -0.24254)
			&& fisequal(n.w, 0))
		return (0);
	return (-1);
}
