/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:18:30 by hallison          #+#    #+#             */
/*   Updated: 2025/08/29 15:10:13 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	**translation(float x, float y, float z)
{
	float	**transform;

	transform = create_id_matrix();
	transform[0][3] = x;
	transform[1][3] = y;
	transform[2][3] = z;
	return (transform);
}

float	**scaling(float x, float y, float z)
{
	float	**transform;

	transform = create_id_matrix();
	transform[0][0] = x;
	transform[1][1] = y;
	transform[2][2] = z;
	return (transform);
}

float	**rotation_x(float r)
{
	float	**transform;

	transform = create_id_matrix();
	transform[1][1] = cos(r);
	transform[1][2] = -sin(r);
	transform[2][1] = sin(r);
	transform[2][2] = cos(r);
	return (transform);
}

float	**rotation_y(float r)
{
	float	**transform;

	transform = create_id_matrix();
	transform[0][0] = cos(r);
	transform[0][2] = sin(r);
	transform[2][0] = -sin(r);
	transform[2][2] = cos(r);
	return (transform);
}

float	**rotation_z(float r)
{
	float	**transform;

	transform = create_id_matrix();
	transform[0][0] = cos(r);
	transform[0][1] = -sin(r);
	transform[1][0] = sin(r);
	transform[1][1] = cos(r);
	return (transform);
}
