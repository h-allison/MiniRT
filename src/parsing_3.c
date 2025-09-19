/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:19:08 by hallison          #+#    #+#             */
/*   Updated: 2025/09/18 17:54:06 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
int	rgb_input_format(char *tokens)
{
	return (0);
}

int	parse_ambient_rgb(char **tokens, t_world *world)
{
	int		i;
	char	r[4];
	char	g[4];
	char	b[4];
	char	rgb[4];

	i = 0;
	if (!valid_rgb_values(rgb, str))
	{
		free(rgb_str);
		return(rt_error("Ambient color must be format [255,255,255]", -1));
	}
}
*/

int	parse_ambient_ratio(char *token, t_world *world)
{
	char	*ambient_str;
	int		ret;

	ret = 0;
	ambient_str = token;
	ret = rt_atof(ambient_str, &world->ambient_ratio);
	if (ret != 0)
		return(rt_error("A: ambient ratio: invalid input", -1));
	if (world->ambient_ratio < 0 || world->ambient_ratio > 1)
		return(rt_error("A: ambient ratio: must be in range [0.0, 1.0]", -1));
	printf("Ambient ratio = %f\n", world->ambient_ratio);
	return (0);
}

int	parse_ambient(char **tokens, t_world *world)
{
	if (!tokens[1])
		return(rt_error("A: ambient ratio: missing value", -1));
	if (parse_ambient_ratio(tokens[1], world) != 0)
		return (-1);
	/*
	if (!tokens[2])
		return(rt_error("A: field 2: Ambient RGB required", -1));
	if (parse_ambient_rgb != 0)
		return (-1);
	if (tokens[3])
		return(rt_error("A : should contain only 2 fields", -1));
*/	return(0);
}

int	parse_singular_element(char **tokens, t_data *data)
{
	if (tokens[0][0] == 'A' && tokens[0][1] == '\0')
	{	
		if (parse_ambient(tokens, data->world) == -1)
			return(-1);
	}
	else if (tokens[0][0] == 'C' && tokens[0][1] == '\0')
	   printf("<parse into Camera>\n");	
	else if (tokens[0][0] == 'L' && tokens[0][1] == '\0')
	   printf("<parse into Light>\n");	
	return(0);	
}

void	init_checklist(t_checklist *checklist)
{
	checklist->a_parsed = false;
	checklist->c_parsed = false;
	checklist->l_parsed = false;
}

int	parse_into_world(char **tokens, t_data *data)
{
//	t_preworld		preworld;
	static	int		first_line;
	
	(void) tokens;
	(void) data;

	if (first_line == 0)
	{
		data->world = malloc(sizeof(t_world));
		if (!data->world)
			exit (1);
		init_checklist(&data->world->checklist);
		first_line = 1;
	}
	if (tokens[0][0] >= 'A' && tokens[0][0] <= 'Z')
		parse_singular_element(tokens, data);
	
	// when ambient is encountered, save to apply to all objects at the end
	/*
	(void) tokens;
	return (0);
	*/
	return (0);
}
