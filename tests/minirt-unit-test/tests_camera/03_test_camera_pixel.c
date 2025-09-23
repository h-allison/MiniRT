/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_test_camera_pixel.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:52:32 by smargine          #+#    #+#             */
/*   Updated: 2025/09/23 02:02:50 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_tests.h"
#include "libunit.h"

int test_camera_pixel(void)
{
	t_camera	*c;

	c = camera(200, 125, M_PI / 2);
	if (fisequal(c->pixel_size, 0.01))
	{
		free_matrix(c->transform, 4);
		return (0);
	}
	free_matrix(c->transform, 4);
	return (-1);
}
