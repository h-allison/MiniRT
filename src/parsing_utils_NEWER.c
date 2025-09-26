/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:32:13 by hallison          #+#    #+#             */
/*   Updated: 2025/09/24 13:03:56 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	float	len;
	t_tuple	n;

	if (!btwn_negative_and_positive_1(v))
		return (rt_error_e(element, "must be in range [-1.0, 1.0]", -1));
	if (fisequal(v.x, 0) && fisequal(v.y, 0) && fisequal(v.z, 0))
		return (rt_error_e(element, "cannot be zero", -1));
	len = v.x * v.x + v.y * v.y + v.z * v.z;
	if (!fisequal(len, 1))
	{
		n = tnorm(v);
		rt_error_e(element, "must be normalized", -1);
		printf("Hint: Your input normalized = %f, %f, %f\n", n.x, n.y, n.z);
		return(-1);
	}
	return (0);
}

// TODO remove later if unused
/*
float	**create_orientation_matrix(t_tuple norm)
{
	t_tuple	left;
	t_tuple	true_up;
	t_tuple up;
	float	**orientation;

	// TODO check if norm and up are parallel
	up = vector(DEFAULT_UP);
	left = cross(norm, tnorm(up));
	true_up = cross(left, norm);
	orientation = create_id_matrix();
	orientation[0][0] = left.x;
	orientation[0][1] = left.y;
	orientation[0][2] = left.z;
	orientation[1][0] = true_up.x;
	orientation[1][1] = true_up.y;
	orientation[1][2] = true_up.z;
	orientation[2][0] = -norm.x;
	orientation[2][1] = -norm.y;
	orientation[2][2] = -norm.z;
	return (orientation);
}
*/

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


