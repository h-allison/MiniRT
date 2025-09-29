/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cyl_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 20:24:30 by hallison          #+#    #+#             */
/*   Updated: 2025/09/29 20:26:45 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cyl_position(char *token, t_shape *s)
{
	t_tuple	pos;

	pos = point(0, 0, 0);
	if (rt_atof_tuple(token, &pos) != 0)
		return (rt_error("cy: cylinder position: invalid input", -1));
	s->transform = mmultfree(translation(pos.x, pos.y, pos.z), s->transform);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
	return (0);
}
