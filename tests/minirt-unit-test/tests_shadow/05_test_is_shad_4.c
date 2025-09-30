/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_test_is_shad_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 02:50:55 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/30 15:59:09 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow_tests.h"
#include "libunit.h"

int test_is_shad_4(void)
{
	t_world *w;
	bool	shadowed;

	w = default_world();
	shadowed = is_shadowed(w, 0, point(-2, 2, -2));
	free_world(w);
	if (!shadowed)
	{
		return (0);
	}
	return (-1);
}
