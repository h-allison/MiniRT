/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_files_tests.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:16:24 by hallison          #+#    #+#             */
/*   Updated: 2025/09/28 20:06:09 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_FILES_TESTS_H
# define OBJ_FILES_TESTS_H

# include "libunit.h"
# include "minirt.h"

int	obj_files_tests_launcher(void);
int	test_obj_files_gibberish(void);
int	test_obj_files_vertices(void);
int	test_obj_files_faces(void);

#endif
