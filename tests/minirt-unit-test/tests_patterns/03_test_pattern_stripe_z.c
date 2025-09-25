/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_test_pattern_stripe_z.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:45:25 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/25 01:58:39 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"

int test_pattern_stripe_z(void)
{
	t_pattern	*pat;
	t_rgb		col;

	pat = stripe_pattern(color(0, 0, 0), color(255, 255, 255));
	col = stripe_at(pat, point(0, 0, 0));
	if (col.r != 0 || col.g != 0 || col.b != 0)
		return (free_pattern(pat), -1);
	col = stripe_at(pat, point(0, 0, 1));
	if (col.r != 0 || col.g != 0 || col.b != 0)
		return (free_pattern(pat), -1);
	col = stripe_at(pat, point(0, 0, 2));
	if (col.r != 0 || col.g != 0 || col.b != 0)
		return (free_pattern(pat), -1);
	return (free_pattern(pat), 0);
}
