/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pat_gradient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:57:21 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 20:33:11 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	*gradient_pattern(t_rgb a, t_rgb b)
{
	t_pattern	*gradient;

	gradient = malloc(sizeof(t_pattern));
	gradient->a = a;
	gradient->b = b;
	gradient->transform = create_id_matrix();
	gradient->invtrans = minvert(gradient->transform, 4);
	gradient->pattern_at = gradient_at;
	gradient->uv_pattern = NULL;
	gradient->canvas = NULL;
	gradient->status = true;
	return (gradient);
}

t_rgb	gradient_at(t_pattern *gradient, t_tuple point)
{
	t_rgb	distance;
	float	fraction;

	distance = csub(gradient->b, gradient->a);
	fraction = point.x - floorf(point.x);
	return (cadd(gradient->a, cscale(distance, fraction)));
}
