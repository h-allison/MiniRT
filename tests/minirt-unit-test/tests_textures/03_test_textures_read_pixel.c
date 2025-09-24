/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_test_textures_read_pixel.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/24 00:34:56 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cones_tests.h"

static bool	cisequal(t_rgb a, t_rgb b)
{
	if (!fisequal(a.r, b.r))
		return (false);
	if (!fisequal(a.g, b.g))
		return (false);
	if (!fisequal(a.b, b.b))
		return (false);
	return (true);
}

int	test_textures_read_pixel(void)
{
	t_canvas *canvas;

	canvas = canvas_from_ppm("tests_textures/03_test.ppm");
	if (!canvas
			|| !cisequal(pixel_at(canvas, 0, 0), (t_rgb){1, 0.498, 0})
			|| !cisequal(pixel_at(canvas, 1, 0), (t_rgb){0, 0.498, 1})
			|| !cisequal(pixel_at(canvas, 2, 0), (t_rgb){0.498, 1, 0})
			|| !cisequal(pixel_at(canvas, 3, 0), (t_rgb){1, 1, 1})
			|| !cisequal(pixel_at(canvas, 0, 1), (t_rgb){0, 0, 0})
			|| !cisequal(pixel_at(canvas, 1, 1), (t_rgb){1, 0, 0})
			|| !cisequal(pixel_at(canvas, 2, 1), (t_rgb){0, 1, 0})
			|| !cisequal(pixel_at(canvas, 3, 1), (t_rgb){0, 0, 1})
			|| !cisequal(pixel_at(canvas, 0, 2), (t_rgb){1, 1, 0})
			|| !cisequal(pixel_at(canvas, 1, 2), (t_rgb){0, 1, 1})
			|| !cisequal(pixel_at(canvas, 2, 2), (t_rgb){1, 0, 1})
			|| !cisequal(pixel_at(canvas, 3, 2), (t_rgb){0.498, 0.498, 0.498}))
		return (-1);
	return (0);
}
