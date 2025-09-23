/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:51:51 by hallison          #+#    #+#             */
/*   Updated: 2025/09/22 16:30:52 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_light_rgb(char *token, t_rgb *rgb)
{
	if (rt_atorgb(token, rgb) != 0)
		return(rt_error("L: light color: invalid input", -1));
	printf("light color = %f, %f, %f\n", rgb->r, rgb->g, rgb->b);
	return (0);
}

int	parse_light_position(char *token, t_tuple *position)
{
	if (rt_atof_tuple(token, position) != 0)
		return(rt_error("L: light position: invalid input", -1));
	printf("Light position = %f, %f, %f, %f\n", position->x, position->y, position->z, position->w);
	return (0);
}

int	parse_light_intensity(char *token, float *intensity)
{
	if (rt_atof(token, intensity) != 0)
		return(rt_error("L: intensity: invalid input", -1));
	if (*intensity < 0 || *intensity > 1)
		return(rt_error("L: intensity: must be in range [0.0, 1.0]", -1));
	printf("intensity = %f\n", *intensity);
	return (0);
}

void	alloc_lights(t_world *world)
{
	world->light = malloc(world->checklist.count_light * sizeof(t_light));
	if (!world->light)
		exit(1);	
}

int	parse_light_bonus(char **tokens, t_world *world, int i)
{
	if (tokens[3])
	{
		world->light[i].rgb = color(0, 0, 0);
		if (parse_light_rgb(tokens[3], &world->light[i].rgb) != 0)
			return (rt_error("L: light color: invalid input", -1));
		if (!(valid_rgb_range(world->light[i].rgb))
			return (rt_error("L: light color: rgb not in range 0-255", -1));
		if (tokens[4])
			return(rt_error("L: Too many arguments.", -1));
	}	
	if (i = count_light - 1)
		world->light[i].last = true;
	else
		world->light[i].last = false;
	return (0);
}

int	parse_light_2(char **tokens, t_world *world, int i)
{
	if (tokens[3])
		return(rt_error("L: Too many arguments. Enable bonus to support color", -1));
	world->light[i].last = true;
	return (0);
}

int	parse_light_1(char **tokens, t_world *world, int i)
{
	if (!tokens[1])
		return(rt_error("L: light position: missing values", -1));
	world->light[i]->position = point(0, 0, 0);
	if (parse_light_position(tokens[1], &world->light[i]->position) != 0)
		return (-1);
	if (!tokens[2])
		return(rt_error("L: light intensity: missing values", -1));
	world->light[i]->intensity = 0;
	if (parse_light_intensity(tokens[2], &world->light[i].intensity) != 0)
		return (-1);
	if (world->light[i].intensity < 0 || world->light[i].intensity > 1)
		return(rt_error("L: light intensity: must be in range [0.0, 1.0]", -1));
	return (0);
}

int	parse_light(char **tokens, t_world *world)
{
	static	int	i;
	int			j;
	void (*funcs[3])(void) = {
		parse_light_position,
		parse_light_intensity,
		parse_light_rgb,
		parse_light_end };

	if (i == 0)
		alloc_lights(world);
	while (i < count_light)
	{

		if (parse_light_1(tokens, world, i) != 0)
			return (-1);	
		if (BONUS == true)
		{
			if (parse_light_bonus(tokens, world, i) != 0)
				return (-1);
		}
		else
		{
			if (parse_light_2(token, world, i) != 0)
				return (-1);
		}
		i++
	}
	return(0);
}

