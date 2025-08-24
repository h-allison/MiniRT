/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tuples_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:20:01 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/24 22:35:42 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	tmult(t_tuple a, float scalar)
{
	t_tuple	result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;
	result.w = a.w * scalar;
	return (result);
}

t_tuple	tdiv(t_tuple a, float scalar)
{
	t_tuple	result;

	result.x = a.x / scalar;
	result.y = a.y / scalar;
	result.z = a.z / scalar;
	result.w = a.w / scalar;
	return (result);
}


float	tmag(t_tuple a)
{
	return sqrtf(powf(a.x, 2) + powf(a.y, 2) + powf(a.z, 2) + powf(a.w, 2));
}

t_tuple	tnorm(t_tuple a)
{
	int		magnitude;
	t_tuple	result;

	magnitude = tmag(a);
	result.x = a.x / magnitude;
	result.y = a.y / magnitude;
	result.z = a.z / magnitude;
	result.w = a.w / magnitude;
	return (result);	
}
