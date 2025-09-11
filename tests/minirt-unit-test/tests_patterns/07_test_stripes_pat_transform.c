/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_test_stripes_pat_transform.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:45:38 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/12 00:50:14 by matthias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"

int test_stripes_pat_transform(void)
{
	t_rgb		black;
	t_rgb		white;
	t_rgb		c;
	t_shape		obj;
	t_pattern	pat;

	black = color(0 ,0 ,0);
	white = color(255, 255, 255);
	obj = sphere();
	pat = stripe_pattern(white, black);
	set_pattern_transform(&pat, scaling(2, 2, 2));
	c = stripe_at_object(pat, obj, point(1.5, 0, 0));
	if (c.r != 1 || c.g != 1 || c.b != 1)
		return (-1);
	return (0);
}
