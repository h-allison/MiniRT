/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_reflective.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:03:46 by hallison          #+#    #+#             */
/*   Updated: 2025/09/13 18:26:18 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection_tests.h"

int test_reflect_basic(void)
{
	t_material	m;

	m = material();
	if (m.reflective == 0.0)
		return (0);
	return (-1);
}
