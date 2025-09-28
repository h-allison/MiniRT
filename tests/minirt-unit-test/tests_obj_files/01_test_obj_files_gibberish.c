/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_obj_files_gibberish.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/28 16:34:25 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_files_tests.h"

int	test_obj_files_gibberish(void)
{
	t_parser	*parser;

	parser = parse_obj_file("tests_obj_files/01_gibberish.obj");
	if (parser->ignored != 5)
	{
		free(parser);
		return (-1);
	}
	free(parser);
	return (0);
}
