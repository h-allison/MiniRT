/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_test_shape_material.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:35:47 by hallison          #+#    #+#             */
/*   Updated: 2025/09/10 01:46:26 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes_tests.h"

int test_shape_material(void)
{
	t_object	s;
	t_material	m;

	s = create_test_shape();
	m = s.m;
    if (m.ambient == s.m.ambient && m.diffuse == s.m.diffuse)
		return (0);
	return (-1);
}
