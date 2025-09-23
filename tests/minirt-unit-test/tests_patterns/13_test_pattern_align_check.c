/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_test_pattern_align_check.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:15:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/23 02:42:05 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"

int test_pattern_align_check(void)
{
	t_rgb		main;
	t_rgb		ul;
	t_rgb		ur;
	t_rgb		bl;
	t_rgb		br;
	t_rgb		c;
	t_tuple		uv;
	t_pattern	*pattern;
	
	main = color(1, 1, 1);
	ul = color(1, 0, 0);
	ur = color(1, 1, 0);
	bl = color(0, 1, 0);
	br = color(0, 1, 1);

	pattern = uv_align_check(main, ul, ur, bl, br);
	uv.x = 0.5;
	uv.y = 0.5;
	c = uv_align_check_at(pattern, uv);
	if (!fisequal(c.r, main.r) || !fisequal(c.g, main.g)
			|| !fisequal(c.b, main.b))
		return (-1);
	uv.x = 0.1;
	uv.y = 0.9;
	c = uv_align_check_at(pattern, uv);
	if (!fisequal(c.r, ul.r) || !fisequal(c.g, ul.g)
			|| !fisequal(c.b, ul.b))
		return (-1);
	uv.x = 0.9;
	uv.y = 0.9;
	c = uv_align_check_at(pattern, uv);
	if (!fisequal(c.r, ur.r) || !fisequal(c.g, ur.g)
			|| !fisequal(c.b, ur.b))
		return (-1);
	uv.x = 0.1;
	uv.y = 0.1;
	c = uv_align_check_at(pattern, uv);
	if (!fisequal(c.r, bl.r) || !fisequal(c.g, bl.g)
			|| !fisequal(c.b, bl.b))
		return (-1);
	uv.x = 0.9;
	uv.y = 0.1;
	c = uv_align_check_at(pattern, uv);
	if (!fisequal(c.r, br.r) || !fisequal(c.g, br.g)
			|| !fisequal(c.b, br.b))
		return (-1);
	return (0);
}
