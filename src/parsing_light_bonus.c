/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_light_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:05:15 by hallison          #+#    #+#             */
/*   Updated: 2025/09/29 20:28:51 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_light_rgb(char *token, t_light *light)
{
	t_rgb	col_255;
	t_rgb	col;
	float	brightness;

	col_255 = color(0, 0, 0);
	if (rt_atorgb(token, &col_255) != 0)
		return (rt_error("L: light color: invalid input", -1));
	brightness = light->intensity.r;
	if (!valid_rgb_range(col_255))
		return (rt_error("L: rgb values must be in range [0,255]", -1));
	col = color(col_255.r, col_255.g, col_255.b);
	light->intensity = cscale(col, brightness);
	return (0);
}

int	parse_light_bonus(char **tokens, t_light *light)
{
	if (tokens[3])
	{
		if (parse_light_rgb(tokens[3], light) != 0)
			return (-1);
	}
	if (tokens[4])
		return (rt_error("L: Extraneous args.", -1));
	return (0);
}
