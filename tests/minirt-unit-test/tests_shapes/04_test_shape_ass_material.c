/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_test_shape_ass_material.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:35:47 by hallison          #+#    #+#             */
/*   Updated: 2025/09/10 01:46:19 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes_tests.h"

int test_shape_ass_material(void)
{
	t_object	s;
	t_material	m;

	s = create_test_shape();
	m = material();
	m.ambient = 1;
	s.m = m;
    if (s.m.ambient == m.ambient)
		return (0);
	return (-1);
}
