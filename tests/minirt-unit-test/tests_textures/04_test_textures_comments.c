/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_test_textures_comments.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/24 01:11:37 by mmillhof         ###   ########.fr       */
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

int	test_textures_comments(void)
{
	t_canvas *canvas;

	canvas = canvas_from_ppm("tests_textures/04_test.ppm");
	if (!canvas
			|| !cisequal(pixel_at(canvas, 0, 0), (t_rgb){1, 1, 1})
			|| !cisequal(pixel_at(canvas, 1, 0), (t_rgb){1, 0, 1}))
		return (-1);
	return (0);
}
