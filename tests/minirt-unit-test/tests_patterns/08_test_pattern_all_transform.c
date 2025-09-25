/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_test_pattern_all_transform.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:45:38 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/25 02:28:38 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"

int test_pattern_all_transform(void)
{
	t_rgb		c;
	t_shape		*obj;
	t_pattern	*pat;

	obj = sphere();
	set_transform(obj, scaling(2, 2, 2));
	pat = create_test_pattern();
	set_pattern_transform(pat, translation(0.5, 1, 1.5));
	c = pattern_at_shape(pat, obj, point(2.5, 3, 3.5));
	free_shape(obj);
	free_pattern(pat);
	if (c.r != 0.75 || c.g != 0.5 || c.b != 0.25)
		return (-1);
	return (0);
}
