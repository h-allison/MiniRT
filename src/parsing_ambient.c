/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ambient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:48:50 by hallison          #+#    #+#             */
/*   Updated: 2025/10/02 16:46:04 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient_rgb(char *token, t_world *world)
{
	t_rgb	temp_255;

	temp_255.r = 0;
	temp_255.g = 0;
	temp_255.b = 0;
	if (rt_atorgb(token, &temp_255) != 0)
		return (rt_error("A: ambient color: invalid input", -1));
	if (!valid_rgb_range(temp_255))
		return (rt_error("A: ambient color: rgb not in range 0-255", -1));
	world->ambient_rgb = color(temp_255.r, temp_255.g, temp_255.b);
	return (0);
}

int	parse_ambient_ratio(char *token, t_world *world)
{
	world->ambient_ratio = 0;
	if (rt_atof(token, &world->ambient_ratio) != 0)
		return (rt_error("A: ambient ratio: invalid input", -1));
	if (world->ambient_ratio < 0 || world->ambient_ratio > 1)
		return (rt_error("A: ambient ratio: must be in range [0.0, 1.0]", -1));
	return (0);
}
/*
t_rgb	rgb_norm(t_rgb c)
{
	float	magnitude;

	magnitude = sqrtf(c.r * c.r + c.b * c.b + c.g * c.g);
	c.r = c.r / magnitude;
	c.g = c.g / magnitude;
	c.b = c.b / magnitude;
	return (c);
}
*/

int	parse_ambient(char **tokens, t_world *world)
{
//	t_rgb	hue;

	if (!tokens[1])
		return (rt_error("A: ambient ratio: missing value", -1));
	if (parse_ambient_ratio(tokens[1], world) != 0)
		return (-1);
	if (!tokens[2])
		return (rt_error("A: ambient color: missing values", -1));
	if (parse_ambient_rgb(tokens[2], world) != 0)
		return (-1);
	if (tokens[3])
		return (rt_error("A: too many arguments", -1));
		/*
	hue = rgb_norm(world->ambient_rgb);
	world->ambient_total = cscale(hue, world->ambient_ratio);
	world->ambient_hue = hue;
	*/
	return (0);
}
