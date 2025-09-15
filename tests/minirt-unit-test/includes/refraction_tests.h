/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_tests.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:16:24 by hallison          #+#    #+#             */
/*   Updated: 2025/09/16 00:33:32 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFRACTION_TESTS_H
# define REFRACTION_TESTS_H

# include "libunit.h"
# include "minirt.h"
# include "libft.h"

int refract_tests_launcher(void);
int test_refract_and_transp(void);
int test_refract_glass_sphere(void);
int	test_refract_find_n1_n2(void);
int	test_refract_under_point(void);
int test_refract_color_opaque(void);
int test_refract_max_recursion(void);

#endif
