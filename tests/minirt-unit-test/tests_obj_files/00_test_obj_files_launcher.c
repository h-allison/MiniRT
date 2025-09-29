/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_obj_files_launcher.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 01:46:21 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/28 20:05:50 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_files_tests.h"
#include "libunit.h"

int	obj_files_tests_launcher(void)
{
	t_unit_test	testlist[100];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "OBJ_FILES: Ignore gibberish  ", &test_obj_files_gibberish);
	load_test(testlist, "OBJ_FILES: Vertex records  ", &test_obj_files_vertices);
	load_test(testlist, "OBJ_FILES: Parsing triangle faces  ", &test_obj_files_faces);
	ret = launch_tests(testlist);
	return (ret);
}
