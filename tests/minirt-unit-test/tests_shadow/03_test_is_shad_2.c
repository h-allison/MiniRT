/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_test_is_shad_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 02:49:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/23 02:49:52 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow_tests.h"
#include "libunit.h"

int test_is_shad_2(void)
{
	t_world w;
	bool	shadowed;

	w = default_world();
	shadowed = is_shadowed(&w, 0, point(10, -10, 10));
	free(w.light);
	free_matrices_and_ret(w.s[0], 0);
	free_matrices_and_ret(w.s[1], 0);
	free(w.s);
	if (shadowed)
	{
		return(0);
	}
	return(-1);
}
