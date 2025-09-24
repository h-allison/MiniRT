/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_world.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:55:40 by hallison          #+#    #+#             */
/*   Updated: 2025/09/23 18:13:53 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int	rt_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1 && s2 && s1[i] == s2[i])
		i++;
	if (s1 || s2)
		return (-1);
	return (0);
}

int	parse_shape(char **tokens, t_world *world)
{
	static	int	s_i;
	int		ret;
	
	ret = 0;
	if (rt_strcmp(tokens[0], "pl"))
		ret = parse_plane(tokens, world, &s_i);
	else if (rt_strcmp(tokens[0], "sp"))
		ret = parse_sphere(tokens, world, &s_i);
/*
	else if (rt_strcmp(tokens[0], "cy"))
		ret = parse_cyl(tokens, world, &s_i);
	else if (rt_strcmp(tokens[0], "cb"))
		ret = parse_cube(tokens, world, &s_i);
	else if (rt_strcmp(tokens[0], "cn"))
		ret = parse_cone(tokens, world, &s_i);
*/
	else
		return(rt_error("parse_shape: unknown shape", -1));
	return (ret);	
}

int	parse_into_world(char **tokens, t_data *data)
{
	if (tokens[0][0] >= 'A' && tokens[0][0] <= 'Z')
		return (parse_singular_element(tokens, data->world, data));
	else
		return (parse_shape(tokens, data->world));
	// when ambient is encountered, save to apply to all objects at the end
	return (0);
}
