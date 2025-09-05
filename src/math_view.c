/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:38:47 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/05 23:56:50 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	**view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple	forward;
	t_tuple	left;
	t_tuple	true_up;
	float	**orientation;

	forward = tsub(to, from);
	forward = tnorm(forward);
	left = cross(forward, tnorm(up));
	true_up = cross(left, forward);
	orientation = create_id_matrix();
	orientation[0][0] = left.x;
	orientation[0][1] = left.y;
	orientation[0][2] = left.z;
	orientation[1][0] = true_up.x;
	orientation[1][1] = true_up.y;
	orientation[1][2] = true_up.z;
	orientation[2][0] = -forward.x;
	orientation[2][1] = -forward.y;
	orientation[2][2] = -forward.z;
	return (mmultfree(orientation, translation(-from.x, -from.y, -from.z)));
}
