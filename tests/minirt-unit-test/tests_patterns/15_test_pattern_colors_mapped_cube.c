/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_test_pattern_colors_mapped_cube.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:15:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/25 02:49:44 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"

static bool	cisequal(t_rgb a, t_rgb b)
{
	if (a.r != b.r)
		return (false);
	if (a.g != b.g)
		return (false);
	if (a.b != b.b)
		return (false);
	return (true);
}

int	test_pattern_colors_mapped_cube(void)
{
	t_rgb	red;	
	t_rgb	yellow;
	t_rgb	brown;
	t_rgb	green;
	t_rgb	cyan;
	t_rgb	blue;
	t_rgb	purple;
	t_rgb	white;
	t_pattern	*left;
	t_pattern	*front;
	t_pattern	*right;
	t_pattern	*back;
	t_pattern	*up;
	t_pattern	*down;
	t_tuple		p;

	red = color(255, 0, 0);
	yellow = color(255, 255, 0);
	brown = color(255, 127, 0);
	green = color(0, 255, 0);
	cyan = color(0, 255, 255);
	blue = color(0, 0, 255);
	purple = color(255, 0, 255);
	white = color(255, 255, 255);

	left = uv_align_check(yellow, cyan, red, blue, brown);
	p = cube_map(point(-1, 0, 0));
	if (!cisequal(uv_align_check_at(left, p), yellow))
		return (free_pattern(left), -1);
	p = cube_map(point(-1, 0.9, -0.9));
	if (!cisequal(uv_align_check_at(left, p), cyan))
		return (free_pattern(left), -1);
	p = cube_map(point(-1, 0.9, 0.9));
	if (!cisequal(uv_align_check_at(left, p), red))
		return (free_pattern(left), -1);
	p = cube_map(point(-1, -0.9, -0.9));
	if (!cisequal(uv_align_check_at(left, p), blue))
		return (free_pattern(left), -1);
	p = cube_map(point(-1, -0.9, 0.9));
	if (!cisequal(uv_align_check_at(left, p), brown))
		return (free_pattern(left), -1);
	free_pattern(left);
	front = uv_align_check(cyan, red, yellow, brown, green);
	p = cube_map(point(0, 0, 1));
	if (!cisequal(uv_align_check_at(front, p), cyan))
		return (free_pattern(front), -1);
	p = cube_map(point(-0.9, 0.9, 1));
	if (!cisequal(uv_align_check_at(front, p), red))
		return (free_pattern(front), -1);
	p = cube_map(point(0.9, 0.9, 1));
	if (!cisequal(uv_align_check_at(front, p), yellow))
		return (free_pattern(front), -1);
	p = cube_map(point(-0.9, -0.9, 1));
	if (!cisequal(uv_align_check_at(front, p), brown))
		return (free_pattern(front), -1);
	p = cube_map(point(0.9, -0.9, 1));
	if (!cisequal(uv_align_check_at(front, p), green))
		return (free_pattern(front), -1);
	free_pattern(front);
	right = uv_align_check(red, yellow, purple, green, white);
	p = cube_map(point(1, 0, 0));
	if (!cisequal(uv_align_check_at(right, p), red))
		return (free_pattern(right), -1);
	p = cube_map(point(1, 0.9, 0.9));
	if (!cisequal(uv_align_check_at(right, p), yellow))
		return (free_pattern(right), -1);
	p = cube_map(point(1, 0.9, -0.9));
	if (!cisequal(uv_align_check_at(right, p), purple))
		return (free_pattern(right), -1);
	p = cube_map(point(1, -0.9, 0.9));
	if (!cisequal(uv_align_check_at(right, p), green))
		return (free_pattern(right), -1);
	p = cube_map(point(1, -0.9, -0.9));
	if (!cisequal(uv_align_check_at(right, p), white))
		return (free_pattern(right), -1);
	free_pattern(right);
	back = uv_align_check(green, purple, cyan, white, blue);
	p = cube_map(point(0, 0, -1));
	if (!cisequal(uv_align_check_at(back, p), green))
		return (free_pattern(back), -1);
	p = cube_map(point(0.9, 0.9, -1));
	if (!cisequal(uv_align_check_at(back, p), purple))
		return (free_pattern(back), -1);
	p = cube_map(point(-0.9, 0.9, -1));
	if (!cisequal(uv_align_check_at(back, p), cyan))
		return (free_pattern(back), -1);
	p = cube_map(point(0.9, -0.9, -1));
	if (!cisequal(uv_align_check_at(back, p), white))
		return (free_pattern(back), -1);
	p = cube_map(point(-0.9, -0.9, -1));
	if (!cisequal(uv_align_check_at(back, p), blue))
		return (free_pattern(back), -1);
	free_pattern(back);
	up = uv_align_check(brown, cyan, purple, red, yellow);
	p = cube_map(point(0, 1, 0));
	if (!cisequal(uv_align_check_at(up, p), brown))
		return (free_pattern(up), -1);
	p = cube_map(point(-0.9, 1, -0.9));
	if (!cisequal(uv_align_check_at(up, p), cyan))
		return (free_pattern(up), -1);
	p = cube_map(point(0.9, 1, -0.9));
	if (!cisequal(uv_align_check_at(up, p), purple))
		return (free_pattern(up), -1);
	p = cube_map(point(-0.9, 1, 0.9));
	if (!cisequal(uv_align_check_at(up, p), red))
		return (free_pattern(up), -1);
	p = cube_map(point(0.9, 1, 0.9));
	if (!cisequal(uv_align_check_at(up, p), yellow))
		return (free_pattern(up), -1);
	free_pattern(up);
	down = uv_align_check(purple, brown, green, blue, white);
	p = cube_map(point(0, -1, 0));
	if (!cisequal(uv_align_check_at(down, p), purple))
		return (free_pattern(down), -1);
	p = cube_map(point(-0.9, -1, 0.9));
	if (!cisequal(uv_align_check_at(down, p), brown))
		return (free_pattern(down), -1);
	p = cube_map(point(0.9, -1, 0.9));
	if (!cisequal(uv_align_check_at(down, p), green))
		return (free_pattern(down), -1);
	p = cube_map(point(-0.9, -1, -0.9));
	if (!cisequal(uv_align_check_at(down, p), blue))
		return (free_pattern(down), -1);
	p = cube_map(point(0.9, -1, -0.9));
	if (!cisequal(uv_align_check_at(down, p), white))
		return (free_pattern(down), -1);
	return (free_pattern(down), 0);
}   
