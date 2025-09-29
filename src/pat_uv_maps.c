/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pat_uv_maps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:11:08 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 19:11:24 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	no_map(t_tuple p)
{
	t_tuple	uv;
	uv.x = p.x;
	uv.y = p.y;
	return (uv);
}

t_tuple	spherical_map(t_tuple p)
{
	float	theta;
	float	radius;
	float	phi;
	float	raw_u;
	t_tuple	 uv;

	theta = atan2f(p.x, p.z);
	radius = tmag(vector(p.x, p.y, p.z));
	phi = acosf(p.y / radius);
	raw_u = theta / (2 * M_PI);
	uv.x = 1 - (raw_u + 0.5);
	uv.y = 1 - phi / M_PI;
	return (uv);
}

t_tuple	cylindrical_map(t_tuple p)
{
	float	theta;
	float	raw_u;
	t_tuple	 uv;

	theta = atan2f(p.x, p.z);
	raw_u = theta / (2 * M_PI);
	uv.x = 1 - (raw_u + 0.5);
	uv.y = fmod(p.y, 1);
	return (uv);
}

t_tuple	planar_map(t_tuple p)
{
	t_tuple	uv;

	uv.x = fmod(p.x, 1);
	uv.y = fmod(p.z, 1);
	return (uv);
}

t_tuple	cube_map(t_tuple point)
{
	float	abs_x;
	float	abs_y;
	float	abs_z;
	float	coord;

	abs_x = fabs(point.x);
	abs_y = fabs(point.y);
	abs_z = fabs(point.z);
	coord = maxf(abs_x, abs_y, abs_z);

	if (coord == point.x)
		return (cube_uv_right(point));
	else if (coord == -point.x)
		return (cube_uv_left(point));
	else if (coord == point.y)
		return (cube_uv_up(point));
	else if (coord == -point.y)
		return (cube_uv_down(point));
	else if (coord == point.z)
		return (cube_uv_front(point));
return (cube_uv_back(point));
}
