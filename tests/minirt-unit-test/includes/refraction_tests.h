/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_tests.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:16:24 by hallison          #+#    #+#             */
/*   Updated: 2025/09/15 15:45:59 by hallison         ###   ########.fr       */
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

#endif
