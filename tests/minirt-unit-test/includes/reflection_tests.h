/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_tests.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:16:24 by hallison          #+#    #+#             */
/*   Updated: 2025/09/13 21:46:57 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFLECTION_TESTS_H
# define REFLECTION_TESTS_H

# include "libunit.h"
# include "minirt.h"

int reflect_tests_launcher(void);
int	test_reflect_basic(void);
int test_reflect_comps(void);
int test_reflect_col_nonreflect(void);
int test_reflect_col_reflective(void);
int test_reflect_shade_hit_reflective(void);

#endif
