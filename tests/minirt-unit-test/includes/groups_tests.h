/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_tests.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:44:02 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/19 12:36:24 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GROUPS_TESTS_H
# define GROUPS_TESTS_H

# include "libunit.h"
# include "minirt.h"
# include "libft.h"

int groups_tests_launcher(void);
int test_groups_basic(void);
int test_groups_has_parent(void);
int test_groups_add_child(void);
int test_groups_intersect(void);

#endif
