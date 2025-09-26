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

//	if (!btwn_negative_and_positive_1(v))
		//return (rt_error_e(element, "must be in range [-1.0, 1.0]", -1));
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
