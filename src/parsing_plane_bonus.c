/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plane_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:59:16 by hallison          #+#    #+#             */
/*   Updated: 2025/09/30 19:08:00 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	bonus_specular(char *element, char **tokens, t_shape *s, int *t_i)
{
	float	value;

	if (!tokens[1])
		return (rt_error_e(element, "specular: invalid input", -1));
	if (rt_atof(tokens[1], &value) != 0)
		return (rt_error_e(element, "specular: invalid input", -1));
	if (value < 0 || value > 1)
		return (rt_error_e(element, "specular: must be in range [-1, 1.0]", -1));
	s->m->specular = value;	
	(void) t_i;
	return (0);
}

int	bonus_diffuse(char *element, char **tokens, t_shape *s, int *t_i)
{
	float	value;

	printf("in bonus_diffuse\n");
	printf("s->m is currently: = %p \n", &s->m);
	printf("diffuse is currently: s->m->diffuse = %f\n", s->m->diffuse);
	printf("tokens[1] = %s\n", tokens[1]);
	printf("tokens[2] = %s\n", tokens[2]);
	if (!tokens[1])
		return (rt_error_e(element, "diffuse: invalid input", -1));
	if (rt_atof(tokens[1], &value) != 0)
		return (rt_error_e(element, "diffuse: invalid input", -1));
	if (value < 0 || value > 1)
		return (rt_error_e(element, "diffuse: must be in range [-1, 1.0]", -1));
	s->m->diffuse = value;
	(void) t_i;
	return (0);
}

// TODO found an instance of ambient > 1 (line 453 in scenes_world). Should it really be capped?

int	bonus_ambient(char *element, char **tokens, t_shape *s, int *t_i)
{
	float	value;

	if (!tokens[1])
		return (rt_error_e(element, "ambient: invalid input", -1));
	if (rt_atof(tokens[1], &value) != 0)
		return (rt_error_e(element, "ambient: invalid input", -1));
	if (value < 0 || value > 1)
		return (rt_error_e(element, "ambient: must be in range [-1, 1.0]", -1));
	s->m->ambient = value;	
	(void) t_i;
	return (0);
}

int	parse_plane_bonus(char **tokens, t_shape *s)
{
	int	t_i;
	int	ret;

	t_i = 0;
	ret = 0;
	while(tokens[t_i])
	{
		if (rt_strcmp(tokens[t_i], "ambient") == 0)
			ret = (bonus_ambient("pl", tokens, s + t_i, &t_i));
		else if (rt_strcmp(tokens[t_i], "diffuse") == 0)
		{
			printf("Skipping diffuse assignment for now\n");
		//	ret = (bonus_diffuse("pl", tokens, s + t_i, &t_i));
		}		
		else if (rt_strcmp(tokens[t_i], "specular") == 0)
			ret = (bonus_specular("pl", tokens, s + t_i, &t_i));
		else
		{	
			ret = rt_error("pl: unknown specifier in bonus", -1);
			printf("tokens[t_i] = %s\n", tokens[t_i]);
		}
		if (ret != 0)
			return (-1);
		else
			t_i = t_i + 2;
	}
//	printf("\npl: ambient = %f\n", s->m->ambient);
//	printf("pl: diffuse = %f\n", s->m->diffuse);
//	printf("pl: specular = %f\n", s->m->specular);
	return (0);
}
