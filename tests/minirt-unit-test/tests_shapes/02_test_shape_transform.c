/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_test_shape_transform.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:22:10 by hallison          #+#    #+#             */
/*   Updated: 2025/09/25 01:27:21 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes_tests.h"

// Tests that transforms can be applied to shapes

int test_shape_transform(void)
{
	t_shape		*s;
	int			x;
	int			y;
	float		**tm;

	s = create_test_shape();
	set_transform(s, translation(2, 3, 4));
	tm = translation(2, 3, 4);
	y = 0;
	while(y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (!fisequal(s->transform[y][x], tm[y][x]))
			{
				free_matrix(tm, 4);
				free_shape(s);
				return(-1);
			}
			x++;
		}
		y++;
	}
	free_matrix(tm, 4);
	free_shape(s);
	return(0);
}
