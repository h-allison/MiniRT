/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_test_pattern_obj_transform.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:45:38 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/12 21:27:26 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"

int test_pattern_obj_transform(void)
{
	t_rgb		c;
	t_shape		obj;
	t_pattern	pat;

	obj = sphere();
	set_transform(&obj, scaling(2, 2, 2));
	pat = create_test_pattern();
	c = pattern_at_shape(&pat, &obj, point(2, 3, 4));
	free_matrices_and_ret(&obj, 0);
	if (c.r != 1 || c.g != 1.5 || c.b != 2)
		return (-1);
	return (0);
}
