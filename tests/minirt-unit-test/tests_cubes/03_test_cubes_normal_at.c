/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_test_cubes_normal_at.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/16 23:31:28 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubes_tests.h"

int test_cubes_normal_at(void)
{
	t_shape	c;
	t_tuple	n;

	c = cube();
	n = local_normal_at_cube(&c, point(1, 0.5, -0.8));
	if (n.x != 1 || n.y != 0 || n.z != 0)
		return (-1);
	n = local_normal_at_cube(&c, point(-1, -0.2, 0.9));
	if (n.x != -1 || n.y != 0 || n.z != 0)
		return (-1);
	n = local_normal_at_cube(&c, point(-0.4, 1, -0.1));
	if (n.x != 0 || n.y != 1 || n.z != 0)
		return (-1);
	n = local_normal_at_cube(&c, point(0.3, -1, -0.7));
	if (n.x != 0 || n.y != -1 || n.z != 0)
		return (-1);
	n = local_normal_at_cube(&c, point(-0.6, 0.3, 1));
	if (n.x != 0 || n.y != 0 || n.z != 1)
		return (-1);
	n = local_normal_at_cube(&c, point(0.4, 0.4, -1));
	if (n.x != 0 || n.y != 0 || n.z != -1)
		return (-1);
	n = local_normal_at_cube(&c, point(1, 1, 1));
	if (n.x != 1 || n.y != 0 || n.z != 0)
		return (-1);
	n = local_normal_at_cube(&c, point(-1, -1, -1));
	if (n.x != -1 || n.y != 0 || n.z != 0)
		return (-1);
	return (0);
}
