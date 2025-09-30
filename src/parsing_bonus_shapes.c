/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_shapes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:59:16 by hallison          #+#    #+#             */
/*   Updated: 2025/09/30 20:26:59 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_shape_bonus(char *shape, char **tokens, t_shape *s)
{
	int	t_i;
	int	ret;

	t_i = 0;
	ret = 0;
	while (tokens[t_i])
	{
		if (rt_strcmp(tokens[t_i], "ambient") == 0)
			ret = (bonus_ambient(shape, tokens + t_i, s, &t_i));
		else if (rt_strcmp(tokens[t_i], "diffuse") == 0)
			ret = (bonus_diffuse(shape, tokens + t_i, s, &t_i));
		else if (rt_strcmp(tokens[t_i], "specular") == 0)
			ret = (bonus_specular(shape, tokens + t_i, s, &t_i));
		else
			ret = rt_error_e(shape, "unknown specifier in bonus", -1);
		if (ret != 0)
			return (-1);
	}
	return (0);
}
