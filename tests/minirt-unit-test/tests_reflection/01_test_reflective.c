/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_reflective.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:02:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/25 18:42:55 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection_tests.h"

int test_reflect_basic(void)
{
	t_material	*m;

	m = material();
	if (m->reflective != 0.0)
		return (-1);
	free_material(m);
	return (0);
}
