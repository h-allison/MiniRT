/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_shapes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:59:16 by hallison          #+#    #+#             */
/*   Updated: 2025/10/02 16:53:12 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	bonus_transparency(char *element, char **tokens, t_shape *s, int *t_i);
int	bonus_refractive_index(char *element, char **tokens, t_shape *s, int *t_i);

int	ambient_diff_spec(char *shape, char **tokens, t_shape *s, int *t_i)
{
	int	ret;

	ret = 0;
	if (rt_strcmp(tokens[0], "ambient") == 0)
		ret = (bonus_ambient(shape, tokens, s, t_i));
	else if (rt_strcmp(tokens[0], "diffuse") == 0)
		ret = (bonus_diffuse(shape, tokens, s, t_i));
	else if (rt_strcmp(tokens[0], "specular") == 0)
		ret = (bonus_specular(shape, tokens, s, t_i));
	return (ret);
}

int	parse_shape_bonus(char *shape, char **tks, t_shape *s)
{
	int	t_i;
	int	ret;

	t_i = 0;
	ret = 0;
	while (tks[t_i])
	{
		if (rt_strcmp(tks[t_i], "ambient") == 0
			|| rt_strcmp(tks[t_i], "diffuse") == 0
			|| rt_strcmp(tks[t_i], "specular") == 0)
			ret = ambient_diff_spec(shape, tks + t_i, s, &t_i);
		else if (rt_strcmp(tks[t_i], "shininess") == 0)
			ret = (bonus_shininess(shape, tks + t_i, s, &t_i));
		else if (rt_strcmp(tks[t_i], "reflective") == 0)
			ret = (bonus_reflective(shape, tks + t_i, s, &t_i));
		else if (rt_strcmp(tks[t_i], "transparency") == 0)
			ret = (bonus_transparency(shape, tks + t_i, s, &t_i));
		else if (rt_strcmp(tks[t_i], "refractive_index") == 0)
			ret = (bonus_refractive_index(shape, tks + t_i, s, &t_i));
		else
			ret = rt_error_e(shape, "unknown specifier in bonus", -1);
		if (ret != 0)
			return (-1);
	}
	return (0);
}

int	bonus_transparency(char *element, char **tokens, t_shape *s, int *t_i)
{
	float	value;

	if (!tokens[1])
		return (rt_error_e(element, "transparency: invalid input", -1));
	if (rt_atof(tokens[1], &value) != 0)
		return (rt_error_e(element, "transparency: invalid input", -1));
	if (value < 0 || value > 1)
		return (rt_error_e(element, "transparency: must be btwn [0, 1]", -1));
	s->m->transparency = value;
	*t_i = *t_i + 2;
	return (0);
}

int	bonus_refractive_index(char *element, char **tokens, t_shape *s, int *t_i)
{
	float	value;

	if (!tokens[1])
		return (rt_error_e(element, "refractive_index: invalid input", -1));
	if (rt_atof(tokens[1], &value) != 0)
		return (rt_error_e(element, "refractive_index: invalid input", -1));
	if (value < 0 || value > 10)
		return (rt_error_e(element, "refractive_index: must be btwn 0-10", -1));
	s->m->refractive_index = value;
	*t_i = *t_i + 2;
	return (0);
}
