/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:07:25 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/11 02:18:05 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	stripe_pattern(t_rgb a, t_rgb b)
{
	t_pattern	pat;

	pat.a = a;
	pat.b = b;
	return (pat);
}

t_rgb	stripe_at(t_pattern pat, t_tuple point)
{
	if (fisequal(fmodf(point.x, 2),0))
	{
		return (pat.a);
	}
	return (pat.b);
}
