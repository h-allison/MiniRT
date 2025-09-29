/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pat_ring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:58:07 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 19:03:13 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	*ring_pattern(t_rgb a, t_rgb b)
{
	t_pattern	*ring;

	ring = malloc(sizeof(t_pattern));
	ring->a = a;
	ring->b = b;
	ring->transform = create_id_matrix();
	ring->invtrans = minvert(ring->transform, 4);
	ring->pattern_at = ring_at;
	ring->uv_pattern = NULL;
	ring->canvas = NULL;
	ring->status = true;
	return (ring);
}

t_rgb	ring_at(t_pattern *ring, t_tuple point)
{
	if ((int)floorf(sqrtf(point.x * point.x + point.z * point.z)) % 2 == 0)
		return (ring->a);
	return (ring->b);
}
