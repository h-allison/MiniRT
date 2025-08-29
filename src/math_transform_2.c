/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_transform_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:10:28 by hallison          #+#    #+#             */
/*   Updated: 2025/08/29 15:27:07 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	**shearing(float *shear)
{
	float	**transform;

	transform = create_id_matrix();
	transform[0][1] = shear[0];
	transform[0][2] = shear[1];
	transform[1][0] = shear[2];
	transform[1][2] = shear[3];
	transform[2][0] = shear[4];
	transform[2][1] = shear[5];
	return (transform);
}
