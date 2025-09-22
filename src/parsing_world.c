/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_world.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:55:40 by hallison          #+#    #+#             */
/*   Updated: 2025/09/22 20:59:22 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


// TODO: Support for multiple lights in bonus version
int	parse_singular_element(char **tokens, t_world *world)
{
	if (tokens[0][0] == 'A' && tokens[0][1] == '\0')
	{	
		if (world->checklist->a_parsed == true)
			(return (ret_error("A: File contains more than one ambient\n"));
		if (parse_ambient(tokens, world) == -1)
			return(-1);
		world->checklist->a_parsed == true;
	}
	else if (tokens[0][0] == 'C' && tokens[0][1] == '\0')
	{	
		if (world->checklist->c_parsed == true)
			(return (ret_error("C: File contains more than 1 camera\n"));
		if (parse_camera(tokens, world) == -1)
			return(-1);
		world->checklist->c_parsed == true;
	}
	else if (tokens[0][0] == 'L' && tokens[0][1] == '\0')
	{	
		if (world->checklist->l_parsed == true && BONUS == false)
			(return (ret_error("C: File contains more than 1 light\n"));
		if (parse_light(tokens, world) == -1)
			return(-1);
		world->checklist->l_parsed == true;
	}
	return(0);	
}


int	parse_into_world(char **tokens, t_data *data)
{
	static	int		first_line;
	
	if (first_line == 0)
	{
		first_line = 1;
	}
	if (tokens[0][0] >= 'A' && tokens[0][0] <= 'Z')
		return (parse_singular_element(tokens, world));
	// when ambient is encountered, save to apply to all objects at the end
	/*
	(void) tokens;
	return (0);
	*/
	return (0);
}
