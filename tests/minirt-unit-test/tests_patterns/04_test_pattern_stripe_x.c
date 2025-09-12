/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_test_pattern_stripe_x.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:45:38 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/12 19:58:40 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"

int test_pattern_stripe_x(void)
{
	t_pattern	pat;
	t_rgb		col;

	pat = stripe_pattern(color(0, 0, 0), color(255, 255, 255));
	col = stripe_at(&pat, point(0, 0, 0));
	if (col.r != 0 || col.g != 0 || col.b != 0)
		return (-1);
	col = stripe_at(&pat, point(0.9, 0, 0));
	if (col.r != 0 || col.g != 0 || col.b != 0)
		return (-1);
	col = stripe_at(&pat, point(1, 0, 0));
	if (col.r != 1 || col.g != 1 || col.b != 1)
		return (-1);
	col = stripe_at(&pat, point(-0.1, 0, 0));
	if (col.r != 1 || col.g != 1 || col.b != 1)
		return (-1);
	col = stripe_at(&pat, point(-1, 0, 0));
	if (col.r != 1 || col.g != 1 || col.b != 1)
		return (-1);
	col = stripe_at(&pat, point(-1.1, 0, 0));
	if (col.r != 0 || col.g != 0 || col.b != 0)
		return (-1);
	return (0);
}
