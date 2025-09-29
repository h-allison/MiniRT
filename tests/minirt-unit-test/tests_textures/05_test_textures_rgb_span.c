/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_test_textures_rgb_span.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/27 17:32:28 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures_tests.h"

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

int	test_textures_rgb_span(void)
{
	t_canvas *canvas;

	canvas = canvas_from_ppm("tests_textures/05_test.ppm");
	if (!canvas
			|| !cisequal(pixel_at(canvas, 0, 0), (t_rgb){0.2, 0.6, 0.8}))
		return (free_canvas(canvas), -1);
	return (free_canvas(canvas), 0);
}
