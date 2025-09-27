/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_test_textures_2D_checkers.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/27 17:32:48 by mmillhof         ###   ########.fr       */
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

int	test_textures_2D_checkers(void)
{
	t_canvas 	*canvas;
	t_pattern	*pattern;

	canvas = canvas_from_ppm("tests_textures/07_test.ppm");
	pattern = uv_image(canvas);
	if (!canvas
			|| !cisequal(uv_image_at(pattern, (t_tuple){0, 0, 0 ,0}), (t_rgb){0.9, 0.9, 0.9})
			|| !cisequal(uv_image_at(pattern, (t_tuple){0.3, 0, 0, 0}), (t_rgb){0.2, 0.2, 0.2})
			|| !cisequal(uv_image_at(pattern, (t_tuple){0.6, 0.3, 0, 0}), (t_rgb){0.1, 0.1, 0.1})
			|| !cisequal(uv_image_at(pattern, (t_tuple){1, 1, 0, 0}), (t_rgb){0.9, 0.9, 0.9}))
		return (free_pattern(pattern), -1);
	return (free_pattern(pattern), 0);
}
