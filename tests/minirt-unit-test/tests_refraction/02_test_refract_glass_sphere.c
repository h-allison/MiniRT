/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_test_refract_glass_sphere.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:02:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/26 16:37:36 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refraction_tests.h"

int test_refract_glass_sphere(void)
{
	t_shape *s;
	float	**idm;
	int		x;
	int		y;

	s = glass_sphere();
	idm = create_id_matrix();
	
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x <4)
		{
			if (s->transform[y][x] != idm[y][x])
				return (free_shape(s), -1);
			x ++;
		}
		y++;
	}
	free_matrix(idm, 4);
	if (s->m->transparency != 1.0 || s->m->refractive_index != 1.5)
		return (free_shape(s), -1);
	
	return (free_shape(s), 0);
}
