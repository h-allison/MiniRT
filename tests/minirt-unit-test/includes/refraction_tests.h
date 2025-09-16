/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_tests.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:16:24 by hallison          #+#    #+#             */
/*   Updated: 2025/09/16 17:18:01 by hallison         ###   ########.fr       */
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
int test_refract_total(void);
int test_refract_color(void);
int	test_refract_shade_hit(void);	
int	test_refract_schlick_total(void);
int	test_refract_schlick_perpendicular(void);
int	test_schlick_n2_bigger_n1(void);
int	test_shadehit_reflective_and_transparent(void);

#endif
