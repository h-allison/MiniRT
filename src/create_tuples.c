/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tuples.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:37:34 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/23 21:18:14 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	point(float x, float y, float z)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = 1;
	return (tuple);
}

t_tuple	vector(float x, float y, float z)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = 0;
	return (tuple);
}

t_rgb	color(float r, float g, float b)
{
	t_rgb	rgb;

	if (r > 255 || r < 0)
	{
		printf("ERROR: Color input out of range\n");
		exit(1);
	}
	if (g > 255 || g < 0)
	{
		printf("ERROR: Color input out of range\n");
		exit(1);
	}
	if (b > 255 || b < 0)
	{
		printf("ERROR: Color input out of range\n");
		exit(1);
	}
	rgb.r = r / 255;
	rgb.g = g / 255;
	rgb.b = b / 255;
	return (rgb);
}

t_rgb	color_scale(float r, float g, float b, float scaling)
{
	t_rgb	rgb;

	if (r > scaling || r < 0)
	{
		printf("ERROR: Color input out of range\n");
		exit(1);
	}
	if (g > scaling || g < 0)
	{
		printf("ERROR: Color input out of range\n");
		exit(1);
	}
	if (b > scaling || b < 0)
	{
		printf("ERROR: Color input out of range\n");
		exit(1);
	}
	rgb.r = r / scaling;
	rgb.g = g / scaling;
	rgb.b = b / scaling;
	return (rgb);
}
