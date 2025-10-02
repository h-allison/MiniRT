/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_world.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:55:40 by hallison          #+#    #+#             */
/*   Updated: 2025/09/29 18:56:32 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	distribute_ambient(t_world *world)
{
	int	i;

	i = 0;
	while (world->s[i] != NULL)
	{
		world->s[i]->m->ambient = world->ambient_ratio;
		i++;
	}
}

int	parse_singular_element(char **tokens, t_world *world, t_data *data)
{
	if (tokens[0][0] == 'A' && tokens[0][1] == '\0')
	{
		if (parse_ambient(tokens, world) == -1)
			return (-1);
	}
	else if (tokens[0][0] == 'C' && tokens[0][1] == '\0')
	{
		if (parse_camera(tokens, data) == -1)
			return (-1);
	}
	else if (tokens[0][0] == 'L' && tokens[0][1] == '\0')
	{
		if (parse_light(tokens, world) == -1)
			return (-1);
	}
	return (0);
}

int	rt_strcmp(char *token, char *s2)
{
	int	i;

	i = 0;
	while (token[i] != '\0' && s2[i] != '\0')
	{
		if (token[i] != s2[i])
			return (-1);
		i++;
	}
	if (token[i] != '\0' || s2[i] != '\0')
		return (-1);
	return (0);
}

int	parse_shape(char **tokens, t_world *world)
{
	int			ret;
	static int	s_i;

	ret = 0;
	if (rt_strcmp(tokens[0], "pl") == 0)
		ret = parse_plane(tokens, world, &s_i);
	else if (rt_strcmp(tokens[0], "sp") == 0)
		ret = parse_sphere(tokens, world, &s_i);
	else if (rt_strcmp(tokens[0], "cy") == 0)
		ret = parse_cyl(tokens, world, &s_i);
	else if (BONUS == true && rt_strcmp(tokens[0], "cb") == 0)
		ret = parse_cube(tokens, world, &s_i);
	else if (BONUS == true && rt_strcmp(tokens[0], "cn") == 0)
		ret = parse_cone(tokens, world, &s_i);
	else
	{
		debug_print_tokens(tokens);
		return (rt_error("parse_shape: unknown shape", -1));
	}
	return (ret);
}

int	parse_into_world(char **tokens, t_data *data)
{
	if (tokens[0][0] >= 'A' && tokens[0][0] <= 'Z')
		return (parse_singular_element(tokens, data->world, data));
	else
		return (parse_shape(tokens, data->world));
	return (0);
}
