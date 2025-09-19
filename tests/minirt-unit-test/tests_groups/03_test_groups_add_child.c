/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_test_groups_add_child.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/19 13:18:20 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "groups_tests.h"

int test_groups_add_child(void)
{
	t_shape	g;
	t_shape	s;

	g = group();
	s = create_test_shape();
	
	add_child(&g, &s);
	if (!g.group || g.group[0] != &s || g.group[1] || s.parent != &g)
		return (-1);
	return (0);
}
