/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_fields.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:01:30 by hallison          #+#    #+#             */
/*   Updated: 2025/09/30 20:02:39 by hallison         ###   ########.fr       */
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
	if (value < 0 || value > 10)
		return (rt_error_e(element, "specular: must be btwn [-1, 10]", -1));
	s->m->specular = value;
	*t_i = *t_i + 2;
	return (0);
}

int	bonus_diffuse(char *element, char **tokens, t_shape *s, int *t_i)
{
	float	value;

	if (!tokens[1])
		return (rt_error_e(element, "diffuse: invalid input", -1));
	if (rt_atof(tokens[1], &value) != 0)
		return (rt_error_e(element, "diffuse: invalid input", -1));
	if (value < 0 || value > 10)
		return (rt_error_e(element, "diffuse: must be btwn [-1, 10]", -1));
	s->m->diffuse = value;
	*t_i = *t_i + 2;
	return (0);
}

// TODO found an instance of ambient > 1 (line 453 in scenes_world).
// Should it really be capped?

int	bonus_ambient(char *element, char **tokens, t_shape *s, int *t_i)
{
	float	value;

	if (!tokens[1])
		return (rt_error_e(element, "ambient: invalid input", -1));
	if (rt_atof(tokens[1], &value) != 0)
		return (rt_error_e(element, "ambient: invalid input", -1));
	if (value < 0 || value > 10)
		return (rt_error_e(element, "ambient: must be in range [-1, 10]", -1));
	s->m->ambient = value;
	*t_i = *t_i + 2;
	return (0);
}
