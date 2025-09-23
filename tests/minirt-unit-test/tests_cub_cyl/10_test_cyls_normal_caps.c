/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_test_cyls_normal_caps.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 21:24:15 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/23 03:35:43 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_cyl_tests.h"

int test_cyls_normal_caps(void)
{
	t_shape			*cyl;
	t_tuple			n;

	cyl = cylinder();
	cyl->minimum = 1;
	cyl->maximum = 2;
	cyl->closed = true;

	n = local_normal_at_cyl(cyl, point(0, 1, 0));
	if (n.x != 0 ||  n.y != -1 || n.z != 0)
		return(-1);
	n = local_normal_at_cyl(cyl, point(0.5, 1, 0));
	if (n.x != 0 ||  n.y != -1 || n.z != 0)
		return(-1);
	n = local_normal_at_cyl(cyl, point(0, 1, 0.5));
	if (n.x != 0 ||  n.y != -1 || n.z != 0)
		return(-1);
	n = local_normal_at_cyl(cyl, point(0, 2, 0));
	if (n.x != 0 ||  n.y != 1 || n.z != 0)
		return(-1);
	n = local_normal_at_cyl(cyl, point(0.5, 2, 0));
	if (n.x != 0 ||  n.y != 1 || n.z != 0)
		return(-1);
	n = local_normal_at_cyl(cyl, point(0, 2, 0.5));
	if (n.x != 0 ||  n.y != 1 || n.z != 0)
		return(-1);
	free_shape(cyl);
	return (0);
}
