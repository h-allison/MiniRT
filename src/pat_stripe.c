/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pat_stripe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:12:15 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 19:19:38 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	*stripe_pattern(t_rgb a, t_rgb b)
{
	t_pattern	*pat;

	pat = malloc(sizeof(t_pattern));
	pat->a = a;
	pat->b = b;
	pat->transform = create_id_matrix();
	pat->invtrans = minvert(pat->transform, 4);
	pat->pattern_at = stripe_at;
	pat->uv_pattern = NULL;
	pat->canvas = NULL;
	pat->status = true;
	return (pat);
}

t_rgb	stripe_at(t_pattern *pat, t_tuple point)
{
	if (fmod(floorf(point.x), 2) == 0)
		return (pat->a);
	return (pat->b);
}
