/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_test_camera_rayforpixel_3.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:52:32 by smargine          #+#    #+#             */
/*   Updated: 2025/09/25 00:09:05 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_tests.h"
#include "libunit.h"

int test_camera_rayforpixel_3(void)
{
	t_camera	*c;
	t_ray		r;
	int			err;

	c = camera(201, 101, M_PI / 2);
	free_matrix(c->transform, 4);
	c->transform = mmultfree(rotation_y(M_PI / 4), translation(0, -2, 5));
	r = ray_for_pixel(c, 100, 50);
	err = !fisequal(r.origin.x, 0);
	err += !fisequal(r.origin.y, 2);
	err += !fisequal(r.origin.z, -5);
	err += !fisequal(r.origin.w, 1);
	err += !fisequal(r.direction.x, sqrtf(2) / 2);
	err += !fisequal(r.direction.y, 0);
	err += !fisequal(r.direction.z, -sqrtf(2) / 2);
	if (err)
	{
		free_matrix(c->transform, 4);
		free(c);
		return (-1);
	}
	free_matrix(c->transform, 4);
	free(c);
	return (0);
}
