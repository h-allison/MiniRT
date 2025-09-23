/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_test_camera_rayforpixel_1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:52:32 by smargine          #+#    #+#             */
/*   Updated: 2025/09/23 02:03:35 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_tests.h"
#include "libunit.h"

int test_camera_rayforpixel_1(void)
{
	t_camera	*c;
	t_ray		r;
	int			err;

	c = camera(201, 101, M_PI / 2);
	r = ray_for_pixel(c, 100, 50);
	err = !fisequal(r.origin.x, 0);
	err += !fisequal(r.origin.y, 0);
	err += !fisequal(r.origin.z, 0);
	err += !fisequal(r.origin.w, 1);
	err += !fisequal(r.direction.x, 0);
	err += !fisequal(r.direction.y, 0);
	err += !fisequal(r.direction.z, -1);
	if (err)
	{
		free_matrix(c->transform, 4);
		return (-1);
	}
	free_matrix(c->transform, 4);
	return (0);
}
