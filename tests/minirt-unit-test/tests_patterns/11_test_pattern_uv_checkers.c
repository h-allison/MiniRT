/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_test_pattern_uv_checkers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:03:46 by hallison          #+#    #+#             */
/*   Updated: 2025/09/21 10:20:35 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"

int test_pattern_uv_checkers(void)
{
	t_rgb		black;
	t_rgb		white;
	t_pattern	checkers;
	t_rgb		col;
	t_tuple		uv;

	black = color(0 ,0 ,0);
	white = color(255, 255, 255);
	checkers = uv_checkers_pattern(2, 2, black, white);
	uv.x = 0;
	uv.y = 0;
	col = uv_checkers_at(&checkers, uv);
	if (col.r != black.r
		|| col.g != black.g
		|| col.b != black.b)
		return (-1);
	uv.x = 0.5;
	uv.y = 0;
	col = uv_checkers_at(&checkers, uv);
	if (col.r != white.r
		|| col.g != white.g
		|| col.b != white.b)
		return (-1);
	uv.x = 0;
	uv.y = 0.5;
	col = uv_checkers_at(&checkers, uv);
	if (col.r != white.r
		|| col.g != white.g
		|| col.b != white.b)
		return (-1);
	uv.x = 0.5;
	uv.y = 0.5;
	col = uv_checkers_at(&checkers, uv);
	if (col.r != black.r
		|| col.g != black.g
		|| col.b != black.b)
		return (-1);
	uv.x = 1.0;
	uv.y = 1.0;
	col = uv_checkers_at(&checkers, uv);
	if (col.r != black.r
		|| col.g != black.g
		|| col.b != black.b)
		return (-1);
	return (0);
}
