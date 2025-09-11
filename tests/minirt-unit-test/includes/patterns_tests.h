/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_tests.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:16:24 by hallison          #+#    #+#             */
/*   Updated: 2025/09/11 01:30:55 by mmillhof         ###   ########.fr       */
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

#endif
