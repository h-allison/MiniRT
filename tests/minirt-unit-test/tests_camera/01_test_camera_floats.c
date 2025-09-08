/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_camera_floats.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:52:32 by smargine          #+#    #+#             */
/*   Updated: 2025/09/08 14:48:47 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_tests.h"
#include "libunit.h"

int test_camera_floats(void)
{
	t_camera	c;

	c = camera(160, 120, M_PI / 2);
	if (fisequal(c.hsize, 160) && fisequal(c.vsize, 120)
			&& fisequal (c.field_of_view, (M_PI / 2)))
	{
		free_matrix(c.transform, 4);
		return (0);
	}
	free_matrix(c.transform, 4);
	return (-1);
}
