/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_shadow_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 02:50:15 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 23:23:54 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow_tests.h"
#include "libunit.h"

int test_shadow_in(void)
{
	t_largs	*largs;
	t_rgb	col;

	largs = calloc(1, sizeof(*largs));
	largs->shape = NULL;
	largs->material = material();
	largs->point = point(0, 0, 0);
	largs->eyev = vector(0, 0, -1);
	largs->normalv = vector(0, 0, -1);
	largs->light = point_light(point(0, 0, -10), color(255, 255, 255));
	largs->in_shadow = 0;
	col = lighting(largs);
	free_largs(largs);
	if (fisequal(col.r, 0.1), fisequal(col.r, 0.1), fisequal(col.r, 0.1))
	{
		return (0);
	}
	return (-1);
}
