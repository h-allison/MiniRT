/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:32:13 by hallison          #+#    #+#             */
/*   Updated: 2025/09/29 17:21:33 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void vector_to_rotation(t_tuple v, float *angle)
{
	float	hypot_0;

	if (fisequal(v.x, 0))
	{
		angle[0] = -atan2f(v.z, v.y);
		if (fisequal(v.z, 0))
			angle[1] = 0;
		else
			angle[1] = -M_PI_2;
	}
	else
	{
		hypot_0 = sqrtf(v.y * v.y + v.x * v.x);
		angle[0] = -atan2f(v.x, v.y);
		angle[1] = -atan2f(v.z, hypot_0);
	}
}

bool	btwn_negative_and_positive_1(t_tuple t)
{
	if (t.x < -1 || t.x > 1)
		return (false);
	if (t.y < -1 || t.y > 1)
		return (false);
	if (t.z < -1 || t.z > 1)
		return (false);
	return (true);
}

int	check_v_normalized(t_tuple v, char *element)
{
	if (!btwn_negative_and_positive_1(v))
		return (rt_error_e(element, "must be in range [-1.0, 1.0]", -1));
	if (fisequal(v.x, 0) && fisequal(v.y, 0) && fisequal(v.z, 0))
		return (rt_error_e(element, "cannot be zero", -1));
	v = tnorm(v);
	return (0);
}

void	debug_print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		printf("\t[%i] %s \n", i, tokens[i]);
		i++;
	}
}

bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\0')
		return (true);
	return (false);
}
