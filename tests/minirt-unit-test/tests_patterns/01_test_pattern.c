/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_pattern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:03:46 by hallison          #+#    #+#             */
/*   Updated: 2025/09/11 00:59:34 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"

int test_pattern_basic(void)
{
	t_rgb		black;
	t_rgb		white;
	t_pattern	pat;

	black = color(0 ,0 ,0);
	white = color(255, 255, 255);
	pat = stripe_pattern(white, black);
	if (pat.a.r == white.r
			&& pat.a.g == white.g
			&& pat.a.b == white.b
			&& pat.b.r == black.r
			&& pat.b.g == black.g
			&& pat.b.b == black.b)
		return (0);
	return (-1);
}
