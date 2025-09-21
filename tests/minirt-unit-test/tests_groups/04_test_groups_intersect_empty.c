/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_test_groups_intersect_empty.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/21 03:49:20 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "groups_tests.h"

int test_groups_intersect_empty(void)
{
	t_shape			g;
	t_intersection	*xs;

	g = group();
	g.saved_ray = ray(point(0, 0, 0), vector(0, 0, 1));
	xs = local_intersect_group(&g);

	if (xs[0].object)
		return (-1);
	free_shape(&g);
	return (0);
}
