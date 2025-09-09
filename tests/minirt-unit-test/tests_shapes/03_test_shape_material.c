/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_test_shape_material.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:35:47 by hallison          #+#    #+#             */
/*   Updated: 2025/09/09 18:35:48 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "shapes_tests.h"

int test_shape_material(void)
{
	t_object	s;
	int			x;
	int			y;
	float		**idm;

	s = create_test_shape();
	idm = create_id_matrix();
	y = 0;
	while(y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (!fisequal(s.transform[y][x], idm[y][x]))
			{
				free_matrix(idm, 4);
				free_matrix(s.transform, 4);
				return(-1);
			}
			x++;
		}
		y++;
	}
	free_matrix(idm, 4);
	free_matrix(s.transform, 4);
	return (0);
}
