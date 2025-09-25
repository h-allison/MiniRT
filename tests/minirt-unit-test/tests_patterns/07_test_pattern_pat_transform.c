/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_test_pattern_pat_transform.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:45:38 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/25 02:29:10 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"

int test_pattern_pat_transform(void)
{
	t_rgb		c;
	t_shape		*obj;
	t_pattern	*pat;

	obj = sphere();
	pat = create_test_pattern();
	set_pattern_transform(pat, scaling(2, 2, 2));
	c = pattern_at_shape(pat, obj, point(2, 3, 4));
	free_shape(obj);
	free_pattern(pat);
	if (c.r != 1 || c.g != 1.5 || c.b != 2)
		return (-1);
	return (0);
}
