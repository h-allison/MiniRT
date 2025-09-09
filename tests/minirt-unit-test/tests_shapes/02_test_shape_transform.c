/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_test_shape_transform.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:22:10 by hallison          #+#    #+#             */
/*   Updated: 2025/09/09 18:43:46 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "shapes_tests.h"

// Tests that transforms can be applied to shapes

int test_shape_transform(void)
{
	t_object	s;
	int			x;
	int			y;
	float		**tm;

	s = create_test_shape();
	set_transform(&s, translation(2, 3, 4));
	tm = translation(2, 3, 4);
	y = 0;
	while(y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (!fisequal(s.transform[y][x], tm[y][x]))
			{
				free_matrix(tm, 4);
				free_matrix(s.transform, 4);
				return(-1);
			}
			x++;
		}
		y++;
	}
	free_matrix(tm, 4);
	free_matrix(s.transform, 4);
	return (0);
}
