/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_test_pattern_spherical_map.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:15:25 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/25 02:36:51 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"

int test_pattern_spherical_map(void)
{
	t_tuple		uv;

	uv = spherical_map(point(0, 0, -1));
	if (!fisequal(uv.x, 0) || !fisequal(uv.y, 0.5))
		return (-1);
	uv = spherical_map(point(1, 0, 0));
	if (!fisequal(uv.x, 0.25) || !fisequal(uv.y, 0.5))
		return (-1);
	uv = spherical_map(point(0, 0, 1));
	if (!fisequal(uv.x, 0.5) || !fisequal(uv.y, 0.5))
		return (-1);
	uv = spherical_map(point(-1, 0, 0));
	if (!fisequal(uv.x, 0.75) || !fisequal(uv.y, 0.5))
		return (-1);
	uv = spherical_map(point(0, 1, 0));
	if (!fisequal(uv.x, 0.5) || !fisequal(uv.y, 1.0))
		return (-1);
	uv = spherical_map(point(0 ,-1 ,0));
	if (!fisequal(uv.x, 0.5) || !fisequal(uv.y, 0))
		return (-1);
	uv = spherical_map(point(sqrtf(2)/2 ,sqrtf(2)/2 ,0));
	if (!fisequal(uv.x, 0.25) || !fisequal(uv.y, 0.75))
		return (-1);
	return (0);
}
