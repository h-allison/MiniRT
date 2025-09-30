/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_test_is_shad_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 02:50:26 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 23:29:56 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow_tests.h"
#include "libunit.h"

int test_is_shad_1(void)
{
	t_world *w;
	float	shadowed;

	w = default_world();
	shadowed = is_shadowed(&w, 0, point(0, 10, 0));
	free_world(w);
	if (!shadowed)
	{
		return (0);
	}
	return (-1);
}
