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

int	parse_shape(char **tokens, t_world *world)
{
	static	int	s_i;
	
	(void)tokens;
	(void)world;
	(void)s_i;
	return(0);;
}


int	parse_into_world(char **tokens, t_data *data)
{
	if (tokens[0][0] >= 'A' && tokens[0][0] <= 'Z')
		return (parse_singular_element(tokens, data->world, data));
	// when ambient is encountered, save to apply to all objects at the end
	return (0);
}
