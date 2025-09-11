/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_shadow_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:52:32 by smargine          #+#    #+#             */
/*   Updated: 2025/09/11 11:44:16 by matthias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow_tests.h"
#include "libunit.h"

int test_shadow_in(void)
{
	t_largs			largs;
	t_rgb			col;

	largs.material.color = color(255, 255, 255);
	largs.material.ambient = 0.1;
	largs.material.diffuse = 0.9;
	largs.material.specular = 0.9;
	largs.material.shininess = 200;
	largs.material.pattern.status = false;
	largs.point = point(0, 0, 0);
	largs.eyev = vector(0, 0, -1);
	largs.normalv = vector(0, 0, -1);
	largs.light = point_light(point(0, 0, -10), color(255, 255, 255));
	largs.in_shadow = true;
	col = lighting(&largs);
	if (fisequal(col.r, 0.1), fisequal(col.r, 0.1), fisequal(col.r, 0.1))
	{
		return (0);
	}
	return (-1);
}
