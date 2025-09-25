/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_test_shape_normal_translate.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:35:47 by hallison          #+#    #+#             */
/*   Updated: 2025/09/25 01:42:12 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes_tests.h"

int test_shape_normal_translate(void)
{
	t_shape	*s;
	t_tuple	n;

	s = create_test_shape();
	set_transform(s, translation(0, 1, 0));
	n = normal_at(s, point(0, 1.70711, -0.70711));
	if (!fisequal(n.x, 0)
			|| !fisequal(n.y, 0.70711)
			|| !fisequal(n.z, -0.70711)
			|| !fisequal(n.w, 0))
		return(free_shape(s), -1);
	return(free_shape(s), 0);
}
