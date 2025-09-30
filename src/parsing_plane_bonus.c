/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plane_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:59:16 by hallison          #+#    #+#             */
/*   Updated: 2025/09/30 16:50:55 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	bonus_ambient(char *element, char **tokens, t_shape *s, int *t_i)
{
	float	value;

	if (rt_atof(tokens[1], &value) != 0)
		return (rt_error_e(element, "ambient: invalid input", -1));
	s->m->ambient = value;	
	*t_i = (*t_i) + 2;
	return (0);
}

int	parse_plane_bonus(char **tokens, t_shape *s)
{
	int	t_i;

	t_i = 0;
	while(tokens[t_i] != NULL)
	{
		if (rt_strcmp(tokens[t_i], "ambient") == 0)
		{
			if (bonus_ambient("pl", tokens, s + t_i, &t_i) != 0)
				return (-1);
		}
		else
			t_i++;
	}
	return (0);
}
