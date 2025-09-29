/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_test_textures_size.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/27 17:31:52 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures_tests.h"

int	test_textures_size(void)
{
	t_canvas *canvas;

	canvas = canvas_from_ppm("tests_textures/02_test.ppm");
	if (!canvas || canvas->width != 10 || canvas->height != 2)
		return (free_canvas(canvas), -1);
	return (free_canvas(canvas), 0);
}
