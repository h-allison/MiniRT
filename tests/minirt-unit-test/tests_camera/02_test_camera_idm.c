/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_test_camera_idm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:52:32 by smargine          #+#    #+#             */
/*   Updated: 2025/09/08 14:47:59 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_tests.h"
#include "libunit.h"

int test_camera_idm(void)
{
	t_camera	c;
	float		**idm;
	int			y;
	int			x;

	idm = create_id_matrix();
	c = camera(WIN_WIDTH, WIN_HEIGHT, M_PI / 2);
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (c.transform[y][x] != idm[y][x])
			{
				free_matrix(idm, 4);
				free_matrix(c.transform, 4);
				return (-1);
			}
			x++;
		}
		y++;
	}
	free_matrix(idm, 4);
	free_matrix(c.transform, 4);
	return (0);
}
