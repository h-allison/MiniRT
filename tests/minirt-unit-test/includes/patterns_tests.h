/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_tests.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:16:24 by hallison          #+#    #+#             */
/*   Updated: 2025/09/21 14:30:44 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERNS_TESTS_H
# define PATTERNS_TESTS_H

# include "libunit.h"
# include "minirt.h"

int	patterns_tests_launcher(void);
int	test_pattern_basic(void);
int	test_pattern_stripe_y(void);
int	test_pattern_stripe_z(void);
int	test_pattern_stripe_x(void);
int	test_pattern_lighting(void);
int test_pattern_obj_transform(void);
int test_pattern_pat_transform(void);
int test_pattern_all_transform(void);
int	test_pattern_gen_basic(void);
int test_pattern_set_transform(void);
int test_pattern_uv_checkers(void);
int test_pattern_spherical_map(void);
int test_pattern_align_check(void);

#endif
