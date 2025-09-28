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

/*
	angle_1 is the angle on a triangle from (0,0,0) to the x,y point in v
	angle_1 is calculated using cos(theta) = adjacent / hypotenuse,
	where adjacent is y and hypotenuse is the square root of (X^2 + Y^2)

	angle_2 is the angle between the the (x,y,z) point and the hypotenuse
	of the first triangle.

	In "angle[1] = facos(hypot_0 / 1)", dividing by 1 is redundant, but
	serves to illustrate that the hypotenuse of the second triangle will
	always be 1, because it it measures the length of the unit vector.

	During the angle_1 calculations, a check is needed to avoid 
	dividing by zero. The hypotenuse will be 0 if (v.x == 0 && v.y == 0).
	In that case, angle_1 = 90 degrees. This is because v is normalized,
	and if x & y are both 0, then z must be 1 or -1. It is necessary to
	rotate down from the y axis by 90 degrees to point to the z axis.
*/

void vector_to_radians(t_tuple v, float angle[2])
{
	float	hypot_0;

	hypot_0 = sqrtf(v.y * v.y + v.x * v.x);
	if (fisequal(hypot_0, 0))
		angle[0] = M_PI_2;
	else
		angle[0] = acosf(v.y / hypot_0);
	angle[1] = acosf(hypot_0 / 1);
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
